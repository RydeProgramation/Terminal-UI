#include "Header.h"

#include "MyUI.h"

#pragma comment(lib, "Terminal Engine.lib")

/*

SI JAMAIS IL Y A UNE ERREUR LNK 2019, c'est qu'il faut initialiser au moins une fois pour que se soit compiler dans Terminal Engine.lib
SI C'EST UN TEMPLATE IL NE FAUT PAS METTRE EN IMPORT/EXPORT CAR IL FAUT INITIAILISER POUR CHAQUE TYPE

*/

using namespace std;
using namespace UITools;

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	cout << WstringToUtf8(L"Clique sur F11, pour une meilleur experience (sans bug) 😊🎉") << endl << endl << endl;

	cout << WstringToUtf8(L"Ensuite clique sur n'importe quelle touche (entrée)") << endl;

	cin.ignore();

	MyUI UI;

	UI.Start();
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