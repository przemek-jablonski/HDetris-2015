#pragma once
#include "SFML/Graphics.hpp"
class Asset : public sf::Transformable
{
	public:
			Asset();
			~Asset();

			void		setweight(float);
			float		getweight();
	//		int			getdim_x();
	//		int			getdim_y();


	private:
			float		weight_modifier;
	//		int			dim_x, dim_y;
};

