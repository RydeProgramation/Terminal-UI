#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trData.h"

#ifndef __TR_WIDGET__
#define __TR_WIDGET__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

#define TopLeft 0
#define TopCenter 1
#define TopRight 2
#define MiddleLeft 3
#define MiddleCenter 4
#define MiddleRight 5
#define BottomLeft 6
#define BottomCenter 7
#define BottomRight 8

struct TERMINAL_ENGINE_API trWidget : trObject
{
public:

	// CONSTR

	trWidget(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, std::string content_, std::string name_);

	// SET

	void SetPosition(int x_, int y_);

	void SetSize(int x_, int y_);

	void SetContent(const std::string& content_);

	void SetName(const std::string& name_);

	void SetActivate(bool actv);

	void SetProtecte(bool prtc);

	void SetDelayCaractere(int Delay);

	void SetColor(int color_);

	bool SetRelativePosition(int rp);

	void SetChange(bool chng);

	void SetDestroy(bool dstr);

	// ADD

	void AddToPosition(int x_, int y_);

	void AddToSize(int x_, int y_);

	void AddToContent(const std::string& content_);

	void AddToColor(int color_);

	// GET

	const trCoordinate<int>& GetPostion() const;

	const trCoordinate<int>& GetRelativePosition() const;

	const trSize<int>& GetSize() const;

	const trData<std::string>& GetContent() const;

	const trData<std::string>& GetName() const;

	const trData<bool>& GetActivate() const;

	const trData<bool>& GetProtecte() const;

	const trData<int>& GetDelayCaractere() const;

	const trData<int>& GetColor() const;

	const trData<int>& GetRP() const;

	const trData<bool>& GetChange() const;

	const trData<bool>& GetDestroy() const;

	// UPDATE APPLY

	void UpdateRelativePositionPoint(int ConsoleSize_x, int ConsoleSize_y);

	void UpdateRelativePosition();

	virtual void APPLY(const trSize<int> SizeWindow_);

	// FNC

	bool VerificationProprety();

	virtual void Display(std::ostringstream& output_line);

	// DESTRUCTEUR

	~trWidget();

private:

	trCoordinate<int> *Position;

	trCoordinate<int> *RelativePosition;

	trSize<int> *size;

	trData<bool> *activate;

	trData<bool> *protecte;

	trData<int> *delayCaractere;

	trData<int> *color;

	trData<bool> *change;

	trData<int> *RP;

	trData<std::string> *content; // peut etre utilisé des pointeurs

	trData<std::string> *name; // peut etre utilisé des pointeurs

	trData<bool> *destroy;

	trCoordinate<int> *RelativePositionPoint;

};

#endif