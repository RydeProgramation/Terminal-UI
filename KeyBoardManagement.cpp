#include "KeyBoardManagement.h"

using namespace std;

// INI

KeyBoardManagement::KeyBoardManagement() : start(false)
{
}

// FNC

void KeyBoardManagement::ActionBTN()
{
	for (int i = 0; i < BTNS.size(); i++)
	{
		if (BTNS[i]->GetDetachKey())
		{
			BTNS[i]->Action();
		}
	}
}

bool KeyBoardManagement::CreateBTN(BTN_Key* Btns)
{
	for (int i = 0; i < BTNS.size(); i++)
	{
		if (BTNS[i]->GetKey() == Btns->GetKey())
		{
			return false;
		}
	}

	BTNS.push_back(Btns);

	return true;
}

// SET

void KeyBoardManagement::SetActionBtnKey(int key, void (*action)())
{
	BTNS[BtnResearch(key)]->SetAction(action);
}

// GET

std::vector<BTN_Key*> KeyBoardManagement::GetBTNS() const
{
	return BTNS;
}

// UPDATE

void KeyBoardManagement::Update()
{
	for (unsigned int i = 0; i < BTNS.size(); i++)
	{
		BTNS[i]->Update();
	}
}

// FNC

int KeyBoardManagement::BtnResearch(int key)
{
	auto it = find_if(BTNS.begin(), BTNS.end(), [key](const BTN_Key* btn) {return btn->GetKey() == key;});

	if (it != BTNS.end())
	{
		return int(distance(BTNS.begin(), it));
	}

	return -1;
}

// START

void KeyBoardManagement::Start()
{
	if (!start)
	{
		Loop();
		start = true;
	}
}

// LOOP

void KeyBoardManagement::Loop()
{
	while (true)
	{
		Update();
	}
}