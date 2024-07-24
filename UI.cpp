#include "Header.h"

// UI

using namespace std;
using namespace UITools;

// INI

UserInterface::UserInterface() : SizeWindow(int(0), int(0)), CursorSelector(int(0)), BorderWidth(int(5))
{

}

// CODE

void UserInterface::Start()
{
	SetupConsole();

	T = thread(&UserInterface::Loop, this);

	T2 = thread(&KeyBoardManagement::Start, &KB);
}

void UserInterface::Update()
{
	SizeWindow.SetSize(GetConsoleSize().GetSizeX().GetDataActual(), GetConsoleSize().GetSizeY().GetDataActual());
	SizeWindow.Update();

	UpdateWidget();

	if (RefreshVerification())
	{
		Refresh();
	}

	/*for (int i = ToPushWidgets.size() - 1; i >= 0; i--)
	{
		CreateWidget(ToPushWidgets[i]);

		delete ToPushWidgets[i]; // DANGEUREUX FUITE DE MEMOIRE POSSIBLE ;( (je le rappelle une fuite de mémoire peut causer de grave dommage sur le pc)

		ToPushWidgets.erase(ToPushWidgets.begin() + i);
	}*/

	for (int i = Widgets.size() - 1; i >= 0; i--)                // <-- a voir pour déplacer en bas
	{                                                       // <-- a voir pour déplacer en bas
		if (Widgets[i]->GetDestroy().GetDataActual())       // <-- a voir pour déplacer en bas
		{                                                   // <-- a voir pour déplacer en bas
			//DestroyWidget(Widgets[i]);                      // <-- a voir pour déplacer en bas
		}                                                   // <-- a voir pour déplacer en bas
	}                                                       // <-- a voir pour déplacer en bas
	                                                        //
	for (int i = 0; i < Widgets.size(); i++)                //
	{                                                       //
		/*if (Widgets[i]->GetDestroy().GetDataActual())     // <-- ici
		{                                                   // <-- ici
			DestroyWidget(Widgets[i]);                      // <-- ici
		}*/                                                 // <-- ici

		if (!Widgets[i]->GetActivate().GetDataActual())
		{
			HideWidget(Widgets[i]);
		}

		else if (Widgets[i]->GetActivate().GetDataActual())
		{
			DisplayWidget(Widgets[i]);
		}
	}

	for (int i = Widgets.size() - 1; i >= 0; i--)           // <-- a voir pour déplacer en bas
	{                                                       // <-- a voir pour déplacer en bas
		if (Widgets[i]->GetDestroy().GetDataActual())       // <-- a voir pour déplacer en bas
		{                                                   // <-- a voir pour déplacer en bas
			DestroyWidget(Widgets[i]);                      // <-- a voir pour déplacer en bas
		}                                                   // <-- a voir pour déplacer en bas
	}

	KB.ActionBTN();
}

void UserInterface::Refresh()
{
	// system("cls");

	Border();

	for (int i = 0; i < Widgets.size(); i++)
	{
		Widgets[i]->SetChange(true);
	}

	hideCursor();
}

bool UserInterface::RefreshVerification()
{
	return (SizeWindow.GetSizeX().GetDataActual() != SizeWindow.GetSizeX().GetDataOld() || SizeWindow.GetSizeY().GetDataActual() != SizeWindow.GetSizeY().GetDataOld()) ? true : false;
}

void UserInterface::Loop()
{
	while (true)
	{
		Update();
	}
}

void UserInterface::Border()
{
	MoveCursorTo(Coordinate<int>(0, 0));

	std::ostringstream output;

	string topBottomBorder(SizeWindow.GetSizeX().GetDataActual() * BorderWidth, '*');
	string sideBorder(BorderWidth * 2, '*');
	string emptyLine(SizeWindow.GetSizeX().GetDataActual() - BorderWidth * 4, ' ');

	output << topBottomBorder;

	string middleLine = sideBorder + emptyLine + sideBorder;
	for (int i = BorderWidth; i < SizeWindow.GetSizeY().GetDataActual() - BorderWidth; ++i) {
		output << middleLine;
	}

	output << topBottomBorder;

	SetColorConsole(15);

	cout << output.str();
	
	MoveCursorTo(Coordinate<int>(0, 0));
}

void UserInterface::SetupConsole()
{
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleCP(CP_UTF8);

	BorderWidth = 6;

	CursorSelector = 0;

	hideCursor();

	SizeWindow.SetSize(GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), GetConsoleSize(BorderWidth).GetSizeY().GetDataActual());
	SizeWindow.Update();

	KB.CreateBTN(new BTN_Key(VK_LEFT, bind(&UserInterface::SelectPrevious, this)));
	KB.CreateBTN(new BTN_Key(VK_RIGHT, bind(&UserInterface::SelectNext, this)));
}

template<typename FuncType, typename... Args>
void UserInterface::SetWidget(string name, FuncType func, Args... args) 
{
	auto widgetIndex = WidgetResearch(name);

	if (widgetIndex->has_value()) 
	{
		// Widgets[widgetIndex.value()]->*func(std::forward<Args>(args)...);

		invoke(func, Widgets[widgetIndex->value()], forward<Args>(args)...);
		
		/*auto action = [func, args...](Widget* widget) 
		{
			(widget->*func)(std::forward<Args>(args)...);
		};

		action(Widgets[widgetIndex.value()]);*/
	}
}


void UserInterface::ToDestroyWidget(string name)
{
	if (WidgetResearch(name).has_value())
	{
		Widgets[WidgetResearch(name).value()]->SetDestroy(true);
	}
}

void UserInterface::ToCreateWidget(Widget* WIDG)
{
	// ToCreateWidget()
}

bool UserInterface::ManageWidget(Widget* WIDG, int Manage)
{
	std::lock_guard<std::mutex> lock(mtx);

	if (Manage == 1) // destroy
	{
		if (WidgetResearch(WIDG->GetName().GetDataActual()).has_value())
		{
			SetColorConsole(15);

			HideWidget(WIDG);

			//delete Widgets[index.value()]; // DANGEUREUX FUITE DE MEMOIRE POSSIBLE ;(

			Widgets.erase(Widgets.begin() + WidgetResearch(WIDG->GetName().GetDataActual()).value());

			delete WIDG;

			// Widgets.erase(0);
			return true;
		}

		return false;
	}

	else if (Manage == 0) // create
	{
		SizeWindow.SetSize(GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), GetConsoleSize(BorderWidth).GetSizeY().GetDataActual());
		SizeWindow.Update();

		for (int i = 0; i < Widgets.size(); i++)
		{
			if (Widgets[i]->GetName().GetDataActual() == WIDG->GetName().GetDataActual())
			{
				return false; // ERROR : Widget already created
			}
		}

		WIDG->APPLY(SizeWindow);

		Widgets.push_back(WIDG);

		return true;
	}

	return false;
}

bool UserInterface::CreateWidget(Widget* WIDG)
{
	// return ManageWidget(WIDG, 0);

	std::lock_guard<std::mutex> lock(mtx);

	SizeWindow.SetSize(GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), GetConsoleSize(BorderWidth).GetSizeY().GetDataActual());
	SizeWindow.Update();

	for (int i = 0; i < Widgets.size(); i++)
	{
		if (Widgets[i]->GetName().GetDataActual() == WIDG->GetName().GetDataActual())
		{
			return false; // ERROR : Widget already created
		}
	}

	WIDG->APPLY(SizeWindow);

	Widgets.push_back(WIDG);

	return true;
}

bool UserInterface::DestroyWidget(Widget* WIDG)
{
	// return ManageWidget(WIDG, 1);

	/*std::lock_guard<std::mutex> lock(mtx);

	if (WidgetResearch(WIDG->GetName().GetDataActual()).has_value())
	{
		SetColorConsole(15);

		HideWidget(WIDG);

		//delete Widgets[index.value()]; // DANGEUREUX FUITE DE MEMOIRE POSSIBLE ;(

		// Widgets.erase(Widgets.begin() + WidgetResearch(WIDG->GetName().GetDataActual()).value());
		
		Widgets.erase(std::remove_if(Widgets.begin(), Widgets.end(), [WIDG](Widget* w) { return w->GetName().GetDataActual() == WIDG->GetName().GetDataActual(); }), Widgets.end());

		delete WIDG;

		// Widgets.erase(0);
		return true;
	}*/



	return false;
}

Widget UserInterface::GetWidget(int index) const
{
	return *Widgets[index];
}

std::optional<int> UserInterface::WidgetResearch(string name)
{
	auto it = find_if(Widgets.begin(), Widgets.end(), [name](const Widget* widget) { return widget->GetName().GetDataActual() == name; });

	if (it != Widgets.end())
	{
		return int(distance(Widgets.begin(), it));
	}

	return nullopt;
}

int UserInterface::DisplayWidget(Widget* WIDG)
{
	if (WIDG->GetChange().GetDataActual())
	{
		CleanWidget(WIDG);

		std::ostringstream output;

		int c = 0;

		for (int j = WIDG->GetRelativePosition().GetY().GetDataActual(); j < WIDG->GetRelativePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual(); j++)
		{
			output << WIDG->GetContent().GetDataActual().substr(min(c, WIDG->GetContent().GetDataActual().size() - 1), WIDG->GetSize().GetSizeX().GetDataActual() - max(WIDG->GetRelativePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0));

			MoveCursorTo(Coordinate<int>(WIDG->GetRelativePosition().GetX().GetDataActual(), j), BorderWidth);

			if (!IsOutSide(Coordinate<int>(WIDG->GetRelativePosition().GetX().GetDataActual(), j), BorderWidth))
			{	
				WIDG->Display(output);
			}

			output.str("");

			c += WIDG->GetSize().GetSizeX().GetDataActual();
		}

		WIDG->SetChange(false);
	}

	if (WIDG->GetDelayCaractere().GetDataActual() != 0) // <-- jsp si ça sert a qqchose
	{                                                   // <-- jsp si ça sert a qqchose
		WIDG->SetDelayCaractere(0);                     // <-- jsp si ça sert a qqchose
	}                                                   // <-- jsp si ça sert a qqchose

	return 0;
}

void UserInterface::HideWidget(Widget* WIDG) // < ----- BUUUG
{
	/*for (int j = min(WIDG->GetRelativePosition().GetY().GetDataActual(), WIDG->GetRelativePosition().GetY().GetDataOld()); j < max(WIDG->GetRelativePosition().GetY().GetDataActual(), WIDG->GetRelativePosition().GetY().GetDataOld()) + max(WIDG->GetSize().GetSizeY().GetDataOld(), WIDG->GetSize().GetSizeY().GetDataActual()); j++)
	{
		for (int i = min(WIDG->GetRelativePosition().GetX().GetDataActual(), WIDG->GetRelativePosition().GetX().GetDataOld()); i < max(WIDG->GetRelativePosition().GetX().GetDataActual(), WIDG->GetRelativePosition().GetX().GetDataOld()) + max(WIDG->GetSize().GetSizeX().GetDataOld(), WIDG->GetSize().GetSizeX().GetDataActual()); i++)
		{
			if (IsOutSide(Coordinate<int>(i, j), false))
			{
				continue; // <-- pas sur (chatgpt)
			}

			MoveCursorTo(Coordinate<int>(j, i), BorderWidth);
			cout << " ";
		}
	}*/
}

void UserInterface::CleanWidget(Widget* WIDG)
{
	for (int j = WIDG->GetRelativePosition().GetY().GetDataOld(); j <= WIDG->GetRelativePosition().GetY().GetDataOld() + WIDG->GetSize().GetSizeY().GetDataOld(); j++)
	{
		if (!IsOutSide(Coordinate<int>(WIDG->GetRelativePosition().GetX().GetDataOld(), j), BorderWidth))
		{
			SetColorConsole(15);
			string clean(WIDG->GetSize().GetSizeX().GetDataOld() - max(WIDG->GetRelativePosition().GetX().GetDataOld() + WIDG->GetSize().GetSizeX().GetDataOld() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0), ' ');
			MoveCursorTo(Coordinate<int>(WIDG->GetRelativePosition().GetX().GetDataOld(), j), BorderWidth);
			cout << clean;
		}
	}
}

void UserInterface::UpdateWidget()
{
	for (int i = 0; i < Widgets.size(); i++)
	{
		Widgets[i]->APPLY(GetConsoleSize(BorderWidth));
	}
}

void UserInterface::Select(string name)
{
	for (int i = 0; i < Widgets.size(); i++)
	{
		if (Selector* sltr = dynamic_cast<Selector*>(Widgets[i]))
		{
			sltr->SetSelected(sltr->GetName().GetDataActual() == name);
			sltr->SetChange(true);
		}
	}
}

void UserInterface::SelectNext()
{
	bool found = false;

	for (int i = 0; i < Widgets.size(); i++)
	{
		if (Selector* sltr = dynamic_cast<Selector*>(Widgets[i]))
		{
			if (found)
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = Widgets.size();
			}

			else if (sltr->IsSelected().GetDataActual())
			{
				found = true;
				sltr->SetSelected(false);
				sltr->SetChange(true);
			}
		}
	}

	if (found)
	{
		for (size_t i = 0; i < Widgets.size(); i++)
		{
			if (Selector* sltr = dynamic_cast<Selector*>(Widgets[i]))
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = Widgets.size();
			}
		}
	}
}

void UserInterface::SelectPrevious()
{
	bool found = false;

	for (int i = int(Widgets.size()) - 1; i >= 0; i--)
	{
		if (Selector* sltr = dynamic_cast<Selector*>(Widgets[i]))
		{
			if (found)
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = 0;
			}

			else if (sltr->IsSelected().GetDataActual())
			{
				found = true;
				sltr->SetSelected(false);
				sltr->SetChange(true);
			}
		}
	}

	if (found)
	{
		for (int i = int(Widgets.size()) - 1; i > 0; i--)
		{
			if (Selector* sltr = dynamic_cast<Selector*>(Widgets[i]))
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = 0;
			}
		}
	}
}