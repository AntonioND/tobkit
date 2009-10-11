/*******************
DS Tracker GUI Class

Contains the widgets
Gets pen/key events
Calls touched widget
********************/

#ifndef GUI_H
#define GUI_H

#include <nds.h>

#include <tobkit/constants.h>
#include <tobkit/theme.h>
#include <tobkit/widget.h>
#include <tobkit/widgetmanager.h>

#include <vector>


namespace TobKit
{

class Widget;

/**
 * \brief This is the user interface class that manages widgets and input and deals with the DS graphics hardware.
 */
class GUI: public WidgetManager
{
	friend class Widget;
	friend class WidgetManager;

	public:
	    // This class is a doubleton(TM)
	    static GUI* instance(Screen screen);
	    static GUI* init(Screen screen, Theme *theme, bool double_buffer=false, u16 *vram=NULL);
	    static GUI* init(Screen screen, bool double_buffer=false, u16 *vram=NULL);

		virtual ~GUI();

		/**
		 * Sets up a text console that you can output text to using printf.
		 *
		 * <b>Interoperability note:</b> This function allocates the highest available text background
		 * of the screen and sets it to mode BgType_Text4bpp with size BgSize_T_256x256.
		 *
		 * \param color the text color in RGB15 format.
		 * \return true on success, false on failure.
		 */
		bool setupConsole(u16 color=RGB15(0,29,4));

        /**
         * Allocates a tile background to be used for tile-based graphics. It is
         * used internally by some widgets like the keyboard that depend on tiles.
         * You only need this function if you want to implement a tile-based widget.
         *
         * <b>Interoperability note:</b> This function allocates the highest available text background
         * of the screen and sets it to mode BgType_Text4bpp with size BgSize_T_256x256.
         *
         * \param widget a pointer to the widget that requests the tile BG
         * \param screen the screen that the tile background will be created for
         * \param tileset_size the size of the tile set in bytes
         * \param tile_ram will be filled with a pointer to the tile memory (pass a reference to a pointer)
         * \param map_size the size of the map in bytes
         * \param map_ram will be filled with a pointer to the map memory (pass a reference to a pointer)
         * \param layer will be filled with the index of the assigned background layer if passed and not NULL.
         * \param handle will be filled with the handle of the assigned background layer if passed and not NULL. The handle can be
         *   used to set background attributes with libnds functions like bgSetScroll etc.
         * \return True on success, false on failure.
         */
        bool addTileBackground(Widget* widget, int tileset_size, u16 **tile_ram,
                int map_size, u16 **map_ram, int *layer=NULL, int *handle=NULL);

        void delTileBackground(Widget *widget);

        /**
         * Allocate a 16-color palette.
         * If you are drawing palette-based graphics on a screen whereTobKit is active,
         * please use this to function to the get palette pointer, so TobKit knows that you are using a palette.
         * \param screen the screen that the palette will be allocated for
         * \param palette will be filled with a pointer to the palette memory (pass a reference to a pointer)
         * \param palette_index the index of the palette to be used in the map
         */
        void addPalette(u16 **palette, int *palette_index);

        /**
         * Delete a palette.
         * \param screen the screen that the palette will be deleted from
         * \param palette_index the index of the palette that shall be deleted.
         */
        void delPalette(int palette_index);

        /**
         * Gets the amount of free VRAM for a screen. VRAM is allocated from back to front, i.e. the value returned is
         * the amount of continuously available RAM at the beginning of VRAM. Use this function if you want to use some
         * of the VRAM for yourself to check if there is enough free VRAM available. It is recommended that you allocate
         * VRAM using addTileBackground(), so TobKit can keep track of the free VRAM and won't overwrite your stuff.
         * \param screen the screen that you want to know the amount free VRAM form.
         * \return the free VRAM in kilobytes.
         */
        u32 getFreeVramKB();

		// Swap buffers when in double-buffering mode
            void swapBuffers(void);

	private:
	    static GUI *instance_main, *instance_sub;

	    static const int N_AVAILABLE_TEXT_BGS_MAIN = 2;
	    static const int N_AVAILABLE_TEXT_BGS_SUB = 2;

		std::vector<Widget*> _tile_widgets; // Keep track of widgets using tile BGs

		Screen _screen;

		u16 *_vram_front, *_vram; // in double-buffered mode, _vram is the backbuffer

		int _free_vram; // given in kb. Memory is allocated from behind.
		int _tile_ram; // given in kb. Total memory that is not used by bmp backgrounds.
		bool _double_buffering;
		u8 _active_buffer; // Actve buffer for double buffering
		int _free_palettes;
		int _free_text_bgs; // Keep track of how many text backgrounds are used. In Mode 5, there are two.
		u16 _flag_used_palettes; // Keep track of used palettes

		// hardware video layers
		int _bmp_bg;

		/**
         * The default constructor. In 99.9% of situations you use this constructor
         * to create a GUI.
         */
        GUI(Screen screen, bool double_buffer=false, u16 *vram=NULL);

        /**
         * The custom consructor that lets you specify stuff yourself.
         * Situations in which you might want to use this one:
         * - You create a custom Widget with some sub-widgets.
         * - You want to manage VRAM yourself.
         * \param theme the color thema for all Widgets in this GUI
         * \param the background color (needed for semi-transparent Widgets)
         * \param main_vram a pointer to the DS's main VRAM
         * \param sub_vram a pointer to the DS's sub VRAM
         */
        GUI(Screen screen, Theme *theme, bool double_buffer=false, u16 *vram=NULL);

		void setup();

		/**
		 * Sets up the display.
		 *
		 * <b>Interoperability note:</b> If it's a main screen GUI, this function allocates VRAM banks A to 0x06000000
		 * and vram bank B to 0x06020000, sets the
		 * video engine to MODE_3_2D and uses background layer 3 in 16 bit bitmap mode.
		 * If it's a sub screen GUI, this function allocates VRAM bank C to 0x06200000,
		 * sets the video engine to MODE_5_2D and uses background layer 2 in 16 bit bitmap mode.
		 *
		 * \param double_buffer enables double-buffering. This is only available on the
		 * main screen. You only need this if you're
		 * doing animations or stuff that renders slowly. To use double-buffering, call
		 * draw() before the vblank and swapBuffers() after the vblank.
		 */

		void setupVideo(bool double_buffer=false);

		void clearScreen();

};

};

#endif
