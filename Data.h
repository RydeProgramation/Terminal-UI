#ifndef __DATA__
#define __DATA__

#include "include.h"

template <class Data_T>
struct Data
{
private:

	Data_T New;

	Data_T Old;

	Data_T Actual;

public:

	Data(Data_T Actual_);

	// SET

	void SetData(Data_T newValue);

	// GET

	Data_T GetDataNew() const;

	Data_T GetDataOld() const;

	Data_T GetDataActual() const;

	// Update

	void Update();
};

#include "Data.cpp"

#endif