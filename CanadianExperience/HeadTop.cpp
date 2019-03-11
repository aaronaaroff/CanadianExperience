/**
 * \file HeadTop.cpp
 *
 * \author Aaron Eshleman
 */


#include "stdafx.h"
#include "HeadTop.h"
#include "ImageDrawable.h"
#include "Timeline.h"


using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;


/**Constructor
 * 
 * \param name 
 * \param filename 
 */
CHeadTop::CHeadTop(wstring name, wstring filename) : CImageDrawable(name, filename)
{

}

/**Draw this head top
*
* \param graphics
*/
void CHeadTop::Draw(Gdiplus::Graphics * graphics)
{
	CImageDrawable::Draw(graphics);

	Point p = TransformPoint(Point(50,85));

	// Eye 1
	DrawRotatingEclipse(graphics, 30, 70);

	// Eye 2
	DrawRotatingEclipse(graphics, 70, 70);

	// Eyebrow 1
	DrawEyebrow(graphics, 10, 28, 25, 28);

	//Eyebrow 2
	DrawEyebrow(graphics, 32, 28, 48, 28);

}


/** Override from drawable class
 * 
 * \returns true
 */
bool CHeadTop::IsMovable()
{
	return true;
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
	// Make p relative to the image center
	p = p - GetCenter();

	// Rotate as needed and offset
	return (RotatePoint(p, mPlacedR) + mPlacedPosition);
}


/** Draws eybrow for head top
 * 
 * \param graphics 
 * \param x, y, x1, y1
 */
void CHeadTop::DrawEyebrow(Gdiplus::Graphics *graphics, int x, int y, int x1, int y1)
{
	Pen pen(Color::Black, 2);

	Point p = TransformPoint(Point(int(x), int(y)));
	Point p1 = TransformPoint(Point(int(x1), int(y1)));

	auto state = graphics->Save();
	graphics->TranslateTransform(p.X, p.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->DrawLine(&pen, Point(x,y), Point(x1,y1));
	graphics->Restore(state);
}


/** Draws eye for head top
 * 
 * \param graphics 
 * \param x
 *\param y
 */
void CHeadTop::DrawRotatingEclipse(Gdiplus::Graphics *graphics, int x, int y)
{
	SolidBrush brush(Color::Black);
	float wid = 15.0f;
	float hit = 20.0f;

	Point p = TransformPoint(Point(int(x), int(y)));

	auto state = graphics->Save();
	graphics->TranslateTransform(p.X, p.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
	graphics->Restore(state);
}


/**
 * Overridden SetKeyframe class from CDrawable to add position capabilities to head top
 */
 void CHeadTop::SetKeyframe()
 {
	 CDrawable::SetKeyframe();

	 mChannel.SetKeyframe(this->GetPosition());

 }

 /**
 * Overridden SetKeyframe class from CDrawable to add position capabilities to head top
 */
 void CHeadTop::GetKeyframe()
 {
	 CDrawable::GetKeyframe();

	 if (mChannel.IsValid())
	 {
		 this->SetPosition(mChannel.GetPosition());
	 }

 }


/**
 * 
 * \param timeline 
 */
 void CHeadTop::SetTimeline(CTimeline * timeline)
 {
	 CDrawable::SetTimeline(timeline);

	 timeline->AddChannel(&mChannel);
 }


/**
 * Destructor
 */
CHeadTop::~CHeadTop()
{
}
