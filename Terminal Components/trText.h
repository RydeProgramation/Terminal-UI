#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"

#ifndef __TR_TEXT__
#define __TR_TEXT__

#ifdef TERMINAL_COMPONENTS_EXPORTS
#define TERMINAL_COMPONENTS_API __declspec(dllexport)
#else
#define TERMINAL_COMPONENTS_API __declspec(dllimport)
#endif

struct TERMINAL_COMPONENTS_API trText : public trWidget
{
public:

	// INI default

	trText();

	virtual void Init() override;

	// INI

	trText(int x_, int y_, int size_x_, int size_y_, uint8_t RelativePosition_, std::wstring content_, std::string name_);

	// INI deep copy

	trText(const trText& other);

	// Copy

	trText& operator=(const trText& other);

	// SET



	// GET



	// APPLY

	bool VerificationProprety() override;

	void APPLY_(const trSize<uint16_t>& SizeWindow) override;

	// DESTRUCTEUR

	~trText();

private:

	
};

#endif