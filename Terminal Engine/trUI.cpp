#include "trUI.h"

// UI

using namespace std;
using namespace UITools;

// fnc

trUserInterface* CreateUserInterface()
{
	// return new trUserInterface(0);
	std::cerr << "NE PAS UTILISER";
	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Aucun RenderType ne correspond",  // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK           // Icône d'erreur + bouton OK
	);
	std::exit(1);
}

// INI default

trUserInterface::trUserInterface() : trUserInterface(RENDER_SYSTEM, 6, L"\033[0m")
{

}

// INI

trUserInterface::trUserInterface(uint8_t RenderType_, int BordW_, wstring RstClr) : SizeWindow(new trSize<uint16_t>(0, 0)), CursorSelector(new trData<int>(0)), Mutex(new std::mutex), KB(new trKeyBoardManagement()), Actors(new std::unordered_map<std::string, trActor*>()), Render_(new std::wostringstream()), RenderColor_(new std::wostringstream()), Thr_UI(new std::thread()), Thr_KB(new std::thread()), BorderWidth(BordW_), BaseColor(new wstring(RstClr))
{
	switch (RenderType_)
	{
	case DIRECT_TERMINAL:
		RenderType = RenderType_;
		break;
	case RENDER_SYSTEM:
		RenderType = RenderType_;
		break;
	default:
		MessageBox(
			NULL,
			L"Aucun RenderType ne correspond",
			L"Erreur",
			MB_ICONERROR | MB_OK
		);
		std::exit(1);
	}
}

// INI deep copy

trUserInterface::trUserInterface(const trUserInterface& other) : SizeWindow(new trSize<uint16_t>(*other.SizeWindow)), CursorSelector(new trData<int>(*other.CursorSelector)), Mutex(new std::mutex), KB(new trKeyBoardManagement()), Actors(new std::unordered_map<std::string, trActor*>(*other.Actors)), Render_(new std::wostringstream()), RenderColor_(new std::wostringstream()), Thr_UI(new std::thread()), Thr_KB(new std::thread()), BorderWidth(other.BorderWidth), RenderType(other.RenderType), BaseColor(new wstring(*other.BaseColor))
{

}

// Copy

trUserInterface& trUserInterface::operator=(const trUserInterface& other)
{
	if (this == &other) { return *this; }

	if (SizeWindow == nullptr) {
		SizeWindow = new trSize<uint16_t>(*other.SizeWindow);
	}
	else {
		*SizeWindow = *other.SizeWindow;
	}

	if (CursorSelector == nullptr) {
		CursorSelector = new trData<int>(*other.CursorSelector);
	}
	else {
		*CursorSelector = *other.CursorSelector;
	}

	if (Mutex == nullptr) {
		Mutex = new std::mutex();
	}
	else {
		// Mutex ne peut pas être copié, donc on le laisse tel quel
	}

	if (KB == nullptr) {
		KB = new trKeyBoardManagement();
	}
	else {
		*KB = *other.KB;
	}

	if (Actors == nullptr) {
		Actors = new std::unordered_map<std::string, trActor*>(*other.Actors);
	}
	else {
		*Actors = *other.Actors;
	}

	if (Render_ == nullptr) {
		Render_ = new std::wostringstream();
	}
	else {
		Render_->str(L""); // Vide le contenu de l'ostringstream
	}

	if (RenderColor_ == nullptr) {
		RenderColor_ = new std::wostringstream();
	}
	else {
		RenderColor_->str(L""); // Vide le contenu de l'ostringstream
	}

	if (Thr_UI == nullptr) {
		Thr_UI = new std::thread();
	}
	else {
		// Le thread ne peut pas être copié, donc on le laisse tel quel
	}

	if (Thr_KB == nullptr) {
		Thr_KB = new std::thread();
	}
	else {
		// Le thread ne peut pas être copié, donc on le laisse tel quel
	}

	if (BaseColor == nullptr) {
		BaseColor = new wstring(*other.BaseColor);
	}
	else {
		*BaseColor = *other.BaseColor;
	}

	RenderType = other.RenderType;

	return *this;
}

// FNC

void trUserInterface::Start()
{
	SetupConsole();

	timeBeginPeriod(2);  // Demande timer à résolution 1 ms

	Thr_UI = new std::thread([this]() { this->Loop(); });
	Thr_KB = new std::thread([this]() { this->KB->Start(); });
}

void trUserInterface::Update()
{
	std::lock_guard<std::mutex> lock(*Mutex); // <<-- A voir pourquoi quand on l'enlève ça crée des prblms

	SizeWindow->SetSize(GetConsoleSize().GetSizeX().GetDataActual(), GetConsoleSize().GetSizeY().GetDataActual());
	SizeWindow->Update();

	if (RefreshVerification()) 
	{
		Refresh();
	}

	KB->Update();
	
	UpdateActors();

	for (auto& widg : *Actors)
	{
		trWidget* widgetPtr = dynamic_cast<trWidget*>(widg.second);
		if (!widgetPtr) continue; // Passe au suivant si ce n'est pas un trWidget

		if (!widg.second->GetActivate().GetDataActual())
		{
			HideWidget(widgetPtr);
		}

		else if (widg.second->GetActivate().GetDataActual() && widg.second->GetChange().GetDataActual())
		{
			DisplayWidget(widgetPtr);
		}
	}

	if (RenderType == RENDER_SYSTEM)
	{
		Render();
	}

	/// Gerer les destruction a ce moment plutot que dans le thread de l'UI (car sinon ça fait des bugs de mutex et de destruction de thread)

	Destroy();

	Refreshed = false;
}

void trUserInterface::Refresh()
{
	Render_->clear();
	RenderColor_->clear();

	Refreshed = true;
	ForceRefresh = false;

	Border();

	for (auto& widg : *Actors)
	{
		widg.second->SetChange(true);
	}

	hideCursor();
}

bool trUserInterface::RefreshVerification()
{
	return (SizeWindow->GetSizeX().GetDataActual() != SizeWindow->GetSizeX().GetDataOld() || SizeWindow->GetSizeY().GetDataActual() != SizeWindow->GetSizeY().GetDataOld() || ForceRefresh) ? true : false;
}

void trUserInterface::Border()
{
	if (RenderType == DIRECT_TERMINAL)
	{
		MoveCursorTo(trCoordinate<int>(0, 0));

		std::ostringstream output;

		string topBottomBorder(SizeWindow->GetSizeX().GetDataActual() * BorderWidth, '*');
		string sideBorder(BorderWidth * 2, '*');
		string emptyLine(SizeWindow->GetSizeX().GetDataActual() - BorderWidth * 4, ' ');

		output << topBottomBorder;

		string middleLine = sideBorder + emptyLine + sideBorder;
		for (int i = BorderWidth; i < SizeWindow->GetSizeY().GetDataActual() - BorderWidth; ++i)
		{
			output << middleLine;
		}

		output << topBottomBorder;

		SetColorConsole(15);

		cout << output.str();

		MoveCursorTo(trCoordinate<int>(0, 0));
	}

	else if (RenderType == RENDER_SYSTEM)
	{
		MoveCursorToOstream(trCoordinate<int>(0, 0), Render_, *SizeWindow);

		wstring topBottomBorder(SizeWindow->GetSizeX().GetDataActual() * BorderWidth, '*');
		wstring sideBorder(BorderWidth * 2, '*');
		wstring emptyLine(max(SizeWindow->GetSizeX().GetDataActual() - BorderWidth * 4, 0), ' ');

		(*Render_) << topBottomBorder;

		wstring middleLine = sideBorder + emptyLine + sideBorder;

		for (int i = BorderWidth; i < SizeWindow->GetSizeY().GetDataActual() - BorderWidth; ++i)
		{
			(*Render_) << middleLine;
		}

		(*Render_) << topBottomBorder;

		CleanOstreamSize(Render_, *SizeWindow);
	}
}

void trUserInterface::SetupConsole()
{
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleCP(CP_UTF8);

	CursorSelector = 0;

	hideCursor();

	SizeWindow->SetSize(GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), GetConsoleSize(BorderWidth).GetSizeY().GetDataActual());
	SizeWindow->Update();

	KB->CreateBTN(trBTN_Key(VK_LEFT, OnRelease, PressToTrigger, bind(&trUserInterface::SelectPrevious, this), this));
	KB->CreateBTN(trBTN_Key(VK_RIGHT, OnRelease, PressToTrigger, bind(&trUserInterface::SelectNext, this), this));
}

/// SELECTION ///

void trUserInterface::Select(const string& name)
{
	for (auto& widg : *Actors)
	{
		if (trSelector* sltr = dynamic_cast<trSelector*>(widg.second))
		{
			sltr->SetSelected(sltr->trWidget::GetName().GetDataActual() == name);
			sltr->trWidget::SetChange(true);
		}
	}
}

void trUserInterface::SelectNext() // <-- a refaire en entier (car pas optimiser + non-utilisation de vector)
{
	// std::lock_guard<std::mutex> lock(*Mutex); ça fait crash, par ce que le lock est appeler dnas un meme lock

	cout << "droite";

	/*bool found = false;

	for (auto& widg : Actors)
	{
		if (trSelector* sltr = dynamic_cast<trSelector*>(widg.second))
		{
			if (found)
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = Actors.size();
			}

			else if (sltr->IsSelected().GetDataActual())
			{
				found = true;
				sltr->SetSelected(false);
				sltr->SetChange(true);
			}
		}
	}

	if (found)
	{
		for (size_t i = 0; i < Actors.size(); i++)
		{
			if (trSelector* sltr = dynamic_cast<trSelector*>(Actors[i]))
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = Actors.size();
			}
		}
	}*/
}

void trUserInterface::SelectPrevious() // <-- a refaire en entier (car pas optimiser + non-utilisation de vector)
{
	// std::lock_guard<std::mutex> lock(*Mutex); ça fait crash, par ce que le lock est appeler dnas un meme lock

	cout << "gauche";

	/*bool found = false;

	for (int i = int(Actors.size()) - 1; i >= 0; i--)
	{
		if (trSelector* sltr = dynamic_cast<trSelector*>(Actors[i]))
		{
			if (found)
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = 0;
			}

			else if (sltr->IsSelected().GetDataActual())
			{
				found = true;
				sltr->SetSelected(false);
				sltr->SetChange(true);
			}
		}
	}

	if (found)
	{
		for (int i = int(Actors.size()) - 1; i > 0; i--)
		{
			if (trSelector* sltr = dynamic_cast<trSelector*>(Actors[i]))
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = 0;
			}
		}
	}*/
}

/// WIDGET MANG ///

bool trUserInterface::CreateActor(trActor* WIDG)
{
	std::lock_guard<std::mutex> lock(*Mutex); // des fois abort()

	if (Actors->find(WIDG->GetName().GetDataActual()) == Actors->end())
	{
		(*Actors)[WIDG->GetName().GetDataActual()] = WIDG;
		WIDG->Init();
	}

	else
	{
		MessageBox(
			NULL,                           // Pas de fenêtre parente
			L"Widget already created",      // Message
			L"Erreur",                      // Titre de la boîte
			MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
		);
		return false;
	}

	return true;
}

bool trUserInterface::DestroyActor(trActor* WIDG)
{
	WIDG->SetDestroy(true);

	return true; 
}

bool trUserInterface::DestroyActor(const string& name) // VERIF SI BUG
{
	// Ne pas mettre de mutex ici

	if ((*Actors)[name])
	{
		return DestroyActor((*Actors)[name]);
	}

	MessageBox(
		NULL,
		L"Widget Not found for destroying",
		L"Erreur",
		MB_ICONERROR | MB_OK 
	);

	return false;
}

bool trUserInterface::Destroy()
{
	for (auto it = Actors->begin(); it != Actors->end(); )
	{
		if (it->second->GetDestroy().GetDataActual())
		{
			delete it->second;          // supprime l'objet pointé
			it = Actors->erase(it);   // efface et récupère l'itérateur valide suivant
			ForceRefresh = true;
		}
		else
		{
			++it;
		}
	}

	return true; // Retourne true si tous les widgets ont été détruits avec succès
}

const trActor trUserInterface::GetActor(const string& Name) const
{
	auto it = Actors->find(Name);

	if (it != Actors->end())
	{
		return *(it->second);
	}

	else
	{
		MessageBox(
			NULL,
			L"Widget Not found",
			L"Warning",
			MB_ICONERROR | MB_OK
		);

		return trActor::EmptyActor; // Retourne un actor vide

		// return trWidget::EmptyWidget(); // Retourne le widget vide
		
		// faurda changer en actor

		// return trActor(0, 0, MiddleCenter, L""); // Retourne un actor vide
	}
}

// Protected 

trActor* trUserInterface::GetPtrActor(const std::string& Name) const
{
	auto it = Actors->find(Name);

	if (it != Actors->end())
	{
		return (it->second);
	}

	else
	{
		MessageBox(
			NULL,
			L"Widget Not found",
			L"Warning",
			MB_ICONERROR | MB_OK
		);

		return nullptr; // Retourne le widget vide
	}
}

// private FNC

void trUserInterface::DisplayWidget(trWidget* WIDG)
{
	///

	/// je pense que je peut deja optimiser par juste crée des appel pour éviter d'appeler 50 000 fois une fonction inutilement

	///

	// améliorer pour direct_terminal a voir quoi faire
	if (RenderType == DIRECT_TERMINAL)
	{
		CleanWidget(WIDG);

		std::wostringstream output;

		int col = 0;

		for (int ln = WIDG->GetAbsolutePosition().GetY().GetDataActual(); ln < WIDG->GetAbsolutePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual(); ln++)
		{
			output << WIDG->GetContent().GetDataActual().substr(min(col, WIDG->GetContent().GetDataActual().size() - 1), WIDG->GetSize().GetSizeX().GetDataActual() - max(WIDG->GetAbsolutePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0));

			MoveCursorTo(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataActual(), ln), BorderWidth);

			if (!IsOutSide(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataActual(), ln), BorderWidth))
			{
				WIDG->Display(output);
			}

			output.str(L"");

			col += WIDG->GetSize().GetSizeX().GetDataActual();
		}

		WIDG->SetChange(false);
	}

	else if (RenderType == RENDER_SYSTEM)
	{
		if (!Refreshed)
		{
			CleanWidget(WIDG);
		}

		std::wostringstream output;

		int col = 0;

		std::vector<trPair<std::wstring, trCoordinate<int>>> rstColortemp;

		for (int ln = WIDG->GetAbsolutePosition().GetY().GetDataActual(); ln < WIDG->GetAbsolutePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual(); ln++)
		{
			output << WIDG->GetContent().GetDataActual().substr(min(col, WIDG->GetContent().GetDataActual().size()), WIDG->GetSize().GetSizeX().GetDataActual() - max(WIDG->GetAbsolutePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0));

			if (!IsOutSide(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataActual(), ln), BorderWidth))
			{
				MoveCursorToOstream(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataActual(), ln), Render_, *SizeWindow, BorderWidth);

				// PROTOTYPE COULEUR

				rstColortemp.push_back(trPair<wstring, trCoordinate<int>>(L"\033[0m" + *BaseColor, trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataActual() + static_cast<int>(output.str().size()), ln)));

				// fin PROTOTYPE COULEUR

				*Render_ << output.str();
			}

			output.str(L"");

			col += WIDG->GetSize().GetSizeX().GetDataActual();
		}

		WIDG->SetResetColor(rstColortemp);

		WIDG->SetChange(false);
	}
}

void trUserInterface::DisplayColor()
{
	///

	/// je pense que je peut deja optimiser par juste crée des appel pour éviter d'appeler 50 000 fois une fonction inutilement

	///

	std::map<int, wstring> Color;

	for (auto& it : *Actors)
	{
		trWidget* widgetPtr = dynamic_cast<trWidget*>(it.second);
		if (!widgetPtr) continue; // Passe au suivant si ce n'est pas un trWidget

		for (auto& it_ : widgetPtr->GetColoredContent().GetDataActual())
		{
			// La condition en dessous est juste watafak, pourquoi ça marche (je sais pas)... Mais est-ce ça marche ? (Du tonnerre, enfaite pas de fou)
			if (!IsOutSide(*it_.second->second, BorderWidth, false) && !IsOutSide(trCoordinate<int>(it_.second->second->GetY().GetDataActual() + widgetPtr->GetAbsolutePosition().GetY().GetDataActual(), it_.second->second->GetY().GetDataActual() + widgetPtr->GetAbsolutePosition().GetY().GetDataActual()), BorderWidth, false))
			{
				if (it_.second->second->GetY().GetDataActual() + widgetPtr->GetAbsolutePosition().GetY().GetDataActual() < widgetPtr->GetSize().GetSizeY().GetDataActual() + widgetPtr->GetAbsolutePosition().GetY().GetDataActual()) // verifier si la couelur n'est pas en dehors du widget en taille
				{
					MoveCursorToOstream(trCoordinate<int>(it_.second->second->GetX().GetDataActual() + widgetPtr->GetAbsolutePosition().GetX().GetDataActual(), it_.second->second->GetY().GetDataActual() + widgetPtr->GetAbsolutePosition().GetY().GetDataActual()), Render_, *SizeWindow, BorderWidth);
					Color[static_cast<int>(Render_->tellp())] = *it_.second->first;
				}
			}
		}

		for (auto& it_ : widgetPtr->GetResetColor())
		{
			if (!IsOutSide(*it_.second, BorderWidth, false))
			{
				MoveCursorToOstream(*it_.second, Render_, *SizeWindow, BorderWidth);
				Color[static_cast<int>(Render_->tellp())] = *it_.first;
			}
		}
	}

	for (auto it = Color.rbegin(); it != Color.rend(); ++it)
	{
		if (it->first <= RenderColor_->str().size())
		{
			RenderColor_->str(RenderColor_->str().insert(it->first, it->second));
		}
	}

	// reset les color a la fin de la ligne
	RenderColor_->str(RenderColor_->str().insert(0, L"\033[0m" + *BaseColor));
}

void trUserInterface::HideWidget(trWidget* WIDG) // < ----- BUUUG
{
	/*for (int ln = min(WIDG->GetAbsolutePosition().GetY().GetDataActual(), WIDG->GetAbsolutePosition().GetY().GetDataOld()); ln < max(WIDG->GetAbsolutePosition().GetY().GetDataActual(), WIDG->GetAbsolutePosition().GetY().GetDataOld()) + max(WIDG->GetSize().GetSizeY().GetDataOld(), WIDG->GetSize().GetSizeY().GetDataActual()); ln++)
	{
		for (int i = min(WIDG->GetAbsolutePosition().GetX().GetDataActual(), WIDG->GetAbsolutePosition().GetX().GetDataOld()); i < max(WIDG->GetAbsolutePosition().GetX().GetDataActual(), WIDG->GetAbsolutePosition().GetX().GetDataOld()) + max(WIDG->GetSize().GetSizeX().GetDataOld(), WIDG->GetSize().GetSizeX().GetDataActual()); i++)
		{
			if (IsOutSide(trCoordinate<int>(i, ln), false))
			{
				continue; // <-- pas sur (chatgpt)
			}

			MoveCursorTo(trCoordinate<int>(ln, i), BorderWidth);
			cout << " ";
		}
	}*/

	CleanWidget(WIDG);

	throw std::out_of_range("code pas fait (utiliser cleanwidget ?)"); // jsp pas pk ln'utilise out of range ;(((((((((((((((((
}

void trUserInterface::CleanWidget(trWidget* WIDG)
{
	if (RenderType == DIRECT_TERMINAL)
	{
		for (int ln = WIDG->GetAbsolutePosition().GetY().GetDataOld(); ln <= WIDG->GetAbsolutePosition().GetY().GetDataOld() + WIDG->GetSize().GetSizeY().GetDataOld(); ln++)
		{
			if (!IsOutSide(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataOld(), ln), BorderWidth))
			{
				SetColorConsole(15);
				wstring clean(WIDG->GetSize().GetSizeX().GetDataOld() - max(WIDG->GetAbsolutePosition().GetX().GetDataOld() + WIDG->GetSize().GetSizeX().GetDataOld() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0), ' ');
				MoveCursorTo(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataOld(), ln), BorderWidth);
				cout << WstringToUtf8(clean);
			}
		}
	}

	else if (RenderType == RENDER_SYSTEM)
	{
		for (int ln = WIDG->GetAbsolutePosition().GetY().GetDataOld(); ln <= WIDG->GetAbsolutePosition().GetY().GetDataOld() + WIDG->GetSize().GetSizeY().GetDataOld(); ln++)
		{
			if (!IsOutSide(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataOld(), ln), BorderWidth))
			{
				wstring clean(WIDG->GetSize().GetSizeX().GetDataOld() - max((WIDG->GetAbsolutePosition().GetX().GetDataOld() + WIDG->GetSize().GetSizeX().GetDataOld() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual()), 0), ' ');
				MoveCursorToOstream(trCoordinate<int>(WIDG->GetAbsolutePosition().GetX().GetDataOld(), ln), Render_, *SizeWindow, BorderWidth);
				*Render_ << clean;
			}
		}
	}
}

void trUserInterface::UpdateActors()
{
	for (auto& widg : *Actors)
	{
		widg.second->APPLY(GetConsoleSize(BorderWidth));
	}
}

void trUserInterface::Loop()
{
	while (true)
	{
		Update();
	}
}

void trUserInterface::Render()
{
	// PROTOTYPE COULEUR qui marche tres bien (a voir si on peut l'optimiser) ou le mettre de façon definitive

	RenderColor_->str(Render_->str());

	DisplayColor(); // il faut optimiser

	// fin PROTOTYPE COULEUR

	MoveCursorTo(trCoordinate<int>(0, 0));

	string temp = WstringToUtf8(RenderColor_->str());

	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	std::print("{}", temp); // ici il faut optimiser
}

// Fonciton utilise (à deplacer dans trUiTools je pense)

void trUserInterface::MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* output, const trSize<uint16_t>& SizeOutput)
{
	output->seekp(Pos.GetX().GetDataActual() + Pos.GetY().GetDataActual() * SizeOutput.GetSizeX().GetDataActual());
}

void trUserInterface::MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* output, const trSize<uint16_t>& SizeOutput, uint8_t BorderW)
{
	int adjustedX = Pos.GetX().GetDataActual() + (BorderW * 2);
	int adjustedY = Pos.GetY().GetDataActual() + BorderW;

	int position = adjustedX + adjustedY * SizeOutput.GetSizeX().GetDataActual();

	output->seekp(position);
}

void trUserInterface::CleanOstreamSize(std::wostringstream* output, const trSize<uint16_t>& SizeOutput)
{
	output->str(output->str().substr(0, SizeOutput.GetSizeX().GetDataActual() * SizeOutput.GetSizeY().GetDataActual()));
}

// DESTRUCTEUR

trUserInterface::~trUserInterface()
{
	delete KB;

	delete Mutex;

	delete Actors;

	delete Thr_UI;

	delete Thr_KB;

	delete SizeWindow;

	delete CursorSelector;

	delete Render_;

	delete RenderColor_;

	delete BaseColor;

	timeEndPeriod(1);    // Libère la résolution demandée
}