#include "trUI_Tools.h"
#include "trSelector.h"

using namespace std;
using namespace UITools;

// INI default

trSelector::trSelector() : trWidget(), Selected(new trData<bool>(false)), ColorSelected(new trData<int>(0))
{
}

// INI

trSelector::trSelector(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, wstring content_, string name_) : trWidget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_), Selected(new trData<bool>(true)), ColorSelected(new trData<int>(14))
{

}

// INI deep copy

trSelector::trSelector(const trSelector& other) : trWidget(other), Selected(other.Selected), ColorSelected(other.ColorSelected)
{

}

// Copy

trSelector& trSelector::operator=(const trSelector& other)
{
	// Si on est en train de se copier soi-même, il n'y a rien à faire
	if (this == &other) { return *this; }

	trWidget::operator=(other);;

	Selected = new trData<bool>(*other.Selected);
	ColorSelected = new trData<int>(*other.ColorSelected);

	return *this;
}

// SET

void trSelector::SetSelected(bool Slct)
{
	Selected->SetData(Slct);
}

void trSelector::SetColorSelected(int color)
{
	ColorSelected->SetData(color);
}

// GET

const trData<bool> trSelector::IsSelected() const
{
	return *Selected;
}

const trData<int> trSelector::GetColorSelected() const
{
	return *ColorSelected;
}

// APPLY

void trSelector::APPLY(const trSize<int>& SizeWindow_)
{
	trWidget::APPLY(SizeWindow_);
	Selected->Update();
	ColorSelected->Update();
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
	delete Selected; 
	delete ColorSelected;
}
