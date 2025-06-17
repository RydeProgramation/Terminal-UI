#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"

#ifndef __TR_ACTOR__
#define __TR_ACTOR__

#ifdef TERMINAL_COMPONENTS_EXPORTS
#define TERMINAL_COMPONENTS_API __declspec(dllexport)
#else
#define TERMINAL_COMPONENTS_API __declspec(dllimport)
#endif

struct TERMINAL_COMPONENTS_API trActor : trWidget
{
public:

	// INI default

	trActor();

	// INI

	trActor(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, std::wstring content_, std::string name_);

	// INI deep copy

	trActor(const trActor& other);

	// Copy

	trActor& operator=(const trActor& other);

	// APPLY

	void APPLY(const trSize<int>& SizeWindow_) override;

	virtual void APPLY_Implementation();

	// DESTRUCTEUR

	~trActor();

private:


};

#endif