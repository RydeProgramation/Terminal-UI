#pragma once

#include "include.h"
#include "trBTN_Key.h"
#include "trSize.h"
#include "trCoordinate.h"

#ifndef __TR_KEYBOARD_M__
#define __TR_KEYBOARD_M__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

class TERMINAL_ENGINE_API trKeyBoardManagement : trObject
{
public:

	// INI && default
	trKeyBoardManagement();

	// INI deep copy
	trKeyBoardManagement(const trKeyBoardManagement& other);

	// copy
	trKeyBoardManagement& operator=(const trKeyBoardManagement& other);

	// FNC
	/// <summary>
	/// Permet de gérer l'action sur les boutons
	/// </summary>
	void ActionBTN(); // Pas utilise je pense

	// Create
	/// <summary>
	/// 
	/// </summary>
	bool CreateBTN(const trBTN_Key& Btns);

	// SET
	void SetActionBtnKey(int Key, void (*action)());

	// GET
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const std::unordered_map<int, trBTN_Key>& GetBTNS() const; // PROBLEME JE PENSE

	// Update
	/// <summary>
	/// Traitement du Clavier
	/// </summary>
	virtual void Update();

	// FNC
	

	// START
	void Start();

	// DESTRUCTEUR
	~trKeyBoardManagement();

private:

	void Loop();

protected:

	std::unordered_map<int, trBTN_Key> *BTNS; // Je sais pas quoi choisir entre vector et unoredered_map...

private:

	bool Start_ = false;
};

#endif
