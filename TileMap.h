#pragma once
#include "Asset.h"
class TileMap : public Asset
{
public:
	//friend class Main_Game;
						TileMap();
	int					getdim_x();
	int					getdim_y();
	int***				getmap();

//	int					map[10][8][3];
						//10 x szerokosc
						//8 y wysokosc
					//aktualnie :: x:10, y:13
private:
	sf::Texture			cubet;
	sf::Sprite			cube;
	int					***map;
	void				map_create();
	void				map_prepare();
	int					dim_x, dim_y;

};

