#include "Header.h"

#include "MyUI.h"

#pragma comment(lib, "Terminal Engine.lib") // je crois inutile par ce queje le fait pas pour les autres dll

/*

SI JAMAIS IL Y A UNE ERREUR LNK 2019, c'est qu'il faut initialiser au moins une fois pour que se soit compiler dans Terminal Engine.lib
SI C'EST UN TEMPLATE IL NE FAUT PAS METTRE EN IMPORT/EXPORT CAR IL FAUT INITIAILISER POUR CHAQUE TYPE

*/

using namespace std;
using namespace UITools;

bool IsConsoleFocused() {
	HWND consoleWindow = GetConsoleWindow();
	HWND foregroundWindow = GetForegroundWindow();

	return consoleWindow != nullptr && consoleWindow == foregroundWindow;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	cout << WstringToUtf8(L"Clique sur F11, pour une meilleur experience (sans bug) 😊🎉") << endl << endl << endl;

	cout << WstringToUtf8(L"Ensuite clique sur n'importe quelle touche (entrée)") << endl;

/*
	while (true) {
		if (IsConsoleFocused()) {
			std::cout << "✅ CONSOLE FOCUS\n";
		}
		else {
			std::cout << "❌ PAS FOCUS\n";
		}

		Sleep(500); // évite de spammer le CPU
	}
*/

	cin.ignore();

	MyUI UI;

	UI.Start();

	// 👇 Boucle d'attente douce si jamais tout est fait sur UI::Start()
	while (true) {
		Sleep(10000); // 🔄 Laisse le CPU tranquille sans bloquer l'UI
	}
}

/*

  __  __                   _                ____                  _
 |  \/  |   ___    _ __   | |_    ___      / ___|   __ _   _ __  | |   ___
 | |\/| |  / _ \  | '_ \  | __|  / _ \    | |      / _` | | '__| | |  / _ \
 | |  | | | (_) | | | | | | |_  |  __/    | |___  | (_| | | |    | | | (_) |
 |_|  |_|  \___/  |_| |_|  \__|  \___|     \____|  \__,_| |_|    |_|  \___/

  ____    _    __    __                 _                    ____
 |  _ \  (_)  / _|  / _|  _   _   ___  (_)   ___    _ __    / ___|  _   _   _ __  __   __   ___
 | | | | | | | |_  | |_  | | | | / __| | |  / _ \  | '_ \  | |     | | | | | '__| \ \ / /  / _ \
 | |_| | | | |  _| |  _| | |_| | \__ \ | | | (_) | | | | | | |___  | |_| | | |     \ V /  |  __/
 |____/  |_| |_|   |_|    \__,_| |___/ |_|  \___/  |_| |_|  \____|  \__,_| |_|      \_/    \___|

 */