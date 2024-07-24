#pragma once

#include "include.h"
#include "Coordinate.h"
#include "Size.h"
#include "Widget.h"
#include "Data.h"

#ifndef __UI_TOOLS__
#define __UI_TOOLS__

namespace UITools
{
	/// <summary>
	/// Déplace le curseur vers
	/// </summary>
	/// <param name="Coordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	void MoveCursorTo(Coordinate<int> Coordinate, int BorderWitdh);

	/// <summary>
	/// Déplace le curseur vers
	/// </summary>
	/// <param name="Coordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	void MoveCursorTo(Coordinate<int> Coordinate);

	/// <summary>
	/// Cache le curseur
	/// </summary>
	void hideCursor();

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="Coordinate"></param>
	/// <returns></returns>
	// template <typename Widget_T>
	bool IsOutSide(Coordinate<int> xy, int BorderWidth);

	/// <summary>
	/// Permet de verfier si les coordonnées données sont en dehors de la fenêtre
	/// </summary>
	/// <param name="WIDG"></param>
	/// <param name="Coordinate"></param>
	/// <returns></returns>
	// template <typename Widget_T>
	bool IsOutSide(Coordinate<int> xy);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	bool IsInWidget(Widget* WIDG, Coordinate<int> crd);

	/// <summary>
	///
	/// </summary>
	/// <param name="color"></param>
	void SetColorConsole(int color);

	/// <summary>
	/// Permet d'obtenir la taille de la console
	/// </summary>
	/// <param name="Coordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	Size<int> GetConsoleSize(int BorderWitdh);

	/// <summary>
	/// Permet d'obtenir la taille de la console
	/// </summary>
	/// <param name="Coordinate"></param>
	/// <param name="WithBorder"> Mettre false si tu veux être à l'interieur des bordures </param>
	Size<int> GetConsoleSize();
}

#endif