#include "trText.h"
#include "trUIToolsCore.h"

REGISTER_TYPE(trText, int, int, int, int, uint8_t, std::wstring, std::string);

using namespace std;
using namespace UIToolsCore;

// INI default

trText::trText() : trWidget(), AnimationVector(new std::vector<trPair<uint16_t, std::wstring>>()), indexAnimation(0)
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

trText::trText(const trText& other) : trWidget(other), AnimationVector(other.AnimationVector), indexAnimation(other.indexAnimation)
{

}

// Copy

trText& trText::operator=(const trActor& other_)
{
	try
	{
		const trText& other = dynamic_cast<const trText&>(other_);

		// Si on est en train de se copier soi-même, il n'y a rien à faire
		if (this == &other) { return *this; }

		trWidget::operator=(other_);

		if (AnimationVector == nullptr) {
			AnimationVector = new std::vector<trPair<uint16_t, std::wstring>>(*other.AnimationVector);
		}
		else {
			*AnimationVector = *other.AnimationVector;
		}

		return *this;
	}

	catch (const std::bad_cast&)
	{
		trWidget& Me = dynamic_cast<trWidget&>(*this);

		Me = other_;

		return *this;
	}
}

// SET

void trText::SetAnimationVector(const std::vector<trPair<uint16_t, std::wstring>>& AnimationVector_)
{
	delete AnimationVector;
	AnimationVector = new std::vector<trPair<uint16_t, std::wstring>>(AnimationVector_);
}

void trText::SetProprety(const std::string& name, const std::string& data, const std::string& type)
{
	trWidget::SetProprety(name, data, type);


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

void trText::AddAnimation(uint16_t Time_, const std::wstring& AnimationText_)
{
	// faudrait utiliser un mutex ici je pense
	trPair<uint16_t, std::wstring> Animation_(Time_, AnimationText_);

	AnimationVector->push_back(Animation_);
}

// RESET

void trText::ResetIndexAnimation()
{
	indexAnimation = 0;
}

// FNC

void trText::DoCharToCharAnimation(uint16_t SleepTime_, const std::wstring Content_)
{
	SetContent(L"");

	SetActivate(true);

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

void trText::DoCharToCharAnimation(uint16_t SleepTime_)
{
	const std::wstring Content_ = GetRawContent().GetDataActual().empty() ? GetRawContent().GetDataNew() : GetRawContent().GetDataActual();

	SetContent(L"");

	SetActivate(true);

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
	indexAnimation >= AnimationVector->size() - 1 ? indexAnimation : indexAnimation++;

	SetContent((*AnimationVector)[indexAnimation].GetSecond());
}

void trText::DoPreviousFrameAnimation()
{
	indexAnimation <= 0 ? 0 : indexAnimation--;

	SetContent((*AnimationVector)[indexAnimation].GetSecond());
}

void trText::DoAnimation()
{
	indexAnimation = 0;

	for (auto& it : *AnimationVector)
	{
		Sleep(it.GetFirst());

		SetContent(it.GetSecond());

		indexAnimation++;
	}
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
