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

#ifndef __TR_WORLD__
#define __TR_WORLD__

#ifdef TERMINAL_WORLD_EXPORTS
#define TERMINAL_WORLD_API __declspec(dllexport)
#else
#define TERMINAL_WORLD_API __declspec(dllimport)
#endif

class TERMINAL_WORLD_API trWorld : public trObject
{
public:

	// INI default

	trWorld();

	// INI deep copy

	trWorld(const trWorld& other);

	// Copy

	trWorld& operator=(const trWorld& other);

	/// ACTOR MANG /// a mettre probablement en static

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
	/// Détruit tous les widgets
	/// </summary>
	/// <returns> true si tous les widgets ont été détruits avec succès, false sinon </returns>
	bool Destroy();

public:

	// GET

	/// <summary>
	/// Obtient un widget par son nom
	/// </summary>
	/// <param name="Name"> Le nom du widget à obtenir </param>
	/// <returns> Un object de type trWidget si le widget existe, nullptr sinon </returns>
	const trActor& GetActor(const std::string& Name) const;

	/// <summary>
	/// Obtient un pointeur vers tous les widgets
	/// </summary>
	/// <returns> Un pointeur vers une map contenant tous les widgets </returns>
	const std::unordered_map<std::string, trActor*>& GetActors() const;

	/// <summary>
	/// Met à jour un widget (rafraichit son contenu, sa position, etc.)
	/// </summary>
	void UpdateActors();

	/// <summary>
	/// Obtient un pointeur vers un widget par son nom
	/// </summary>
	/// <param name="Name"> Le nom du widget à obtenir </param>
	/// <returns> Un pointeur vers un object de type trWidget si le widget existe, nullptr sinon </returns>
	trActor* GetPtrActor(const std::string& Name) const;

public: 

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

public:

	// DESTRUCTEUR

	~trWorld();

private:

	std::unordered_map<std::string, trActor*> *Actors;
};

#endif