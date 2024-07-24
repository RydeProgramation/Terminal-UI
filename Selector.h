#pragma once

#include "include.h"
#include "Size.h"
#include "Coordinate.h"
#include "Widget.h"
#include "Data.h"

#ifndef __SELECTOR__
#define __SELECTOR__

struct Selector : Widget
{
private:

	Data<bool> selected;

	Data<int> colorSelected;

public:

	Selector(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, std::string content_, std::string name_);

	// SET

	void SetSelected(bool Slct);

	void SetColorSelected(int color);

	// GET

	Data<bool> IsSelected() const;

	Data<int> GetColorSelected() const;

	// APPLY

	void APPLY(Size<int>SizeWindow_) override;

	void Display(ostringstream& output_line) override;
};

#endif