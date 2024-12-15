#include "trData.h"

#ifndef __TR_DATA_INL__
#define __TR_DATA_INL__

/*
template <class Data_T>
trData<Data_T>::trData(const Data_T& Actual_)
{
	New = new Data_T(Actual_);
	Old = new Data_T(Actual_);
	Actual = new Data_T(Actual_);
}

template<class Data_T>
trData<Data_T>::~trData() 
{
	delete New;
	delete Old;
	delete Actual;
}

// SET

template <class Data_T>
void trData<Data_T>::SetData(const Data_T& newValue)
{
	*New = newValue;
}

// GET

template <class Data_T>
Data_T trData<Data_T>::GetDataNew() const
{
	return *New;
}

template <class Data_T>
Data_T trData<Data_T>::GetDataOld() const 
{
	return *Old;
}

template <class Data_T>
Data_T trData<Data_T>::GetDataActual() const 
{
	return *Actual;
}

// UPDATE

template <class Data_T>
void trData<Data_T>::Update() 
{
	*Old = *Actual;
	*Actual = *New;
}*/

#endif
