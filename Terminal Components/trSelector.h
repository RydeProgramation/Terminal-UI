#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"

#ifndef __TR_SELECTOR__
#define __TR_SELECTOR__

#ifdef TERMINAL_COMPONENTS_EXPORTS
#define TERMINAL_COMPONENTS_API __declspec(dllexport)
#else
#define TERMINAL_COMPONENTS_API __declspec(dllimport)
#endif

struct TERMINAL_COMPONENTS_API trSelector : trWidget
{
public:

	// INI default

	trSelector();

	// INI

	trSelector(int x_, int y_, int size_x_, int size_y_, uint8_t RelativePosition_, std::wstring content_, std::string name_);

	// INI deep copy

	trSelector(const trSelector& other);

	// Copy

	trSelector& operator=(const trSelector& other);

	// SET

	void SetSelected(bool Slct);

	void SetColorSelected(int color);

	// GET

	const trData<bool> IsSelected() const;

	const trData<int> GetColorSelected() const;

	// APPLY

	void APPLY_(const trSize<uint16_t>& SizeWindow) override;

	void Display(std::wostringstream& OutputLine) override;

	// DESTRUCTEUR

	~trSelector();

private:

	trData<bool> *Selected;

	trData<int> *ColorSelected;
};

#endif