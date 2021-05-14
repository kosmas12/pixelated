/*
This file is part of Pixelated - a cross platform image viewer
Copyright (C) 2021 Kosmas Raptis

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef PIXELATED_GFX_H
#define PIXELATED_GFX_H

#if !defined(NXDK)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

void drawTexCoordsAlpha(SDL_Texture *texture, int alpha, SDL_Rect coords);
SDL_Texture *genWelcomeTex();
SDL_Texture *genNameTex();
SDL_Texture *genCopyrightTex();
void displayStartupText();

#endif //PIXELATED_GFX_H
