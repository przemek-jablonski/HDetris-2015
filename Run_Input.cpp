#include "Run_Input.h"
#include <iostream>


Run_Input::Run_Input(sf::RenderWindow& win) : render_win(win)
{
	assetinjector();
	Choice = 0;
	run();
}

Run_Input::~Run_Input()
{

}

void Run_Input::assetinjector()
{
	awalk.openFromFile("Assets/BGM/awalk.flac");
	awalk.setLoop(true);
	awalk.setVolume(65);
	awalk.play();
	buf[0].loadFromFile("Assets/efx/menumov.flac");
	buf[1].loadFromFile("Assets/efx/menuenter.flac");
	snd[0].setBuffer(buf[0]);
	snd[1].setBuffer(buf[1]);
	tex[0].loadFromFile("Assets/gfx/mainmenu.png");
	spr[0].setTexture(tex[0]);
	fontcorbel.loadFromFile("Assets/corbel.ttf");

	dialog1.setFont(fontcorbel);
	dialog1.setString("NORMAL MODE");
	dialog1.setCharacterSize(100);
	dialog1.setPosition(350, 75);

	dialog1sub.setFont(fontcorbel);
	dialog1sub.setString("[game of tetris with slower drop time\n             and more custom bricks]");
	dialog1sub.setCharacterSize(35);
	dialog1sub.setPosition(325, 160);

	dialog2.setFont(fontcorbel);
	dialog2.setString("CHALLENGE MODE");
	dialog2.setCharacterSize(100);
	dialog2.setPosition(285, 340);

	dialog2sub.setFont(fontcorbel);
	dialog2sub.setString("[game of tetris with significantly faster drop time, \nshorter levels and only classic bricks available]");
	dialog2sub.setCharacterSize(35);
	dialog2sub.setPosition(285, 420);


	dialog3.setFont(fontcorbel);
	dialog3.setString("back to main menu");
	dialog3.setCharacterSize(70);
	dialog3.setPosition(340, 620);
}

void Run_Input::run()
{
	while (render_win.isOpen())
	{
		event_handler();
		update();
		render();
	}
}

void Run_Input::event_handler()
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
			if (Choice > 3)
				Choice = Choice % 3;
		}
		if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::W)
		{
			snd[0].play();
			--Choice;
			if (Choice == 0 || Choice == -1)
				Choice = 3;
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
				std::cout << "ERROR: RUN_INPUT CHOICE EXCEPTION:" << ex;
			}
		}
	}
}

void Run_Input::choicehandler()
{
	if (Choice == 0)
	{
		std::string exception;
		exception = "Choice==0, error initializing module.\nNo module initialized, sry :C\n";
		throw exception;
	}
	if (Choice == 1)
	{
		std::cout << "choice==1: STANDARD MODE\n";
		awalk.stop();
			Main_Game tetris(render_win);
			tetris.start();
	}
	if (Choice == 2)
	{
		awalk.stop();
		std::cout << "choice==2: CHALLENGE MODE\n";
		Main_Game tetris(2, render_win);
		tetris.start();
	}
	if (Choice == 3)
	{
		awalk.stop();
		std::cout << "choice==3: BACK TO MAIN MENU\n";
		Main_Menu menu(render_win);
	}
}

void Run_Input::update()
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
		dialog2sub.setColor(sf::Color(200, 200, 15, 255));
	}
	else
	{
		dialog2.setColor(sf::Color(50, 0, 160, 255));
		dialog2sub.setColor(sf::Color(55, 10, 160));
	}

	if (Choice == 3)
	{
		dialog3.setColor(sf::Color(255, 255, 30, 255));
	}
	else
		dialog3.setColor(sf::Color(50, 0, 160, 255));

}

void Run_Input::render()
{
	render_win.clear(sf::Color::White);

	render_win.draw(spr[0]);
	render_win.draw(dialog1);
	render_win.draw(dialog2);
	render_win.draw(dialog3);
	render_win.draw(dialog4);
	render_win.draw(dialog1sub);
	render_win.draw(dialog2sub);
	render_win.display();
}