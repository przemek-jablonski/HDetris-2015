#include "Animation.h"
#include <iostream>


Animation::Animation()
{
	initializator();
}
Animation::Animation(float fut)
{
	frameupdate_time = fut;
	initializator();
}

Animation::~Animation()
{
}

void Animation::initializator()
{
	tcosmos.loadFromFile("Assets/gfx/bg_cosmos.png");
	tdust.loadFromFile("Assets/gfx/bg_dust.png");
	tstars.loadFromFile("Assets/gfx/bg_stars.png");
	thills.loadFromFile("Assets/gfx/bg_hills.png");
	scosmos.setTexture(tcosmos);
	sdust.setTexture(tdust);
	sstars.setTexture(tstars);
	shills.setTexture(thills);
	std::cout << "trolll\n";
}

void Animation::render(int type)
{
	switch (type)
	{
	case 1: //STARS

		break;
	case 2: //COSMOS
		
		break;
	case 3: //DUST
		
		break;
	}
}

void Animation::update(float time)
{
	frameupdate_time = time;
}