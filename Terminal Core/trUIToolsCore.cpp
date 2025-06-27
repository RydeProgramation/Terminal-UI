#include "trUIToolsCore.h"

using namespace std;

// UI tool CORE

trSize<uint16_t> UIToolsCore::GetConsoleSize(uint8_t BorderWitdh)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	uint16_t Conlumns = csbi.srWindow.Right - csbi.srWindow.Left + 1 - (BorderWitdh * 2) * 2;
	uint16_t Rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1 - (BorderWitdh * 2);

	return trSize<uint16_t>(Conlumns, Rows);
}

trSize<uint16_t> UIToolsCore::GetConsoleSize()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	uint16_t Conlumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	uint16_t Rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return trSize<uint16_t>(Conlumns, Rows);
}

bool UIToolsCore::IsMyWindowInFocus() // ne fonctionne pas si la console n'est pas au premier plan
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// CONSOLE_SCREEN_BUFFER_INFO csbi; bzr

	// return GetConsoleWindow() == GetForegroundWindow();

	// boite de dialogue d'erreur pour arreter l'appli si cette fonction est utilisé

	MessageBox(NULL, L"La fonction ne fonctionne jamais", L"Erreur", MB_OK | MB_ICONERROR);
	return false;
}

std::string UIToolsCore::WstringToUtf8(const std::wstring& wstr)
{
	// Calculer la taille nécessaire pour la chaîne UTF-8
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);

	// Convertir la chaîne wchar_t en UTF-8
	std::string utf8_str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8_str[0], size_needed, NULL, NULL);

	return utf8_str;
}

void UIToolsCore::SetColorConsole(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);
}

bool UIToolsCore::IsPureColor(const std::wstring& input) // code chatGPT
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