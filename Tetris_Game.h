#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Main_Menu.h"
#include "Main_Game.h"
#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC
class Tetris_Game
{

public:
						Tetris_Game();
						Tetris_Game(int);
					   ~Tetris_Game();
	enum GameState		{Start, Intro, MainMenu, RunInput, HighScores, HelpCredits, Exit, 
							MainGame, GameOver, Help2, HighScores2};
	GameState			state;
private:

	sf::RenderWindow	render_win;
	sf::Texture			tx;
	sf::Sprite			sp;
	sf::Font			font;
	sf::Text			gameover;
//	sf::Music			walk;

	void		event_handler();
	void		render();
	void		asset_injector();
	void		run();

	int			mode;

	sf::SoundBuffer buf[1];
	sf::Sound		snd[1];
};

