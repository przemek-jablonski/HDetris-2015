#pragma once
#include "Asset.h"
#include "TileMap.h"
class Brick : public Asset
{
public:
					Brick(); 
					Brick(int);
					Brick(int, float weight); 
					Brick(int, float weight, int rotate);
					~Brick();
		int***		getshape();
		int			getweight();
		int			getdim_x();
		int			getdim_y();
		int			gethistory();
		int***		shaperedefiner(int, int);
		int			type;
		int			typet[10];


private:
		void		shapecreation();
		void		shapedefiner();
		int			***shape;
		int			dim_x, dim_y;

		int			rotation;
		void		rotationR();
		void		rotationL();
		void		rotate();
		void		shapeclear();

protected:
		int			history;
};
