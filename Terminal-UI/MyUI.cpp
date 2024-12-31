#include "Header.h"

#include "MyUI.h"

using namespace std;
using namespace UITools;

// INI

MyUI::MyUI() : trUserInterface(1, 6, L"\033[0m")
{

}

MyUI::~MyUI()
{

}

// test CHAT GPT

void hsvToRgb(float h, float s, float v, int& r, int& g, int& b) {
	float c = v * s;
	float x = static_cast<float>(c * (1 - fabs(fmod(h / 60.0, 2) - 1)));
	float m = v - c;

	float rPrime, gPrime, bPrime;
	if (h < 60) {
		rPrime = c; gPrime = x; bPrime = 0;
	}
	else if (h < 120) {
		rPrime = x; gPrime = c; bPrime = 0;
	}
	else if (h < 180) {
		rPrime = 0; gPrime = c; bPrime = x;
	}
	else if (h < 240) {
		rPrime = 0; gPrime = x; bPrime = c;
	}
	else if (h < 300) {
		rPrime = x; gPrime = 0; bPrime = c;
	}
	else {
		rPrime = c; gPrime = 0; bPrime = x;
	}

	r = static_cast<int>((rPrime + m) * 255);
	g = static_cast<int>((gPrime + m) * 255);
	b = static_cast<int>((bPrime + m) * 255);
}

// Fonction pour appliquer un dégradé arc-en-ciel avec décalage
wstring applyColorToText(const wstring& text, float offset) {
	wstring coloredText;
	float hueStep = 360.0f / text.size(); // Espace de teinte pour chaque caractère
	float hue = offset; // Démarrage de la teinte avec un décalage

	for (wchar_t c : text) {
		int r, g, b;
		hsvToRgb(fmod(hue, 360.0f), 1.0f, 1.0f, r, g, b); // Saturation et luminosité maximales

		// Construire la séquence de couleur ANSI
		wstring colorRgb = L"\033[38;2;" + to_wstring(r) + L";" + to_wstring(g) + L";" + to_wstring(b) + L"m";

		// Ajouter le caractère coloré
		coloredText += colorRgb + c;

		// Passer à la teinte suivante
		hue += hueStep;
	}

	// Réinitialiser les couleurs à la fin
	coloredText += L"\033[0m";

	return coloredText;
}

// CODE

void MyUI::Start()
{
	trUserInterface::Start();

	vector<wstring> hello3;

	/*hello3.push_back(L"\033[38;2;50;100;125m _   _      _ _        \033[38;2;50;100;150m__        __         _     _\033[38;2;50;100;255m _\n"); // 54
	hello3.push_back(L"\033[38;2;50;100;125m| | | | ___| | | ___   \033[38;2;50;100;150m\\ \\      / /__  _ __| | __| \033[38;2;50;100;255m| |"); // 54
	hello3.push_back(L"\033[38;2;50;100;125m| |_| |/ _ \\ | |/ _ \\\033[38;2;50;100;150m   \\ \\ /\\ / / _ \\| '__| |/ _` \033[38;2;50;100;255m| |"); // 54
	hello3.push_back(L"\033[38;2;50;100;125m|  _  |  __/ | | (_) | \033[38;2;50;100;150m  \\ V  V / (_) | |  | | (_| \033[38;2;50;100;255m|_|"); // 54
	hello3.push_back(L"\033[38;2;50;100;125m|_| |_|\\___|_|_|\\___/\033[38;2;50;100;150m     \\_/\\_/ \\___/|_|  |_|\\__,_\033[38;2;50;100;255m(_)"); // 54*/

	hello3.push_back(applyColorToText(L" _   _      _ _        __        __         _     _ _ ", 0)); // 54
	hello3.push_back(applyColorToText(L"| | | | ___| | | ___   \\ \\      / /__  _ __| | __| | |", 0)); // 54
	hello3.push_back(applyColorToText(L"| |_| |/ _ \\ | |/ _ \\   \\ \\ /\\ / / _ \\| '__| |/ _` | |", 0)); // 54
	hello3.push_back(applyColorToText(L"|  _  |  __/ | | (_) |   \\ V  V / (_) | |  | | (_| |_|", 0)); // 54
	hello3.push_back(applyColorToText(L"|_| |_|\\___|_|_|\\___/     \\_/\\_/ \\___/|_|  |_|\\__,_(_)", 0)); // 54

	vector<wstring> hello2;

	hello2.push_back(L" _   _      _ _        __        __         _     _\n"); // 52
	hello2.push_back(L"| | | | ___| | | ___   \\ \\      / /__  _ __| | __| |"); // 52
	hello2.push_back(L"| |_| |/ _ \\ | |/ _ \\   \\ \\ /\\ / / _ \\| '__| |/ _` |"); // 52
	hello2.push_back(L"|  _  |  __/ | | (_) |   \\ V  V / (_) | |  | | (_| |"); // 52
	hello2.push_back(L"|_| |_|\\___|_|_|\\___/     \\_/\\_/ \\___/|_|  |_|\\__,_|"); // 52

	vector<wstring> hello;

	hello.push_back(L" _   _      _ _\n"); // 22
	hello.push_back(L"| | | | ___| | | ___\n"); // 22
	hello.push_back(L"| |_| |/ _ \\ | |/ _ \\\n"); // 22
	hello.push_back(L"|  _  |  __/ | | (_) |"); // 22
	hello.push_back(L"|_| |_|\\___|_|_|\\___/\n"); // 22

	wstring hello3_ = hello3[0] + hello3[1] + hello3[2] + hello3[3] + hello3[4];
	wstring hello_ = hello[0] + hello[1] + hello[2] + hello[3] + hello[4];
	wstring hello2_ = hello2[0] + hello2[1] + hello2[2] + hello2[3] + hello2[4];

	CreateWidgetWait(new trWidget(100, -1, 22, 5, MiddleCenter, hello_, "Hello"));

	for (int i = 0; i < 115; i++)
	{
		SetWidget("Hello", &trWidget::AddToPosition, -1, 0);

		Sleep(10);
	}

	Sleep(1500);

	CreateWidgetWait(new trWidget(0, -1, 52, 5, MiddleCenter, hello2_, "Hello2"));

	DestroyWidget("Hello");

	Sleep(20 * 100); 

	CreateWidgetWait(new trWidget(1, -1, 54, 5, MiddleCenter, hello3_, "Hello3"));

	DestroyWidget("Hello2");
	
	int i = 0;

	for (int i = 0; i <= 500; i += 5)
	{
		i += 5;
		hello3.clear();

		hello3.push_back(applyColorToText(L" _   _      _ _        __        __         _     _ _ ", float(i))); // 54
		hello3.push_back(applyColorToText(L"| | | | ___| | | ___   \\ \\      / /__  _ __| | __| | |", float(i))); // 54
		hello3.push_back(applyColorToText(L"| |_| |/ _ \\ | |/ _ \\   \\ \\ /\\ / / _ \\| '__| |/ _` | |", float(i))); // 54
		hello3.push_back(applyColorToText(L"|  _  |  __/ | | (_) |   \\ V  V / (_) | |  | | (_| |_|", float(i))); // 54
		hello3.push_back(applyColorToText(L"|_| |_|\\___|_|_|\\___/     \\_/\\_/ \\___/|_|  |_|\\__,_(_)", float(i))); // 54

		hello3_ = hello3[0] + hello3[1] + hello3[2] + hello3[3] + hello3[4];

		SetWidget("Hello3", &trWidget::SetContent, hello3_);
	}

	for (int i = 0; i < 10; i++)
	{
		SetWidget("Hello3", &trWidget::AddToPosition, 0, 1);

		Sleep(50);
	}

	for (int i = 0; i < 5; i++)
	{
		SetWidget("Hello3", &trWidget::AddToSize, 0, -1);

		Sleep(50);
	}

	DestroyWidget("Hello3");

	wstring paragColor = L"\033[38;2;255;182;193mSalutations, brave lache\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bons, brave aventurier !\033[0m\033[38;2;176;224;230m Mon projet est une application maléfique\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\033[0m\033[38;2;152;251;152mapplication magique qui ouvre les portes des marchés financiers.\033[0m\nÀ l'aide de la puissante technique de \033[38;2;216;191;216mDiCaprio\b\b\b\b\b\b\b\bMonte-Carlo\033[0m, \033[38;2;240;230;140mje simule des trajectoires aléatoires\033[0m pour les options (calls et \033[38;2;250;235;215mputain\b\b\bs\033[0m).\n\033[38;2;255;222;173mImagine-toi chevauchant un dragon volant au-dessus des courbes de prix, scrutant les volatilités et les risques.\033[0m\nLes prix d'\033[38;2;255;228;196moptions\033[0m se révèlent tels des trésors cachés dans les profondeurs du marché. \033[38;2;240;255;255mQue la probabilités soit avec toi !\033[0m\n\033[38;2;245;222;179mJe te propose donc cette application pour que tu fasses tes propres simulations et découvre les secrets enfouis\033[0m dans\f\033[38;2;216;191;216mles volutes des courbes financières.\033[0m 🎉";

	trSize<int>* size_ = new trSize<int>(GetConsoleSize()); 

	CreateWidgetWait(new trWidget(0, 0, 123, 6, MiddleCenter, L"", "Paragraphe"));

	for (int i = 0; i < paragColor.size(); i++)
	{
		if (paragColor[i] == L'\033')
		{
			// Trouve la fin de la séquence ANSI (caractère 'm' à la fin)
			size_t endSeq = paragColor.find(L'm', i);

			if (endSeq != std::wstring::npos) {
				// On prend toute la séquence ANSI, en incluant le 'm'
				std::wstring ansiSeq = paragColor.substr(i, endSeq - i + 1);  // +1 pour inclure 'm'

				// On ajoute la séquence ANSI à l'interface
				SetWidget("Paragraphe", &trWidget::AddToContent, ansiSeq);

				// On saute l'indice de la séquence ANSI pour ne pas la traiter à nouveau
				i += static_cast<int>(ansiSeq.size() - 1); // -1 car on a déjà ajouté un caractère
			}
		}

		else
		{
			// Si ce n'est pas une séquence ANSI, on ajoute un seul caractère
			SetWidget("Paragraphe", &trWidget::AddToContent, wstring(1, paragColor[i]));
		}
		
		Sleep(35);
	}

	Sleep(2500);

	for (int i = 0; i < 6; i++)
	{
		SetWidget("Paragraphe", &trWidget::AddToSize, 0, -1);

		Sleep(250);
	}

	DestroyWidget("Paragraphe");

	Menu1();
}

void MyUI::Menu1()
{
	vector<wstring> sim_cont;

	sim_cont.push_back(L" ________       ___      _____ ______       ___  ___      ___           ________      _________    ___      ________      ________       ");
	sim_cont.push_back(L"|\\   ____\\     |\\  \\    |\\   _ \\  _   \\    |\\  \\|\\  \\    |\\  \\         |\\   __  \\    |\\___   ___\\ |\\  \\    |\\   __  \\    |\\   ___  \\     ");
	sim_cont.push_back(L"\\ \\  \\___|_    \\ \\  \\   \\ \\  \\\\\\__\\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\        \\ \\  \\|\\  \\   \\|___ \\  \\_| \\ \\  \\   \\ \\  \\|\\  \\   \\ \\  \\\\ \\  \\    ");
	sim_cont.push_back(L" \\ \\_____  \\    \\ \\  \\   \\ \\  \\\\|__| \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\        \\ \\   __  \\       \\ \\  \\   \\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\\\ \\  \\   ");
	sim_cont.push_back(L"  \\|____|\\  \\    \\ \\  \\   \\ \\  \\    \\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\____    \\ \\  \\ \\  \\       \\ \\  \\   \\ \\  \\   \\ \\  \\\\\\  \\   \\ \\  \\\\ \\  \\  ");
	sim_cont.push_back(L"    ____\\_\\  \\    \\ \\__\\   \\ \\__\\    \\ \\__\\   \\ \\_______\\   \\ \\_______\\   \\ \\__\\ \\__\\       \\ \\__\\   \\ \\__\\   \\ \\_______\\   \\ \\__\\\\ \\__\\ ");
	sim_cont.push_back(L"   |\\_________\\    \\|__|    \\|__|     \\|__|    \\|_______|    \\|_______|    \\|__|\\|__|        \\|__|    \\|__|    \\|_______|    \\|__| \\|__| ");
	sim_cont.push_back(L"   \\|_________|                                                                                                                          ");

	wstring sim_3d = sim_cont[0] + sim_cont[1] + sim_cont[2] + sim_cont[3] + sim_cont[4] + sim_cont[5] + sim_cont[6] + sim_cont[7];

	CreateWidgetWait(new trWidget(0, -10, static_cast<int>(sim_cont[0].size()), 8, MiddleCenter, sim_3d, "Simulation"));

	vector<wstring> SimCarlo;

	SimCarlo.push_back(L"  __  __                   _                ____                  _         ");
	SimCarlo.push_back(L" |  \\/  |   ___    _ __   | |_    ___      / ___|   __ _   _ __  | |   ___  ");
	SimCarlo.push_back(L" | |\\/| |  / _ \\  | '_ \\  | __|  / _ \\    | |      / _` | | '__| | |  / _ \\ ");
	SimCarlo.push_back(L" | |  | | | (_) | | | | | | |_  |  __/    | |___  | (_| | | |    | | | (_) |");
	SimCarlo.push_back(L" |_|  |_|  \\___/  |_| |_|  \\__|  \\___|     \\____|  \\__,_| |_|    |_|  \\___/  ");

	vector<wstring> Diff;

	Diff.push_back(L"  ____    _    __    __                 _                    ____                                ");
	Diff.push_back(L" |  _ \\  (_)  / _|  / _|  _   _   ___  (_)   ___    _ __    / ___|  _   _   _ __  __   __   ___  ");
	Diff.push_back(L" | | | | | | | |_  | |_  | | | | / __| | |  / _ \\  | '_ \\  | |     | | | | | '__| \\ \\ / /  / _ \\ ");
	Diff.push_back(L" | |_| | | | |  _| |  _| | |_| | \\__ \\ | | | (_) | | | | | | |___  | |_| | | |     \\ V /  |  __/ ");
	Diff.push_back(L" |____/  |_| |_|   |_|    \\__,_| |___/ |_|  \\___/  |_| |_|  \\____|  \\__,_| |_|      \\_/    \\___| ");

	wstring Diff_ = Diff[0] + Diff[1] + Diff[2] + Diff[3] + Diff[4];

	wstring SimCarlo_ = SimCarlo[0] + SimCarlo[1] + SimCarlo[2] + SimCarlo[3] + SimCarlo[4];

	CreateSelectorWait(new trSelector(-25, 5, static_cast<int>(SimCarlo[0].size()), 5, MiddleCenter, SimCarlo_, "SimCarlo"));

	// je vais tenter d'abord de pouvoir déplacer le bloc "SimCarlo" pour voir si mon trKeyBoardManagment fonctionne

	// ICI

	// CreateSelectorWait(new trSelector(25, 5, static_cast<int>(Diff[0].size()), 5, MiddleCenter, Diff_, "SimDiffusion"));

	while (true)
	{

	} 
}

void MyUI::CreateWidgetWait(trWidget* WIDG)
{
	CreateWidget(WIDG);

	while (WIDG->GetChange().GetDataActual()) {} // faire attention ici
}

void MyUI::CreateSelectorWait(trSelector* WIDG)
{
	CreateWidget(WIDG);

	while (WIDG->GetChange().GetDataActual()) {} // faire attention ici
}


