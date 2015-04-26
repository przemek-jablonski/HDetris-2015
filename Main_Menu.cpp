#include "Main_Menu.h"
#include <iostream>


Main_Menu::Main_Menu(sf::RenderWindow& win) : render_win(win)
{
//	state = MainMenu;
	assetinjector();
	Choice = 0;
	run();
	
}


Main_Menu::~Main_Menu()
{
}

void Main_Menu::assetinjector()
{
	buf[0].loadFromFile("Assets/efx/menumov.flac");
	buf[1].loadFromFile("Assets/efx/menuenter.flac");
	snd[0].setBuffer(buf[0]);
	snd[1].setBuffer(buf[1]);

	tex[0].loadFromFile("Assets/gfx/mainmenu.png");
	spr[0].setTexture(tex[0]);
	fontcorbel.loadFromFile("Assets/corbel.ttf");

	dialog1.setFont(fontcorbel);
	dialog1.setString("PLAY TETRIS");
	dialog1.setCharacterSize(100);
	dialog1.setPosition(350, 200);

	dialog1sub.setFont(fontcorbel);
	dialog1sub.setString(" [play the game of tetris]");
	dialog1sub.setCharacterSize(35);
	dialog1sub.setPosition(395, 305);
//	dialog1sub.setColor(sf::Color(75, 25, 160, 255));

	dialog2.setFont(fontcorbel);
	dialog2.setString("EXIT GAME");
	dialog2.setCharacterSize(72);
	dialog2.setPosition(440, 450);


	
}
void Main_Menu::run()
{
	while (render_win.isOpen())
	{
		event_handler();
		update();
		render();
	}
}

void Main_Menu::event_handler()
{
	sf::Event ev;
	while (render_win.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			render_win.close();
		}
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::S)
		{
			snd[0].play();
			++Choice;
			if (Choice > 2)
				Choice = Choice % 2;
		}
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::W)
		{
			snd[0].play();
			--Choice;
			if (Choice == 0 || Choice == -1)
				Choice = 2;
		}
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return)
		{
			snd[1].play();
			try
			{
				choicehandler();
			}
			catch (std::string ex)
			{
				std::cout << "ERROR: MAIN_MENU CHOICE EXCEPTION: " << ex;
			}
		}
	}
}

void Main_Menu::choicehandler()
{
	if (Choice == 0)
	{
		std::string exception;
		exception = "Choice==0, error initializing module.\nNo module initialized, sry :C\n";
		throw exception;
	}
	if (Choice == 1)
	{
		std::cout << "choice==1: initializing Run_Game module\n";
		Run_Input run_input(render_win);
	}
	if (Choice == 2)
	{
		std::cout << "choice==2: initializing Quit procedure\n";
		render_win.close();
	}
}

void Main_Menu::update()
{
	if (Choice == 1)
	{
		dialog1.setColor(sf::Color(255, 255, 30, 255));
		dialog1sub.setColor(sf::Color(200, 200, 15, 255));
	}
	else
	{
		dialog1.setColor(sf::Color(50, 0, 160, 255));
		dialog1sub.setColor(sf::Color(55, 10, 160));
	}
	if (Choice == 2)
	{
		dialog2.setColor(sf::Color(255, 255, 30, 255));
	}
	else
		dialog2.setColor(sf::Color(50, 0, 160, 255));
}


void Main_Menu::render()
{
	render_win.clear(sf::Color::White);
	render_win.draw(spr[0]);
	render_win.draw(dialog1);
	render_win.draw(dialog2);
	render_win.draw(dialog1sub);
	render_win.display();
}