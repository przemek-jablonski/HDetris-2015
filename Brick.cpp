#include "Brick.h"
#include <iostream>


Brick::Brick()
{
	this->setweight(1.f);
	this->dim_x = 4;
	this->dim_y = 4;
	shapecreation();
	type = 1;
	typet[1] = 1;
	shapedefiner();
	history++;
}

Brick::Brick(int num)
{
	this->setweight(1.f);
	this->dim_x = 4;
	this->dim_y = 4;
	shapecreation();
	type = num;
	typet[num] = 1;
	shapedefiner();
	history++;
}

Brick::Brick(int num, float weight)
{
	this->setweight(weight);
	this->dim_x = 4;
	this->dim_y = 4;
	shapecreation();
	type = num;
	typet[num] = 1;
	shapedefiner();
	history++;
}
Brick::Brick(int num, float weight, int rotate)
{
	this->setweight(weight);
	this->dim_x = 4;
	this->dim_y = 4;
	shapecreation();
	type = num;
	typet[num] = rotate;
	shapedefiner();
	history++;
}

		Brick::~Brick()			{	}
int		Brick::getweight()		{ return Asset::getweight(); }
int***  Brick::getshape()		{ return shape; }
int		Brick::getdim_x()		{ return dim_x; }
int		Brick::getdim_y()		{ return dim_y; }
int		Brick::gethistory()		{ return history; }

void	Brick::rotationR()
{
	rotation++;
	rotate();
}

void	Brick::shapeclear()
{
	for (int x = 0; x < this->dim_x; ++x)
	{
		for (int y = 0; y < this->dim_y; ++y)
		{
			this->shape[x][y][0] = 0;
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		typet[i] = 0;
	}
}

int***	Brick::shaperedefiner(int type, int rotation)
{
	for (int i = 0; i < 10; ++i)
	{
		typet[i] = 0;
	}

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			this->shape[x][y][0] = 0; //availability status layer
			this->shape[x][y][1] = -1; //history layer
			this->shape[x][y][2] = -1; //colour hue ID layer
			this->shape[x][y][3] = 0; //parent shape array indicator
		}
	}

	typet[type] = rotation;
	shapedefiner();
	return shape;
}

void	Brick::rotate()
{
	shapeclear();
	switch (type)
	{
	case 1:
		switch (rotation)
		{
			case 1:
				std::cout << "Standard rotation (T brick).\n";
				this->shape[0][0][0] = 1; // T
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				this->shape[1][1][0] = 1;
				break;
			case 2:
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][2][0] = 1;
				break;
			case 3:
				this->shape[1][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[2][1][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				this->shape[1][1][0] = 1;
				break;
			default:
				std::cout << "Error processing rotation();\n";
				break;
		}
		break;
	}
}


void Brick::shapecreation()
{

	for (int i = 0; i < 10; ++i)
	{
		typet[i] = 0;
	}

	shape = new int**[4];
	for (int x = 0; x < 4; ++x)
	{
		*(shape + x) = new int*[4];
		for (int y = 0; y < 4; ++y)
		{
			*(*(shape + x) + y) = new int[4];
		}
	}
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			this->shape[x][y][0] =  0; //availability status layer
			this->shape[x][y][1] = -1; //history layer
			this->shape[x][y][2] = -1; //colour hue ID layer
			this->shape[x][y][3] =  0; //parent shape array indicator
		}
	}
}

void Brick::shapedefiner()
{
//	this->shape[0][0][3] = 1;
		if (typet[0] != 0)
		{
			switch (typet[0])
			{
			case 1:
				this->shape[0][0][0] = 1; // T
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				this->shape[1][1][0] = 1;
				break;
			case 2:
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][2][0] = 1;
				break;
			case 3:
				this->shape[1][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[2][1][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				this->shape[1][1][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[1] != 0)
		{
			switch (typet[1])
			{
				case 1:
					this->shape[0][0][0] = 1; // L
					this->shape[0][1][0] = 1;
					this->shape[0][2][0] = 1;
					this->shape[1][2][0] = 1;
					break;
				case 2:
					this->shape[0][0][0] = 1;
					this->shape[1][0][0] = 1;
					this->shape[2][0][0] = 1;
					this->shape[0][1][0] = 1;
					break;
				case 3:
					this->shape[0][0][0] = 1;
					this->shape[1][0][0] = 1;
					this->shape[1][1][0] = 1;
					this->shape[1][2][0] = 1;
					break;
				case 4:
					this->shape[0][1][0] = 1;
					this->shape[1][1][0] = 1;
					this->shape[2][1][0] = 1;
					this->shape[2][0][0] = 1;
					break;
				default:
					std::cout << "Error\n" << std::endl;
					break;
			}

		}
		if (typet[2] != 0)
		{
			switch (typet[2])
			{
			case 1:
				this->shape[1][0][0] = 1; // J
				this->shape[1][1][0] = 1;
				this->shape[1][2][0] = 1;
				this->shape[0][2][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[2][1][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				this->shape[1][0][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				this->shape[2][1][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}

		if (typet[3] != 0)
		{
			switch (typet[3])
			{
			case 1:
				this->shape[0][1][0] = 1; // S
				this->shape[1][1][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[1][2][0] = 1;
				break;
			case 3:
				this->shape[0][1][0] = 1; // S
				this->shape[1][1][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[1][2][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[4] != 0)
		{
			switch (typet[4])
			{
			case 1:
				this->shape[0][0][0] = 1; // Z
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[2][1][0] = 1;
				break;
			case 2:
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1; // Z
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[2][1][0] = 1;
				break;
			case 4:
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[5] != 0)
		{
			switch (typet[5])
			{
			case 1:
				this->shape[0][0][0] = 1; // O (box)
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1; // O (box)
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1; // O (box)
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1; // O (box)
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[6] != 0)
		{
			switch (typet[6])
			{
			case 1:
				this->shape[0][0][0] = 1; // 2L
				this->shape[0][1][0] = 1;
				this->shape[1][1][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[0][1][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				break;
			case 4:
				this->shape[1][0][0] = 1;
				this->shape[1][1][0] = 1;
				this->shape[0][1][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[7] != 0)
		{
			switch (typet[7])
			{
			case 1:
				this->shape[0][0][0] = 1; // 4I
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				this->shape[0][3][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				this->shape[3][0][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1; // 4I
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				this->shape[0][3][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				this->shape[3][0][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[8] != 0)
		{
			switch (typet[8])
			{
			case 1:
				this->shape[0][0][0] = 1; // 3I
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1; // 3I
				this->shape[0][1][0] = 1;
				this->shape[0][2][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				this->shape[2][0][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
		if (typet[9] != 0)
		{
			switch (typet[9])
			{
			case 1:
				this->shape[0][0][0] = 1; // 2I
				this->shape[0][1][0] = 1;
				break;
			case 2:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				break;
			case 3:
				this->shape[0][0][0] = 1; // 2I
				this->shape[0][1][0] = 1;
				break;
			case 4:
				this->shape[0][0][0] = 1;
				this->shape[1][0][0] = 1;
				break;
			default:
				std::cout << "Error\n" << std::endl;
				break;
			}
		}
	
}