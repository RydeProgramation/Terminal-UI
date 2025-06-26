#pragma once

#include "include.h"

#include "trSize.h"
#include "trKeyBoardManagement.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"
#include "trPair.h"
#include "trSelector.h"
#include "trUITools.h"
#include "trActor.h"

#ifndef __TR_UI__
#define __TR_UI__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

#define DIRECT_TERMINAL 0
#define RENDER_SYSTEM 1

class TERMINAL_ENGINE_API trUserInterface : public trObject // séparér les fonctionalités en plusieurs classes (trUI_Render, trUI_Display, trUI_World...)
{
public: 

	// INI default

	trUserInterface();
	
	// INI

	trUserInterface(uint8_t RenderType_, int BordW_, std::wstring RstClr);

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
	/// Raffraichie l'interface utilisateur
	/// </summary>
	virtual void Refresh();

	/// <summary>
	/// Vérifie si l'interface utilisateur doit être rafraichie 
	/// </summary>
	/// <returns> true si l'interface utilisateur doit être rafraichie, false sinon </returns>
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
	/// Sélectionne un widget par son nom
	/// </summary>
	/// <param name="name"> Le nom du widget à sélectionner </param>
	void Select(const std::string& name); // a changer la méthode

	/// <summary>
	/// Séléctionne le widget suivant
	/// </summary>
	void SelectNext();

	/// <summary>
	/// Séléctionne le widget précédent
	/// </summary>
	void SelectPrevious();

	/// WIDGET MANG ///

	/// <summary>
	/// Crée un widget
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="WIDG"> Le widget à créer </param>
	/// <returns> true si le widget a été créé avec succès, false sinon </returns>
	bool CreateActor(trActor* WIDG);

	/// <summary>
	/// Détruit un widget
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="WIDG"> Le widget à détruire </param>
	/// <returns> true si le widget a été détruit avec succès, false sinon </returns>
	bool DestroyActor(trActor* WIDG);

	/// <summary>
	/// Détruit un widget par son nom
	/// </summary>
	/// <typeparam name="Widget_T"> trWidget, trSelector... </typeparam>
	/// <param name="name"> Le nom du widget à détruire </param>
	/// <returns> true si le widget a été détruit avec succès, false sinon </returns>
	bool DestroyActor(const std::string& Name);

	/// <summary>
	/// Obtient un widget par son nom
	/// </summary>
	/// <param name="Name"> Le nom du widget à obtenir </param>
	/// <returns> Un object de type trWidget si le widget existe, nullptr sinon </returns>
	const trActor GetActor(const std::string& Name) const;

protected:
		
	/// <summary>
	/// Obtient un pointeur vers un widget par son nom
	/// </summary>
	/// <param name="Name"> Le nom du widget à obtenir </param>
	/// <returns> Un pointeur vers un object de type trWidget si le widget existe, nullptr sinon </returns>
	trActor* GetPtrActor(const std::string& Name) const;

public: // IL FAUDERA VRAIMENT MODIFIER L'ENDROIT OU ON FAIT ÇA

	/// <summary>
	/// Pour éxécuter une fonciton sur un Widget
	/// </summary>
	/// <param Name="Name_">Le nom du Widget</param>
	/// <param Name="func">L'adresse de la fonction par exemple (&trWidget::AddToContent)</param>
	/// <param Name="...args">Les argument</param>
	template <typename Func, typename... Args>
	void SetActor(const std::string& Name, Func&& func, Args&&... args)
	{
		trWidget* widget = dynamic_cast<trWidget*>((*Actors)[Name]);

		if (/*(*Actors)[Name]*/widget != nullptr)
		{
			std::invoke(std::forward<Func>(func), /*(*Actors)[Name]*/widget, std::forward<Args>(args)...);
		}
	}

	// TEST

	/*/// invoke_if_possible : appelle la fonction si elle est valide
	template <typename T, typename Func, typename... Args>
	auto invoke_if_possible(T* object, Func&& func, Args&&... args)
		-> std::enable_if_t<std::is_invocable_v<Func, T*, Args...>>
	{
		std::invoke(std::forward<Func>(func), object, std::forward<Args>(args)...);
	}

	/// Surcharge : si la fonction n'est pas invocable, ne fait rien
	template <typename T, typename Func, typename... Args>
	auto invoke_if_possible(T* / *object* /, Func&& / *func* /, Args&&... / *args* /)
		-> std::enable_if_t<!std::is_invocable_v<Func, T*, Args...>>
	{
		// Rien du tout 😄
	}

	/// Et ta fonction principale :
	template <typename Func, typename... Args>
	void SetActor(const std::string& Name, Func&& func, Args&&... args)
	{
		auto it = Actors->find(Name);
		if (it != Actors->end() && it->second)
		{
			// On ne sait pas le type réel, donc on tente dynamiquement
			trActor* base = it->second;
			invoke_if_possible(base, std::forward<Func>(func), std::forward<Args>(args)...);
		}
	}*/

private: // FNC

	/// <summary>
	/// Affiche un widget
	/// </summary>
	/// <param name="WIDG"> Le widget à afficher </param>
	/// <returns> true si le widget a été affiché avec succès, false sinon </returns>
	void DisplayWidget(trWidget* WIDG); // à vérifier

	/// <summary>
	/// Aplique les couleurs
	/// </summary>
	void DisplayColor(); // à verifier

	/// <summary>
	/// Cache un widget (le rend invisible)
	/// </summary>
	/// <param name="WIDG"> Le widget à cacher </param>
	void HideWidget(trWidget* WIDG);

	/// <summary>
	/// Nettoie un widget (le rend vide)
	/// </summary>
	/// <param name="WIDG"> Le widget à nettoyer </param>
	void CleanWidget(trWidget* WIDG);

	/// <summary>
	/// Met à jour un widget (rafraichit son contenu, sa position, etc.)
	/// </summary>
	void UpdateActors();

	/// <summary>
	/// Boucle principale de l'interface utilisateur
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
	/// <param name="Pos"> Position du curseur </param>
	/// <param name="Output"> Ostream dans lequel on va écrire </param>
	void MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* Output, const trSize<uint16_t>& SizeOutput);

	/// <summary>
	/// Permet de déplacer pour un ostrinstream donnée la position du curseur en tenant compte de la bordure
	/// </summary>
	/// <param name="Pos"> Position du curseur </param>
	/// <param name="Output"> Ostream dans lequel on va écrire </param>
	/// <param name="SizeOutput"> Taille de l'output (pour le terminal) </param>
	/// <param name="BorderW"> Largeur de la bordure </param>
	void MoveCursorToOstream(const trCoordinate<int>& Pos, std::wostringstream* Output, const trSize<uint16_t>& SizeOutput, uint8_t BorderW);

	/// <summary>
	/// Permet de déplacer pour un ostrinstream donnée la position du curseur
	/// </summary>
	/// <param name="Pos"> Position du curseur </param>
	/// <param name="Output"> Ostream dans lequel on va écrire </param>
	void CleanOstreamSize(std::wostringstream* Output, const trSize<uint16_t>& SizeOutput);

public:

	// DESTRUCTEUR

	~trUserInterface();

protected:

	trKeyBoardManagement *KB;

	uint8_t BorderWidth;

	std::wstring *BaseColor;

	std::mutex* Mutex; // Mutex pour les threads et a voir pour mieux les utiliser de façon plus propore et moins a la râche

private:

	std::unordered_map<std::string, trActor*> *Actors;

	std::thread *Thr_UI;

	std::thread *Thr_KB;

	trSize<uint16_t> *SizeWindow;

	trData<int> *CursorSelector;

	std::wostringstream *Render_;

	std::wostringstream *RenderColor_;

	uint8_t RenderType;

	bool Refreshed = false;

	bool ForceRefresh = false;
};

TERMINAL_ENGINE_API trUserInterface* CreateUserInterface();

#endif