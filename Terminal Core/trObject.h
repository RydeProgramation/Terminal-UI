#pragma once

#include "include.h"

#ifndef __TR_OBJECT__
#define __TR_OBJECT__

#ifdef TERMINAL_CORE_EXPORTS
#define TERMINAL_CORE_API __declspec(dllexport)
#else
#define TERMINAL_CORE_API __declspec(dllimport)
#endif

class TERMINAL_CORE_API trObject
{
public:
	trObject() = default;

	virtual ~trObject() = default;
};

#endif