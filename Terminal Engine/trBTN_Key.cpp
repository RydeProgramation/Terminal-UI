#include "trBTN_Key.h"

using namespace std;

// INI default

trBTN_Key::trBTN_Key() : Key(0), Pressed(false), KeyDetached(false), action(new std::function<void()>()), Protect(false)
{
}

// INI

trBTN_Key::trBTN_Key(int key_, std::function<void()> action_) : Key(key_), Pressed(false), KeyDetached(false), action(new std::function<void()>(action_)), Protect(false)
{

}

// INI deep copy

trBTN_Key::trBTN_Key(const trBTN_Key& other) : Key(other.Key), Pressed(other.Pressed), KeyDetached(other.KeyDetached), action(new std::function<void()>(*other.action)), Protect(false)
{
}

// Copy

trBTN_Key& trBTN_Key::operator=(const trBTN_Key& other)
{
	if (this == &other) { return *this; }

	Key = other.Key;
	Pressed = other.Pressed;
	KeyDetached = other.KeyDetached;
	action = new std::function<void()>(*other.action);
	Protect = other.Protect;

	return *this;
}

// SET / RESET

void trBTN_Key::Reset()
{	
	KeyDetached = false;
	Pressed = false;
}

void trBTN_Key::SetAction(std::function<void()> action_)
{
	action = new std::function<void()>(action_);
}

// GET

const bool trBTN_Key::IsKeyDetached() const
{
	return KeyDetached;
}

const int trBTN_Key::GetKey() const
{
	return Key;
}

// UPDATE

void trBTN_Key::Update() // ne sert a rien pour l'instant
{
	
}

// FNC

void trBTN_Key::DoAction()
{
	if (action)
	{
		Protect = true; // <--- NE MARCHE PAS MDR

		if (KeyDetached)
		{
			(*action)();
		}

		Reset();

		Protect = false; // <--- NE MARCHE PAS MDR
	}
}

trBTN_Key::~trBTN_Key()
{
	delete action;
}
