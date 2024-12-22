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

#define DIRECT_TERMINAL 0
#define RENDER_SYSTEM 1

class TERMINAL_ENGINE_API trUserInterface : trObject // RANGER LES FONCTINON C'EST DANS UN BORDEL PAS POSSIBLE
{
public: 
	
	// INI

	trUserInterface(int RenderType_);
	
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
	/// Permet de déplacer pour un ostrinstream donnée la position du curseur
	/// </summary>
	/// <param name="Pos"></param>
	/// <param name="output"></param>
	void MoveCursorToOstream(const trCoordinate<int> &Pos, std::wostringstream *output, const trSize<int> &SizeOutput);

	/// <summary>
	/// Permet de déplacer pour un ostrinstream donnée la position du curseur en prenant compte de la bordure
	/// </summary>
	/// <param name="Pos"></param>
	/// <param name="output"></param>
	/// <param name="BorderW"></param>
	void MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* output, const trSize<int>& SizeOutput, int BorderW);

	/// <summary>
	/// Permet de déplacer pour un ostrinstream donnée la position du curseur
	/// </summary>
	/// <param name="Pos"></param>
	/// <param name="output"></param>
	void CleanOstreamSize(std::wostringstream* output, const trSize<int>& SizeOutput);

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

	/// <summary>
	/// Raffraichie le terminal en affichant les "pixel"
	/// </summary>
	void Render();

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

	std::wostringstream *Render_;

	int RenderType;
};

TERMINAL_ENGINE_API trUserInterface* CreateUserInterface();

// #include "UI.inl" // <-- Inutile

#endif