
#ifndef MAP_H_
#define MAP_H_

#include "include.h"
#include"Base.h"

#define MAX_TILES 20

class TileMat : public Base {
public:
	TileMat() {  }
	~TileMat() {  }
};

class GameMap {
public:
	//GameMap();
	//~GameMap();

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const {
		return game_map_;
	}
	void SetMap(Map& map_data) {
		game_map_ = map_data;
	}

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};

#endif