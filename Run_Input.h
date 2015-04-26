#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Main_Menu.h"
#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

class Run_Input
{
public:
					Run_Input(sf::RenderWindow&);
					~Run_Input();

private:
	void			run();
	void			event_handler();
	void			update();
	void			render();
	void			assetinjector();
	void			choicehandler();


private:

	sf::Music		awalk;
	int				Choice;
	sf::RenderWindow& render_win;

	sf::Text		dialog1;
	sf::Text		dialog2;
	sf::Text		dialog3;
	sf::Text		dialog4;
	sf::Text		dialog1sub, dialog2sub;

	sf::Texture		tex[10];
	sf::Sprite		spr[10];
	sf::Font		fontcorbel;

	sf::SoundBuffer buf[2];
	sf::Sound		snd[2];
};

