#include "trWidget.h"
#include "trUI_Tools.h"

using namespace std;
using namespace UITools;

// INI

trWidget::trWidget(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, wstring content_, string name_) : Position(new trCoordinate<int>(x_, y_)), size(new trSize<int>(size_x_, size_y_)), content(new trData<wstring>(ContentReorganisation(content_, trSize<int>(size_x_, size_y_)))), name(new trData<string>(name_)), activate(new trData<bool>(true)), color(new trData<int>(15)), protecte(new trData<bool>(false)), change(new trData<bool>(true)), RP(new trData<int>(RelativePosition_)), destroy(new trData<bool>(false)), RelativePositionPoint(new trCoordinate<int>(0, 0)), RelativePosition(new trCoordinate<int>(0, 0))
{
}

// SET

void trWidget::SetPosition(int x_, int y_)
{
	Position->SetCoord(x_, y_);
}

void trWidget::SetSize(int x_, int y_)
{
	size->SetSize(x_, y_);
}

void trWidget::SetContent(const wstring& content_)
{
	content->SetData(ContentReorganisation(content->GetDataNew() + content_, *size));
	// content->SetData(content_);
}

void trWidget::SetName(const string& name_)
{
	name->SetData(name_);
}

void trWidget::SetActivate(bool actv)
{
	activate->SetData(actv);
}

void trWidget::SetProtecte(bool prtc)
{
	protecte->SetData(prtc);
}

/*void trWidget::SetDelayCaractere(int Delay) INUTILE
{
	delayCaractere->SetData(max(Delay, 0));
}*/

void trWidget::SetColor(int color_)
{
	color->SetData(max(color_, 0));
}

bool trWidget::SetRelativePosition(int rp)
{
	if (rp < 0 || rp > 9)
	{
		RP->SetData(0);
		return false;
	}

	RP->SetData(rp);
	return true;
}

void trWidget::SetChange(bool chng)
{
	change->SetData(chng);
}

void trWidget::SetDestroy(bool dstr)
{
	destroy->SetData(dstr);
}

// ADD

void trWidget::AddToPosition(int x_, int y_)
{
	Position->SetCoord(Position->GetX().GetDataNew() + x_, Position->GetY().GetDataNew() + y_);
}

void trWidget::AddToSize(int x_, int y_)
{
	size->SetSize(size->GetSizeX().GetDataNew() + x_, size->GetSizeY().GetDataNew() + y_);
}

void trWidget::AddToContent(const wstring& content_)
{
	content->SetData(ContentReorganisation(content->GetDataNew() + content_, *size));
}

void trWidget::AddToColor(int color_)
{
	color->SetData(color->GetDataNew() + color_);
}

// GET

const trCoordinate<int>& trWidget::GetPostion() const
{
	return *Position;
}

const trCoordinate<int>& trWidget::GetRelativePosition() const
{
	return *RelativePosition;
}

const trSize<int>& trWidget::GetSize() const
{
	return *size;
}

const trData<wstring>& trWidget::GetContent() const
{
	return *content;
}

const trData<string>& trWidget::GetName() const
{
	return *name;
}

const trData<bool>& trWidget::GetActivate() const
{
	return *activate;
}

const trData<bool>& trWidget::GetProtecte() const
{
	return *protecte;
}

/*const trData<int>& trWidget::GetDelayCaractere() const INUTILE
{
	return *delayCaractere;
}*/

const trData<int>& trWidget::GetColor() const
{
	return *color;
}

const trData<int>& trWidget::GetRP() const
{
	return *RP;
}

const trData<bool>& trWidget::GetChange() const
{
	return *change;
}

const trData<bool>& trWidget::GetDestroy() const
{
	return *destroy;
}

// APPLY

void trWidget::UpdateRelativePositionPoint(int ConsoleSize_x, int ConsoleSize_y)
{
	switch (RP->GetDataActual())
	{
	case TopLeft:
		RelativePositionPoint->SetCoord(0, 0);
		break;
	case TopCenter:
		RelativePositionPoint->SetCoord((ConsoleSize_x / 2) - (size->GetSizeX().GetDataActual() / 2), 0);
		break;
	case TopRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x - size->GetSizeX().GetDataActual(), 0);
		break;
	case MiddleLeft:
		RelativePositionPoint->SetCoord(0, (ConsoleSize_y / 2) - (size->GetSizeY().GetDataActual() / 2));
		break;
	case MiddleCenter:
		RelativePositionPoint->SetCoord((ConsoleSize_x / 2) - (size->GetSizeX().GetDataActual() / 2), (ConsoleSize_y / 2) - (size->GetSizeY().GetDataActual() / 2));
		break;
	case MiddleRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x - size->GetSizeX().GetDataActual(), (ConsoleSize_y / 2) - (size->GetSizeY().GetDataActual() / 2));
		break;
	case BottomLeft:
		RelativePositionPoint->SetCoord(0, ConsoleSize_y - size->GetSizeY().GetDataActual());
		break;
	case BottomCenter:
		RelativePositionPoint->SetCoord((ConsoleSize_x / 2) - (size->GetSizeX().GetDataActual() / 2), ConsoleSize_y - size->GetSizeY().GetDataActual());
		break;
	case BottomRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x - size->GetSizeX().GetDataActual(), ConsoleSize_y - size->GetSizeY().GetDataActual());
		break;
	default:
		std::cerr << "AUCUN NE CORESPOND";
		std::exit(1);
	}

	RelativePositionPoint->Update();
}

void trWidget::UpdateRelativePosition()
{
	RelativePosition->SetCoord(max(Position->GetX().GetDataNew() + RelativePositionPoint->GetX().GetDataActual(), 0), max(Position->GetY().GetDataNew() + RelativePositionPoint->GetY().GetDataActual(), 0));
}

void trWidget::APPLY(const trSize<int>& SizeWindow_)
{
	UpdateRelativePositionPoint(SizeWindow_.GetSizeX().GetDataActual(), SizeWindow_.GetSizeY().GetDataActual());
	UpdateRelativePosition();
	
	RelativePosition->Update();
	Position->Update();
	size->Update();
	activate->Update();
	protecte->Update();
	content->Update();
	// delayCaractere->Update(); INUTILE
	color->Update();
	name->Update();
	RP->Update();
	destroy->Update();

	change->SetData(VerificationProprety() ? true : change->GetDataNew());
	change->Update();
}

// FNC

bool trWidget::VerificationProprety()
{
	return (Position->GetX().GetDataOld() != Position->GetX().GetDataActual() || Position->GetY().GetDataOld() != Position->GetY().GetDataActual() || size->GetSizeX().GetDataOld() != size->GetSizeX().GetDataActual() || size->GetSizeY().GetDataOld() != size->GetSizeY().GetDataActual() || activate->GetDataOld() != activate->GetDataActual() || color->GetDataOld() != color->GetDataActual() || content->GetDataOld() != content->GetDataActual() || RP->GetDataOld() != RP->GetDataActual());
}

void trWidget::Display(wostringstream& output_line)
{
	SetColorConsole(GetColor().GetDataActual());
	cout << WstringToUtf8(output_line.str());
}

std::wstring trWidget::ContentReorganisation(std::wstring _content, const trSize<int>& SizeWidget) const
{
	size_t Cherche = 0;

	int Verif = 0; // je veux juste vérifier si il ne reste plus de code/séquence soit max 5 normalenement

	for (int i = 0; i < _content.size(); i++) // rendre plus concis ?
	{
		Verif = 0;

		Cherche = _content.find('\t');

		if (Cherche != std::wstring::npos)
		{
			wstring space = L"   ";
			_content.erase(Cherche, 1);
			_content.insert(Cherche, space);
		}

		else
		{
			Verif++;
		}


		Cherche = _content.find('\b');

		if (Cherche != std::string::npos)
		{
			_content.erase(Cherche, 1);
			_content.erase(Cherche - 1, 1);
		}

		else
		{
			Verif++;
		}

		Cherche = min(min(_content.find('\n'), _content.find('\f')), _content.find('\v'));

		if (Cherche != std::wstring::npos && _content.find('\b') == std::wstring::npos && _content.find('\t') == std::wstring::npos)
		{
			size_t ligne = (Cherche) / (SizeWidget.GetSizeX().GetDataActual());
			size_t espace_a_remplir = (SizeWidget.GetSizeX().GetDataActual()) - (Cherche - ligne * SizeWidget.GetSizeX().GetDataActual());

			_content.erase(Cherche, 1);

			wstring toinsert = L"";
			toinsert.insert(0, espace_a_remplir, ' ');
			_content.insert(Cherche, toinsert);
		}
			
		else
		{
			Verif++;
		}

		Cherche = _content.find('\r');

		if (Cherche != std::wstring::npos)
		{
			size_t ligne = (Cherche) / (SizeWidget.GetSizeX().GetDataActual());
			size_t espace_a_suppr = (Cherche - ligne * SizeWidget.GetSizeX().GetDataActual());

			_content.erase(Cherche, 1);
			_content.erase(Cherche - espace_a_suppr, espace_a_suppr);
		}

		else
		{
			Verif++;
		}

		/*Cherche = _content.find('\\'); // a voir

		if (Cherche != std::string::npos)
		{
			// code;
		}

		else
		{
			Verif++;
		}*/


		if (Verif == 4 /*5*/)
		{
			break;
		}

		// securité pas important je pense
		if (i > _content.size() / 2)
		{
			MessageBox(
				NULL,                           // Pas de fenêtre parente
				L"Il y a trop d'itérations ! dans la fonciton ContentReorganisation",  // Message
				L"Erreur",                      // Titre de la boîte
				MB_ICONERROR | MB_OK           // Icône d'erreur + bouton OK
			);
		}
	}

	// POUR LES COULEURS

	return _content;
}

// DESTRUCTEUR

trWidget::~trWidget()
{
	delete Position;

	delete RelativePosition;

	delete size;

	delete activate;

	delete protecte;

	// delete delayCaractere; INUTILE

	delete color;

	delete change;

	delete RP;

	delete content; 

	delete name; 

	delete destroy;

	delete RelativePositionPoint;
}
