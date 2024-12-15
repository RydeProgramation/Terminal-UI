#pragma once

#include "include.h"

#include "trSize.h"
#include "trKeyBoardManagement.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"
#include "trSelector.h"
#include "trUI_Tools.h"

#ifndef __TR_UI__
#define __TR_UI__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

// INTERFACE INUTILE

/*
class TERMINAL_ENGINE_API trUserInterface // RANGER LES FONCTINON C'EST DANS UN BORDEL PAS POSSIBLE
{
public:

	// DEF
	virtual ~trUserInterface() = default;

	// FNC

	/// <summary>
	/// Lance l'interface utilisateur
	/// </summary>
	virtual void Start() = 0;

	/// <summary>
	/// Update (cote...);
	/// </summary>
	/// <param name="BorderWidth"> BorderWidth des * </param>
	virtual void Update() = 0;

	/// <summary>
	/// 
	/// </summary>
	virtual void Refresh() = 0;

	/// <summary>
	/// 
	/// </summary>
	virtual bool RefreshVerification() = 0;

	/// <summary>
	/// Crée une bordure
	/// </summary>
	/// <param name="BorderWidth">Nombre de pixel sur le coté</param>
	virtual void Border() = 0;

	/// <summary>
	/// SetupConsole
	/// </summary>
	virtual void SetupConsole() = 0;

	/// SELECTION ///

	/// <summary>
	/// Select (trSelector...)
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	virtual void Select(std::string name) = 0; // a changer la méthode

	/// <summary>
	/// /
	/// </summary>
	virtual void SelectNext() = 0;

	/// <summary>
	/// 
	/// </summary>
	virtual void SelectPrevious() = 0;

	/// WIDGET MANG ///

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	// template <typename Widget_T>
	virtual bool CreateWidget(trWidget* WIDG) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	// template <typename Widget_T> 
	virtual bool DestroyWidget(trWidget* WIDG) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	// template <typename Widget_T> 
	virtual bool DestroyWidget(std::string name) = 0;

	/// <summary>
	/// FONCTION VIDE
	/// </summary>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	virtual trWidget GetWidget(std::string name) const = 0;
};*/

class TERMINAL_ENGINE_API trUserInterface : trObject // RANGER LES FONCTINON C'EST DANS UN BORDEL PAS POSSIBLE
{
public: 
	
	// INI

	trUserInterface();
	
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

	/// SELECTION ///

	/// <summary>
	/// Select (trSelector...)
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	void Select(const std::string& name); // a changer la méthode

	/// <summary>
	/// /
	/// </summary>
	void SelectNext();

	/// <summary>
	/// 
	/// </summary>
	void SelectPrevious();

	/// WIDGET MANG ///

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	bool CreateWidget(trWidget* WIDG);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	bool DestroyWidget(trWidget* WIDG);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	bool DestroyWidget(const std::string& name);

	/// <summary>
	/// FONCTION VIDE
	/// </summary>
	/// <param name="name"></param>
	/// <param name="WIDG"></param>
	const trWidget GetWidget(const std::string& name) const;

	template <typename Func, typename... Args>
	void SetWidget(const std::string& name, Func&& func, Args&&... args) 
	{
		std::invoke(std::forward<Func>(func), (*Widgets)[name], std::forward<Args>(args)...);
	}

private: // FNC

	/// <summary>
	/// Affiche un widget
	/// </summary>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	int DisplayWidget(trWidget* WIDG); // pas fini

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	void HideWidget(trWidget* WIDG);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="WIDG"></param>
	void CleanWidget(trWidget* WIDG);

	/// <summary>
	/// 
	/// </summary>
	void UpdateWidget();

	/// <summary>
	/// 
	/// </summary>
	void Loop();

public:

	// DESTRUCTEUR

	~trUserInterface();

protected:

	trKeyBoardManagement *KB;

	int BorderWidth;

	std::mutex *mtx;

private:

	std::unordered_map<std::string, trWidget*> *Widgets;

	std::thread *T;

	std::thread *T2;

	trSize<int> *SizeWindow;

	trData<int> *CursorSelector;
};

TERMINAL_ENGINE_API trUserInterface* CreateUserInterface();

// #include "UI.inl" // <-- Inutile

#endif