#pragma once

#include "include.h"

#include "trCoordinate.h"
#include "trSize.h"
#include "trWidget.h"
#include "trData.h"

#ifndef __TR_UI_TOOLS__
#define __TR_UI_TOOLS__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

namespace UITools
{
	/// <summary>
	/// Déplace le curseur vers
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_ENGINE_API void MoveCursorTo(trCoordinate<int> trCoordinate, int BorderWitdh);

	/// <summary>
	/// Déplace le curseur vers
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_ENGINE_API void MoveCursorTo(trCoordinate<int> trCoordinate);

	/// <summary>
	/// Cache le curseur
	/// </summary>
	TERMINAL_ENGINE_API void hideCursor();

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="trCoordinate"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(trCoordinate<int> xy, int BorderWidth);

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="trCoordinate"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(trCoordinate<int> xy);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsInWidget(trWidget* WIDG, trCoordinate<int> crd);

	/// <summary>
	///
	/// </summary>
	/// <param name="color"></param>
	TERMINAL_ENGINE_API void SetColorConsole(int color);

	/// <summary>
	/// Permet d'obtenir la taille de la console
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_ENGINE_API trSize<int> GetConsoleSize(int BorderWitdh);

	/// <summary>
	/// Permet d'obtenir la taille de la console
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_ENGINE_API trSize<int> GetConsoleSize();

	/// <summary>
	/// Permet de convertir un wstring en string
	/// </summary>
	/// <param name="wstr"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API std::string WstringToUtf8(const std::wstring& wstr);

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