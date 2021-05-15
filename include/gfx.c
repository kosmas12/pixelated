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

#include "gfx.h"
#include "core.h"
#include "files.h"

void drawTexCoordsAlpha(SDL_Texture *texture, int alpha, SDL_Rect coords) {
    SDL_SetTextureAlphaMod(texture, alpha);
    if (coords.x == 0 &&
        coords.y == 0 &&
        coords.w == 0 &&
        coords.h == 0) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }
    SDL_RenderCopy(renderer, texture, NULL, &coords);
}

SDL_Texture *genWelcomeTex() {
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *welcome = TTF_RenderUTF8_Blended(mediumFont, "Welcome to", color);
    if (!welcome) {
        printf("Couldn't draw welcome text: %s", SDL_GetError());
        return NULL;
    }
    SDL_Texture *welcomeTexture = SDL_CreateTextureFromSurface(renderer, welcome);
    if (!welcomeTexture) {
        printf("Couldn't create welcome texture: %s", SDL_GetError());
        return NULL;
    }

    return welcomeTexture;
}

SDL_Texture *genNameTex() {
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *pixelated = TTF_RenderUTF8_Blended(bigFont, "Pixelated", color);
    if (!pixelated) {
        printf("Couldn't draw name text: %s", SDL_GetError());
        return NULL;
    }

    SDL_Texture *pixelatedTexture = SDL_CreateTextureFromSurface(renderer, pixelated);
    if (!pixelatedTexture) {
        printf("Couldn't create name texture: %s", SDL_GetError());
        return NULL;
    }

    return pixelatedTexture;
}

SDL_Texture *genCopyrightTex() {
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *copyright = TTF_RenderUTF8_Blended_Wrapped(mediumFont,
                                                            "Copyright (C) 2021 Kosmas Raptis. "
                                                            "Licensed under the GNU General Public License Version 2",
                                                            color, 550);
    if (!copyright) {
        printf("Couldn't create copyright surface: %s", SDL_GetError());
        return NULL;
    }

    SDL_Texture *copyrightTexture = SDL_CreateTextureFromSurface(renderer, copyright);
    if (!copyrightTexture) {
        printf("Couldn't create copyright texture: %s", SDL_GetError());
        return NULL;
    }

    return copyrightTexture;
}

void displayStartupText() {
    SDL_Rect welcomeCoords = {225, 70, 260, 60};
    SDL_Texture *welcomeTex = genWelcomeTex();
    if (!welcomeTex) {
        Quit();
    }

    SDL_Rect nameCoords = {90, 120, 500, 150};
    SDL_Texture *nameTex = genNameTex();
    if (!nameTex) {
        SDL_DestroyTexture(welcomeTex);
        Quit();
    }

    SDL_Rect copyrightCoords = {10, 280, 550, 200};
    SDL_Texture *copyrightTex = genCopyrightTex();
    if (!copyrightTex) {
        SDL_DestroyTexture(welcomeTex);
        SDL_DestroyTexture(nameTex);
        Quit();
    }

    for (int i = 0; i < 255; i += 5) {
        SDL_RenderFillRect(renderer, NULL);
        drawTexCoordsAlpha(welcomeTex, i, welcomeCoords);
        drawTexCoordsAlpha(nameTex, i, nameCoords);
        drawTexCoordsAlpha(copyrightTex, i, copyrightCoords);
        SDL_RenderPresent(renderer);
    }

    SDL_Delay(3000);

    for (int i = 255; i >= 0; i -= 5) {
        SDL_RenderFillRect(renderer, NULL);
        drawTexCoordsAlpha(welcomeTex, i, welcomeCoords);
        drawTexCoordsAlpha(nameTex, i, nameCoords);
        drawTexCoordsAlpha(copyrightTex, i, copyrightCoords);
        SDL_RenderPresent(renderer);
    }
}

void drawDirListing() {
    SDL_Rect curCoords;
    curCoords.x = 0;
    curCoords.y = 0;

    SDL_Color textColor = {255, 255, 255, 255};

    int i = 0;

    SDL_Surface *file;
    SDL_Texture *fileTex;


    while (files[i] != NULL) {
        file = TTF_RenderUTF8_Blended(smallFont, files[i], textColor);
        curCoords.w = file->w;
        curCoords.h = file->h;
        fileTex = SDL_CreateTextureFromSurface(renderer, file);
        SDL_FreeSurface(file);
        SDL_RenderCopy(renderer, fileTex, NULL, &curCoords);
        SDL_DestroyTexture(fileTex);
        curCoords.y += 35;
        ++i;
    }

    SDL_RenderPresent(renderer);

}
