#include "Header.h"

#include "MyUI.h"

using namespace std;
using namespace UITools;

// INI

MyUI::MyUI() : trUserInterface(1)
{

}

MyUI::~MyUI()
{

}

// CODE

void MyUI::Start()
{
	trUserInterface::Start();
	
	// ZONE DE TEST
	while (true)
	{
	}
	// FIN DE ZONE DE TEST

	vector<string> hello3;

	hello3.push_back(" _   _      _ _        __        __         _     _ _ "); // 54
	hello3.push_back("| | | | ___| | | ___   \\ \\      / /__  _ __| | __| | |"); // 54
	hello3.push_back("| |_| |/ _ \\ | |/ _ \\   \\ \\ /\\ / / _ \\| '__| |/ _` | |"); // 54
	hello3.push_back("|  _  |  __/ | | (_) |   \\ V  V / (_) | |  | | (_| |_|"); // 54
	hello3.push_back("|_| |_|\\___|_|_|\\___/     \\_/\\_/ \\___/|_|  |_|\\__,_(_)"); // 54

	vector<string> hello2;

	hello2.push_back(" _   _      _ _        __        __         _     _ "); // 52
	hello2.push_back("| | | | ___| | | ___   \\ \\      / /__  _ __| | __| |"); // 52
	hello2.push_back("| |_| |/ _ \\ | |/ _ \\   \\ \\ /\\ / / _ \\| '__| |/ _` |"); // 52
	hello2.push_back("|  _  |  __/ | | (_) |   \\ V  V / (_) | |  | | (_| |"); // 52
	hello2.push_back("|_| |_|\\___|_|_|\\___/     \\_/\\_/ \\___/|_|  |_|\\__,_|"); // 52

	vector<string> hello;

	hello.push_back(" _   _      _ _       "); // 22
	hello.push_back("| | | | ___| | | ___  "); // 22
	hello.push_back("| |_| |/ _ \\ | |/ _ \\ "); // 22
	hello.push_back("|  _  |  __/ | | (_) |"); // 22
	hello.push_back("|_| |_|\\___|_|_|\\___/ "); // 22

	string hello3_ = hello3[0] + hello3[1] + hello3[2] + hello3[3] + hello3[4];
	string hello_ = hello[0] + hello[1] + hello[2] + hello[3] + hello[4];
	string hello2_ = hello2[0] + hello2[1] + hello2[2] + hello2[3] + hello2[4];

	CreateWidgetWait(new trWidget(100, -1, 22, 5, MiddleCenter, hello_, "Hello"));

	for (int i = 0; i < 115; i++)
	{
		SetWidget("Hello", &trWidget::AddToPosition, -1, 0);

		Sleep(10);
	}

	Sleep(1500);

	DestroyWidget("Hello");

	CreateWidgetWait(new trWidget(0, -1, 52, 5, MiddleCenter, hello2_, "Hello2"));

	Sleep(20 * 100); 

	DestroyWidget("Hello2");

	CreateWidgetWait(new trWidget(1, -1, 54, 5, MiddleCenter, hello3_, "Hello3"));

	SetWidget("Hello3", &trWidget::SetColor, 11);


	Sleep(1000);

	for (int i = 0; i < 10; i++)
	{
		SetWidget("Hello3", &trWidget::AddToPosition, 0, 1);

		Sleep(50);
	}

	for (int i = 0; i < 5; i++)
	{
		SetWidget("Hello3", &trWidget::AddToSize, 0, -1);

		SetWidget("Hello3", &trWidget::AddToColor, 1);

		Sleep(50);
	}

	DestroyWidget("Hello3");

	string parag = "Salutations, brave aventurier ! Mon projet est une application magique qui ouvre les portes des marches financiers.\nA l'aide de la puissante technique de Monte-Carlo, je simule des trajectoire aleatoire pour les options (calls et puts).Imagine-toi chevauchant un dragon volant au-dessus des courbes de prix, scrutant les volatilites et les risques.\nLes prix d'options se revelent tels des tresors caches dans les profondeurs du marche. Que la chance soit avec toi !\nJe te propose donc cette application pour que tu fasses tes propres simulations et decouvres les secrets enfouis dans\nles volutes des courbes financieres.";

	// BUUG
	// BUUG --- EN gros le string parag contient des \n qui font que le texte saute la ligne et du coup fait écrire dans le terminal n'importe comment
	// BUUG

	trSize<int>* size_ = new trSize<int>(GetConsoleSize());

	CreateWidgetWait(new trWidget(0, 0, 120, 6, MiddleCenter, parag, "Paragraphe"));

	// Widgets[WidgetResearch("Paragraphe")]->delay_caractere = 25;

	Sleep(25 * parag.size());

	/*while (Widgets[WidgetResearch("Paragraphe")]->delay_caractere != 0)
	{
	}*/

	Sleep(3500);

	for (int i = 0; i < 6; i++)
	{
		/*Widgets[WidgetResearch("Paragraphe")]->new_size_y = Widgets[WidgetResearch("Paragraphe")]->size_y;

		Widgets[WidgetResearch("Paragraphe")]->new_size_y += -1;*/

		Sleep(800);
	}

	DestroyWidget("Paragraphe");

	Menu1();

	while (true)
	{ }
}

void MyUI::Menu1()
{
	/* vector<string> sim_cont;

	sim_cont.push_back(" ________       ___      _____ ______       ___  ___      ___           ________      _________    ___      ________      ________       ");
	sim_cont.push_back("|\\   ____\\     |\\  \\    |\\   _ \\  _   \\    |\\  \\|\\  \\    |\\  \\         |\\   __  \\    |\\___   ___\\ |\\  \\    |\\   __  \\    |\\   ___  \\     ");
	sim_cont.push_back("\\ \\  \\___|_    \\ \\  \\   \\ \\  \\\\\\__\\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\        \\ \\  \\|\\  \\   \\|___ \\  \\_| \\ \\  \\   \\ \\  \\|\\  \\   \\ \\  \\\\ \\  \\    ");
	sim_cont.push_back(" \\ \\_____  \\    \\ \\  \\   \\ \\  \\\\|__| \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\        \\ \\   __  \\       \\ \\  \\   \\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\\\ \\  \\   ");
	sim_cont.push_back("  \\|____|\\  \\    \\ \\  \\   \\ \\  \\    \\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\____    \\ \\  \\ \\  \\       \\ \\  \\   \\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\\\ \\  \\  ");
	sim_cont.push_back("    ____\\_\\  \\    \\ \\__\\   \\ \\__\\    \\ \\__\\   \\ \\_______\\   \\ \\_______\\   \\ \\__\\ \\__\\       \\ \\__\\   \\ \\__\\   \\ \\_______\\   \\ \\__\\\\ \\__\\ ");
	sim_cont.push_back("   |\\_________\\    \\|__|    \\|__|     \\|__|    \\|_______|    \\|_______|    \\|__|\\|__|        \\|__|    \\|__|    \\|_______|    \\|__| \\|__| ");
	sim_cont.push_back("   \\|_________|                                                                                                                          ");

	string sim_3d = sim_cont[0] + sim_cont[1] + sim_cont[2] + sim_cont[3] + sim_cont[4] + sim_cont[5] + sim_cont[6] + sim_cont[7];

	CreateWidget(CenterX(sim_cont[0].size()), 5, sim_cont[0].size(), 8, sim_3d, "Simulation");

	vector<string> SimCarlo;

	SimCarlo.push_back("  __  __                   _                ____                  _         ");
	SimCarlo.push_back(" |  \\/  |   ___    _ __   | |_    ___      / ___|   __ _   _ __  | |   ___  ");
	SimCarlo.push_back(" | |\\/| |  / _ \\  | '_ \\  | __|  / _ \\    | |      / _` | | '__| | |  / _ \\ ");
	SimCarlo.push_back(" | |  | | | (_) | | | | | | |_  |  __/    | |___  | (_| | | |    | | | (_) |");
	SimCarlo.push_back(" |_|  |_|  \\___/  |_| |_|  \\__|  \\___|     \\____|  \\__,_| |_|    |_|  \\___/  ");

	vector<string> Diff;

	Diff.push_back("  ____    _    __    __                 _                    ____                                ");
	Diff.push_back(" |  _ \\  (_)  / _|  / _|  _   _   ___  (_)   ___    _ __    / ___|  _   _   _ __  __   __   ___  ");
	Diff.push_back(" | | | | | | | |_  | |_  | | | | / __| | |  / _ \\  | '_ \\  | |     | | | | | '__| \\ \\ / /  / _ \\ ");
	Diff.push_back(" | |_| | | | |  _| |  _| | |_| | \\__ \\ | | | (_) | | | | | | |___  | |_| | | |     \\ V /  |  __/ ");
	Diff.push_back(" |____/  |_| |_|   |_|    \\__,_| |___/ |_|  \\___/  |_| |_|  \\____|  \\__,_| |_|      \\_/    \\___| ");

	string Diff_ = Diff[0] + Diff[1] + Diff[2] + Diff[3] + Diff[4];

	string SimCarlo_ = SimCarlo[0] + SimCarlo[1] + SimCarlo[2] + SimCarlo[3] + SimCarlo[4];

	CreateSelector(CenterX(SimCarlo[0].size()) / 2 - 20, 25, 76, 5, SimCarlo_, "SimCarlo");

	CreateSelector(200 - Diff[0].size(), 25, Diff[0].size(), 5, Diff_, "SimDiffusion");

	Selector* sltr = dynamic_cast<Selector*>(Widgets[WidgetResearch("SimCarlo")]);

	sltr->color_selected = 11;

	sltr = nullptr;

	sltr = dynamic_cast<Selector*>(Widgets[WidgetResearch("SimDiffusion")]);

	sltr->color_selected = 11;

	while (true)
	{

	} */
}

void MyUI::CreateWidgetWait(trWidget* WIDG)
{
	CreateWidget(WIDG);

	while (WIDG->GetChange().GetDataActual()) {}
}

