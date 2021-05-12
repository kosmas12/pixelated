/*
Pixelated - a cross platform image viewer
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

#include <stdio.h>
#if !defined(NXDK)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <hal/debug.h>
#include <hal/video.h>
#include <SDL.h>
#include <SDL_image.h>
#define printf(...) debugPrint(__VA_ARGS__)
#endif
int Init() {

#if defined(NXDK)
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
#endif

    printf("Welcome to Pixelated! Initializing...");

    int sdlflags = SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_GAMECONTROLLER;

    if (SDL_Init(sdlflags) > 0) {
        printf("Could not initialize SDL: %s", SDL_GetError());
        return 0;
    }


#if defined (NXDK)
    int imgflags = IMG_INIT_JPG|IMG_INIT_PNG;
#else
    int imgflags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP;
#endif

    if (IMG_Init(imgflags) != imgflags) {
        printf("Could not initialize SDL_image: %s", IMG_GetError());
        SDL_Quit();
        return 0;
    }
    return 1;
}

int main() {

    if (!Init()) {
        exit(1);
    }

    return 0;
}
