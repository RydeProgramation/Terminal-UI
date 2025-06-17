#include "trUI_Tools.h"
#include "trActor.h"

using namespace std;
using namespace UITools;

// INI default

trActor::trActor() : trWidget()
{

}

// INI

trActor::trActor(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, wstring content_, string name_) : trWidget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_)
{

}

// INI deep copy

trActor::trActor(const trActor& other) : trWidget(other)
{

}

// Copy

trActor& trActor::operator=(const trActor& other)
{
	// Si on est en train de se copier soi-même, il n'y a rien à faire
	if (this == &other) { return *this; }

	trWidget::operator=(other);;

	return *this;
}

// APPLY

void trActor::APPLY(const trSize<int>& SizeWindow_)
{
	APPLY_Implementation();

	trWidget::APPLY(SizeWindow_);
}

void trActor::APPLY_Implementation()
{
	// some code
}

trActor::~trActor()
{

}
