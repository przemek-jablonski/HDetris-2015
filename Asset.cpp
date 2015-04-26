#include "Asset.h"


Asset::Asset()
{
	this->weight_modifier = -1.f;
}


Asset::~Asset()
{
}

/*int Asset::getdim_x()
{
	return this->dim_x;
}

int Asset::getdim_y()
{
	return this->dim_y;
}*/

void Asset::setweight(float w)
{
	this->weight_modifier = (float) w;
}

float Asset::getweight()
{
	return this->weight_modifier;
}

