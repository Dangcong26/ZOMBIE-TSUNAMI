#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
 
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
 
// Screen
const int SCREEN_WIDTH = 1280; 
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

struct Map{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

    //int** tile;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	// char* file_name_;
    //Map() {
    //    tile = new int* [MAX_MAP_Y];
    //    for (int i = 0; i < MAX_MAP_Y; i++) {
    //        tile[i] = new int[MAX_MAP_X] {0}; // Kh?i t?o t?t c? ph?n t? v? 0
    //    }
    //}

    //~Map() {
    //    if (tile) {
    //        for (int i = 0; i < MAX_MAP_Y; i++) {
    //            delete[] tile[i];
    //        }
    //        delete[] tile;
    //    }
    //}
};

#endif