#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"

#ifndef __TR_SELECTOR__
#define __TR_SELECTOR__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

struct TERMINAL_ENGINE_API trSelector : trWidget
{
public:

	// INI

	trSelector(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, std::wstring content_, std::string name_);

	// SET

	void SetSelected(bool Slct);

	void SetColorSelected(int color);

	// GET

	const trData<bool> IsSelected() const;

	const trData<int> GetColorSelected() const;

	// APPLY

	void APPLY(const trSize<int>& SizeWindow_) override;

	void Display(std::wostringstream& output_line) override;

	// DESTRUCTEUR

	~trSelector() = default;

private:

	trData<bool> selected;

	trData<int> colorSelected;
};

#endif