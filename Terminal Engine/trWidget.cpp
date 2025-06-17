#include "trWidget.h"
#include "trUI_Tools.h"

using namespace std;
using namespace UITools;

// INI default

trWidget::trWidget() : trWidget(0, 0, 0, 0, TopLeft, L"", "default")
{
}

// INI

trWidget::trWidget(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, wstring content_, string name_) : PositionRelative(new trCoordinate<int>(x_, y_)), Size(new trSize<int>(size_x_, size_y_)), ColoredContent(new trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>()), BaseColor(new std::vector<trPair<std::wstring, trCoordinate<int>>>()), RawContent(new trData<wstring>(content_)), Name(new trData<string>(name_)), Activate(new trData<bool>(true)), Color(new trData<int>(15)), Protecte(new trData<bool>(false)), Change(new trData<bool>(true)), RpType(new trData<int>(RelativePosition_)), Destroy(new trData<bool>(false)), RelativePositionPoint(new trCoordinate<int>(0, 0)), Content(new trData<wstring>(ContentReorganisation(content_, trSize<int>(size_x_, size_y_))))
{
	UpdateRelativePositionPoint(GetConsoleSize().GetSizeX().GetDataActual(), GetConsoleSize().GetSizeY().GetDataActual());

	PositionAbsolue = new trCoordinate<int>(max(PositionRelative->GetX().GetDataNew() + RelativePositionPoint->GetX().GetDataActual(), 0), max(PositionRelative->GetY().GetDataNew() + RelativePositionPoint->GetY().GetDataActual(), 0));
}

// INI deep copy

trWidget::trWidget(const trWidget& other) : PositionRelative(new trCoordinate<int>(*other.PositionRelative)), Size(new trSize<int>(*other.Size)), ColoredContent(new trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>(*other.ColoredContent)), BaseColor(new std::vector<trPair<std::wstring, trCoordinate<int>>>(*other.BaseColor)), RawContent(new trData<wstring>(*other.RawContent)), Name(new trData<string>(*other.Name)), Activate(new trData<bool>(*other.Activate)), Color(new trData<int>(*other.Color)), Protecte(new trData<bool>(*other.Protecte)), Change(new trData<bool>(true)), RpType(new trData<int>(*other.RpType)), Destroy(new trData<bool>(*other.Destroy)), RelativePositionPoint(new trCoordinate<int>(*other.RelativePositionPoint)), PositionAbsolue(new trCoordinate<int>(*other.PositionAbsolue)), Content(new trData<wstring>(*other.Content))
{

}

// Copy

trWidget& trWidget::operator=(const trWidget& other)
{
	if (this == &other) { return *this; }

	PositionRelative = new trCoordinate<int>(*other.PositionRelative);
	Size = new trSize<int>(*other.Size);
	ColoredContent = new trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>(*other.ColoredContent);
	BaseColor = new std::vector<trPair<std::wstring, trCoordinate<int>>>(*other.BaseColor);
	RawContent = new trData<wstring>(*other.RawContent);
	Name = new trData<string>(*other.Name);
	Activate = new trData<bool>(*other.Activate);
	Color = new trData<int>(*other.Color);
	Protecte = new trData<bool>(*other.Protecte);
	Change = new trData<bool>(true);
	RpType = new trData<int>(*other.RpType);
	Destroy = new trData<bool>(*other.Destroy);
	RelativePositionPoint = new trCoordinate<int>(*other.RelativePositionPoint);
	PositionAbsolue = new trCoordinate<int>(*other.PositionAbsolue);
	Content = new trData<wstring>(*other.Content);

	return *this;
}

// SET

void trWidget::SetPosition(int x_, int y_)
{
	PositionRelative->SetCoord(x_, y_);
}

void trWidget::SetSize(int x_, int y_)
{
	Size->SetSize(x_, y_);
	Content->SetData(ContentReorganisation(RawContent->GetDataNew(), trSize<int>(x_, y_)));
}

void trWidget::SetContent(const wstring& content_)
{
	RawContent->SetData(content_);
	Content->SetData(ContentReorganisation(content_, *Size));
}

void trWidget::SetResetColor(const vector<trPair<std::wstring, trCoordinate<int>>>& RstColor)
{
	*BaseColor = RstColor;
}

void trWidget::SetName(const string& name_)
{
	Name->SetData(name_);
}

void trWidget::SetActivate(bool actv)
{
	Activate->SetData(actv);
}

void trWidget::SetProtecte(bool prtc)
{
	Protecte->SetData(prtc);
}

void trWidget::SetColor(int color_)
{
	Color->SetData(max(color_, 0));
}

bool trWidget::SetTypeRelativePosition(int rp)
{
	if (rp < 0 || rp > 9)
	{
		RpType->SetData(0);
		return false;
	}

	RpType->SetData(rp);
	return true;
}

void trWidget::SetChange(bool chng)
{
	Change->SetData(chng);
}

void trWidget::SetDestroy(bool dstr)
{
	Destroy->SetData(dstr);
}

// ADD

void trWidget::AddToPosition(int x_, int y_)
{
	PositionRelative->SetCoord(PositionRelative->GetX().GetDataNew() + x_, PositionRelative->GetY().GetDataNew() + y_);
}

void trWidget::AddToSize(int x_, int y_)
{
	Size->SetSize(Size->GetSizeX().GetDataNew() + x_, Size->GetSizeY().GetDataNew() + y_);
	Content->SetData(ContentReorganisation(RawContent->GetDataNew(), trSize<int>(Size->GetSizeX().GetDataNew(), Size->GetSizeY().GetDataNew())));
}

void trWidget::AddToContent(const wstring& content_)
{
	RawContent->SetData(RawContent->GetDataNew() + content_);
	Content->SetData(ContentReorganisation(RawContent->GetDataNew(), *Size));
}

void trWidget::AddToColor(int color_)
{
	Color->SetData(Color->GetDataNew() + color_);
}

// GET

const trCoordinate<int>& trWidget::GetPosition() const
{
	return *PositionRelative;
}

const trCoordinate<int>& trWidget::GetAbsolutePosition() const
{
	return *PositionAbsolue;
}

const trSize<int>& trWidget::GetSize() const
{
	return *Size;
}

const trData<wstring>& trWidget::GetContent() const
{
	return *Content;
}

const trData<wstring>& trWidget::GetRawContent() const
{
	return *RawContent;
}

const trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>& trWidget::GetColoredContent() const
{
	return *ColoredContent;
}

const std::vector<trPair<std::wstring, trCoordinate<int>>>& trWidget::GetResetColor() const
{
	return *BaseColor;
}

const trData<string>& trWidget::GetName() const
{
	return *Name;
}

const trData<bool>& trWidget::GetActivate() const
{
	return *Activate;
}

const trData<bool>& trWidget::GetProtecte() const
{
	return *Protecte;
}

const trData<int>& trWidget::GetColor() const
{
	return *Color;
}

const trData<int>& trWidget::GetRP() const
{
	return *RpType;
}

const trData<bool>& trWidget::GetChange() const
{
	return *Change;
}

const trData<bool>& trWidget::GetDestroy() const
{
	return *Destroy;
}

// APPLY

void trWidget::UpdateRelativePositionPoint(int ConsoleSize_x, int ConsoleSize_y)
{
	switch (RpType->GetDataActual())
	{
	case TopLeft:
		RelativePositionPoint->SetCoord(0, 0);
		break;
	case TopCenter:
		RelativePositionPoint->SetCoord((ConsoleSize_x / 2) - (Size->GetSizeX().GetDataActual() / 2), 0);
		break;
	case TopRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x - Size->GetSizeX().GetDataActual(), 0);
		break;
	case MiddleLeft:
		RelativePositionPoint->SetCoord(0, (ConsoleSize_y / 2) - (Size->GetSizeY().GetDataActual() / 2));
		break;
	case MiddleCenter:
		RelativePositionPoint->SetCoord((ConsoleSize_x / 2) - (Size->GetSizeX().GetDataActual() / 2), (ConsoleSize_y / 2) - (Size->GetSizeY().GetDataActual() / 2));
		break;
	case MiddleRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x - Size->GetSizeX().GetDataActual(), (ConsoleSize_y / 2) - (Size->GetSizeY().GetDataActual() / 2));
		break;
	case BottomLeft:
		RelativePositionPoint->SetCoord(0, ConsoleSize_y - Size->GetSizeY().GetDataActual());
		break;
	case BottomCenter:
		RelativePositionPoint->SetCoord((ConsoleSize_x / 2) - (Size->GetSizeX().GetDataActual() / 2), ConsoleSize_y - Size->GetSizeY().GetDataActual());
		break;
	case BottomRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x - Size->GetSizeX().GetDataActual(), ConsoleSize_y - Size->GetSizeY().GetDataActual());
		break;
	default:
		std::cerr << "AUCUN NE CORESPOND";
		std::exit(1);
	}

	RelativePositionPoint->Update();
}

void trWidget::UpdateRelativePosition()
{
	PositionAbsolue->SetCoord(max(PositionRelative->GetX().GetDataNew() + RelativePositionPoint->GetX().GetDataActual(), 0), max(PositionRelative->GetY().GetDataNew() + RelativePositionPoint->GetY().GetDataActual(), 0));
}

void trWidget::APPLY(const trSize<int>& SizeWindow_)
{
	Size->Update();

	UpdateRelativePositionPoint(SizeWindow_.GetSizeX().GetDataActual(), SizeWindow_.GetSizeY().GetDataActual());
	UpdateRelativePosition();
	
	PositionAbsolue->Update();
	PositionRelative->Update();
	Activate->Update();
	Protecte->Update();
	Content->Update();
	RawContent->Update();
	ColoredContent->Update();
	Color->Update();
	Name->Update();
	RpType->Update();
	Destroy->Update();

	Change->SetData(VerificationProprety() ? true : Change->GetDataNew());
    Change->Update();
}

// FNC

bool trWidget::VerificationProprety()
{
	return (PositionRelative->GetX().GetDataOld() != PositionRelative->GetX().GetDataActual() || PositionRelative->GetY().GetDataOld() != PositionRelative->GetY().GetDataActual() || Size->GetSizeX().GetDataOld() != Size->GetSizeX().GetDataActual() || Size->GetSizeY().GetDataOld() != Size->GetSizeY().GetDataActual() || Activate->GetDataOld() != Activate->GetDataActual() || Color->GetDataOld() != Color->GetDataActual() || Content->GetDataOld() != Content->GetDataActual() || RpType->GetDataOld() != RpType->GetDataActual());
}

void trWidget::Display(wostringstream& output_line)
{
	SetColorConsole(GetColor().GetDataActual());
	cout << WstringToUtf8(output_line.str());
}

std::wstring trWidget::ContentReorganisation(std::wstring _content, const trSize<int>& SizeWidget) const
{
	size_t Cherche = 0;
	size_t Cherche_ = 0;

	int Verif = 0;

	trMap<int, trPair<std::wstring, trCoordinate<int>>> coloredtemp;

	const int max_ = static_cast<int>(_content.size());

	for (int i = 0; i < max_; i++) // rendre plus concis ?
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

		if (Cherche != std::wstring::npos)
		{
			_content.erase(Cherche, 1);
			_content.erase(Cherche - 1, 1);
		}

		else
		{
			Verif++;
		}

		Cherche = min(_content.find('\033'), min(min(_content.find('\n'), _content.find('\f')), _content.find('\v')));

		if (Cherche != std::wstring::npos && _content.find('\b') == std::wstring::npos && _content.find('\t') == std::wstring::npos && Cherche == _content.find('\033'))
		{
			Cherche_ = _content.find('m', Cherche) + 1;
			
			if (Cherche_ != std::wstring::npos + 1)
			{
				if (IsPureColor(_content.substr(Cherche, Cherche_ - Cherche)))
				{
					int coordX = static_cast<int>(Cherche) % SizeWidget.GetSizeX().GetDataActual();
					int coordY = static_cast<int>(Cherche) / SizeWidget.GetSizeX().GetDataActual();

					wstring couleur = _content.substr(Cherche, Cherche_ - Cherche);
					
					coloredtemp[coordX + coordY * SizeWidget.GetSizeX().GetDataActual()] = trPair<wstring, trCoordinate<int>>(couleur, trCoordinate<int>(coordX, coordY));
					
					// Faire continuer la ligne de couleur

					for (int i = coordY + 1; i < SizeWidget.GetSizeY().GetDataActual(); i++)
					{
						coloredtemp[i * SizeWidget.GetSizeX().GetDataActual()] = trPair<wstring, trCoordinate<int>>(couleur, trCoordinate<int>(0, i));
					}

				}

				_content.erase(Cherche, Cherche_ - Cherche);
			}

			else // bah c'est un prblm 
			{
				_content.erase(Cherche); 
				
				// c'est plus estetique mais il y a deux petit problm

				// 1 -- bah quand on ajoute une lettre petit a petit on a l'impression que a freeze ?
				// 2 -- si j'amais y'a pas de m a supprime tout (aprs logique c'est la ligne de code

				// fin test
			} 
		}

		else
		{
			Verif++;
		}

		if (Cherche != std::wstring::npos && _content.find('\b') == std::wstring::npos && _content.find('\t') == std::wstring::npos && Cherche == min(min(_content.find('\n'), _content.find('\f')), _content.find('\v')))
		{
			size_t ligne = (Cherche) / (SizeWidget.GetSizeX().GetDataActual());
			size_t espace_a_remplir = (SizeWidget.GetSizeX().GetDataActual()) - (Cherche % SizeWidget.GetSizeX().GetDataActual()); // changer le calcul

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
			size_t espace_a_suppr = Cherche % SizeWidget.GetSizeX().GetDataActual();

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

		if (Verif == 5)
		{
			break;
		}

		// securité pas important je pense
		if (i > _content.size() / 2 && i > 350 && coloredtemp.GetSize() < i)
		{
			MessageBox(
				NULL,
				L"Il y a beaucoup d'itérations ! dans la fonction ContentReorganisation. Est-ce normal ? si oui ignorer ce message (pas de panique !)", 
				L"Message",                    
				MB_ICONERROR | MB_OK           
			);
		}
	}

	ColoredContent->SetData(coloredtemp);

	return _content;
}

const trWidget& trWidget::EmptyWidget()
{
	if (!EmptyWidgetInstance)
	{
		// Initialise le widget vide avec des valeurs par défaut
		EmptyWidgetInstance = new trWidget(
			0, 0,                      // PositionRelative par défaut (x, y)
			0, 0,                      // Taille par défaut (width, height)
			MiddleCenter,              // PositionRelative relative par défaut
			L"",                       // Contenu vide
			""                         // Nom vide
		);

		EmptyWidgetInstance->SetActivate(false);   // Désactivé
		EmptyWidgetInstance->SetProtecte(false);   // Non protégé
		EmptyWidgetInstance->SetColor(0);          // Couleur par défaut
		EmptyWidgetInstance->SetDestroy(false);    // Pas détruit
	}
	return *EmptyWidgetInstance;
}

// Définition dans le fichier source

trWidget* trWidget::EmptyWidgetInstance = nullptr;

// DESTRUCTEUR

trWidget::~trWidget()
{
	delete PositionRelative;

	delete PositionAbsolue;

	delete Size;

	delete Activate;

	delete Protecte;

	delete Color;

	delete Change;

	delete RpType;

	delete Content; 

	delete ColoredContent;

	delete BaseColor;

	delete RawContent;

	delete Name; 

	delete Destroy;

	delete RelativePositionPoint;
}
