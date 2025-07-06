#include "trWidget.h"
#include "trUIToolsCore.h"

REGISTER_TYPE(trWidget, int, int, int, int, uint8_t, std::wstring, std::string);

using namespace std;
using namespace UIToolsCore;

// INI default

trWidget::trWidget() : trWidget(0, 0, 0, 0, TopLeft, L"", "None")
{
}

// INI

trWidget::trWidget(int x_, int y_, int size_x_, int size_y_, uint8_t RelativePositionType_, wstring content_, string name_) : trPawn(x_, y_, RelativePositionType_, name_), Size(new trSize<int>(size_x_, size_y_)), ColoredMap(new trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>()), BaseColor(new std::vector<trPair<std::wstring, trCoordinate<int>>>()), RawContent(new trData<wstring>(content_)), Color(new trData<wstring>(L"\x1B[0m")), Content(new trData<wstring>(ContentReorganisation(content_, trSize<int>(size_x_, size_y_)))), ColoredContent(new trData<wstring>(ContentReorganisationKeepColor(content_, trSize<int>(size_x_, size_y_))))
{
	
}

// INI deep copy

trWidget::trWidget(const trWidget& other) : trPawn(other), Size(new trSize<int>(*other.Size)), ColoredMap(new trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>(*other.ColoredMap)), BaseColor(new std::vector<trPair<std::wstring, trCoordinate<int>>>(*other.BaseColor)), RawContent(new trData<wstring>(*other.RawContent)), Color(new trData<wstring>(*other.Color)), Content(new trData<wstring>(*other.Content)), ColoredContent(new trData<wstring>(*other.ColoredContent))
{

}

void trWidget::Init()
{

}

// Copy

trWidget& trWidget::operator=(const trWidget& other)
{
	if (this == &other) { return *this; }

	trPawn::operator=(other);

	if (Size == nullptr) {
		Size = new trSize<int>(*other.Size);
	}
	else {
		*Size = *other.Size;
	}

	if (ColoredMap == nullptr) {
		ColoredMap = new trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>(*other.ColoredMap);
	}
	else {
		*ColoredMap = *other.ColoredMap;
	}

	if (BaseColor == nullptr) {
		BaseColor = new std::vector<trPair<std::wstring, trCoordinate<int>>>(*other.BaseColor);
	}
	else {
		*BaseColor = *other.BaseColor;
	}

	if (RawContent == nullptr) {
		RawContent = new trData<wstring>(*other.RawContent);
	}
	else {
		*RawContent = *other.RawContent;
	}

	if (Color == nullptr) {
		Color = new trData<wstring>(*other.Color);
	}
	else {
		*Color = *other.Color;
	}

	if (Content == nullptr) {
		Content = new trData<wstring>(*other.Content);
	}
	else {
		*Content = *other.Content;
	}

	if (ColoredContent == nullptr) {
		ColoredContent = new trData<wstring>(*other.ColoredContent);
	}
	else {
		*ColoredContent = *other.ColoredContent;
	}

	return *this;
}

// SET

void trWidget::SetSize(int x_, int y_)
{
	Size->SetSize(x_, y_);
	Content->SetData(ContentReorganisation(RawContent->GetDataNew(), trSize<int>(x_, y_)));
}

void trWidget::SetContent(const wstring& content_)
{
	RawContent->SetData(content_);
	Content->SetData(ContentReorganisation(content_, *Size));
	ColoredContent->SetData(ContentReorganisationKeepColor(content_, *Size));
}

void trWidget::SetResetColor(const vector<trPair<std::wstring, trCoordinate<int>>>& RstColor)
{
	*BaseColor = RstColor;
}

void trWidget::SetColor(uint8_t R, uint8_t G, uint8_t B, bool Backround)
{
	wstring BackRoundOrNot = Backround ? to_wstring(48) : to_wstring(38);

	Color->SetData(L"\x1b[" + BackRoundOrNot + L";" + L"2" + L";" + to_wstring(R) + L";" + to_wstring(G) + L";" + to_wstring(B) + L"m");
	Content->SetData(ContentReorganisation(RawContent->GetDataActual(), *Size));
	ColoredContent->SetData(ContentReorganisationKeepColor(RawContent->GetDataActual(), *Size));
}

void trWidget::SetColor(const std::wstring& CodeCouleurAnsi)
{
	// Vérifie que ça commence bien par \033[
	if (CodeCouleurAnsi.size() >= 3 && CodeCouleurAnsi[0] == L'\033' && CodeCouleurAnsi[1] == L'[') {
		// Et que ça finit bien par 'm'
		if (CodeCouleurAnsi.back() == L'm') {
			Color->SetData(CodeCouleurAnsi); // ✅ Code valide
			Content->SetData(ContentReorganisation(RawContent->GetDataActual(), *Size));
			ColoredContent->SetData(ContentReorganisationKeepColor(RawContent->GetDataActual(), *Size));
		}
		else {
			MessageBoxW(nullptr, (L"Le code ANSI ne se termine pas par 'm':\n" + CodeCouleurAnsi).c_str(),
				L"❌ Code ANSI invalide", MB_ICONERROR | MB_OK);
		}
	}
	else {
		MessageBoxW(nullptr, (L"Le code ANSI est invalide (doit commencer par '\\033['):\n" + CodeCouleurAnsi).c_str(),
			L"❌ Code ANSI invalide", MB_ICONERROR | MB_OK);
	}
}

void trWidget::ResetColor()
{
	Color->SetData(L"\x1b[0m");
}

// ADD

void trWidget::AddToSize(int x_, int y_)
{
	Size->SetSize(Size->GetSizeX().GetDataNew() + x_, Size->GetSizeY().GetDataNew() + y_);
	Content->SetData(ContentReorganisation(RawContent->GetDataNew(), trSize<int>(Size->GetSizeX().GetDataNew(), Size->GetSizeY().GetDataNew())));
}

void trWidget::AddToContent(const wstring& content_)
{
	RawContent->SetData(RawContent->GetDataNew() + content_);
	Content->SetData(ContentReorganisation(RawContent->GetDataNew(), *Size));
	ColoredContent->SetData(ContentReorganisationKeepColor(RawContent->GetDataNew(), *Size));
}

// GET

const trSize<int>& trWidget::GetSize() const
{
	return *Size;
}

const trData<wstring>& trWidget::GetContent() const
{
	return *Content;
}

const trData<wstring>& trWidget::GetColoredContent() const
{
	return *ColoredContent;
}

const trData<wstring>& trWidget::GetRawContent() const
{
	return *RawContent;
}

const trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>& trWidget::GetColoredMap() const
{
	return *ColoredMap;
}

const std::vector<trPair<std::wstring, trCoordinate<int>>>& trWidget::GetResetColor() const
{
	return *BaseColor;
}

const trData<wstring>& trWidget::GetColor() const
{
	return *Color;
}

// APPLY

void trWidget::APPLY_(const trSize<uint16_t>& SizeWindow)
{// RESPECTER L'ORDRE STP

	Size->Update();

	trPawn::APPLY_(SizeWindow);

	Content->Update();
	RawContent->Update();
	ColoredMap->Update();
	Color->Update();
	ColoredContent->Update();
}

// FNC

bool trWidget::VerificationProprety()
{
	return (
		trPawn::VerificationProprety() ||
		Size->GetSizeX().GetDataOld() != Size->GetSizeX().GetDataActual() ||
		Size->GetSizeY().GetDataOld() != Size->GetSizeY().GetDataActual() ||
		Color->GetDataOld() != Color->GetDataActual() ||
		Content->GetDataOld() != Content->GetDataActual() ||
		RawContent->GetDataOld() != RawContent->GetDataActual() ||
		ColoredContent->GetDataOld() != ColoredContent->GetDataActual()
		);
}

void trWidget::UpdateRelativePositionPoint(const trSize<uint16_t>& SizeWindow)
{
	int ConsoleSize_x = SizeWindow.GetSizeX().GetDataActual();
	int ConsoleSize_y = SizeWindow.GetSizeY().GetDataActual();

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
}

void trWidget::Display(wostringstream& output_line)
{
	// SetColorConsole(GetColor().GetDataActual());
	cout << WstringToUtf8(output_line.str());
}

std::wstring trWidget::ContentReorganisation(std::wstring _content, const trSize<int>& SizeWidget) const
{
	size_t Cherche = 0;
	size_t Cherche_ = 0;

	int Verif = 0;

	trMap<int, trPair<std::wstring, trCoordinate<int>>> coloredtemp;

	const int max_ = static_cast<int>(_content.size());

	for (int i = 0; i < max_; i++) // rendre plus concis ? fait dans celui qui garde la couleur
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
		if (i > _content.size() / 2 && i > 35000 && coloredtemp.GetSize() < i)
		{
			MessageBox(
				NULL,
				L"Il y a beaucoup d'itérations ! dans la fonction ContentReorganisation. Est-ce normal ? si oui ignorer ce message (pas de panique !)", 
				L"Message",                    
				MB_ICONERROR | MB_OK           
			);
		}
	}

	ColoredMap->SetData(coloredtemp);

	return _content;
}

std::wstring trWidget::ContentReorganisationKeepColor(std::wstring _content, const trSize<int>& SizeWidget) const
{
	size_t Cherche = 0;

	const int max_ = static_cast<int>(_content.size());

	_content = GetColor().GetDataNew() + _content;

	for (int i = 0; i < max_; i++)
	{
		Cherche = _content.find('\b');
		Cherche = min(

			min(min(_content.find('\b'),
			_content.find('\t')),

			min(_content.find('\n'),
			_content.find('\f'))),

			min(_content.find('\v'),
			_content.find('\r'))
		/*, _content.find('\\'),
		_content.find('\0x')*/);

		if (Cherche == std::wstring::npos)
		{
			break;
		}

		else if (Cherche == _content.find('\t'))
		{
			wstring space = L"	";
			_content.erase(Cherche, 1);
			_content.insert(Cherche, space);
		}

		else if (Cherche == _content.find('\b'))
		{
			_content.erase(Cherche, 1);
			_content.erase(Cherche - 1, 1);
		}

		else if (Cherche == _content.find('\n') || Cherche == _content.find('\f') || Cherche == _content.find('\v'))
		{
			_content.erase(Cherche, 1);

			wstring tempContent = RemoveColor(_content.substr(0, Cherche)); // enlver les ansi \033 en cherchant le m le plus proche

			size_t ChercheTemp = tempContent.size(); 

			size_t ligne = (ChercheTemp) / (SizeWidget.GetSizeX().GetDataActual());
			size_t espace_a_remplir = (SizeWidget.GetSizeX().GetDataActual()) - (ChercheTemp % SizeWidget.GetSizeX().GetDataActual()); // changer le calcul

			wstring toinsert = L"";
			toinsert.insert(0, espace_a_remplir, ' ');
			_content.insert(Cherche, toinsert);
		}

		else if (Cherche == _content.find('\r'))
		{
			size_t ligne = (Cherche) / (SizeWidget.GetSizeX().GetDataActual());
			size_t espace_a_suppr = Cherche % SizeWidget.GetSizeX().GetDataActual();

			_content.erase(Cherche, 1);
			_content.erase(Cherche - espace_a_suppr, espace_a_suppr);
		}

		/*Cherche = _content.find('\\'); // a voir

		if (Cherche != std::string::npos)
		{
			// code;
		}*/

		// securité pas important je pense
		if (i > _content.size() / 2 && i > 35000)
		{
			MessageBox(
				NULL,
				L"Il y a beaucoup d'itérations ! dans la fonction ContentReorganisation. Est-ce normal ? si oui ignorer ce message (pas de panique !)",
				L"Message",
				MB_ICONERROR | MB_OK
			);
		}
	}

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
		EmptyWidgetInstance->SetColor(L"\x1b[0m");          // Couleur par défaut
		EmptyWidgetInstance->SetDestroy(false);    // Pas détruit
	}
	return *EmptyWidgetInstance;
}

// Définition dans le fichier source

trWidget* trWidget::EmptyWidgetInstance = nullptr;

// DESTRUCTEUR

trWidget::~trWidget()
{
	delete Size;

	delete Color;

	delete Content; 

	delete ColoredMap;

	delete BaseColor;

	delete RawContent;

	delete ColoredContent;
}
