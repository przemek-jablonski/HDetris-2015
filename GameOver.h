#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Main_Menu.h"
#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

class GameOver
{
public:
	GameOver(sf::RenderWindow&);
	~GameOver();

private:

	void	event_handler();
	void	render();
	void	run();
	void	assetinjector();

	sf::RenderWindow&	render_win;
	sf::Texture	tx;
	sf::Sprite	sp;
	sf::Font	font;
	sf::Text	gameover;

	sf::SoundBuffer buf[1];
	sf::Sound		snd[1];
};

