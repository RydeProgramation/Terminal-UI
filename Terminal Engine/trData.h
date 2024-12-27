#pragma once

#include "trObject.h"

#ifndef __TR_DATA__
#define __TR_DATA__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

template <class DATA_T>
struct trData : trObject
{
public:

	// INI default
	trData() : Old(new DATA_T()), Actual(new DATA_T()), New(new DATA_T())
	{

	}

	// INI
	trData(const DATA_T& Actual_) : Old(new DATA_T(Actual_)), Actual(new DATA_T(Actual_)), New(new DATA_T(Actual_))
	{

	}

	// INI deep copy
	trData(const trData& other) : Old(new DATA_T(*other.Old)), Actual(new DATA_T(*other.Actual)), New(new DATA_T(*other.New))
	{

	}

	// Copy
	trData& operator=(const trData& other)
	{
		if (this == &other)
		{
			return *this;
		}

		Old = new DATA_T(*other.Old);
		Actual = new DATA_T(*other.Actual);
		New = new DATA_T(*other.New);

		return *this;
	}

	// SET
	void SetData(const DATA_T& newValue)
	{
		*New = newValue;
	}

	// GET
	const DATA_T& GetDataNew() const
	{
		return *New;
	}

	const DATA_T& GetDataOld() const
	{
		return *Old;
	}

	const DATA_T& GetDataActual() const
	{
		return *Actual;
	}

	// Update
	void Update()
	{
		*Old = *Actual;
		*Actual = *New;
	}

	// Destructuer
	~trData()
	{
		delete New;
		delete Old;
		delete Actual;
	}

private:

	DATA_T* New;
	DATA_T* Actual;
	DATA_T* Old;

};

#endif
