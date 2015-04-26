#include "TileMap.h"
#include "Main_Game.h"


TileMap::TileMap()
{
	this->dim_x = 12; // dim_x -szerokosc
	this->dim_y = 20; // dim_y - wysokosc
	map_create();
	map_prepare();

	cubet.loadFromFile("asset_cube50.png");
	cube.setTexture(cubet);
}
int TileMap::getdim_x()		{ return dim_x;	}
int TileMap::getdim_y()		{ return dim_y; }

int *** TileMap::getmap()	{ return map;	}

void TileMap::map_create()
{
	map = new int**[this->dim_x];
	for (int x = 0; x < this->dim_x; ++x) 
	{
		*(map + x) = new int*[this->dim_y];
		for (int y = 0; y < this->dim_y; ++y) 
		{
				*(*(map + x) + y) = new int[4];
		}
	}
}

void TileMap::map_prepare()
{
	for (int x = 0; x < this->dim_x; x++)
	{
		for (int y = 0; y < this->dim_y; y++)
		{
			this->map[x][y][0] =  0; //availability status layer
			this->map[x][y][1] = -1; //history layer
			this->map[x][y][2] = -1; //colour hue ID layer
			this->map[x][y][3] =  0; //parent shape array identificator
		}
	}
}
