#pragma once

#include "include.h"
#include "trData.h"

#ifndef __TR_SIZE__
#define __TR_SIZE__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

template <class SIZE_T>
struct TERMINAL_ENGINE_API trSize : trObject
{
public:

	// INI

	trSize(const SIZE_T& x_, const SIZE_T& y_) : x(new trData<SIZE_T>(x_)), y(new trData<SIZE_T>(y_))
	{
		
	}

	// SET

	void SetSize(const SIZE_T& x_, const SIZE_T& y_) /*override*/
	{
		x->SetData(x_);
		y->SetData(y_);
	}

	// GET

	const trData<SIZE_T>& GetSizeX() const 
	{
		return *x;
	}

	const trData<SIZE_T>& GetSizeY() const 
	{
		return *y;
	}

	// Update
	void Update() 
	{
		x->Update();
		y->Update();
	}

	// DESTRUCTEUR

	~trSize()
	{
		delete x;
		delete y;
	}

private:

	trData<SIZE_T> *x;
	trData<SIZE_T> *y;
};

// #include "Size.inl" // <-- Inutile

#endif
