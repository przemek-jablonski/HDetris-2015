#include "Tetris_Game.h"
#include <iostream>


Tetris_Game::Tetris_Game()
{
	render_win.create(sf::VideoMode(1280, 720, 32), "SFML C++ Tetris app.");
	int fps = 60;
	render_win.setFramerateLimit(fps);
//	sf::RenderWindow	&render_ref = render_win;

	mode = 1;
	asset_injector();
	run();
}

Tetris_Game::Tetris_Game(int mod) 
{
	mode = 2;
	asset_injector();
	run();
}


Tetris_Game::~Tetris_Game()
{
}


void Tetris_Game::asset_injector()
{
	buf[0].loadFromFile("Assets/efx/menuenter.flac");
	snd[0].setBuffer(buf[0]);
	font.loadFromFile("Assets/corbel.ttf");
	tx.loadFromFile("Assets/gfx/introscene.jpg");
	if (mode == 2)
		tx.loadFromFile("Assets/gfx/gameover.jpg");
	sp.setTexture(tx);
}

void Tetris_Game::run()
{
	while (render_win.isOpen())
	{
		event_handler();
		render();
	}
}

void Tetris_Game::event_handler()
{
	sf::Event ev;
	while (render_win.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			render_win.close();
		}

		if (ev.type == sf::Event::KeyPressed &&
			(ev.key.code == sf::Keyboard::Escape || ev.key.code == sf::Keyboard::Space
			|| ev.key.code == sf::Keyboard::Return))
		{
			snd[0].play();
			sf::RenderWindow &t = render_win;
			Main_Menu main_menu(t);
		}
	}
}

void Tetris_Game::render()
{
	render_win.clear(sf::Color::Black);
	render_win.draw(sp);
	render_win.display();
}