#include "trUI.h"

// UI

using namespace std;
using namespace UITools;

// fnc

trUserInterface* CreateUserInterface()
{
	return new trUserInterface(0);
	std::cerr << "NE PAS UTILISER";
	std::exit(1);
}

// INI

trUserInterface::trUserInterface(int RenderType_) : SizeWindow(new trSize((0), int(0))), CursorSelector(new trData(int(0))), BorderWidth(int(5)), mtx(new std::mutex), KB(new trKeyBoardManagement()), Widgets(new std::unordered_map<std::string, trWidget*>()), Render_(new std::wostringstream()), T(new std::thread()), T2(new std::thread())
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
			NULL,                           // Pas de fenêtre parente
			L"Aucun RenderType ne correspond",  // Message
			L"Erreur",                      // Titre de la boîte
			MB_ICONERROR | MB_OK           // Icône d'erreur + bouton OK
		);
		std::exit(1);
	}
}

// CODE

void trUserInterface::Start()
{
	SetupConsole();

	T = new std::thread([this]() { this->Loop(); });
	T2 = new std::thread([this]() { this->KB->Start(); });
}

void trUserInterface::Update()
{
	SizeWindow->SetSize(GetConsoleSize().GetSizeX().GetDataActual(), GetConsoleSize().GetSizeY().GetDataActual());
	SizeWindow->Update();

	std::lock_guard<std::mutex> lock(*mtx); // je sais pas si ça sert vrm mddrrrr

	if (RefreshVerification()) 
	{
		Refresh();
	}
	
	UpdateWidget();

	for (auto& widg : *Widgets)
	{

		if (!widg.second->GetActivate().GetDataActual())
		{
			HideWidget(widg.second);
		}

		else if (widg.second->GetActivate().GetDataActual() && widg.second->GetChange().GetDataActual())
		{
			DisplayWidget(widg.second);
		}
	}

	if (RenderType == RENDER_SYSTEM)
	{
		Render();
	}

	KB->ActionBTN(); // a voir lors du changement pour le traitement du clavier et souris
}

void trUserInterface::Refresh()
{
	Render_->clear();

	Border();

	for (auto& widg : *Widgets)
	{
		widg.second->SetChange(true);
	}

	hideCursor();
}

bool trUserInterface::RefreshVerification()
{
	return (SizeWindow->GetSizeX().GetDataActual() != SizeWindow->GetSizeX().GetDataOld() || SizeWindow->GetSizeY().GetDataActual() != SizeWindow->GetSizeY().GetDataOld()) ? true : false;
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
	MoveCursorTo(trCoordinate<int>(0, 0));

	cout << WstringToUtf8(Render_->str());
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
		wstring emptyLine(SizeWindow->GetSizeX().GetDataActual() - BorderWidth * 4, ' ');

 		(*Render_) << topBottomBorder;

		wstring middleLine = sideBorder + emptyLine + sideBorder;

		for (int i = BorderWidth; i < SizeWindow->GetSizeY().GetDataActual() - BorderWidth; ++i) 
        {
			(*Render_) << middleLine;
		}

 		(*Render_) << topBottomBorder;

 		SetColorConsole(12); // DE BASE 15 pour blanc

		CleanOstreamSize(Render_, *SizeWindow);
	}
}

void trUserInterface::SetupConsole()
{
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleCP(CP_UTF8);

	BorderWidth = 6;

	CursorSelector = 0;

	hideCursor();

	SizeWindow->SetSize(GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), GetConsoleSize(BorderWidth).GetSizeY().GetDataActual());
	SizeWindow->Update();

	KB->CreateBTN(new trBTN_Key(VK_LEFT, bind(&trUserInterface::SelectPrevious, this)));
	KB->CreateBTN(new trBTN_Key(VK_RIGHT, bind(&trUserInterface::SelectNext, this)));
}

bool trUserInterface::CreateWidget(trWidget* WIDG)
{
	std::lock_guard<std::mutex> lock(*mtx);

	if (Widgets->find(WIDG->GetName().GetDataActual()) == Widgets->end())
	{
		(*Widgets)[WIDG->GetName().GetDataActual()] = WIDG;
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

bool trUserInterface::DestroyWidget(trWidget* WIDG)
{
	std::lock_guard<std::mutex> lock(*mtx);

	CleanWidget(WIDG);

	Widgets->erase(WIDG->GetName().GetDataActual());

	delete WIDG;

	return false;
}

bool trUserInterface::DestroyWidget(const string& name) // VERIF SI BUG
{
	std::lock_guard<std::mutex> lock(*mtx);

	if ((*Widgets)[name])
	{
		CleanWidget((*Widgets)[name]);

		delete (*Widgets)[name];

		Widgets->erase(name);

		return true;
	}

	// throw std::out_of_range("ERROR N'EXISTE PAS");

	MessageBox(
		NULL,                           // Pas de fenêtre parente
		L"Widget Not found for destroying",  // Message
		L"Erreur",                      // Titre de la boîte
		MB_ICONERROR | MB_OK           // Icône d'erreur + bouton OK
	);

	return false;
}

const trWidget trUserInterface::GetWidget(const string& Name) const
{	
	auto it = Widgets->find(Name);

	if (it != Widgets->end()) 
	{
		return *(it->second);
	}

	else 
	{
		MessageBox(
			NULL,                           // Pas de fenêtre parente
			L"Widget Not found",            // Message
			L"Erreur",                      // Titre de la boîte
			MB_ICONERROR | MB_OK            // Icône d'erreur + bouton OK
		);
	}
}

int trUserInterface::DisplayWidget(trWidget* WIDG)
{
	// améliorer pour direct_terminal a voir quoi faire
	if (RenderType == DIRECT_TERMINAL)
	{
		CleanWidget(WIDG);

		std::wostringstream output;

		int c = 0;

		for (int j = WIDG->GetRelativePosition().GetY().GetDataActual(); j < WIDG->GetRelativePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual(); j++)
		{
			output << WIDG->GetContent().GetDataActual().substr(min(c, WIDG->GetContent().GetDataActual().size() - 1), WIDG->GetSize().GetSizeX().GetDataActual() - max(WIDG->GetRelativePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0));

			// ANALYSER SI OUTPOUT NE CONTIENT PAS DE "\n" VOIR LE SYSYTEM AVEC RENDER

			MoveCursorTo(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataActual(), j), BorderWidth);

			if (!IsOutSide(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataActual(), j), BorderWidth))
			{
				WIDG->Display(output);
			}

			output.str(L"");

			c += WIDG->GetSize().GetSizeX().GetDataActual();
		}

		WIDG->SetChange(false);
	}

	else if (RenderType == RENDER_SYSTEM)
	{
		CleanWidget(WIDG);

		std::wostringstream output;

		int c = 0;

		for (int j = WIDG->GetRelativePosition().GetY().GetDataActual(); j < WIDG->GetRelativePosition().GetY().GetDataActual() + WIDG->GetSize().GetSizeY().GetDataActual(); j++)
		{
			output << WIDG->GetContent().GetDataActual().substr(min(c, WIDG->GetContent().GetDataActual().size()), WIDG->GetSize().GetSizeX().GetDataActual() - max(WIDG->GetRelativePosition().GetX().GetDataActual() + WIDG->GetSize().GetSizeX().GetDataActual() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0));

			MoveCursorToOstream(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataActual(), j), Render_, *SizeWindow, BorderWidth);

			if (!IsOutSide(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataActual(), j), BorderWidth))
			{
				// SetColorConsole(WIDG->GetColor().GetDataActual());

				*Render_ << output.str();
			}

			output.str(L"");

			c += WIDG->GetSize().GetSizeX().GetDataActual();
		}

		WIDG->SetChange(false);
	}

	return 0;
}

void trUserInterface::MoveCursorToOstream(const trCoordinate<int> &Pos, std::wostringstream* output, const trSize<int>& SizeOutput)
{
	output->seekp(Pos.GetX().GetDataActual() + Pos.GetY().GetDataActual() * SizeOutput.GetSizeX().GetDataActual());
}

void trUserInterface::MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* output, const trSize<int>& SizeOutput, int BorderW)
{
	int adjustedX = Pos.GetX().GetDataActual() + (BorderW * 2);
	int adjustedY = Pos.GetY().GetDataActual() + BorderW;

	int position = adjustedX + adjustedY * SizeOutput.GetSizeX().GetDataActual();

	output->seekp(position);
}

void trUserInterface::CleanOstreamSize(std::wostringstream* output, const trSize<int>& SizeOutput)
{
	output->str(output->str().substr(0, SizeOutput.GetSizeX().GetDataActual() * SizeOutput.GetSizeY().GetDataActual()));
}

void trUserInterface::HideWidget(trWidget* WIDG) // < ----- BUUUG
{
	/*for (int j = min(WIDG->GetRelativePosition().GetY().GetDataActual(), WIDG->GetRelativePosition().GetY().GetDataOld()); j < max(WIDG->GetRelativePosition().GetY().GetDataActual(), WIDG->GetRelativePosition().GetY().GetDataOld()) + max(WIDG->GetSize().GetSizeY().GetDataOld(), WIDG->GetSize().GetSizeY().GetDataActual()); j++)
	{
		for (int i = min(WIDG->GetRelativePosition().GetX().GetDataActual(), WIDG->GetRelativePosition().GetX().GetDataOld()); i < max(WIDG->GetRelativePosition().GetX().GetDataActual(), WIDG->GetRelativePosition().GetX().GetDataOld()) + max(WIDG->GetSize().GetSizeX().GetDataOld(), WIDG->GetSize().GetSizeX().GetDataActual()); i++)
		{
			if (IsOutSide(trCoordinate<int>(i, j), false))
			{
				continue; // <-- pas sur (chatgpt)
			}

			MoveCursorTo(trCoordinate<int>(j, i), BorderWidth);
			cout << " ";
		}
	}*/

	CleanWidget(WIDG);

	throw std::out_of_range("code pas fait (utiliser cleanwidget ?)"); // jsp pas pk j'utilise out of range ;(((((((((((((((((
}

void trUserInterface::CleanWidget(trWidget* WIDG)
{
	if (RenderType == DIRECT_TERMINAL)
	{
		for (int j = WIDG->GetRelativePosition().GetY().GetDataOld() - 1; j < WIDG->GetRelativePosition().GetY().GetDataOld() + WIDG->GetSize().GetSizeY().GetDataOld(); j++)
		{
			if (!IsOutSide(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataOld(), j), BorderWidth))
			{
				SetColorConsole(15);
				wstring clean(WIDG->GetSize().GetSizeX().GetDataOld() - max(WIDG->GetRelativePosition().GetX().GetDataOld() + WIDG->GetSize().GetSizeX().GetDataOld() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual(), 0), ' ');
				MoveCursorTo(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataOld(), j), BorderWidth);
				cout << WstringToUtf8(clean);
			}
		}
	}

	else if (RenderType == RENDER_SYSTEM)
	{
		for (int j = WIDG->GetRelativePosition().GetY().GetDataOld() - 1; j < WIDG->GetRelativePosition().GetY().GetDataOld() + WIDG->GetSize().GetSizeY().GetDataOld(); j++)
		{
			if (!IsOutSide(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataOld(), j), BorderWidth))
			{
				SetColorConsole(15);
				wstring clean(WIDG->GetSize().GetSizeX().GetDataOld() - max((WIDG->GetRelativePosition().GetX().GetDataOld() + WIDG->GetSize().GetSizeX().GetDataOld() - GetConsoleSize(BorderWidth).GetSizeX().GetDataActual()), 0), ' ');
				MoveCursorToOstream(trCoordinate<int>(WIDG->GetRelativePosition().GetX().GetDataOld(), j), Render_, *SizeWindow, BorderWidth);
				*Render_ << clean;
			}
		}
	}
}

void trUserInterface::UpdateWidget()
{
	for (auto& widg : *Widgets)
	{
		widg.second->APPLY(GetConsoleSize(BorderWidth));
	}
}

void trUserInterface::Select(const string& name)
{
	for (auto& widg : *Widgets)
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
	/*bool found = false;

	for (auto& widg : Widgets)
	{
		if (trSelector* sltr = dynamic_cast<trSelector*>(widg.second))
		{
			if (found)
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = Widgets.size();
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
		for (size_t i = 0; i < Widgets.size(); i++)
		{
			if (trSelector* sltr = dynamic_cast<trSelector*>(Widgets[i]))
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = Widgets.size();
			}
		}
	}*/
}

void trUserInterface::SelectPrevious() // <-- a refaire en entier (car pas optimiser + non-utilisation de vector)
{
	/*bool found = false;

	for (int i = int(Widgets.size()) - 1; i >= 0; i--)
	{
		if (trSelector* sltr = dynamic_cast<trSelector*>(Widgets[i]))
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
		for (int i = int(Widgets.size()) - 1; i > 0; i--)
		{
			if (trSelector* sltr = dynamic_cast<trSelector*>(Widgets[i]))
			{
				sltr->SetSelected(true);
				sltr->SetChange(true);
				found = false;
				i = 0;
			}
		}
	}*/
}

// DESTRUCTEUR

trUserInterface::~trUserInterface()
{
	delete KB;

	delete mtx;

	delete Widgets;

	delete T;

	delete T2;

	delete SizeWindow;

	delete CursorSelector;

	delete Render_;
}