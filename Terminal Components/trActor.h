#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trData.h"
#include "trPair.h"
#include "trMap.h"

#ifndef __TR_ACTOR__
#define __TR_ACTOR__

#ifdef TERMINAL_CORE_EXPORTS
#define TERMINAL_CORE_API __declspec(dllexport)
#else
#define TERMINAL_CORE_API __declspec(dllimport)
#endif

class TERMINAL_CORE_API trActor : public trObject
{
public:

	// INI default

	trActor();

	virtual void Init() {};

	// INI

	trActor(std::string name_);

	// INI deep copy

	trActor(const trActor& other);

	// Copy

	trActor& operator=(const trActor& other);

	// SET

	void SetName(const std::string& name_);

	void SetActivate(bool Activate_);

	void SetProtecte(bool Protected_);

	void SetChange(bool Change_);

	void SetDestroy(bool Destroy_);

	// GET

	const trData<std::string>& GetName() const;

	const trData<bool>& GetActivate() const;

	const trData<bool>& GetProtecte() const;

	const trData<bool>& GetChange() const;

	const trData<bool>& GetDestroy() const;

	// APPLY

	void APPLY(const trSize<uint16_t>& SizeWindow);

protected:

	virtual void APPLY_(const trSize<uint16_t>& SizeWindow) {};

public:
	
	virtual void APPLY_Implementation() {};

	// FONCTION

	virtual bool VerificationProprety(); 

	// DESTRUCTEUR

	virtual ~trActor();

private:

	trData<bool>* Activate;

	trData<bool>* Protected;

	trData<bool>* ToChange;

	trData<std::string>* Name;

	trData<bool>* ToDestroy;

public:

	// EMPTY ACTOR STATIC

	static trActor EmptyActor;
};

#endif