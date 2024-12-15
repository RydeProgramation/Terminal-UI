#include "trBTN_Key.h"

using namespace std;

//  INI

trBTN_Key::trBTN_Key(int key_, std::function<void()> action_) : key(key_), pressed(false), detachKey(false), action(new std::function<void()>(action_)), protect(false)
{

}

// SET / RESET

void trBTN_Key::Reset()
{
	detachKey = false;
	pressed = false;
}

void trBTN_Key::SetAction(std::function<void()> action_)
{
	action = new std::function<void()>(action_);
}

// GET

bool trBTN_Key::GetDetachKey() const
{
	return detachKey;
}

int trBTN_Key::GetKey() const
{
	return key;
}

// UPDATE

void trBTN_Key::Update() // FAUT CHANGER LA METHODE Il faut faire en sorte que quand on clique ça appele le bouton avec un map par ce que fait une verif pour chaque bouton c'est aps opti
{
	if (!protect) // <--- NE MARCHE PAS MDR
	{
		detachKey = (pressed && !(GetAsyncKeyState(key) & 0x8000)) ? true : detachKey;

		pressed = (GetAsyncKeyState(key) & 0x8000 && !detachKey) ? true : pressed;
	}

}

// FNC

void trBTN_Key::Action()
{
	if (action)
	{
		protect = true; // <--- NE MARCHE PAS MDR
		if (detachKey)
		{
			(*action)();
		}
		Reset();
		protect = false; // <--- NE MARCHE PAS MDR
	}
}

trBTN_Key::~trBTN_Key()
{
	delete action;
}
