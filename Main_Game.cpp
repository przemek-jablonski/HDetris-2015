#include "Main_Game.h"
#include "TileMap.h"
#include "Asset.h"
#include "Coord.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>


Main_Game::Main_Game(sf::RenderWindow& win) : render_win(win)
{
	render_win.create(sf::VideoMode(1280, 720, 32), "SFML C++ Tetris app.");
	render_win.setFramerateLimit(60);
	this->mode = 1;
	sprite_injector();
	bricktype = 0;
	brickrotation = 0;
	score = 0;
	lines_num = 0;
	drops_num = 0;
	level = 1;
	nextlevel_score = 4000;
	anim_upd = false;
	actual_weight = 1;
	opac = false;
	first = true;
}

Main_Game::Main_Game(int mod, sf::RenderWindow& win) : render_win(win)
{
	render_win.create(sf::VideoMode(1280, 720, 32), "SFML C++ Tetris app.");
	render_win.setFramerateLimit(60);
	this->mode = mod;
	sprite_injector();
	bricktype = 0;
	brickrotation = 0;
	score = 0;
	lines_num = 0;
	drops_num = 0;
	level = 1;
	nextlevel_score = 1000;
	anim_upd = false;
	actual_weight = 2;
	opac = false;
	first = true;
}


Main_Game::~Main_Game()
{
	//~destructor
}

void Main_Game::start()
{
	track1.play();
	while (render_win.isOpen())
	{
		if (time_drop_score.asMilliseconds() != 0)
		{
			long t = (time_drop_score.asMilliseconds() / 100)*(-4) + 150;
			if (t>0) score += t;
			time_drop_score = sf::Time::Zero;
		}
		
		events_handler();
		update();
		render();
		time_update = clock_update.restart();
		
	}
}

void Main_Game::levelupdate()
{
	if (score >= nextlevel_score)
	{
		++level;
		snd[5].play();
		if (mode == 1)
		{
			nextlevel_score = nextlevel_score * 2;
			actual_weight += (float)level*(0.30);
		}
		else
		{
			nextlevel_score = nextlevel_score * 2;
			actual_weight = actual_weight + (float)level*(0.75);
		}

		std::cout << "Actual Weight of Brick: " << actual_weight << std::endl;
	}
}

void Main_Game::events_handler()
{
	seek1();
	sf::Event ev1;
	while (render_win.pollEvent(ev1))
	{
		if (ev1.type == sf::Event::Closed)						//event logic on demand
			render_win.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	//real time event logic
		{
			track1.stop();
			Main_Menu menu(render_win);
		}
		if (ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::Space)
		{
			//
		}
		if (ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::W 
			|| ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::E 
			 || ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::Up)
		{
			snd[2].play();
			rotateR();
			collisiondetection();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (isValid(0, 1))
			{
				
				collisiondetection();
				move(0, 1);
			}
		}

		if (ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::A
			|| ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::Left)
		{
			if (isValid(-1, 0))
			{
				
				collisiondetection();
				move(-1, 0);
			}
		}

		if (ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::D
			|| ev1.type == sf::Event::KeyPressed && ev1.key.code == sf::Keyboard::Right)
		{
			if (isValid(1, 0))
			{
				
				collisiondetection();
				move(1, 0);
			}
		}
	}
}

void Main_Game::rotateR()
{
	Coord start = brickorigin;
	int brickt = bricktype;
	int brickr = brickrotation;

	++brickrotation;
	if (brickrotation > 4)
		brickrotation = brickrotation % 4;

	brickactual.typet[bricktype] = brickrotation;
	std::cout << "ROTATION IS: " << brickr << std::endl;
	++brickr;

	if (brickr > 4)
		brickr = brickr % 4;
	
	for (size_t j = 0; j < placementof_1.size(); ++j)
	{
		int tmpx = placementof_1[j].x;
		int tmpy = placementof_1[j].y;
		tilemap.getmap()[tmpx][tmpy][0] = 0;
	}

	brickactual.shaperedefiner(brickt, brickr);
	quickshapeinsert(start, brickt, brickr);

}

void Main_Game::quickshapeinsert(Coord c, int type, int rot)
{
	int *** shape = brickactual.getshape();
	for (int x = 0; x < brickactual.getdim_x(); x++)
	{
		for (int y = 0; y < brickactual.getdim_y(); y++)
		{
			if (shape[x][y][0] == 1)
				tilemap.getmap()[x+c.x][y+c.y][0] = 1;
		}
	}
}

bool Main_Game::isValid(int dx, int dy)
{
	bool validation;
	for (size_t i = 0; i < placementof_1.size(); ++i)
	{
		if ((placementof_1[i].x +dx )> (tilemap.getdim_x() - 1))
		{
			validation = false;
			return validation;
		}
		if ((placementof_1[i].x + dx) < 0)
		{
			validation = false;
			return validation;
		}
		if ((placementof_1[i].y + dy) > (tilemap.getdim_y() -1))
		{
			validation = false;
			return validation;
		}
		if (tilemap.getmap()[place1ix + dx][place1iy + dy][0] == 2)
		{
			validation = false;
			collisiondetection();
			return validation;
		}
	}
	validation = true;
	return validation;
}

bool Main_Game::seekorigin()
{
	if (placementof_1.size() == 0 /*|| brickorigin.x == -1 || brickorigin.y == -1*/)
		return false;
	if (bricktype == 2 || bricktype == 3 || bricktype == 13 || bricktype == 16)
	{
		brickorigin.x = placementof_1[0].x;
		brickorigin.y = placementof_1[0].y;
		brickorigin.y -= 1;
	}
	else
	{
		brickorigin.x = placementof_1[0].x;
		brickorigin.y = placementof_1[0].y;
	}


	tilemap.getmap()[brickorigin.x][brickorigin.y][3] = 1;
	return true;
}

void Main_Game::update()
{
		linedetection();
		test();
	if (placementof_1.size() == 0)
	{
		shapeinsert();
		seek1();
		snd[0].play();
		
		if (!first)
		{
			if ((clock_1.restart()).asMilliseconds() < 100.f)
			{
				track1.stop();
				snd[1].play();
				GameOver gameover(render_win);
			}
		}
		first = false;
	}
	else
	{
		gravity();
	}
	collisiondetection();
	levelupdate();

	//ADDITIONAL STATSORZ
	time_total = clock_total.getElapsedTime();
	time_animate = time_total;
	time_s = int(time_total.asSeconds()) % 60;
	time_m = int(time_total.asSeconds()) - time_s;
	time_m = time_m / 60;
	std::string st;
	std::string str;
/*	st = "TOTAL SCORE: " + std::to_string(score) + " pts\n"
		+ "Time:\n" + std::to_string(time_m) + "  m  " + std::to_string(time_s) + "  s.\n"
		+ "Level: " + std::to_string(level) + "\n"
		+ "Next level: " + std::to_string(nextlevel_score) + "pts.\n"
		+ "Lines: " + std::to_string(lines_num) + "\n"
		+ "Drops: " + std::to_string(drops_num) + "\n";
	

	additional_stats.setString(st);
	additional_stats.setFont(font_corbel);
	additional_stats.setCharacterSize(40);
//	additional_stats.setStyle(sf::Text::Bold);
	additional_stats.setColor(sf::Color::White);
	additional_stats.setPosition(800, 200);*/

	//str = "\t" + std::to_string(time_m) + " m  " + std::to_string(time_s) + " s;"
	str = "TIME:\t\t\t\t\t\t\t  SCORE:\tlines:  " + std::to_string(lines_num);
	tt1.setString(str);
	tt1.setFont(font_corbel);
	tt1.setCharacterSize(46);
	tt1.setColor(sf::Color::White);
	tt1.setPosition(28.f, 550.f);

	str = std::to_string(time_m) + "m " + std::to_string(time_s) + "s";
	tt2.setString(str);
	tt2.setFont(font_corbel);
	tt2.setCharacterSize(58);
	tt2.setColor(sf::Color::White);
	tt2.setPosition(28.f, 600.f);

	str = " \t\t\t\t\t\t " + std::to_string(score);
	tt3.setString(str);
	tt3.setFont(font_corbel);
	tt3.setCharacterSize(59);
	tt3.setColor(sf::Color::White);
	tt3.setPosition(40.f, 600.f);

	str = " \t\t\t\t\t\t\t\t\t\t  drops: " + std::to_string(drops_num);
	tt4.setString(str);
	tt4.setFont(font_corbel);
	tt4.setCharacterSize(46);
	tt4.setColor(sf::Color::White);
	tt4.setPosition(32.f, 600.f);

	str = " \nlevel: " + std::to_string(level);
	tt5.setString(str);
	tt5.setFont(font_corbel);
	tt5.setCharacterSize(35);
	tt5.setColor(sf::Color::White);
	tt5.setPosition(28.f, 640.f);

	str = " \n\t\t\t\t\t\t\t\t\t\t\t next lvl: " + std::to_string(nextlevel_score) + "pts";
	tt6.setString(str);
	tt6.setFont(font_corbel);
	tt6.setCharacterSize(35);
	tt6.setColor(sf::Color::White);
	tt6.setPosition(34.f, 640.f);


}

void Main_Game::shapeinsert()
{
	if (bricks.size() == 0)
	{
			int c = rand() % 10;
			if (mode = !1)
			{
				c = rand() % 6;
			}

			Brick	brick1(c, 1, (rand() % 4 + 1));
			Brick	brick2(c, 1, (rand() % 4 + 1));
	

		bricks.push_back(brick1);
		bricks.push_back(brick2);

		brickactual = bricks[(bricks.size() - 2)];
		actual_weight = brickactual.getweight();
		bricknext = bricks[(bricks.size() - 1)];
	}
	else
	{
		int c = rand() % 10;
		if (mode = !1)
		{
			c = rand() % 6;
		}
			Brick	brick(c, 1, (rand() % 4 + 1));
		bricks.push_back(brick);

		brickactual = bricks[(bricks.size() - 2)];
		bricknext = bricks[(bricks.size() - 1)];
	}
	
	for (int i = 0; i < 10; ++i)
	{
		if (brickactual.typet[i] != 0)
		{
			bricktype = i;
			brickrotation = brickactual.typet[i];
		}
	}
	
	int *** shape = brickactual.getshape();
	for (int i = 0; i < brickactual.getdim_x(); i++)
	{
		for (int j = 0; j < brickactual.getdim_y(); j++)
		{
			if (shape[i][j][0] == 1)
				tilemap.getmap()[i+3][j][0] += 1;
		}
	}
}

std::vector<int> 
	 Main_Game::linedetection()
{
	std::vector<int> lines;
	lines.clear();
	int count = 0;

	for (int y = (tilemap.getdim_y()-1) ; y > -1; y--)
	{
		for (int x = 0; x < tilemap.getdim_x(); ++x)
		{
			if (tilemap.getmap()[x][y][0] == 2)
				++count;

			if (count == tilemap.getdim_x())
				lines.push_back(y);
		}
		count = 0;
	}
	line_delete(lines);
	return lines;
}

bool Main_Game::line_delete(std::vector<int> lines)
{
	for (size_t i = 0; i < lines.size(); ++i)
	{
		for (int x = 0; x < tilemap.getdim_x(); ++x)
			tilemap.getmap()[x][lines[i]][0] = 0;

		for (int x = 0; x < tilemap.getdim_x(); ++x)
		{
			for (int y = (lines[i]-1); y > -1; --y)
				tilemap.getmap()[x][y + 1][0] = tilemap.getmap()[x][y][0];
		}
	}
	if (lines.size() != 0)
	{
		snd[4].play();
		time_line_score = clock_line_score.restart();
		score += (time_line_score.asMilliseconds() / 45) * (lines.size() + 3);
		lines_num++;
	}
	
	return false;
}

bool Main_Game::collisiondetection()
{
	for (size_t i = 0; i < placementof_1.size(); ++i)
	{
		// horizontal locker: no leaving (x) max dimensions.
		if ((place1iy + 1) >= tilemap.getdim_y())
		{
				all_lock();
				return true;
		}
		else
		// vertical locker: blocking and locking movement
		//					if (y+1) == 2.
		{
			if (tilemap.getmap()[place1ix][(place1iy + 1)][0] == 2)
			{
				std::cout << "Collision detected ( (y+1)==2 )\n";
				all_lock();
				return true;
			}
		}
	}
	return false;
}

bool Main_Game::all_lock()
{
	for (size_t j = 0; j < placementof_1.size(); ++j)
	{
		int tmpx = placementof_1[j].x;
		int tmpy = placementof_1[j].y;
		tilemap.getmap()[tmpx][tmpy][0] = 2;
	}
	time_drop_score = clock_drop_score.restart();
	++drops_num;
	return true;
}

std::vector<Coord> 
Main_Game::seek1()
{
	placementof_1.clear();
	for (int x = 0; x < tilemap.getdim_x(); ++x)
	{
		for (int y = 0; y < tilemap.getdim_y(); ++y)
		{
			if (tilemap.getmap()[x][y][0] == 1)
			{
				Coord c(x, y);
				placementof_1.push_back(c);
			}
		}
	}
	if (placementof_1.size() != 0)
	{
		brickorigin = placementof_1[0];
			if (
				(bt == 0 && (br == 2 || br == 3)) ||
				(bt == 1 && br == 4) ||
				(bt == 3 && (br == 1 && br == 3)) ||
				(br == 4 && (br == 2 && br == 4)))
			{
				brickorigin.y -= 1;
			}
			else
			{
				if (bt == 2 && br == 1)
					brickorigin.y -= 2;
			}
	}
	else
	{
		std::cout << "placementof_1.size() == 0 !!!!!!!!";
	}
	return placementof_1;
}


void Main_Game::gravity()
{
	time_gravity = clock_gravity.getElapsedTime();
	if (time_gravity.asMilliseconds() > (1000.f/ actual_weight) )
	{
		if( isValid(0, 1) )
		{
		
			collisiondetection();
			move(0, 1);
		}
		clock_gravity.restart();
		time_gravity = sf::Time::Zero;
	}
}

void Main_Game::move(int dx, int dy)
{
//	seekorigin();
	//(1) brick movement:
	for (size_t k = 0; k < placementof_1.size(); ++k)
		tilemap.getmap()[placementof_1[k].x][placementof_1[k].y][0] = 0;

	for (size_t k = 0; k < placementof_1.size(); ++k)
		tilemap.getmap()[(placementof_1[k].x + dx)][(placementof_1[k].y + dy)][0] = 1;
	//(3) brick movement
}


void Main_Game::render()
{
	render_win.clear(sf::Color::Red);
	render_win.draw(spr[0]);
//	spr[11].setPosition(0, (time_update.asMilliseconds()/5));
	render_win.draw(spr[11]);
	render_win.draw(spr[3]);
	render_win.draw(spr[4]);
//	spr[8].setPosition((time_total.asMilliseconds() / 550), (time_total.asMilliseconds() / 950));
	spr[12].setColor(sf::Color(255, ((time_total.asMilliseconds()/60)%70 + 140), 150, (((time_total.asMilliseconds() /60)% 70 + 165))));
	render_win.draw(spr[12]);
	render_win.draw(spr[8]);
//	render_win.draw(spr[9]);
	spr[7].setPosition(-(time_total.asMilliseconds() / 105), 0);
	render_win.draw(spr[7]); 
	render_win.draw(spr[5]);
	spr[10].setPosition(-(time_total.asMilliseconds() / 35), 0);
	render_win.draw(spr[10]);
	render_win.draw(spr[6]);
	drawmap();
//	render_win.draw(additional_stats);
	render_win.draw(tt1);
	render_win.draw(tt2);
	render_win.draw(tt3);
	render_win.draw(tt4);
	render_win.draw(tt5);
	render_win.draw(tt6);
	render_win.display();
}

void Main_Game::drawmap()
{
	for (int x = 0; x < tilemap.getdim_x(); x++)
	{
		for (int y = 0; y < tilemap.getdim_y(); y++)
		{
			if (tilemap.getmap()[x][y][0] == 0)
			{
				spr[2].setPosition( (x* 33) + 405 , y * 33 + 20);
				spr[2].setColor(sf::Color(255, 255, 255, 50));
				render_win.draw(spr[2]);
			}
			if (tilemap.getmap()[x][y][0] == 1)
			{
				spr[1].setPosition((x * 33) + 405, y * 33 + 20);
				spr[1].setColor(sf::Color(255, 212, 52, 255));
				render_win.draw(spr[1]);
			}
			if (tilemap.getmap()[x][y][0] == 2)
			{
				spr[1].setPosition((x * 33) + 405, y * 33+20);
				spr[1].setColor(sf::Color(255, 140, 52, 255));
				render_win.draw(spr[1]);
			}
		}
	}

//	int mov = time_total.asMilliseconds() /5;
//	spr[3].setPosition(0, mov);
//	render_win.draw(spr[3]);

	for (int x = 0; x < bricknext.getdim_x(); ++x)
	{
		for (int y = 0; y < bricknext.getdim_x(); ++y)
		{
			if (bricknext.getshape()[x][y][0] == 1)
			{
				spr[1].setPosition((x * 33) + 240  +20, (y * 33)+535  +20);
				spr[1].setColor(sf::Color(255, 212, 52, 255));
				render_win.draw(spr[1]);
			}
		}
	}
}

void Main_Game::sprite_injector()
{
	bricks.clear();

	font_corbel.loadFromFile("Assets/asset_corbel.ttf");
	srand(time(NULL));

	track1.openFromFile("Assets/BGM/Ligature.flac");


	buf[0].loadFromFile("Assets/efx/brickcreation.flac");
	buf[1].loadFromFile("Assets/efx/brickdrop.flac");
	buf[2].loadFromFile("Assets/efx/brickrotation.flac");
	buf[3].loadFromFile("Assets/efx/gameover.flac");
	buf[4].loadFromFile("Assets/efx/linedelete.flac");
	buf[5].loadFromFile("Assets/efx/menuenter.flac");
	snd[0].setBuffer(buf[0]);
	snd[1].setBuffer(buf[1]);
	snd[2].setBuffer(buf[2]);
	snd[3].setBuffer(buf[3]);
	snd[4].setBuffer(buf[4]);
	snd[5].setBuffer(buf[5]);

	snd[0].setVolume(90);
	snd[1].setVolume(60);
	snd[2].setVolume(50);
	snd[3].setVolume(50);
	snd[4].setVolume(30);
	snd[5].setVolume(30);



	tex[0].loadFromFile("Assets/gfx/bg_sky.png");
	tex[3].loadFromFile("Assets/gfx/bg_planetD.png");
	tex[4].loadFromFile("Assets/gfx/bg_clouds_venus.png");
	tex[5].loadFromFile("Assets/gfx/bg_hills.png");
	tex[6].loadFromFile("Assets/gfx/infopanel_bg.png");
	tex[7].loadFromFile("Assets/gfx/bg_cosmos.png");
	tex[8].loadFromFile("Assets/gfx/bg_planetR.png");
	tex[9].loadFromFile("Assets/gfx/bg_planetL.png");
	tex[10].loadFromFile("Assets/gfx/bg_dust.png");
	tex[11].loadFromFile("Assets/gfx/bg_stars.png");
	tex[12].loadFromFile("Assets/gfx/bg_planetRbg.png");


	if (!tex[1].loadFromFile("Assets/Textures/cube2bw33.png"))
		std::cout << "Failed to load: tex[1]: cube2bw33.png." << std::endl;
	else
		std::cout << "Loading succesful: tex[1]: cube2bw33.png." << std::endl;

	if (!tex[2].loadFromFile("Assets/Textures/white332.png"))
		std::cout << "Failed to load: tex[1]: cube2_0white.png." << std::endl;
	else
		std::cout << "Loading succesful: tex[1]: cube2_0white.png." << std::endl;

	

//	tex[3].loadFromFile("Assets/bg_stars.png");
//	tex[3].setRepeated(1);

	spr[0].setTexture(tex[0]);
	spr[1].setTexture(tex[1]);
	spr[2].setTexture(tex[2]);
	spr[3].setTexture(tex[3]);
	spr[4].setTexture(tex[4]);
	spr[5].setTexture(tex[5]);
	spr[6].setTexture(tex[6]);
	spr[7].setTexture(tex[7]);
	spr[8].setTexture(tex[8]);
	spr[9].setTexture(tex[9]);
	spr[10].setTexture(tex[10]);
	spr[11].setTexture(tex[11]);
	spr[11].setOrigin(0, 1100);
	spr[12].setTexture(tex[12]);

	anim[1].setTexture(tex[11]);
	anim[2].setTexture(tex[7]);
	anim[2].setOrigin(900, 0);
	anim[3].setTexture(tex[10]);
}

void Main_Game::test()
{
//	std::cout << "Bricktype: (" << bricktype << ") / Brickrotation: (" <<  brickrotation << ")" << std::endl;
}