#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.h"
#include "Brick.h"
#include "Asset.h"
#include "Coord.h"
#include "Main_Menu.h"
#include "Animation.h"
#include "GameOver.h"
#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "sfml-audio.lib")
#endif // SFML_STATIC
class Main_Game
{
		friend		class Asset;
		friend		class Brick;

#pragma region	//	CORE GAME MECHANICS METHODS	 // 

		public:
							Main_Game(sf::RenderWindow&);			// constr
							Main_Game(int, sf::RenderWindow&);		// constr
			virtual			~Main_Game();			// destr
			void			start();				// main game loop
		
		private:
			void			events_handler();		// handling user input
			void			update();				// updating game logic
			void			render();				// handling on-screen rendering
			void			drawmap();				// NEW: Drawing Tetris Array
			
#pragma endregion 


#pragma region //	ADDITIONAL BUILT-IN-CLASS METHODS	//

			#define			place1ix		placementof_1[i].x
			#define			place1iy		placementof_1[i].y
			#define			bt				bricktype
			#define			br				brickrotation

		private:
			void			sprite_injector();		// gathering and injecting textures into game
			void			draw();
			void			move(int, int);
			void			shapeinsert();
			void			gravity();
		 std::vector<Coord> seek1();
			bool			collisiondetection();
		 std::vector<int>   linedetection();
			bool			line_delete(std::vector<int>);
			bool			all_lock();
			bool			isValid(int, int);
			void			test();
			bool			seekorigin();
			void			rotateR();
			void			quickshapeinsert(Coord, int, int);
			void			levelupdate();

#pragma endregion


#pragma region //	ADDITIONAL BUILT-IN-CLASS ASSETS	//

	private:
			//################################################
			sf::Texture		tex[13];
			sf::Sprite		spr[13];
			sf::Sprite		anim[4];

			#define s0	this->asset_sprites[0]
			#define s1	this->asset_sprites[1]
			#define s2	this->asset_sprites[2]
			std::vector<sf::Texture> asset_textures;
			std::vector<sf::Sprite> asset_sprites;
			//################################################

			std::vector<Brick> bricks;
			

			//################################################
			int				actual_weight;
			TileMap			tilemap;
		sf::RenderWindow&	render_win;
			Brick			*creationpointer;
		std::vector<Brick>  brickarray;
			Brick			brickactual;
			Brick			bricknext;
			Coord			brickorigin;	

			int				bricktype;		
			int				brickrotation;
			int				mode;
			//################################################

			std::vector<Coord> placementof_1;
			std::vector<Coord> placementof_3; 
			

			sf::Music       track1;
			sf::Font		font_corbel;
	//		sf::Text		additional_stats;
			sf::Text		tt1;
			sf::Text		tt2;
			sf::Text		tt3;
			sf::Text		tt4;
			sf::Text		tt5;
			sf::Text		tt6;

			long			nextlevel;
			int				time_m;
			int				time_s;
			int				lines_num;
			int				drops_num;
			unsigned long	score;
			bool			opac;
			int				op;
			bool			first;

			int				level;
			unsigned long	nextlevel_score;

			sf::Time		time_line_score;
			sf::Time		time_drop_score;
			sf::Time		time_gravity;
			sf::Time		time_total;
			sf::Time		time_update;
			sf::Time		time_animate;
			sf::Time		time_1;
			sf::Time		time_2;

			sf::Clock		clock_line_score;
			sf::Clock		clock_drop_score;
			sf::Clock		clock_gravity;
			sf::Clock		clock_total;
			sf::Clock		clock_update;
			sf::Clock		clock_animate;
			sf::Clock		clock_1;
			sf::Clock		clock_2;
			bool			anim_upd;

			sf::Texture		tstar;
			sf::Sprite		sstar;
	//		Animation		animation;

			sf::SoundBuffer buf[6];
			sf::Sound		snd[6];

#pragma endregion

};

