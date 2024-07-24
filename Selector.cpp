#include "include.h"
#include "UI_Tools.h"
#include "Selector.h"

using namespace std;
using namespace UITools;

// SET

Selector::Selector(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, string content_, string name_) : Widget(x_, y_, size_x_, size_y_, RelativePosition_, content_, name_), selected(true), colorSelected(14)
{

}

void Selector::SetSelected(bool Slct)
{
	selected.SetData(Slct);
}

void Selector::SetColorSelected(int color)
{
	colorSelected.SetData(color);
}

// GET

Data<bool> Selector::IsSelected() const
{
	return selected;
}

Data<int> Selector::GetColorSelected() const
{
	return colorSelected;
}

// APPLY

void Selector::APPLY(Size<int> SizeWindow_)
{
	Widget::APPLY(SizeWindow_);
	selected.Update();
	colorSelected.Update();
}

void Selector::Display(ostringstream& output_line)
{
	if (IsSelected().GetDataActual())
	{
		SetColorConsole(GetColorSelected().GetDataActual());
		cout << output_line.str();
	}

	if (!IsSelected().GetDataActual())
	{
		SetColorConsole(GetColor().GetDataActual());
		cout << output_line.str();
	}
}
