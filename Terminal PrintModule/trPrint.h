#pragma once

#include "include.h"

#include "trObject.h"

#ifndef __TR_PRINT__
#define __TR_PRINT__

#ifdef TERMINAL_PRINT_MODULE_EXPORTS
#define TERMINAL_PRINT_API __declspec(dllexport)
#else
#define TERMINAL_PRINT_API __declspec(dllimport)
#endif

namespace trPrint
{
	void TERMINAL_PRINT_API trPrint(const std::wstring& ToPrint_);
};

#endif