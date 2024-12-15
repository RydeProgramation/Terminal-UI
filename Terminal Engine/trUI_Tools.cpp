#include "trUI_Tools.h"

using namespace std;

// UI tool

bool UITools::IsOutSide(trCoordinate<int> xy, int BorderWidth)
{
	if (xy.GetY().GetDataActual() >= GetConsoleSize(BorderWidth).GetSizeY().GetDataActual() || xy.GetX().GetDataActual() >= GetConsoleSize(BorderWidth).GetSizeX().GetDataActual())
	{
		return true;
	}

	else if (xy.GetY().GetDataActual() <  0 || xy.GetX().GetDataActual() < 0)
	{
		return true;
	}

	return false;
}

bool UITools::IsOutSide(trCoordinate<int> xy)
{
	if (xy.GetY().GetDataActual() >= GetConsoleSize().GetSizeY().GetDataActual() || xy.GetX().GetDataActual() >= GetConsoleSize().GetSizeX().GetDataActual())
	{
		return true;
	}

	else if (xy.GetY().GetDataActual() < 0 || xy.GetX().GetDataActual() < 0)
	{
		return true;
	}

	return false;
}

void UITools::MoveCursorTo(trCoordinate<int> trCoordinate, int BorderWidth)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { static_cast<SHORT>(trCoordinate.GetX().GetDataActual() + (BorderWidth * 2)), static_cast<SHORT>(trCoordinate.GetY().GetDataActual() + BorderWidth) };
	SetConsoleCursorPosition(hConsole, Position);
}

void UITools::MoveCursorTo(trCoordinate<int> trCoordinate)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { static_cast<SHORT>(trCoordinate.GetX().GetDataActual()), static_cast<SHORT>(trCoordinate.GetY().GetDataActual()) };
	SetConsoleCursorPosition(hConsole, Position);
}

void UITools::hideCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);

	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

bool UITools::IsInWidget(trWidget* WIDG, trCoordinate<int> crd)
{
	if (crd.GetX().GetDataActual() >= WIDG->GetRelativePosition().GetX().GetDataActual() && crd.GetX().GetDataActual() <= WIDG->GetRelativePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual())
	{
		if (crd.GetY().GetDataActual() >= WIDG->GetRelativePosition().GetY().GetDataActual() && crd.GetY().GetDataActual() <= WIDG->GetRelativePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual())
		{
			return true;
		}
	}

	return false;
}

void UITools::SetColorConsole(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);
}

trSize<int> UITools::GetConsoleSize(int BorderWitdh)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	int Conlumns = csbi.srWindow.Right - csbi.srWindow.Left + 1 - (BorderWitdh * 2) * 2;
	int Rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1 - (BorderWitdh * 2);

	return trSize<int>(Conlumns, Rows);
}

trSize<int> UITools::GetConsoleSize()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	int Conlumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int Rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return trSize<int>(Conlumns, Rows);
}