#include "trUIToolsCore.h"
#include "trPawn.h"

using namespace std;
using namespace UIToolsCore;

// INI default

trPawn::trPawn() : trPawn(0, 0, TopLeft, "None")
{

}

// INI

trPawn::trPawn(int x_, int y_, int RelativePositionType_, string name_) : trActor(name_), PositionRelative(new trCoordinate<int>(x_, y_)), RpType(new trData<uint8_t>(RelativePositionType_)), RelativePositionPoint(new trCoordinate<int>(0, 0)), PawnCollision(new std::vector<trActor*>()), /*TEST DE COPILOT*/ PositionAbsolue(new trCoordinate<int>(max(x_ + RelativePositionPoint->GetX().GetDataActual(), 0), max(y_ + RelativePositionPoint->GetY().GetDataActual(), 0)))
{

}

void trPawn::Init()
{
	UpdateRelativePositionPoint(GetConsoleSize());

	RelativePositionPoint->Update();

	PositionAbsolue = new trCoordinate<int>(max(PositionRelative->GetX().GetDataNew() + RelativePositionPoint->GetX().GetDataActual(), 0), max(PositionRelative->GetY().GetDataNew() + RelativePositionPoint->GetY().GetDataActual(), 0));
}

// INI deep copy

trPawn::trPawn(const trPawn& other) : trActor(other), PositionRelative(new trCoordinate<int>(*other.PositionRelative)), RpType(new trData<uint8_t>(*other.RpType)), RelativePositionPoint(new trCoordinate<int>(*other.RelativePositionPoint)), PositionAbsolue(new trCoordinate<int>(*other.PositionAbsolue)), PawnCollision(new vector<trActor*>(*other.PawnCollision))
{

}

// Copy

trPawn& trPawn::operator=(const trPawn& other)
{
	if (this == &other) { return *this; }

	trActor::operator=(other);

	if (RpType == nullptr) {
		RpType = new trData<uint8_t>(*other.RpType);
	}
	else {
		*RpType = *other.RpType;
	}

	if (PositionRelative == nullptr) {
		PositionRelative = new trCoordinate<int>(*other.PositionRelative);
	}
	else {
		*PositionRelative = *other.PositionRelative;
	}

	if (RelativePositionPoint == nullptr) {
		RelativePositionPoint = new trCoordinate<int>(*other.RelativePositionPoint);
	}
	else {
		*RelativePositionPoint = *other.RelativePositionPoint;
	}

	if (PositionAbsolue == nullptr) {
		PositionAbsolue = new trCoordinate<int>(*other.PositionAbsolue);
	}
	else {
		*PositionAbsolue = *other.PositionAbsolue;
	}

	if (PawnCollision == nullptr) {
		PawnCollision = new vector<trActor*>(*other.PawnCollision);
	}
	else {
		*PawnCollision = *other.PawnCollision;
	}

	return *this;
}

// SET

void trPawn::SetPosition(int x_, int y_)
{
	PositionRelative->SetCoord(x_, y_);
}

bool trPawn::SetTypeRelativePosition(int rp)
{
	if (rp < 0 || rp > 9)
	{
		RpType->SetData(0);
		return false;
	}

	RpType->SetData(rp);
	return true;
}

void trPawn::SetPawnCollision(trActor* actor, bool collision)
{
	if (actor != nullptr)
	{
		if (collision)
		{
			PawnCollision->push_back(actor); // faire belek ici
		}

		else
		{
			// bah je sais pas ce que tu fait mdr
		}
	}
}

// ADD

void trPawn::AddToPosition(int x_, int y_)
{
	PositionRelative->SetCoord(PositionRelative->GetX().GetDataNew() + x_, PositionRelative->GetY().GetDataNew() + y_);
}

// GET

const trCoordinate<int>& trPawn::GetPosition() const
{
	return *PositionRelative;
}

const trCoordinate<int>& trPawn::GetAbsolutePosition() const
{
	return *PositionAbsolue;
}

const trData<uint8_t>& trPawn::GetRelativePositionType() const
{
	return *RpType;
}

const vector<trActor*>& trPawn::GetPawnCollision() const
{
	return *PawnCollision;
}

// APPLY

void trPawn::UpdateRelativePosition()
{
	PositionAbsolue->SetCoord(max(PositionRelative->GetX().GetDataNew() + RelativePositionPoint->GetX().GetDataActual(), 0), max(PositionRelative->GetY().GetDataNew() + RelativePositionPoint->GetY().GetDataActual(), 0));
}

void trPawn::APPLY_(const trSize<uint16_t>& SizeWindow)
{
	UpdateRelativePositionPoint(SizeWindow);

	RelativePositionPoint->Update();

	UpdateRelativePosition();

	PositionAbsolue->Update();
	PositionRelative->Update();
	RpType->Update();

	if (PawnCollision->size() > 0)
	{
		/*for (auto& it : *PawnCollision) // a utiliser si jamais mais bon pas besoin pour l'instant
		{
			
		}*/

		SetChange(true); // on met a jour les collisions

		PawnCollision->clear();
	}
}

// FNC

bool trPawn::VerificationProprety()
{
	return (
		trActor::VerificationProprety() ||
		PositionRelative->GetX().GetDataOld() != PositionRelative->GetX().GetDataActual() ||
		PositionRelative->GetY().GetDataOld() != PositionRelative->GetY().GetDataActual() ||
		RpType->GetDataOld() != RpType->GetDataActual()
		);
}

void trPawn::UpdateRelativePositionPoint(const trSize<uint16_t>& SizeWindow)
{
	int ConsoleSize_x = GetConsoleSize().GetSizeX().GetDataActual();
	int ConsoleSize_y = GetConsoleSize().GetSizeY().GetDataActual();

	switch (RpType->GetDataActual())
	{
	case TopLeft:
		RelativePositionPoint->SetCoord(0, 0);
		break;
	case TopCenter:
		RelativePositionPoint->SetCoord(ConsoleSize_x / 2, 0);
		break;
	case TopRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x, 0);
		break;
	case MiddleLeft:
		RelativePositionPoint->SetCoord(0, ConsoleSize_y / 2);
		break;
	case MiddleCenter:
		RelativePositionPoint->SetCoord(ConsoleSize_x / 2, ConsoleSize_y / 2);
		break;
	case MiddleRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x, ConsoleSize_y / 2);
		break;
	case BottomLeft:
		RelativePositionPoint->SetCoord(0, ConsoleSize_y);
		break;
	case BottomCenter:
		RelativePositionPoint->SetCoord(ConsoleSize_x / 2, ConsoleSize_y);
		break;
	case BottomRight:
		RelativePositionPoint->SetCoord(ConsoleSize_x, ConsoleSize_y);
		break;
	default:
		std::cerr << "AUCUN NE CORESPOND";
		std::exit(1);
	}
}

// DESTRUCTEUR

trPawn::~trPawn()
{
	delete PositionRelative;

	delete RelativePositionPoint;

	delete PositionAbsolue;

	delete RpType;

	delete PawnCollision;
}