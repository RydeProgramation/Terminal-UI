#include "BTN_Key.h"

using namespace std;

//  INI

BTN_Key::BTN_Key(int key_, std::function<void()> action_) : key(key_), pressed(false), detachKey(false), action(action_), protect(false)
{

}

// SET / RESET

void BTN_Key::Reset()
{
	detachKey = false;
	pressed = false;
}

void BTN_Key::SetAction(std::function<void()> action_)
{
	action = action_;
}

// GET

bool BTN_Key::GetDetachKey() const
{
	return detachKey;
}

int BTN_Key::GetKey() const
{
	return key;
}

// UPDATE

void BTN_Key::Update()
{
	if (!protect) // <--- NE MARCHE PAS MDR
	{
		detachKey = (pressed && !(GetAsyncKeyState(key) & 0x8000)) ? true : detachKey;

		pressed = (GetAsyncKeyState(key) & 0x8000 && !detachKey) ? true : pressed;
	}
	
}

// FNC

void BTN_Key::Action()
{
	if (action)
	{
		protect = true; // <--- NE MARCHE PAS MDR
		if (detachKey)
		{
			action();
		}
		Reset();
		protect = false; // <--- NE MARCHE PAS MDR
	}
}
