#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow& win) : render_win(win)
{
	assetinjector();
	run();
}

GameOver::~GameOver()
{
	//
}

void GameOver::run()
{
	while (render_win.isOpen())
	{
		event_handler();
		render();
	}
}

void GameOver::assetinjector()
{
	buf[0].loadFromFile("Assets/efx/menumov.flac");
	snd[0].setBuffer(buf[0]);
	font.loadFromFile("Assets/corbel.ttf");
	gameover.setFont(font);
	gameover.setColor(sf::Color::Black);
	gameover.setCharacterSize(150);
	gameover.setString("GAME OVER :(");
	gameover.setPosition(330, 230);
	tx.loadFromFile("Assets/gfx/gameover.jpg");
	sp.setTexture(tx);
}

void GameOver::event_handler()
{
	sf::Event ev;
	while (render_win.pollEvent(ev))
	{
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

void GameOver::render()
{
	render_win.clear(sf::Color::White);
	render_win.draw(sp);
	render_win.draw(gameover);
	render_win.display();
}