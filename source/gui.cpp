#include <tobkit/gui.h>

#include <algorithm>

/* ===================== PUBLIC ===================== */

namespace TobKit
{

GUI* GUI::instance(Screen screen)
{
    if(screen == MAIN_SCREEN) {
        if(instance_main == NULL) {
            instance_main = new GUI(screen);
        }
        return instance_main;
    } else {
        if(instance_sub == NULL) {
            instance_sub = new GUI(screen);
        }
        return instance_sub;
    }
}

GUI* GUI::init(Screen screen, Theme *theme, bool double_buffer, u16 *vram)
{
    if(screen == MAIN_SCREEN) {
        if(instance_main == NULL) {
            if(theme == NULL) {
                theme = new Theme();
            }
            instance_main = new GUI(screen, theme, double_buffer, vram);
        }
        return instance_main;
    } else {
        if(theme == NULL) {
            theme = new Theme();
        }
        if(instance_sub == NULL) {
            instance_sub = new GUI(screen, theme, double_buffer, vram);
        }
        return instance_sub;
    }
}

GUI* GUI::init(Screen screen, bool double_buffer, u16 *vram)
{
    return init(screen, NULL, double_buffer, vram);
}

GUI::~GUI()
{

}

bool GUI::setupConsole(u16 color)
{
	if(_screen == MAIN_SCREEN) {
		// Enable Text background
	    if(_free_text_bgs == 0) {
	        return false;
	    }
	    int bg = _free_text_bgs - 1;
	    _free_text_bgs--;
		videoBgEnable(bg);

		// Set tile and map bases. The libnds default font is 8kb, and the tile map takes 2kb
		int map_base = _free_vram / 2 - 2;
		int tile_base = _free_vram / 16 - 1;
		_free_vram = tile_base * 16;

		PrintConsole *pc = consoleInit(NULL, bg, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base, true, true);
		bgSetPriority(pc->bgId, 1);
		BG_PALETTE[255] = color;
	} else {
		// Enable Text background
	    if(_free_text_bgs == 0) {
            return false;
        }
        int bg = _free_text_bgs - 1;
        _free_text_bgs--;
	    videoBgEnableSub(bg);

		// Set tile and map bases. The libnds default font is 8kb, and the tile map takes 2kb
		int map_base = _free_vram / 2 - 2;
		int tile_base = _free_vram / 16 - 1;
		_free_vram = tile_base * 16;

		PrintConsole *pc = consoleInit(NULL, bg, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base, false, true);
		bgSetPriority(pc->bgId, 1);
		BG_PALETTE_SUB[255] = color;
	}

	return true;
}


void GUI::swapBuffers(void)
{
	if(!_double_buffering) return;

	u16 *tmp = _vram_front;
	_vram_front = _vram; _vram = tmp;

	_active_buffer = 1 - _active_buffer;
	if(_active_buffer == 1) {
	    bgSetMapBase(_bmp_bg, 4);
	} else {
	    bgSetMapBase(_bmp_bg, 10);
	}
}



void GUI::addPalette(u16 **palette, int *palette_index)
{
    if ((_screen == MAIN_SCREEN) && (_free_palettes > 0)) {
        int idx = -1;
        bool found = false;
        while (idx < 15 && found == false) {
            idx++;
            if ((_flag_used_palettes & (1 << idx)) == 0) {
                found = true;
            }
        }
        *palette_index = idx;
        *palette = BG_PALETTE + 16 * (*palette_index);
        _flag_used_palettes |= 1 << (*palette_index);
        _free_palettes--;
    } else if ((_screen == SUB_SCREEN) && (_free_palettes > 0)) {
        int idx = -1;
        bool found = false;
        while (idx < 15 && found == false) {
            idx++;
            if ((_flag_used_palettes & (1 << idx)) == 0) {
                found = true;
            }
        }
        *palette_index = idx;
        *palette = BG_PALETTE_SUB + 16 * (*palette_index);
        _flag_used_palettes |= 1 << (*palette_index);
        _free_palettes--;
    } else {
        *palette_index = -1;
    }
}

void GUI::delPalette(int palette_index)
{
    if(_screen == MAIN_SCREEN) {
        _flag_used_palettes &= ~(1<<palette_index);
        _free_palettes++;
    } else {
        _flag_used_palettes &= ~(1<<palette_index);
        _free_palettes++;
    }
}

bool GUI::addTileBackground(Widget* widget, int tileset_size, u16 **tile_ram,
        int map_size, u16 **map_ram, int *layer, int *handle)
{
    // VRAM is allocated from back to front. We try to put the map behind the tiles.
    // A tile base is 16kb, so the last tile base occupied by the tile set must have at least
    // the size of the map free.
    int map_size_kb = ( (map_size - 1) / 1024) + 1;
    int tileset_size_kb = ( (tileset_size - 1) / 1024) + 1;
    int map_size_bases = ((map_size_kb - 1) / 2) + 1;
    int tile_size_bases = ((tileset_size_kb - 1) / 16) + 1;
    int last_tilebase_free_ram_kb = tile_size_bases * 16 - tileset_size_kb;
    bool map_behind_tiles;
    int required_vram_kb;
    if(last_tilebase_free_ram_kb >= map_size_bases * 2) {
        map_behind_tiles = true;
        required_vram_kb = tile_size_bases * 16;
    } else {
        map_behind_tiles = false;
        required_vram_kb = tile_size_bases * 16 + map_size_bases * 2;
    }

    //
    // Check Requirements
    //
    if(_free_vram < required_vram_kb) {
        return false;
    }
    if(_free_text_bgs == 0) {
        return false;
    }

    //
    // Alloc VRAM
    //
    int tile_base = _free_vram / 16 - tile_size_bases;
    int map_base;
    if(map_behind_tiles) {
        map_base = (tile_base * 16 + tileset_size_kb + 1) / 2;
    } else {
        map_base = (tile_base * 16 - map_size_kb) / 2;
    }
    _free_vram -= required_vram_kb;

    //iprintf("alloc: map: %d tile: %d free: %d\n");

    //
    // Setup background
    //
    int bg = _free_text_bgs - 1;
    _free_text_bgs--;
    int bgh;
    if(_screen == MAIN_SCREEN) {
        videoBgEnable(bg);
        bgh = bgInit(bg, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base);

    } else {
        videoBgEnableSub(bg);
        bgh = bgInitSub(bg, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base);
    }

    *tile_ram = (u16*)bgGetGfxPtr(bgh);
    *map_ram = (u16*)bgGetMapPtr(bgh);
    bgSetScroll(bgh, 0, 0);
    bgUpdate();
    if(layer != NULL) {
        *layer = bg;
    }
    if(handle != NULL) {
        *handle = bgh;
    }
    _tile_widgets.push_back(widget);

    return true;
}

void GUI::delTileBackground(Widget *widget)
{
    // Free the background associated with the widget (if there is one)
    std::vector<Widget*>::iterator w_it = std::find(_tile_widgets.begin(), _tile_widgets.end(), widget);
    if (w_it != _tile_widgets.end()) {
        _tile_widgets.erase(w_it);
        _free_vram = _tile_ram;
        if(_screen == MAIN_SCREEN) {
            _free_text_bgs = N_AVAILABLE_TEXT_BGS_MAIN;
            videoBgDisable(0);
            videoBgDisable(1);
        } else {
            _free_text_bgs = N_AVAILABLE_TEXT_BGS_SUB;
            videoBgDisableSub(0);
            videoBgDisableSub(1);
        }
        std::vector<Widget*> tile_widgets_tmp = _tile_widgets;
        _tile_widgets.clear();
        for (uint i = 0; i < tile_widgets_tmp.size(); ++i) {
            tile_widgets_tmp[i]->setupTileBg();
            tile_widgets_tmp[i]->pleaseDraw();
        }
    }
}

/* ===================== PRIVATE ===================== */

GUI* GUI::instance_main = 0;
GUI* GUI::instance_sub = 0;

GUI::GUI(Screen screen, bool double_buffer, u16 *vram)
    :WidgetManager(screen, this, Theme()),
    _screen(screen), _vram(vram)
{
    _gui = this;
    setup();
    setupVideo(double_buffer);
}

GUI::GUI(Screen screen, Theme *theme, bool double_buffer, u16 *vram)
    :WidgetManager(screen, this, Theme(*theme)),
    _screen(screen), _vram(vram)
{
    setup();
    setupVideo(double_buffer);
}

void GUI::setup()
{
    _double_buffering = false;
    _active_buffer = 1;
    _free_palettes = 16;
    if(_screen == MAIN_SCREEN) {
        _free_text_bgs = N_AVAILABLE_TEXT_BGS_MAIN;
    } else {
        _free_text_bgs = N_AVAILABLE_TEXT_BGS_SUB;
    }
    _flag_used_palettes = 0;

    for(u8 i=0;i<14;++i) {
        _shortcuts.push_back(0);
    }
}

void GUI::setupVideo(bool double_buffer)
{
    // Double-buffering works only on the main screen
    if( (double_buffer == true) && (_screen == SUB_SCREEN) ) {
        return;
    }
    _double_buffering = double_buffer;

    if(_screen == MAIN_SCREEN)
    {
        // Video Mode
        videoSetMode(MODE_3_2D);

        // VRAM
        vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
        if(double_buffer) {
            vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
        }

        // Map the bitmap screens to the end of VRAM, so the beginning is free for tile and map data

        // When using double buffering, we have 2*128kb = 256kb of free VRAM using banks A and B.
        // We need 2*96=192KB of it, leaving 64kb free.
        // One BMP base equals 16KB. So, our BMP base is 64/16=4.
        // When using single buffering, we have 128kb VRAM using bank A.
        // We need 96KB of 128kb, leaving 32kb free.
        // One BMP base equals 16KB. So, our BMP base is 32/16=2.

        int bmp_base;
        if(double_buffer) {
            bmp_base = 4;
            _free_vram = _tile_ram = 64;
        } else {
            bmp_base = 2;
            _free_vram = _tile_ram = 32;
        }

        // Background layer 2 setup
        _bmp_bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, bmp_base, 0);
        bgSetPriority(_bmp_bg, 2);

        // Set VRAM pointers
        if(double_buffer) {
            _vram_front = (u16*)BG_BMP_RAM(bmp_base);
            _vram = (u16*)BG_BMP_RAM(bmp_base+6);
        } else {
            _vram = (u16*)BG_BMP_RAM(bmp_base);
        }

        // Fill VRAM
        u16 col = _theme->col_bg;
        u32 colcol = col | col << 16;

        swiFastCopy(&colcol, _vram, 192*256/2 | COPY_MODE_FILL);

        if(double_buffer) {
            swiFastCopy(&colcol, _vram_front, 192*256/2 | COPY_MODE_FILL);
        }
    } else if(_screen == SUB_SCREEN) {
        // Video Mode
        videoSetModeSub(MODE_5_2D);

        // VRAM
        vramSetBankC(VRAM_C_SUB_BG_0x06200000);

        // Background layer 2 setup
        int sub_bg2 = bgInitSub(2, BgType_Bmp16, BgSize_B16_256x256, 2, 0);
        bgSetPriority(sub_bg2, 2);

        // Set VRAM pointer
        _vram = (u16*)BG_BMP_RAM_SUB(2);

        // Fill VRAM
        u16 col = _theme->col_bg;
        u32 colcol = col | col << 16;
        swiFastCopy(&colcol, _vram, 192*256/2 | COPY_MODE_FILL);

        _free_vram = _tile_ram = 32;
    }
}

void GUI::clearScreen()
{
    u32 colcol = _theme->col_bg | _theme->col_bg << 16;
    dmaFillWords(colcol, _vram, 256*192*2);
}

};
