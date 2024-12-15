#pragma once

#include "include.h"
#include "trData.h"

#ifndef __TR_COORDINATE__
#define __TR_COORDINATE__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

template <class COORD_T>
struct TERMINAL_ENGINE_API trCoordinate : trObject
{
public:

	// INI
	trCoordinate(const COORD_T& x_, const COORD_T& y_) : x(new trData<COORD_T>(x_)), y(new trData<COORD_T>(y_)) /*x(std::make_unique<trData<COORD_T>>(x_)), y(std::make_unique<trData<COORD_T>>(y_))*/
	{

	}

	// SET
	void SetCoord(const COORD_T& x_, const COORD_T& y_) 
	{
		x->SetData(x_);
		y->SetData(y_);
	}

	// GET
	const trData<COORD_T>& GetX() const 
	{
		return *x;
	}
	 
	const trData<COORD_T>& GetY() const 
	{
		return *y;
	}

	// UPDATE
	void Update() 
	{
		x->Update();
		y->Update();
	}

	// DESTRUCTEUR

	~trCoordinate()
	{
		delete x;
		delete y;
	}

private:

	trData<COORD_T> *x;
	trData<COORD_T> *y;
};

//#include "Coordinate.inl" // <-- Inutile

#endif
