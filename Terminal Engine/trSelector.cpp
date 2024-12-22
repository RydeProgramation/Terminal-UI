#include "trUI_Tools.h"
#include "trSelector.h"

using namespace std;
using namespace UITools;

// INI

trSelector::trSelector(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, wstring content_, string name_) : trWidget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_), selected(true), colorSelected(14)
{

}

// SET

void trSelector::SetSelected(bool Slct)
{
	selected.SetData(Slct);
}

void trSelector::SetColorSelected(int color)
{
	colorSelected.SetData(color);
}

// GET

const trData<bool> trSelector::IsSelected() const
{
	return selected;
}

const trData<int> trSelector::GetColorSelected() const
{
	return colorSelected;
}

// APPLY

void trSelector::APPLY(const trSize<int>& SizeWindow_)
{
	trWidget::APPLY(SizeWindow_);
	selected.Update();
	colorSelected.Update();
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