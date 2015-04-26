#pragma once
#include <SFML/Graphics.hpp>
class Animation 
{
public:
	Animation();
	Animation(float);
	~Animation();

private:
	void		initializator();
	void		render(int); 
	void		update(float);

	sf::Texture tcosmos, tdust, tstars;
	sf::Texture thills;
	sf::Sprite	scosmos, sdust, sstars;
	sf::Sprite  shills;

	float		frameupdate_time;
};

