#pragma once

#include "include.h"

#ifndef __TR_OBJECT__
#define __TR_OBJECT__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

class TERMINAL_ENGINE_API trObject // object simple : JE VAIS ESSAYER D'ARRETER LES PROBLEMES AVEC CA
{
public:
	trObject() = default;

	virtual ~trObject() = default;

private:
	void destroy_() { delete this; } // Peut causer des problèmes NE PAS APPELER
};

#endif
