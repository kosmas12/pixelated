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

#ifndef PIXELATED_CORE_H
#define PIXELATED_CORE_H

#include <stdio.h>
#if !defined(NXDK)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define HOME "./"
#define SEPARATOR "/"
#else
#include <hal/xbox.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define HOME "D:\\"
#define SEPARATOR "\\"
#define printf(...) debugPrint(__VA_ARGS__)
#endif

SDL_Window *window;
SDL_Renderer *renderer;
SDL_GameController *controller;
SDL_Event event;
TTF_Font *bigFont;
TTF_Font *mediumFont;
TTF_Font *smallFont;

int initLibs();
void initGC();
int initWindow();
int initText();
int checkIfQuit();
void Quit();
int Init();

#endif //PIXELATED_CORE_H
