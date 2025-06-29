#pragma once

#include "Header.h"

#ifndef __MYUI__
#define __MYUI__


class MyUI : trUserInterface
{
public:

	MyUI();

	virtual ~MyUI();

	void Start() override;

	void Menu1();

private:

	// attendre qu'il s'affiche au moins une fois pour éviter d'être trop rapide dans l'execution
	void CreateWidgetWait(trWidget* WIDG); 

	// attendre qu'il s'affiche au moins une fois pour éviter d'être trop rapide dans l'execution
	void CreateSelectorWait(trSelector* WIDG);
};

class Munition : public trWidget
{
public:

	Munition(int x_, int y_, int RelativePosition_, std::wstring content_, std::string name_)
		: trWidget(x_, y_, 1, 1, RelativePosition_, content_, name_ + std::to_string(bulletCount))
	{
		this->SetContent(L"*");
		bulletCount++;
	}

	void APPLY_Implementation() override
	{
		if (a <= 10)
		{
			this->AddToPosition(0, -1);
			a++;
		}
		
		else
		{
			this->SetDestroy(true);
		}
	}

	int a = 0;

	static int bulletCount;
};
#endif