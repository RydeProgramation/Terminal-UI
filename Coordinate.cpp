#include "Coordinate.h"

#ifndef __COORDINATE_M__
#define __COORDINATE_M__

using namespace std;

// INISIALIZATION

template <class COORD_T>
Coordinate<COORD_T>::Coordinate(COORD_T x_, COORD_T y_) : x(x_), y(y_)
{

}

// SET

template <class COORD_T>
void Coordinate<COORD_T>::SetCoord(COORD_T x_, COORD_T y_)
{
	x.SetData(x_);
	y.SetData(y_);
}

// GET

template <class COORD_T>
Data<COORD_T> Coordinate<COORD_T>::GetX() const
{
	return x;
}

template <class COORD_T>
Data<COORD_T> Coordinate<COORD_T>::GetY() const
{
	return y;
}

// UPDATE

template <class COORD_T>
void Coordinate<COORD_T>::Update()
{
	x.Update();
	y.Update();
}

#endif