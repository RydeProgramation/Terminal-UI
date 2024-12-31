#include "trKeyBoardManagement.h"

using namespace std;

// INI
trKeyBoardManagement::trKeyBoardManagement() : Start_(false), BTNS(new std::unordered_map<int, trBTN_Key>())
{
	
}

// INI deep copy
trKeyBoardManagement::trKeyBoardManagement(const trKeyBoardManagement& other) : Start_(other.Start_), BTNS(new std::unordered_map<int, trBTN_Key>(*other.BTNS))
{

}

// copy
trKeyBoardManagement& trKeyBoardManagement::operator=(const trKeyBoardManagement& other)
{
	if (this == &other) { return *this; }

	Start_ = other.Start_;
	BTNS = new std::unordered_map<int, trBTN_Key>(*other.BTNS);

	return *this;
}

// FNC
void trKeyBoardManagement::ActionBTN() // PAS OTPI DU TOUT
{
	/*Action Mapping : Correspond aux actions comme "Sauter", "Tirer".
Axis Mapping : Correspond aux axes comme "Déplacement horizontal" ou "Rotation de la caméra".*/

	// faire plutot

	/*
	Recevoir la touche du clavier : c'est fonction
	BTNS[Key]->Action();
	*/
}

bool trKeyBoardManagement::CreateBTN(const trBTN_Key& Btn)
{
	(*BTNS)[Btn.GetKey()] = Btn;

	return true;
}

// SET
void trKeyBoardManagement::SetActionBtnKey(int Key, void (*action)()) 
{
	(*BTNS)[Key].SetAction(action);
}

// GET
const std::unordered_map<int, trBTN_Key>& trKeyBoardManagement::GetBTNS() const
{
	return *BTNS;
}

// UPDATE
void trKeyBoardManagement::Update() 
{
	for (auto& it : *BTNS) 
	{
		it.second.Update(); // ne sert a rien
	}

	ActionBTN();
}

// START
void trKeyBoardManagement::Start() 
{
	if (!Start_) 
	{
		Start_ = true;
		Loop();
	}
}

// LOOP
void trKeyBoardManagement::Loop() 
{
	while (true) 
	{
		Update();
	}
}

trKeyBoardManagement::~trKeyBoardManagement()
{
	delete BTNS;
}

