#pragma once

#include "include.h"
#include "Data.h"
#include "Size.h"
#include "Coordinate.h"

#ifndef __BTN_KEY__
#define __BTN_KEY__

struct BTN_Key
{
private:

	int key;

	bool protect;

	bool pressed;

	bool detachKey; // Une action peut se faire

	std::function<void()> action;

public:

	BTN_Key(int key_, std::function<void()> action_);

	// SET

	void Reset();
	
	// SET

	void SetAction(std::function<void()> action_);

	// GET

	bool GetDetachKey() const;

	int GetKey() const;

	// Update

	void Update();

	// FNC

	void Action();
};

#endif