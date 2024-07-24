#pragma once

#include "include.h"
#include "Data.h"

#ifndef __SIZE__
#define __SIZE__

template <class SIZE_T>
struct Size
{
private:

	Data<SIZE_T> x;
	Data<SIZE_T> y;

public:

	Size(SIZE_T x_, SIZE_T y_);

	// set

	void SetSize(SIZE_T x_, SIZE_T y_);

	// GET

	Data<SIZE_T> GetSizeX() const;

	Data<SIZE_T> GetSizeY() const;

	// Update

	void Update();
};

#include "size.cpp"

#endif
