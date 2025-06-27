#pragma once

#include "include.h"

#include "trCoordinate.h"
#include "trSize.h"
#include "trActor.h"
#include "trData.h"

#ifndef __TR_UI_TOOLS_CORE__
#define __TR_UI_TOOLS_CORE__

#ifdef TERMINAL_CORE_EXPORTS
#define TERMINAL_CORE_API __declspec(dllexport)
#else
#define TERMINAL_CORE_API __declspec(dllimport)
#endif

#define TopLeft 0
#define TopCenter 1
#define TopRight 2
#define MiddleLeft 3
#define MiddleCenter 4
#define MiddleRight 5
#define BottomLeft 6
#define BottomCenter 7
#define BottomRight 8

namespace UIToolsCore
{
	/// <summary>
	/// Permet d'obtenir la taille de la console
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_CORE_API trSize<uint16_t> GetConsoleSize(uint8_t BorderWitdh);

	/// <summary>
	/// Permet d'obtenir la taille de la console
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_CORE_API trSize<uint16_t> GetConsoleSize();

	/// <summary>
	/// Permet de savoir si la fenêtre de l'application est au premier plan
	/// </summary>
	/// <returns> true si la fenêtre est au premier plan, false sinon </returns>
	TERMINAL_CORE_API bool IsMyWindowInFocus();

	/// <summary>
	/// Permet de convertir un wstring en string
	/// </summary>
	/// <param name="wstr"></param>
	/// <returns></returns>
	TERMINAL_CORE_API std::string WstringToUtf8(const std::wstring& wstr);

	/// <summary>
	/// Permet de convertir un string en wstring
	/// </summary>
	/// <param name="color"></param>
	TERMINAL_CORE_API void SetColorConsole(int color);

	/// <summary>
	/// comme le nom l'indique
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	TERMINAL_CORE_API bool IsPureColor(const std::wstring& input);

	/// <summary>
	/// FONCTION VIDE
	/// </summary>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	template<typename obj, typename FuncType, typename... Args>
	void SetFunctionTo(obj* object, FuncType func, Args... args)
	{
		if (object)
		{
			std::invoke(func, object, std::forward<Args>(args)...);
		}
	}
}

#endif