#include "trCoordinate.h"

#ifndef __TR_COORDINATE_INL__
#define __TR_COORDINATE_INL__

// INITIALIZATION

/*
template <class COORD_T>
trCoordinate<COORD_T>::trCoordinate(const COORD_T& x_, const COORD_T& y_)
{
	x = new trData<COORD_T>(x_);
	y = new trData<COORD_T>(y_);
}*/

/*
template<class COORD_T>
trCoordinate<COORD_T>::~trCoordinate()
{
	delete x;
	delete y;
}*/

// SET

/*
template <class COORD_T>
void trCoordinate<COORD_T>::SetCoord(const COORD_T& x_, const COORD_T& y_)
{
	x->SetData(x_);
	y->SetData(y_);
}*/

// GET

/*
template <class COORD_T>
trData<COORD_T> trCoordinate<COORD_T>::GetX() const
{
	return *x;
}*/

/*
template <class COORD_T>
trData<COORD_T> trCoordinate<COORD_T>::GetY() const
{
	return *y;
}*/

// UPDATE

/*
template <class COORD_T>
void trCoordinate<COORD_T>::Update()
{
	x->Update();
	y->Update();
}*/

#endif
