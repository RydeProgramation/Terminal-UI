#include "trBTN_Key.h"

using namespace std;

// INI default

trBTN_Key::trBTN_Key() : key(0), pressed(false), detachKey(false), action(new std::function<void()>()), protect(false)
{
}

// INI

trBTN_Key::trBTN_Key(int key_, std::function<void()> action_) : key(key_), pressed(false), detachKey(false), action(new std::function<void()>(action_)), protect(false)
{

}

// INI deep copy

trBTN_Key::trBTN_Key(const trBTN_Key& other) : key(other.key), pressed(other.pressed), detachKey(other.detachKey), action(new std::function<void()>(*other.action)), protect(false)
{
}

// Copy

trBTN_Key& trBTN_Key::operator=(const trBTN_Key& other)
{
	if (this == &other) { return *this; }

	key = other.key;
	pressed = other.pressed;
	detachKey = other.detachKey;
	action = new std::function<void()>(*other.action);
	protect = other.protect;

	return *this;
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
