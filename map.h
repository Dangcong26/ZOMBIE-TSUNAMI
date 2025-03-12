#include "include.h"
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include"include.h"
#include"Base.h"

#define MAX_TILES 20

class TileMat : public Base {
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};

#endif