#include "trText.h"
#include "trUIToolsCore.h"

using namespace std;
using namespace UIToolsCore;

// INI default

trText::trText() : trWidget()
{

}

// INI

trText::trText(int x_, int y_, int size_x_, int size_y_, uint8_t RelativePosition_, wstring content_, string name_) : trWidget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_)
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


// GET


// APPLY

bool trText::VerificationProprety()
{
	return (
		trWidget::VerificationProprety()
		);
}

void trText::APPLY_(const trSize<uint16_t>& SizeWindow)
{
	trText::APPLY_(SizeWindow);

}

trText::~trText()
{
	
}
