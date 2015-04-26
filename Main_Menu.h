#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include "Tetris_Game.h"
#include "Run_Input.h"
class Main_Menu 
{
public:
					Main_Menu(sf::RenderWindow&);
					~Main_Menu();
	void			 run();


private:

	void			event_handler();
	void			update();
	void			render();
	void			assetinjector();
	void			choicehandler();
	

private:

	int				StateType;
	int				Choice;
  sf::RenderWindow& render_win;
	sf::Texture		tex[10];
	sf::Sprite		spr[10];
	sf::Font		fontcorbel;
	sf::Text		dialog1;
	sf::Text		dialog2;
	sf::Text		dialog1sub;

	sf::SoundBuffer buf[2];
	sf::Sound		snd[2];



};

