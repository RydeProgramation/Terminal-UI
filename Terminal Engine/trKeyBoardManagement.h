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

	// INI
	trKeyBoardManagement();

	// FNC
	/// <summary>
	/// Permet de gérer l'action sur les boutons
	/// </summary>
	void ActionBTN() /*override*/;

	// Create
	/// <summary>
	/// 
	/// </summary>
	bool CreateBTN(trBTN_Key* Btns) /*override*/;

	// SET
	void SetActionBtnKey(int key, void (*action)()) /*override*/;

	// GET
	const std::vector<trBTN_Key*>& GetBTNS() const /*override*/; // PROBLEME JE PENSE

	// Update
	/// <summary>
	/// Traitement du Clavier
	/// </summary>
	virtual void Update() /*override*/;

	// FNC
	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns> Position in the vector BTNS </returns>
	int BtnResearch(int key) /*override*/;

	// START
	void Start() /*override*/;

	// DESTRUCTEUR
	~trKeyBoardManagement();

private:
	void Loop();

protected:
	std::vector<trBTN_Key*> *BTNS; // Je sais pas quoi choisir entre vector et unoredered_map...

private:
	bool start;
};

#endif
