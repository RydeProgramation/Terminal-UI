#pragma once

#include "Header.h"

#ifndef __MYUI__
#define __MYUI__

class MyUI : UserInterface
{
public:

	MyUI();

	void Start() override;

	void Menu1();

private:

	void CreateWidgetWait(Widget* WIDG);

};

#endif