#pragma once

#include "trObject.h"

#ifndef __TR_DATA__
#define __TR_DATA__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

template <class trData_T>
struct TERMINAL_ENGINE_API trData : trObject
{
public:

	// INI
	trData(const trData_T& Actual_) : Old(new trData_T(Actual_)), Actual(new trData_T(Actual_)), New(new trData_T(Actual_))
	{

	}

	// SET
	void SetData(const trData_T& newValue)
	{
		*New = newValue;
	}

	// GET
	const trData_T& GetDataNew() const
	{
		return *New;
	}

	const trData_T& GetDataOld() const
	{
		return *Old;
	}

	const trData_T& GetDataActual() const
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

	trData_T *New;
	trData_T *Old;
	trData_T *Actual;

};

// #include "Data.inl" // INUTILE

#endif
