#include "trKeyBoardManagement.h"

using namespace std;

// INI
trKeyBoardManagement::trKeyBoardManagement() : start(false), BTNS(new vector<trBTN_Key*>)
{
	
}

// INI deep copy
trKeyBoardManagement::trKeyBoardManagement(const trKeyBoardManagement& other) : start(other.start), BTNS(new vector<trBTN_Key*>(*other.BTNS))
{

}

// copy
trKeyBoardManagement& trKeyBoardManagement::operator=(const trKeyBoardManagement& other)
{
	if (this == &other) { return *this; }

	start = other.start;
	BTNS = new vector<trBTN_Key*>(*other.BTNS);

	return *this;
}

// FNC
void trKeyBoardManagement::ActionBTN() // PAS OTPI DU TOUT
{
	for (size_t i = 0; i < BTNS->size(); i++) 
	{
		if ((*BTNS)[i]->GetDetachKey()) 
		{
			(*BTNS)[i]->Action();
		}
	}

	// faire plutot

	/*
	Recevoir la touche du clavier : c'est fonction
	BTNS[key]->Action();
	*/
}

bool trKeyBoardManagement::CreateBTN(trBTN_Key* Btns)
{
	for (size_t i = 0; i < BTNS->size(); i++) 
	{
		if ((*BTNS)[i]->GetKey() == Btns->GetKey()) 
		{
			return false;
		}
	}

	BTNS->push_back(Btns);
	return true;
}

// SET
void trKeyBoardManagement::SetActionBtnKey(int key, void (*action)()) 
{
	(*BTNS)[BtnResearch(key)]->SetAction(action);
}

// GET
const std::vector<trBTN_Key*>& trKeyBoardManagement::GetBTNS() const 
{
	return *BTNS;
}

// UPDATE
void trKeyBoardManagement::Update() 
{
	for (size_t i = 0; i < BTNS->size(); i++) 
	{
		(*BTNS)[i]->Update();
	}
}

// FNC
int trKeyBoardManagement::BtnResearch(int key) 
{
	auto it = find_if(BTNS->begin(), BTNS->end(), [key](const trBTN_Key* btn) { return btn->GetKey() == key; });

	if (it != BTNS->end()) {
		return int(distance(BTNS->begin(), it));
	}

	return -1;
}

// START
void trKeyBoardManagement::Start() 
{
	if (!start) 
	{
		Loop();
		start = true;
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

