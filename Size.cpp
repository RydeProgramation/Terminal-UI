#include "Size.h"

#ifndef __SIZE_M__ 
#define __SIZE_M__

using namespace std;

// INI

template <class SIZE_T>
Size<SIZE_T>::Size(SIZE_T x_, SIZE_T y_) : x(x_), y(y_)
{

}

// SET

template <class SIZE_T>
void Size<SIZE_T>::SetSize(SIZE_T x_, SIZE_T y_)
{
	x.SetData(x_);
	y.SetData(y_);
}

// GET

template <class SIZE_T>
Data<SIZE_T> Size<SIZE_T>::GetSizeX() const
{
	return x;
}

template <class SIZE_T>
Data<SIZE_T> Size<SIZE_T>::GetSizeY() const
{
	return y;
}

// Update

template <class SIZE_T>
void Size<SIZE_T>::Update()
{
	x.Update();
	y.Update();
}

#endif