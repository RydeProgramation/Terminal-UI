#pragma once

#include "include.h"
#include "Size.h"
#include "KeyBoardManagement.h"
#include "Coordinate.h"
#include "Widget.h"
#include "Data.h"

#ifndef __UI__
#define __UI__

class UserInterface
{
protected:

	KeyBoardManagement KB; // Regarder s'il ne faut pas le faire en pointeur ? si jamais quelqu'un fait une dérivé de KeyboardManagement ?

	int BorderWidth;
	
	std::mutex mtx;
	
private:
	
	std::vector<Widget*> Widgets;

	std::vector<Widget*> ToPushWidgets;

	std::thread T;

	std::thread T2;

	Size<int> SizeWindow;

	Data<int> CursorSelector;

public: 
	
	// INI

	UserInterface();
	
	// FNC

	/// <summary>
	/// Lance l'interface utilisateur
	/// </summary>
	virtual void Start();

	/// <summary>
	/// Update (cote...);
	/// </summary>
	/// <param name="BorderWidth"> BorderWidth des * </param>
	virtual void Update();

	/// <summary>
	/// 
	/// </summary>
	virtual void Refresh();

	/// <summary>
	/// 
	/// </summary>
	bool RefreshVerification();

	/// <summary>
	/// Crée une bordure
	/// </summary>
	/// <param name="BorderWidth">Nombre de pixel sur le coté</param>
	void Border();

	/// <summary>
	/// SetupConsole
	/// </summary>
	virtual void SetupConsole();

	/// <summary>
	/// FONCTION VIDE
	/// </summary>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	template<typename FuncType, typename... Args>
	void SetWidget(string name, FuncType func, Args... args);

	/// <summary>
	/// FONCTION VIDE
	/// </summary>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	Widget GetWidget(int index) const;

	/// <summary>
	/// Permet d'obtenir la position dans le vecteur d'un widget
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	std::optional<int> WidgetResearch(std::string name);

	/// <summary>
	/// SetWidget to destroy (without directly destroy it)
	/// </summary>
	/// <param name="name"></param>
	void ToDestroyWidget(std::string name);

	/// <summary>
	/// SetWidget to destroy (without directly destroy it)
	/// </summary>
	/// <param name="name"></param>
	void ToCreateWidget(Widget* WIDG); // <--- a voir si c'est a utiliser

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> Widget, Selector... </typeparam>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	// template <typename Widget_T>
	bool CreateWidget(Widget* WIDG);

	/// <summary>
	/// Select (Selector...)
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	void Select(std::string name); // a changer la méthode

	/// <summary>
	/// /
	/// </summary>
	void SelectNext();

	/// <summary>
	/// 
	/// </summary>
	void SelectPrevious();

private: // FNC

	/// <summary>
	/// Affiche un widget
	/// </summary>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	int DisplayWidget(Widget* WIDG); // pas fini

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	void HideWidget(Widget* WIDG);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	void CleanWidget(Widget* WIDG);

	//void

	/// <summary>
	/// 
	/// </summary>
	void UpdateWidget();

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> Widget, Selector... </typeparam>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	// template <typename Widget_T> 
	bool DestroyWidget(Widget* WIDG); 

	/// <summary>
	///
	/// </summary>
	/// <param name="WIDG"></param>
	bool ManageWidget(Widget* WIDG, int Manage);

	/// <summary>
	/// 
	/// </summary>
	void Loop();
};

#endif