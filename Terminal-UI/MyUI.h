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

	void CreateWidgetWait(trWidget* WIDG);

};

#endif