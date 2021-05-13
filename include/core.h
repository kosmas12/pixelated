//
// Created by kosmas on 13/5/21.
//

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
