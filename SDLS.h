#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
using namespace std;
void init(SDL_Window* &win, SDL_Renderer* &rer, int sizeX, int sizeY);
void deinit(SDL_Window* win, SDL_Renderer* rer);
void gameovr(vector<SDL_Texture*> Textures, bool& stop, SDL_Renderer*& rer, SDL_Rect boardRect);
