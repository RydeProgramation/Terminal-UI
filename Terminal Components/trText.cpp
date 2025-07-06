#include "trText.h"
#include "trUIToolsCore.h"

REGISTER_TYPE(trText, int, int, int, int, uint8_t, std::wstring, std::string);

using namespace std;
using namespace UIToolsCore;

// INI default

trText::trText() : trWidget()
{

}

// INI

trText::trText(int x_, int y_, int size_x_, int size_y_, uint8_t RelativePosition_, wstring content_, string name_) : trWidget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_), AnimationVector(new std::vector<trPair<uint16_t, std::wstring>>()), indexAnimation(0)
{

}

void trText::Init()
{
	
}

// INI deep copy

trText::trText(const trText& other) : trWidget(other)
{

}

// Copy

trText& trText::operator=(const trText& other)
{
	// Si on est en train de se copier soi-même, il n'y a rien à faire
	if (this == &other) { return *this; }

	trWidget::operator=(other);

	return *this;
}

// SET

void trText::SetAnimationVector(const std::vector<trPair<uint16_t, std::wstring>>& AnimationVector_)
{
	delete AnimationVector;
	AnimationVector = new std::vector<trPair<uint16_t, std::wstring>>(AnimationVector_);
}

// GET

const std::vector<trPair<uint16_t, std::wstring>>& trText::GetAnimationVector() const
{
	return *AnimationVector;
}

// ADD

void trText::AddAnimation(const trPair<uint16_t, std::wstring>& Animation_)
{
	// faudrait utiliser un mutex ici je pense
	AnimationVector->push_back(Animation_);
}

// FNC

void trText::DoCharToCharAnimation(uint16_t SleepTime_, const std::wstring& Content_)
{
	for (int i = 0; i < Content_.size(); i++)
	{
		if (Content_[i] == L'\033') // ca serait cool que ça fonctionne tout le temps
		{
			// Trouve la fin de la séquence ANSI (caractère 'm' à la fin)
			size_t endSeq = Content_.find(L'm', i);

			if (endSeq != std::wstring::npos) {
				// On prend toute la séquence ANSI, en incluant le 'm'
				std::wstring ansiSeq = Content_.substr(i, endSeq - i + 1);  // +1 pour inclure 'm'

				// On ajoute la séquence ANSI à l'interface
				AddToContent(ansiSeq);
				// World->SetActor<trWidget>("Paragraphe", &trWidget::AddToContent, ansiSeq);

				// On saute l'indice de la séquence ANSI pour ne pas la traiter à nouveau
				i += static_cast<int>(ansiSeq.size() - 1); // -1 car on a déjà ajouté un caractère
			}
		}

		else
		{
			// Si ce n'est pas une séquence ANSI, on ajoute un seul caractère
			AddToContent(wstring(1, Content_[i]));
			//World->SetActor<trWidget>("Paragraphe", &trWidget::AddToContent, wstring(1, paragColor[i]));
		}

		Sleep(SleepTime_);
	}
}

void trText::DoNextFrameAnimation()
{

}

void trText::DoAnimation()
{

}

// APPLY

bool trText::VerificationProprety()
{
	return (
		trWidget::VerificationProprety()
		);
}

void trText::APPLY_(const trSize<uint16_t>& SizeWindow)
{
	trWidget::APPLY_(SizeWindow);

}

trText::~trText()
{
	delete AnimationVector;
}
