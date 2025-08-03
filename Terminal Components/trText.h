#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trWidget.h"
#include "trData.h"

#ifndef __TR_TEXT__
#define __TR_TEXT__

#ifdef TERMINAL_COMPONENTS_EXPORTS
#define TERMINAL_COMPONENTS_API __declspec(dllexport)
#else
#define TERMINAL_COMPONENTS_API __declspec(dllimport)
#endif

class TERMINAL_COMPONENTS_API trText : public trWidget
{
public:

	// INI default

	trText();

	virtual void Init() override;

	// INI

	trText(int x_, int y_, int size_x_, int size_y_, uint8_t RelativePosition_, std::wstring content_, std::string name_);

	// INI deep copy

	trText(const trText& other);

	// Copy

	virtual trText& operator=(const trActor& other) override;

	// SET

	void SetAnimationVector(const std::vector<trPair<uint16_t, std::wstring>>& AnimationVector_);

	virtual void SetProprety(const std::string& name, const std::string& data, const std::string& type) override;

	// GET

	const std::vector<trPair<uint16_t, std::wstring>>& GetAnimationVector() const;

	// ADD
	
	void AddAnimation(const trPair<uint16_t, std::wstring>& Animation_);

	void AddAnimation(uint16_t Time_, const std::wstring& Animation_);

	// FNC

	void DoCharToCharAnimation(uint16_t SleepTime_, const std::wstring Content_);

	void DoCharToCharAnimation(uint16_t SleepTime_);

	void DoNextFrameAnimation();

	void DoPreviousFrameAnimation();

	void DoAnimation();

	// APPLY

	bool VerificationProprety() override;

protected:

	void APPLY_(const trSize<uint16_t>& SizeWindow) override;

public:

	// DESTRUCTEUR

	~trText();

private:

	std::vector<trPair<uint16_t, std::wstring>> *AnimationVector;

	uint16_t indexAnimation;
public:
	void ResetIndexAnimation();
};


#endif