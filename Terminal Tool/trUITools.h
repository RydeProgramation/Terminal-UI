#pragma once

#include "include.h"

#include "trCoordinate.h"
#include "trSize.h"
#include "trWidget.h"
#include "trData.h"
#include "trUIToolsCore.h"

#ifndef __TR_UI_TOOLS__
#define __TR_UI_TOOLS__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

namespace UITools
{
	using namespace UIToolsCore;

	/// <summary>
	/// Déplace le curseur vers
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_ENGINE_API void MoveCursorTo(const trCoordinate<int>& Coordinate_, uint8_t BorderWitdh_);

	/// <summary>
	/// Déplace le curseur vers
	/// </summary>
	/// <param name="trCoordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	TERMINAL_ENGINE_API void MoveCursorTo(const trCoordinate<int>& Coordinate_);

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
	TERMINAL_ENGINE_API bool IsOutSide(const trCoordinate<int>& xy, uint8_t BorderWidth_);

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="trCoordinate"></param>
	/// <param name="CountTouch"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(const trCoordinate<int>& xy, uint8_t BorderWidth_, bool CountTouch);

	/// <summary>
	/// Permet de verifier si c'est en dehors juste avec les coord 1 dimensions
	/// </summary>
	/// <param name="z"></param>
	/// <param name="BorderWidth"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(int z, uint8_t BorderWidth_, bool CountTouch);

	/// <summary>
	/// Permet de verifier si c'est en dehors juste avec les coord 1 dimensions
	/// </summary>
	/// <param name="z"></param>
	/// <param name="BorderWidth"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(int z, uint8_t BorderWidth_);

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="trCoordinate"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(const trCoordinate<int>& xy);

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="trCoordinate"></param>
	/// <param name="CountTouch"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(const trCoordinate<int>& xy, bool CountTouch);

	/// <summary>
	/// Permet de verifier si c'est en dehors juste avec les coord 1 dimensions
	/// </summary>
	/// <param name="z"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(int z);
	
	/// <summary>
	/// Permet de verifier si c'est en dehors juste avec les coord 1 dimensions
	/// </summary>
	/// <param name="z"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsOutSide(int z, bool CountTouch);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	TERMINAL_ENGINE_API bool IsInWidget(trWidget* WIDG, const trCoordinate<int>& crd);
}

#endif