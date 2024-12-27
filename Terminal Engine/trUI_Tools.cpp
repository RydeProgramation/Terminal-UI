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

bool UITools::IsOutSide(trCoordinate<int> xy, int BorderWidth, bool CountTouch)
{
	if (CountTouch)
	{
		if (xy.GetY().GetDataActual() >= GetConsoleSize(BorderWidth).GetSizeY().GetDataActual() || xy.GetX().GetDataActual() >= GetConsoleSize(BorderWidth).GetSizeX().GetDataActual())
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
		if (xy.GetY().GetDataActual() >= GetConsoleSize(BorderWidth).GetSizeY().GetDataActual() || xy.GetX().GetDataActual() > GetConsoleSize(BorderWidth).GetSizeX().GetDataActual())
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

bool UITools::IsOutSide(int z, int BorderWidth)
{
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Le problème est que la distance z, ne pourra jamais être bien convertit en x et y car si le x est plus grans que la taille de la fenêtre ça va juste rajouter une ligne en plus et ce n'est pas ce que nous voulons",      // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
	);

	// Convertir l'indice 1D en coordonnées 2D
	int y = z / GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth ;  // Position verticale (y) 
	int x = z % GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth * 2;  // Position horizontale (x) 

	if (y >= GetConsoleSize(BorderWidth).GetSizeY().GetDataActual() || x >= GetConsoleSize(BorderWidth).GetSizeX().GetDataActual())
	{
		return true;
	}

	else if (y < 0 || x < 0)
	{
		return true;
	}

	return false;
}

bool UITools::IsOutSide(int z, int BorderWidth, bool CountTouch)
{
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Le problème est que la distance z, ne pourra jamais être bien convertit en x et y car si le x est plus grans que la taille de la fenêtre ça va juste rajouter une ligne en plus et ce n'est pas ce que nous voulons",      // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
	);

	// Convertir l'indice 1D en coordonnées 2D
	int y = z / GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth;  // Position verticale (y) 
	int x = z % GetConsoleSize().GetSizeX().GetDataActual() - BorderWidth * 2;  // Position horizontale (x) 

	if (CountTouch)
	{
		if (y >= GetConsoleSize(BorderWidth).GetSizeY().GetDataActual() || x >= GetConsoleSize(BorderWidth).GetSizeX().GetDataActual())
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
		if (y >= GetConsoleSize(BorderWidth).GetSizeY().GetDataActual() || x > GetConsoleSize(BorderWidth).GetSizeX().GetDataActual())
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

bool UITools::IsOutSide(trCoordinate<int> xy, bool CountTouch)
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

void UITools::MoveCursorTo(trCoordinate<int> trCoordinate, int BorderWidth)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PositionRelative = { static_cast<SHORT>(trCoordinate.GetX().GetDataActual() + (BorderWidth * 2)), static_cast<SHORT>(trCoordinate.GetY().GetDataActual() + BorderWidth) };
	SetConsoleCursorPosition(hConsole, PositionRelative);
}

void UITools::MoveCursorTo(trCoordinate<int> trCoordinate)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PositionRelative = { static_cast<SHORT>(trCoordinate.GetX().GetDataActual()), static_cast<SHORT>(trCoordinate.GetY().GetDataActual()) };
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

std::string UITools::WstringToUtf8(const std::wstring& wstr)
{
	// Calculer la taille nécessaire pour la chaîne UTF-8
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);

	// Convertir la chaîne wchar_t en UTF-8
	std::string utf8_str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8_str[0], size_needed, NULL, NULL);

	return utf8_str;
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

bool UITools::IsPureColor(const std::wstring& input) // code chatGPT
{
	size_t firstPos = input.find(L"\x1b"); // ou \033 c'est la meme

	if (firstPos == std::wstring::npos) 
	{
		// Pas de séquence \x1b dans la chaîne
		return false;
	}

	// Vérifie s'il y a une autre occurrence de \x1b après la première
	size_t secondPos = input.find(L"\x1b", firstPos + 1);

	if (secondPos != std::wstring::npos) 
	{
		// Plus d'une séquence \x1b trouvée
		return false;
	}

	// Vérifie que la séquence ANSI commence par \x1b[ et se termine par 'm'
	return bool(input.find(L"\x1b[") == firstPos && input.find(L"m") == input.size() - 1);
}