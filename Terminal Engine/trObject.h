#pragma once

#include "include.h"

#ifndef __TR_OBJECT__
#define __TR_OBJECT__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

class TERMINAL_ENGINE_API trObject 
{
public:
	trObject() = default;

	virtual ~trObject() = default;
};

#endif
