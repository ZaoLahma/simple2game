/*
 * coord.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#include "coord.h"

Coord::Coord() :
x(0),
y(0)
{

}

Coord::Coord(int _x, int _y) :
x(_x),
y(_y)
{

}

int Coord::GetX() const
{
	return x;
}

int Coord::GetY() const
{
	return y;
}

void Coord::SetX(const int _x)
{
	x = _x;
}

void Coord::SetY(const int _y)
{
	y = _y;
}
