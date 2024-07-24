#pragma once

#include "include.h"
#include "Data.h"

#ifndef __COORDINATE__
#define __COORDINATE__

template <class COORD_T>
struct Coordinate
{
private:

	Data<COORD_T> x;
	Data<COORD_T> y;

public:

	Coordinate(COORD_T x_, COORD_T y_);

	// SET

	void SetCoord(COORD_T x_, COORD_T y_);

	// GET

	Data<COORD_T> GetX() const;

	Data<COORD_T> GetY() const;

	// UPDATE

	void Update();
};

#include "Coordinate.cpp"

#endif
