#pragma once

#include "Header.h"

#ifndef __MYUI__
#define __MYUI__


class MyUI : trUserInterface
{
public:

	MyUI();

	~MyUI();

	void Start() override;

	void Menu1();

private:

	// attendre qu'il s'affiche au moins une fois pour éviter d'être trop rapide dans l'execution
	void CreateWidgetWait(trWidget* WIDG); 
};

#endif