#pragma once

#include "include.h"

#include "trSize.h"
#include "trKeyBoardManagement.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"
#include "trPair.h"
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

	// INI default

	trUserInterface();
	
	// INI

	trUserInterface(int RenderType_, int BordW_, std::wstring RstClr);

	// INI deep copy

	trUserInterface(const trUserInterface& other);

	// Copy

	trUserInterface& operator=(const trUserInterface& other);
	
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

	/// <summary>
	/// Pour éxécuter une fonciton sur un Widget
	/// </summary>
	/// <param name="name">Le nom du Widget</param>
	/// <param name="func">L'adresse de la fonction par exemple (&trWidget::AddToContent)</param>
	/// <param name="...args">Les argument</param>
	template <typename Func, typename... Args>
	void SetWidget(const std::string& name, Func&& func, Args&&... args) 
	{
		if ((*Widgets)[name] != nullptr)
		{
			std::invoke(std::forward<Func>(func), (*Widgets)[name], std::forward<Args>(args)...);
		}
	}

private: // FNC

	/// <summary>
	/// Affiche un widget
	/// </summary>
	/// <param name="WIDG"></param>
	/// <returns></returns>
	void DisplayWidget(trWidget* WIDG); // à vérifier

	/// <summary>
	/// Aplique les couleurs
	/// </summary>
	void DisplayColor(); // à verifier

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

	// Fonciton utilise (à deplacer dans trUiTools je pense)

	/// <summary>
	/// Permet de déplacer pour un ostrinstream donnée la position du curseur
	/// </summary>
	/// <param name="Pos"></param>
	/// <param name="output"></param>
	void MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* output, const trSize<int>& SizeOutput);

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

public:

	// DESTRUCTEUR

	~trUserInterface();

protected:

	trKeyBoardManagement *KB;

	int BorderWidth;

	std::wstring *BaseColor;

	std::mutex *mtx;

private:

	std::unordered_map<std::string, trWidget*> *Widgets;

	std::thread *T;

	std::thread *T2;

	trSize<int> *SizeWindow;

	trData<int> *CursorSelector;

	std::wostringstream *Render_;

	std::wostringstream *RenderColor_;

	int RenderType;

	bool Refreshed = false;
};

TERMINAL_ENGINE_API trUserInterface* CreateUserInterface();

// #include "UI.inl" // <-- Inutile

#endif