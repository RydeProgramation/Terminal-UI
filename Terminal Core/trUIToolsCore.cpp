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

std::wstring UIToolsCore::RemoveColor(const std::wstring& input)
{
	std::wstring result = input;
	size_t pos = 0;

	while ((pos = result.find(L"\x1B[", pos)) != std::wstring::npos)
	{
		// Trouver la fin de la séquence ansi, qui termine par 'm'
		size_t endPos = result.find(L'm', pos + 2);
		if (endPos == std::wstring::npos)
			break;  // Séquence incomplète, on stop

		// Effacer la séquence de pos à endPos inclus
		result.erase(pos, endPos - pos + 1);
		// Ne pas avancer pos, car on vient de modifier la string
	}

	return result;
}

inline void UIToolsCore::FastToWString(int value, std::wstring& out)
{
	out.clear();

	if (value < 0) {
		out += L'-';
		value = -value;
	}

	wchar_t temp[20];
	size_t i = 0;

	do {
		temp[i++] = L'0' + (value % 10);
		value /= 10;
	} while (value != 0);

	while (i-- > 0) {
		out += temp[i];
	}
}

void UIToolsCore::substrAnsiSafeUltraFast(
	const std::wstring& input,
	size_t startVisible,
	size_t countVisible,
	std::wstring& result
) {
	result.clear();
	result.reserve(countVisible + 16); // marge pour séquences ANSI

	// 🧠 Écrire en direct sur result
	size_t writeIndex = 0;
	size_t visibleCount = 0;
	bool inAnsi = false;

	for (size_t i = 0; i < input.size(); ++i) {
		wchar_t c = input[i];

		if (c == L'\033') {
			inAnsi = true;
		}

		if (inAnsi) {
			if (writeIndex >= result.size()) result.resize(writeIndex + 1);
			result[writeIndex++] = c;

			if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z')) {
				inAnsi = false;
			}
		}
		else {
			if (visibleCount >= startVisible && visibleCount < startVisible + countVisible) {
				if (writeIndex >= result.size()) result.resize(writeIndex + 1);
				result[writeIndex++] = c;
			}
			++visibleCount;

			if (visibleCount >= startVisible + countVisible) break;
		}
	}

	// Finalise la taille réelle
	result.resize(writeIndex);
}