#pragma once

#include "include.h"

#include "trSize.h"
#include "trCoordinate.h"
#include "trData.h"
#include "trPair.h"
#include "trMap.h"

#ifndef __TR_WIDGET__
#define __TR_WIDGET__

#ifdef TERMINAL_COMPONENTS_EXPORTS
#define TERMINAL_COMPONENTS_API __declspec(dllexport)
#else
#define TERMINAL_COMPONENTS_API __declspec(dllimport)
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

struct TERMINAL_COMPONENTS_API trWidget : trObject
{
public:

	// INI default

	trWidget();

	// INI

	trWidget(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, std::wstring content_, std::string name_);

	// INI deep copy

	trWidget(const trWidget& other);

	// Copy

	trWidget& operator=(const trWidget& other);

	// SET

	void SetPosition(int x_, int y_); 

	void SetSize(int x_, int y_);

	void SetContent(const std::wstring& content_);

	void SetResetColor(const std::vector<trPair<std::wstring, trCoordinate<int>>>& RstColor);

	void SetName(const std::string& name_);

	void SetActivate(bool actv);

	void SetProtecte(bool prtc);

	void SetColor(int color_); // a voir quoi faire avec ça frR

	bool SetTypeRelativePosition(int rp);

	void SetChange(bool chng);

	void SetDestroy(bool dstr);

	// ADD

	void AddToPosition(int x_, int y_);

	void AddToSize(int x_, int y_);

	void AddToContent(const std::wstring& content_);

	void AddToColor(int color_);

	// GET

	const trCoordinate<int>& GetPosition() const;  // n'est jamais utiliser

	const trCoordinate<int>& GetAbsolutePosition() const;

	const trSize<int>& GetSize() const;

	const trData<std::wstring>& GetContent() const;

	const trData<std::wstring>& GetRawContent() const;

	const trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>& GetColoredContent() const;

	const std::vector<trPair<std::wstring, trCoordinate<int>>>& GetResetColor() const;

	const trData<std::string>& GetName() const;

	const trData<bool>& GetActivate() const;

	const trData<bool>& GetProtecte() const;

	const trData<int>& GetColor() const;

	const trData<int>& GetRP() const;

	const trData<bool>& GetChange() const;

	const trData<bool>& GetDestroy() const;

	// UPDATE APPLY

	void UpdateRelativePositionPoint(int ConsoleSize_x, int ConsoleSize_y);

	void UpdateRelativePosition();

	virtual void APPLY(const trSize<int>& SizeWindow_);

	// FNC

	bool VerificationProprety();
	
	virtual void Display(std::wostringstream& output_line);

private:

	std::wstring ContentReorganisation(std::wstring _content, const trSize<int>& SizeWidget) const;

public:

	// Empty Widget (Static)
	static const trWidget& EmptyWidget();

	// DESTRUCTEUR

	~trWidget();

private:

	static trWidget* EmptyWidgetInstance; // Pointeur pour l'instance unique

	trCoordinate<int> *PositionRelative; 

	trSize<int> *Size;

	trData<bool> *Activate;

	trData<bool> *Protecte;

	trData<int> *Color; // a voir si utiliser ??????

	trData<bool> *Change;

	trData<int> *RpType;

	trData<std::wstring>* RawContent;

	/// <summary>
	/// L'index correspond aux coordonnées de l'info en 1 dimensions par rapport aux widget PAS a la fenêtre (merci de bien vouloir lire ;) )
	/// </summary>
	trData<trMap<int, trPair<std::wstring, trCoordinate<int>>>>*ColoredContent;

	std::vector<trPair<std::wstring, trCoordinate<int>>> *BaseColor;

	trData<std::string> *Name; 

	trData<bool> *Destroy;

	trCoordinate<int> *RelativePositionPoint;

	trData<std::wstring>* Content;

	// par rapport au terminal mais ca commence aux bordure, ducoup pas absolue a 100%
	trCoordinate<int>* PositionAbsolue;

};

#endif