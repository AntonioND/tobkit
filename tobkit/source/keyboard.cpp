/*
 * TobKit - A simple user interface toolkit for Nintendo DS homebrew
 *                   Copyright 2005-2009 Tobias Weyand (me@tobw.net)
 *                                   http://code.google.com/p/tobkit
 *
 * TobKit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * TobKit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with TobKit.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>

#include "tobkit/keyboard.h"

#include "tobkit/keyboard.raw.h"
#include "tobkit/keyboard.pal.h"
#include "tobkit/keyboard.map.h"
#include "tobkit/keyb_hit.h"
#include "tobkit/gui.h"

namespace TobKit
{

u8 halftones[] = {1, 3, 6, 8, 10, 13, 15, 18, 20, 22};
u8 x_offsets[] = {0, 11, 16, 27, 32, 48, 59, 64, 75, 80, 91, 96};

/* ===================== PUBLIC ===================== */

Keyboard::Keyboard(WidgetManager *owner, int x, int y, bool visible)
    :Widget(x, y, 224, 40, owner, 0, visible),
    _key_labels_visible(false)
{
    setupPalette();
    setupTileBg();

    memset(_key_labels, ' ', 24);

    pleaseDraw();
}

Keyboard::~Keyboard() {
    _gui->delTileBackground(this);
    _gui->delPalette(_palette_normal_index);
    _gui->delPalette(_palette_fullnotehighlight_index);
    _gui->delPalette(_palette_halfnotehighlight_index);
}

void Keyboard::setupPalette(void)
{
    // Allocate 3 palettes and the char and tile maps
    u16 *palette_normal, *palette_fullnotehighlight, *palette_halfnotehighlight;
    _gui->addPalette(&palette_normal, &_palette_normal_index);
    _gui->addPalette(&palette_fullnotehighlight, &_palette_fullnotehighlight_index);
    _gui->addPalette(&palette_halfnotehighlight, &_palette_halfnotehighlight_index);

    dmaCopy(keyboard_Palette, palette_normal, 32);
    dmaCopy(keyboard_fullnotehighlight_Palette, palette_fullnotehighlight, 32);
    dmaCopy(keyboard_halfnotehighlight_Palette, palette_halfnotehighlight, 32);
}

void Keyboard::setupTileBg(void)
{
    _gui->addTileBackground(this, 736, &_char_base, 140, &_map_base);
    dmaCopy((uint16_t*)keyboard_Tiles, _char_base, 736);
}


// Event calls
void Keyboard::penDown(int x, int y)
{
    // Look up the note in the hit-array
    u8 kbx, kby;
    kbx = (x - _x)/8;
    kby = (y - _y)/8;

    u8 note = keyb_hit[kby][kbx];
    setKeyPal(note);
    signal_note(note);
    _curr_note = note;
}

void Keyboard::penUp(int x, int y)
{
    resetPals();
    signal_release(_curr_note);
}

// Key label handling
void Keyboard::showKeyLabels(void)
{
    _key_labels_visible = true;

    for (u8 key = 0; key < 24; ++key) {
        drawKeyLabel(key);
    }
}

void Keyboard::hideKeyLabels(void)
{
    _key_labels_visible = false;

    for (u8 key = 0; key < 24; ++key) {
        eraseKeyLabel(key);
    }
}

void Keyboard::setKeyLabel(u8 key, char label)
{
    eraseKeyLabel(key);
    _key_labels[key] = label;
    drawKeyLabel(key);
}

/* ===================== PRIVATE ===================== */

void Keyboard::draw(void)
{
    // Fill screen with empty tiles
    for(int i=0;i<768;++i) _map_base[i] = 0;

    // Copy the keyboard to the screen
    for(int py=0; py<5; ++py) {
        for(int px=0; px<28; ++px) {
            _map_base[32*(py+_y/8)+(px+_x/8)] = keyboard_Map[29*py+px+1];
        }
    }
}

// Set the key corresp. to note to palette corresp. to pal_idx
void Keyboard::setKeyPal(u8 note)
{
  u8 hit_row, pal_idx;

  if(isHalfTone(note)) {
    hit_row = 0;
    pal_idx = _palette_halfnotehighlight_index;
  } else {
    hit_row = 4;
    pal_idx = _palette_fullnotehighlight_index;
  }

  for(int px=0; px<28; ++px) {
    if(keyb_hit[hit_row][px] == note) {
      for(int py=0; py<5; ++py) {
        _map_base[32*(py+_y/8)+(px+_x/8)] &= ~(3 << 12); // Clear bits 12 and 13 (from the left)
        _map_base[32*(py+_y/8)+(px+_x/8)] |= (pal_idx << 12); // Write the pal index to bits 12 and 13
      }
    }
  }
}

// 1 for halftones, 0 for fulltones
bool Keyboard::isHalfTone(u8 note)
{
    for(int i=0;i<10;++i) {
        if(note==halftones[i]) return 1;
    }
    return 0;
}

// Reset keyboard colors to normal
void Keyboard::resetPals(void)
{
  for(int px=0; px<28; ++px) {
    for(int py=0; py<5; ++py) {
      _map_base[32*(py+_y/8)+(px+_x/8)] &= ~(3 << 12); // Clear bits 12 and 13 (from the left)
    }
  }
}

void Keyboard::drawKeyLabel(u8 key, bool visible)
{
    u8 xpos, ypos, offset;
    u16 col;

    if(isHalfTone(key))	{
        ypos = 12;
        col = RGB15(31, 31, 31);
        offset = 3;
    } else {
        ypos = 28;
        col = RGB15(0, 0, 0);
        offset = 5;
    }

    if(visible) {
        col |= BIT(15);
    }

    xpos = offset + x_offsets[key % 12];

    if(key > 11) {
        xpos += 111;
    }

    char label[] = {_key_labels[key], 0};

    drawString(label, xpos, ypos, 255, col);
}

void Keyboard::eraseKeyLabel(u8 key)
{
    drawKeyLabel(key, false);
}

};
