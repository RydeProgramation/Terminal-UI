#pragma once

#include "include.h"
#include "BTN_Key.h"
#include "Size.h"
#include "Coordinate.h"

#ifndef __KEYBOARD_M__
#define __KEYBOARD_M__

class KeyBoardManagement
{
protected:

	std::vector<BTN_Key*> BTNS;

private:

	bool start;

public:

	KeyBoardManagement();

	/// <summary>
	/// Permet de gérer l'action sur les bouton
	/// </summary>
	void ActionBTN();

	// Create

	/// <summary>
	/// 
	/// </summary>
	bool CreateBTN(BTN_Key* Btns);

	// SET

	void SetActionBtnKey(int key, void (*action)());

	// GET

	std::vector<BTN_Key*> GetBTNS() const;

	// Update

	/// <summary>
	/// Traitement du Clavier
	/// </summary>
	virtual void Update();

	// FNC

	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns> Position in the vector BTNS </returns>
	int BtnResearch(int key);

	// START

	void Start();

private:

	void Loop();

};

#endif