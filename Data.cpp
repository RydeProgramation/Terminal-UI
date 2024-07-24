#include "Data.h"

#ifndef __DATA_M__
#define __DATA_M__

using namespace std;

template <class Data_T>
Data<Data_T>::Data(Data_T Actual_) : Old(Actual_), Actual(Actual_), New(Actual_)
{

}

// SET

template <class Data_T>
void Data<Data_T>::SetData(Data_T newValue)
{
	New = newValue;
}

// GET

template <class Data_T>
Data_T Data<Data_T>::GetDataNew() const
{
	return New;
}

template <class Data_T>
Data_T Data<Data_T>::GetDataOld() const
{
	return Old;
}

template <class Data_T>
Data_T Data<Data_T>::GetDataActual() const
{
	return Actual;
}

// UPDATE

template <class Data_T>
void Data<Data_T>::Update()
{
	Old = Actual;
	Actual = New;
}

#endif

