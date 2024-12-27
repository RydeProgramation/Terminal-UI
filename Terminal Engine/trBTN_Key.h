#pragma once

#include "include.h"

#include "trData.h"
#include "trSize.h"
#include "trCoordinate.h"

#ifndef __TR_BTN_KEY__
#define __TR_BTN_KEY__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

struct TERMINAL_ENGINE_API trBTN_Key : trObject
{
public:

	// INI default

	trBTN_Key();

	// INI

	trBTN_Key(int key_, std::function<void()> action_);

	// INI deep copy

	trBTN_Key(const trBTN_Key& other);

	// Copy

	trBTN_Key& operator=(const trBTN_Key& other);

	// SET

	void Reset();
	void SetAction(std::function<void()> action_);

	// GET

	bool GetDetachKey() const;
	int GetKey() const;

	// UPDATE

	void Update();

	// FNC

	void Action();

	// DESTRUCTEUR

	~trBTN_Key();

private:

	int key;
	bool protect;
	bool pressed;
	bool detachKey; // Une action peut se faire

	std::function<void()> *action; // a voir belek bug
};

#endif
