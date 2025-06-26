#include "trUITools.h"

using namespace std;

// UI tool

void UITools::MoveCursorTo(const trCoordinate<int>& Coordinate_, uint8_t BorderWitdh_)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PositionRelative = { static_cast<SHORT>(Coordinate_.GetX().GetDataActual() + (BorderWitdh_ * 2)), static_cast<SHORT>(Coordinate_.GetY().GetDataActual() + BorderWitdh_) };
	SetConsoleCursorPosition(hConsole, PositionRelative);
}

void UITools::MoveCursorTo(const trCoordinate<int>& Coordinate_)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PositionRelative = { static_cast<SHORT>(Coordinate_.GetX().GetDataActual()), static_cast<SHORT>(Coordinate_.GetY().GetDataActual()) };
	SetConsoleCursorPosition(hConsole, PositionRelative);
}

void UITools::hideCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);

	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

bool UITools::IsOutSide(const trCoordinate<int>& xy, uint8_t BorderWidth_)
{
	if (xy.GetY().GetDataActual() >= GetConsoleSize(BorderWidth_).GetSizeY().GetDataActual() || xy.GetX().GetDataActual() >= GetConsoleSize(BorderWidth_).GetSizeX().GetDataActual())
	{
		return true;
	}

	else if (xy.GetY().GetDataActual() <  0 || xy.GetX().GetDataActual() < 0)
	{
		return true;
	}

	return false;
}

bool UITools::IsOutSide(const trCoordinate<int>& xy, uint8_t BorderWidth_, bool CountTouch)
{
	if (CountTouch)
	{
		if (xy.GetY().GetDataActual() >= GetConsoleSize(BorderWidth_).GetSizeY().GetDataActual() || xy.GetX().GetDataActual() >= GetConsoleSize(BorderWidth_).GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (xy.GetY().GetDataActual() < 0 || xy.GetX().GetDataActual() < 0)
		{
			return true;
		}
	}

	else
	{
		if (xy.GetY().GetDataActual() >= GetConsoleSize(BorderWidth_).GetSizeY().GetDataActual() || xy.GetX().GetDataActual() > GetConsoleSize(BorderWidth_).GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (xy.GetY().GetDataActual() < 0 || xy.GetX().GetDataActual() < 0)
		{
			return true;
		}
	}

	return false;
}

bool UITools::IsOutSide(int z, uint8_t BorderWidth_, bool CountTouch)
{
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Le problème est que la distance z, ne pourra jamais être bien convertit en x et y car si le x est plus grans que la taille de la fenêtre ça va juste rajouter une ligne en plus et ce n'est pas ce que nous voulons",      // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
	);

	// Convertir l'indice 1D en coordonnées 2D
	int y = z / GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth_;  // Position verticale (y) 
	int x = z % GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth_ * 2;  // Position horizontale (x) 

	if (CountTouch)
	{
		if (y >= GetConsoleSize(BorderWidth_).GetSizeY().GetDataActual() || x >= GetConsoleSize(BorderWidth_).GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (y < 0 || x < 0)
		{
			return true;
		}
	}

	else
	{
		if (y >= GetConsoleSize(BorderWidth_).GetSizeY().GetDataActual() || x > GetConsoleSize(BorderWidth_).GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (y < 0 || x < 0)
		{
			return true;
		}
	}

	return false;
}

bool UITools::IsOutSide(int z, uint8_t BorderWidth_)
{
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Le problème est que la distance z, ne pourra jamais être bien convertit en x et y car si le x est plus grans que la taille de la fenêtre ça va juste rajouter une ligne en plus et ce n'est pas ce que nous voulons",      // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
	);

	// Convertir l'indice 1D en coordonnées 2D
	int y = z / GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth_;  // Position verticale (y) 
	int x = z % GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth_ * 2;  // Position horizontale (x) 

	if (y >= GetConsoleSize(BorderWidth_).GetSizeY().GetDataActual() || x >= GetConsoleSize(BorderWidth_).GetSizeX().GetDataActual())
	{
		return true;
	}

	else if (y < 0 || x < 0)
	{
		return true;
	}

	return false;
}

bool UITools::IsOutSide(const trCoordinate<int>& xy)
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

bool UITools::IsOutSide(const trCoordinate<int>& xy, bool CountTouch)
{
	if (CountTouch)
	{
		if (xy.GetY().GetDataActual() >= GetConsoleSize().GetSizeY().GetDataActual() || xy.GetX().GetDataActual() >= GetConsoleSize().GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (xy.GetY().GetDataActual() < 0 || xy.GetX().GetDataActual() < 0)
		{
			return true;
		}
	}

	else
	{
		if (xy.GetY().GetDataActual() >= GetConsoleSize().GetSizeY().GetDataActual() || xy.GetX().GetDataActual() > GetConsoleSize().GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (xy.GetY().GetDataActual() < 0 || xy.GetX().GetDataActual() < 0)
		{
			return true;
		}
	}

	return false;
}

bool UITools::IsOutSide(int z)
{
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Le problème est que la distance z, ne pourra jamais être bien convertit en x et y car si le x est plus grans que la taille de la fenêtre ça va juste rajouter une ligne en plus et ce n'est pas ce que nous voulons",      // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
	);

	// Convertir l'indice 1D en coordonnées 2D
	int x = z % GetConsoleSize().GetSizeX().GetDataActual();  // Position horizontale (x)
	int y = z / GetConsoleSize().GetSizeX().GetDataActual();  // Position verticale (y)

	if (y >= GetConsoleSize().GetSizeY().GetDataActual() || x >= GetConsoleSize().GetSizeX().GetDataActual())
	{
		return true;
	}

	else if (y < 0 || x < 0)
	{
		return true;
	}

	return false;
}

bool UITools::IsOutSide(int z, bool CountTouch)
{
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Le problème est que la distance z, ne pourra jamais être bien convertit en x et y car si le x est plus grans que la taille de la fenêtre ça va juste rajouter une ligne en plus et ce n'est pas ce que nous voulons",      // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
	);

	// Convertir l'indice 1D en coordonnées 2D
	int x = z % GetConsoleSize().GetSizeX().GetDataActual();  // Position horizontale (x)
	int y = z / GetConsoleSize().GetSizeX().GetDataActual();  // Position verticale (y)

	if (CountTouch)
	{
		if (y >= GetConsoleSize().GetSizeY().GetDataActual() || x >= GetConsoleSize().GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (y < 0 || x < 0)
		{
			return true;
		}
	}

	else
	{
		if (y >= GetConsoleSize().GetSizeY().GetDataActual() || x > GetConsoleSize().GetSizeX().GetDataActual())
		{
			return true;
		}

		else if (y < 0 || x < 0)
		{
			return true;
		}
	}

	return false;
}

bool UITools::IsInWidget(trWidget* WIDG, const trCoordinate<int>& crd) // a mettre dans UIToolsCore
{
	if (crd.GetX().GetDataActual() >= WIDG->GetAbsolutePosition().GetX().GetDataActual() && crd.GetX().GetDataActual() <= WIDG->GetAbsolutePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual())
	{
		if (crd.GetY().GetDataActual() >= WIDG->GetAbsolutePosition().GetY().GetDataActual() && crd.GetY().GetDataActual() <= WIDG->GetAbsolutePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual())
		{
			return true;
		}
	}

	return false;
}

