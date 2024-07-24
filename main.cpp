#include "Header.h"

#include "MyUI.h"

using namespace std;

int main()
{
	srand((unsigned)time(nullptr));

	cout << R"(Clique sur F11, pour une meilleur experience (sans bug) ;)" << endl << endl << endl;

	Sleep(1000);

	cout << R"(Ensuite clique sur n'importe quelle touche (entrée) \ )" << endl;

	cin.ignore();

	MyUI UI;

	UI.Start();

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