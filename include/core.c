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

#include "core.h"

int initLibs() {
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

    if (TTF_Init() > 0) {
        printf("Could not initialize SDL_ttf: %s", TTF_GetError());
        return 0;
    }

    return 1;
}

void initGC() {
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            controller = SDL_GameControllerOpen(i);
            printf("Opened controller %s at port %d\n", SDL_GameControllerName(controller), i);
        }
    }
}

int initWindow() {
    window = SDL_CreateWindow("Pixelated",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              720,
                              480,
                              SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Couldn't create window: %s", SDL_GetError());
        return 0;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        printf("Couldn't create renderer: %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderPresent(renderer);

    return 1;
}

int initText() {
    bigFont = TTF_OpenFont(HOME"resources"SEPARATOR"Raleway.ttf", 90);
    if (!bigFont) {
        printf("Couldn't load big font: %s", TTF_GetError());
        return 0;
    }

    mediumFont = TTF_OpenFont(HOME"resources"SEPARATOR"Raleway.ttf", 40);
    if (!mediumFont) {
        printf("Couldn't load medium font: %s", TTF_GetError());
        return 0;
    }

    smallFont = TTF_OpenFont(HOME"resources"SEPARATOR"Raleway.ttf", 16);
    if (!smallFont) {
        printf("Couldn't load small font: %s", TTF_GetError());
        return 0;
    }

    return 1;
}

int checkIfQuit() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 1;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return 1;
                    default:
                        break;
                }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                switch (event.cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_X:
                        return 1;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}

void Quit() {
    SDL_DestroyWindow(window);
    TTF_CloseFont(bigFont);
    TTF_Quit();
    IMG_Quit();
    SDL_GameControllerClose(controller);
    SDL_Quit();
#if !defined(NXDK)
    exit(0);
#else
    printf("Rebooting...");
    XReboot();
#endif
}

int Init() {
#if defined(NXDK)
    XVideoSetMode(720, 480, 32, REFRESH_DEFAULT);
#endif
    printf("Welcome to Pixelated! Initializing...\n");

    if (!initLibs()) {
        return 0;
    }

    initGC();

    if (!initWindow()) {
        return 0;
    }

    if (!initText()) {
        return 0;
    }

    return 1;
}
