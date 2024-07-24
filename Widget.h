#pragma once

#include "include.h"
#include "Size.h"
#include "Coordinate.h"
#include "Data.h"

#ifndef __WIDGET__
#define __WIDGET__

#define TopLeft 0
#define TopCenter 1
#define TopRight 2
#define MiddleLeft 3
#define MiddleCenter 4
#define MiddleRight 5
#define BottomLeft 6
#define BottomCenter 7
#define BottomRight 8

struct Widget
{
private:

	Coordinate<int> position;

	Coordinate<int> RelativePosition;

	Size<int> size;

	Data<bool> activate;

	Data<bool> protecte;

	Data<int> delayCaractere;

	Data<int> color;

	Data<bool> change;

	Data<int> RP;

	Data<std::string> content;

	Data<std::string> name;

	Data<bool> destroy;

	Coordinate<int> RelativePositionPoint;

public:

	Widget(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, std::string content_, std::string name_);

	virtual ~Widget();

	// SET

	void SetPosition(int x_, int y_);

	void SetSize(int x_, int y_);

	void SetContent(std::string content_);

	void SetName(std::string name_);

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

	void AddToContent(std::string content_);

	void AddToColor(int color_);

	// GET

	Coordinate<int> GetPostion() const;

	Coordinate<int> GetRelativePosition() const;

	Size<int> GetSize() const;

	Data<std::string> GetContent() const;

	Data<std::string> GetName() const;

	Data<bool> GetActivate() const;

	Data<bool> GetProtecte() const;

	Data<int> GetDelayCaractere() const;

	Data<int> GetColor() const;

	Data<int> GetRP() const;

	Data<bool> GetChange() const;

	Data<bool> GetDestroy() const;

	// UPDATE APPLY

	void UpdateRelativePositionPoint(int ConsoleSize_x, int ConsoleSize_y);

	void UpdateRelativePosition();

	virtual void APPLY(Size<int>SizeWindow_);

	// FNC

	bool VerificationProprety();

	virtual void Display(ostringstream& output_line);

};

#endif