#include "trBTN_Key.h"

using namespace std;

// INI default

trBTN_Key::trBTN_Key() : Key(0), KeyState(false), Action(nullptr), Protect(false), Ptr(nullptr), Mode(OnPress), UsingMode(HoldToTrigger)
{

}

// INI

trBTN_Key::trBTN_Key(int key_, int Mode_, int UsingMode_, std::function<void()> action_, trObject* Ptr_) : Key(key_), KeyState(false), Mode(Mode_), UsingMode(UsingMode_), Action(new std::function<void()>(action_)), Protect(false), Ptr(Ptr_)
{

}

// INI deep copy

trBTN_Key::trBTN_Key(const trBTN_Key& other) : Key(other.Key), KeyState(other.KeyState), Mode(other.Mode), Action(new std::function<void()>(*other.Action)), Protect(false), Ptr(other.Ptr), UsingMode(other.UsingMode)
{

}

// Copy

trBTN_Key& trBTN_Key::operator=(const trBTN_Key& other)
{
	if (this == &other) { return *this; }

	if (Action == nullptr) {
		Action = new std::function<void()>(*other.Action);
	}
	else {
		*Action = *other.Action;
	}

	Key = other.Key;
	KeyState = other.KeyState;
	Protect = other.Protect;
	Mode = other.Mode;
	UsingMode = other.UsingMode;
	// FAIRE BELEK ICI
	Ptr = other.Ptr;

	return *this;
}

// SET / RESET

void trBTN_Key::Reset()
{	
	// KeyDetached = false;
	// KeyState = false;
}

void trBTN_Key::SetAction(std::function<void()> action_)
{
	Action = new std::function<void()>(action_);
}

void trBTN_Key::SetPointer(trObject* Ptr_)
{
	Ptr = Ptr_; // fait belek mon reuf
}

// GET

const bool trBTN_Key::GetActionState() const
{
	return ActionState;
}

const int trBTN_Key::GetKeyState() const
{
	return KeyState;
}

const int trBTN_Key::GetKey() const
{
	return Key;
}

// UPDATE

void trBTN_Key::Update(bool NewState_) 
{
	// ici a voir pour le mode
	switch (Mode)
	{
	case OnPress:
		if (!KeyState && NewState_) 
		{
			ActionState = true;
		}
		else if (KeyState && !NewState_) 
		{
			ActionState = false;
		}
		break;
	case OnRelease:
		if (KeyState && !NewState_) 
		{
			ActionState = true;
		}
		else if (!KeyState && NewState_) 
		{
			ActionState = false;
		}
		break;
	default:
		break;
	}

	KeyState = NewState_; // Mets à jour l'état du bouton
}

// FNC

void trBTN_Key::DoAction()
{
	// ici a voir pour le mode
	switch (UsingMode)
	{
	case HoldToTrigger:
		if (Action && ActionState)
		{
			(*Action)();
		}
		break;
	case PressToTrigger: // Eviter si c'est OnRelease
		if (Action && ActionState)
		{
			(*Action)();

			ActionState = false;
		}
		break;
	case Axis:
		// a voir avec une valeur
		break;
	default:
		break;
	}
}

trBTN_Key::~trBTN_Key()
{
	delete Action;
}
