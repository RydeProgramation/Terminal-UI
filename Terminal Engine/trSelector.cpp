#include "trUI_Tools.h"
#include "trSelector.h"

using namespace std;
using namespace UITools;

// INI default

trSelector::trSelector() : trWidget(), selected(new trData<bool>(false)), colorSelected(new trData<int>(0))
{
}

// INI

trSelector::trSelector(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, wstring content_, string name_) : trWidget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_), selected(new trData<bool>(true)), colorSelected(new trData<int>(14))
{

}

// INI deep copy

trSelector::trSelector(const trSelector& other) : trWidget(other), selected(other.selected), colorSelected(other.colorSelected)
{

}

// Copy

trSelector& trSelector::operator=(const trSelector& other)
{
	// Si on est en train de se copier soi-même, il n'y a rien à faire
	if (this == &other) { return *this; }

	trWidget::operator=(other);;

	selected = new trData<bool>(*other.selected);
	colorSelected = new trData<int>(*other.colorSelected);

	return *this;
}

// SET

void trSelector::SetSelected(bool Slct)
{
	selected->SetData(Slct);
}

void trSelector::SetColorSelected(int color)
{
	colorSelected->SetData(color);
}

// GET

const trData<bool> trSelector::IsSelected() const
{
	return *selected;
}

const trData<int> trSelector::GetColorSelected() const
{
	return *colorSelected;
}

// APPLY

void trSelector::APPLY(const trSize<int>& SizeWindow_)
{
	trWidget::APPLY(SizeWindow_);
	selected->Update();
	colorSelected->Update();
}

void trSelector::Display(wostringstream& output_line)
{
	if (IsSelected().GetDataActual())
	{
		SetColorConsole(GetColorSelected().GetDataActual());
		cout << WstringToUtf8(output_line.str());
	}

	if (!IsSelected().GetDataActual())
	{
		SetColorConsole(trWidget::GetColor().GetDataActual());
		cout << WstringToUtf8(output_line.str());
	}
}

trSelector::~trSelector()
{
	delete selected; 
	delete colorSelected;
}
