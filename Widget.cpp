#include "include.h"
#include "Widget.h"
#include "UI_Tools.h"

using namespace std;
using namespace UITools;

// INI

Widget::Widget(int x_, int y_, int size_x_, int size_y_, int RelativePosition_, string content_, string name_) : position(Coordinate<int>(x_, y_)), size(Size<int>(size_x_, size_y_)), content(Data<string>(content_)), name(Data<string>(name_)), activate(Data<bool>(true)), color(Data<int>(15)), delayCaractere(Data<int>(0)), protecte(Data<bool>(false)), change(Data<bool>(true)), RP(Data<int>(RelativePosition_)), destroy(Data<bool>(false)), RelativePositionPoint(Coordinate<int>(0, 0)), RelativePosition(Coordinate<int>(0, 0))
{

}

Widget::~Widget()
{

}

// SET

void Widget::SetPosition(int x_, int y_)
{
	position.SetCoord(x_, y_);
}

void Widget::SetSize(int x_, int y_)
{
	size.SetSize(x_, y_);
}

void Widget::SetContent(string content_)
{
	content.SetData(content_);
}

void Widget::SetName(string name_)
{
	name.SetData(name_);
}

void Widget::SetActivate(bool actv)
{
	activate.SetData(actv);
}

void Widget::SetProtecte(bool prtc)
{
	protecte.SetData(prtc);
}

void Widget::SetDelayCaractere(int Delay)
{
	delayCaractere.SetData(max(Delay, 0));
}

void Widget::SetColor(int color_)
{
	color.SetData(max(color_, 0));
}

bool Widget::SetRelativePosition(int rp)
{
	if (rp < 0 || rp > 9)
	{
		RP.SetData(0);
		return false;
	}

	RP.SetData(rp);
	return true;
}

void Widget::SetChange(bool chng)
{
	change.SetData(chng);
}

void Widget::SetDestroy(bool dstr)
{
	destroy.SetData(dstr);
}

// ADD

void Widget::AddToPosition(int x_, int y_)
{
	position.SetCoord(position.GetX().GetDataNew() + x_, position.GetY().GetDataNew() + y_);
}

void Widget::AddToSize(int x_, int y_)
{
	size.SetSize(size.GetSizeX().GetDataNew() + x_, size.GetSizeY().GetDataNew() + y_);
}

void Widget::AddToContent(string content_)
{
	content.SetData(content.GetDataNew() + content_);
}

void Widget::AddToColor(int color_)
{
	color.SetData(color.GetDataNew() + color_);
}

// GET

Coordinate<int> Widget::GetPostion() const
{
	return position;
}

Coordinate<int> Widget::GetRelativePosition() const
{
	return RelativePosition;
}


Size<int> Widget::GetSize() const
{
	return size;
}

Data<string> Widget::GetContent() const
{
	return content;
}

Data<string> Widget::GetName() const
{
	return name;
}

Data<bool> Widget::GetActivate() const
{
	return activate;
}

Data<bool> Widget::GetProtecte() const
{
	return protecte;
}

Data<int> Widget::GetDelayCaractere() const
{
	return delayCaractere;
}

Data<int> Widget::GetColor() const
{
	return color;
}

Data<int> Widget::GetRP() const
{
	return RP;
}

Data<bool> Widget::GetChange() const
{
	return change;
}

Data<bool> Widget::GetDestroy() const
{
	return destroy;
}

// APPLY

void Widget::UpdateRelativePositionPoint(int ConsoleSize_x, int ConsoleSize_y)
{
	switch (RP.GetDataActual())
	{
	case TopLeft:
		RelativePositionPoint.SetCoord(0, 0);
		break;
	case TopCenter:
		RelativePositionPoint.SetCoord((ConsoleSize_x / 2) - (size.GetSizeX().GetDataActual() / 2), 0);
		break;
	case TopRight:
		RelativePositionPoint.SetCoord(ConsoleSize_x - size.GetSizeX().GetDataActual(), 0);
		break;
	case MiddleLeft:
		RelativePositionPoint.SetCoord(0, (ConsoleSize_y / 2) - (size.GetSizeY().GetDataActual() / 2));
		break;
	case MiddleCenter:
		RelativePositionPoint.SetCoord((ConsoleSize_x / 2) - (size.GetSizeX().GetDataActual() / 2), (ConsoleSize_y / 2) - (size.GetSizeY().GetDataActual() / 2));
		break;
	case MiddleRight:
		RelativePositionPoint.SetCoord(ConsoleSize_x - size.GetSizeX().GetDataActual(), (ConsoleSize_y / 2) - (size.GetSizeY().GetDataActual() / 2));
		break;
	case BottomLeft:
		RelativePositionPoint.SetCoord(0, ConsoleSize_y - size.GetSizeY().GetDataActual());
		break;
	case BottomCenter:
		RelativePositionPoint.SetCoord((ConsoleSize_x / 2) - (size.GetSizeX().GetDataActual() / 2), ConsoleSize_y - size.GetSizeY().GetDataActual());
		break;
	case BottomRight:
		RelativePositionPoint.SetCoord(ConsoleSize_x - size.GetSizeX().GetDataActual(), ConsoleSize_y - size.GetSizeY().GetDataActual());
		break;
	}

	RelativePositionPoint.Update();
}

void Widget::UpdateRelativePosition()
{
	RelativePosition.SetCoord(max(position.GetX().GetDataNew() + RelativePositionPoint.GetX().GetDataActual(), 0), max(position.GetY().GetDataNew() + RelativePositionPoint.GetY().GetDataActual(), 0));
}


void Widget::APPLY(Size<int> SizeWindow_)
{
	UpdateRelativePositionPoint(SizeWindow_.GetSizeX().GetDataActual(), SizeWindow_.GetSizeY().GetDataActual());
	UpdateRelativePosition();

	// change.SetData(VerificationProprety() ? true : change.GetDataNew());

	RelativePosition.Update();
	position.Update();
	size.Update();
	activate.Update();
	protecte.Update();
	delayCaractere.Update();
	color.Update();
	content.Update();
	name.Update();
	RP.Update();
	destroy.Update();

	change.SetData(VerificationProprety() ? true : change.GetDataNew());
	change.Update();
}

// FNC

bool Widget::VerificationProprety()
{
	return (position.GetX().GetDataOld() != position.GetX().GetDataActual() || position.GetY().GetDataOld() != position.GetY().GetDataActual() || size.GetSizeX().GetDataOld() != size.GetSizeX().GetDataActual() || size.GetSizeY().GetDataOld() != size.GetSizeY().GetDataActual() || activate.GetDataOld() != activate.GetDataActual() || color.GetDataOld() != color.GetDataActual() || content.GetDataOld() != content.GetDataActual() || RP.GetDataOld() != RP.GetDataActual());
}

void Widget::Display(ostringstream& output_line)
{
	SetColorConsole(GetColor().GetDataActual());
	cout << output_line.str();
}
