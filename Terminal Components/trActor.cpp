#include "trUIToolsCore.h"
#include "trActor.h"

using namespace std;
using namespace UIToolsCore;

// INI default

trActor::trActor() : trActor("None")
{

}

// INI

trActor::trActor(string name_) : Name(new trData<string>(name_)), Activate(new trData<bool>(true)), Protected(new trData<bool>(false)), ToChange(new trData<bool>(true)), ToDestroy(new trData<bool>(false))
{
	
}

// INI deep copy

trActor::trActor(const trActor& other) : Name(new trData<string>(*other.Name)), Activate(new trData<bool>(*other.Activate)), ToChange(new trData<bool>(true)), ToDestroy(new trData<bool>(*other.ToDestroy)), Protected(new trData<bool>(*other.Protected))
{

}

// Copy

trActor& trActor::operator=(const trActor& other)
{
	if (this == &other) { return *this; }

	if (Name == nullptr) {
		Name = new trData<string>(*other.Name);
	}
	else {
		*Name = *other.Name;
	}

	if (Activate == nullptr) {
		Activate = new trData<bool>(*other.Activate);
	}
	else {
		*Activate = *other.Activate;
	}

	if (Protected == nullptr) {
		Protected = new trData<bool>(*other.Protected);
	}
	else {
		*Protected = *other.Protected;
	}

	if (ToChange == nullptr) {
		ToChange = new trData<bool>(true);
	}
	else {
		*ToChange = *other.ToChange;
	}

	if (ToDestroy == nullptr) {
		ToDestroy = new trData<bool>(*other.ToDestroy);
	}
	else {
		*ToDestroy = *other.ToDestroy;
	}
	
	return *this;
}

// SET

void trActor::SetName(const string& name_)
{
	Name->SetData(name_);
}

void trActor::SetActivate(bool Activate_)
{
	Activate->SetData(Activate_);
}

void trActor::SetProtecte(bool Protected_)
{
	Protected->SetData(Protected_);
}

void trActor::SetChange(bool Change_)
{
	ToChange->SetData(Change_);
}

void trActor::SetDestroy(bool Destroy_)
{
	ToDestroy->SetData(Destroy_);
}

// GET

const trData<string>& trActor::GetName() const
{
	return *Name;
}

const trData<bool>& trActor::GetActivate() const
{
	return *Activate;
}

const trData<bool>& trActor::GetProtecte() const
{
	return *Protected;
}

const trData<bool>& trActor::GetChange() const
{
	return *ToChange;
}

const trData<bool>& trActor::GetDestroy() const
{
	return *ToDestroy;
}

// APPLY

void trActor::APPLY(const trSize<uint16_t>& SizeWindow)
{	
	APPLY_Implementation();

	APPLY_(SizeWindow);

	Activate->Update();
	Protected->Update();
	Name->Update();
	ToDestroy->Update();

	ToChange->SetData(VerificationProprety() ? true : ToChange->GetDataNew());
	ToChange->Update();
}

// FNC

bool trActor::VerificationProprety()
{
	return (
		Activate->GetDataOld() != Activate->GetDataActual()
		);
}

// EMPTY ACTOR STATIC

trActor trActor::EmptyActor = trActor();

// DESTRUCTEUR

trActor::~trActor()
{
	delete Activate;

	delete Protected;

	delete ToChange;

	delete Name;

	delete ToDestroy;
}
