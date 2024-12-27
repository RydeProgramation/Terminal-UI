#pragma once

#include "include.h"

#include "trData.h"

#ifndef __TR_PAIR__
#define __TR_PAIR__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

template <class PAIR_T_1, class PAIR_T_2>
struct trPair : trObject
{
public:

	// INI default

	trPair() : first(new PAIR_T_1()), second(new PAIR_T_2())
	{

	}

	// INI

	trPair(const PAIR_T_1& x_1, const PAIR_T_2& x_2) : first(new PAIR_T_1(x_1)), second(new PAIR_T_2(x_2))
	{

	}

	// INI deep

	trPair(const trPair& other) : first(new PAIR_T_1(*other.first)), second(new PAIR_T_2(*other.second))
	{

	}

	// copy

	trPair& operator=(const trPair& other)
	{
		if (this == &other) 
		{ 
			return *this; 
		}

		first = new PAIR_T_1(*other.first);
		second = new PAIR_T_2(*other.second);

		return *this;
	}

	// SET

	void SetPair(const PAIR_T_1& x_1, const PAIR_T_2& x_2)
	{
		*first = x_1;
		*second = x_2;
	}

	void SetFirst(const PAIR_T_1& x)
	{
		*first = x;
	}

	void SetSecond(const PAIR_T_2& x)
	{
		*second = x;
	}

	// GET

	const PAIR_T_1& GetFirst() const
	{
		return *first;
	}

	const PAIR_T_2& GetSecond() const
	{
		return *second;
	}

	// DESTRUCTEUR

	~trPair()
	{
		delete first;
		delete second;
	}

public:

	PAIR_T_1* first;
	PAIR_T_2* second;
};

#endif