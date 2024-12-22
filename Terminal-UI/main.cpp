#include "Header.h"

#include "MyUI.h"

using namespace std;
using namespace UITools;

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	srand((unsigned)time(nullptr));

	cout << WstringToUtf8(L"Clique sur F11, pour une meilleur experience (sans bug) 😊🎉") << endl << endl << endl;

	Sleep(1000);

	cout << WstringToUtf8(L"Ensuite clique sur n'importe quelle touche (entrée)") << endl;

	std::wstring text = L"\033[31m1234\033[0m"; // size 13
	std::wstring text2 = L"1234"; // size 4

	wostringstream test;
	test << text;

	cout << WstringToUtf8(text) << endl;
	cout << text.size() << endl;
	cout << text.length();

	cin.ignore();

	std::unique_ptr<MyUI> UI = std::make_unique<MyUI>();

	UI->Start();

	// C'est un thread perdu pourquoi pas faire qqchose ici

	while (true)
	{
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