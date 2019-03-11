/**
 * \file PolyDrawable.cpp
 *
 * \author Aaron Eshleman
 */


#include "stdafx.h"
#include "PolyDrawable.h"
#include <vector>

using namespace Gdiplus;

/** Constructor
* \param name The drawable name */
CPolyDrawable::CPolyDrawable(const std::wstring & name) : CDrawable(name)
{
}

/**Draw this poly drawable
*
* \param graphics
*/
void CPolyDrawable::Draw(Gdiplus::Graphics * graphics)
{
	SolidBrush brush(mColor);

	// Transform the points
	std::vector<Point> points;
	for (auto point : mPoints)
	{
		points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
	}

	graphics->FillPolygon(&brush, &points[0], (int)points.size());
}

/**Test to see if a mouse click is on this polydrawable.
*
* \param pos
* \returns bool
*/
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
	// Transform the points
	std::vector<Point> points;
	for (auto point : mPoints)
	{
		points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
	}

	GraphicsPath path;
	path.AddPolygon(&points[0], (int)points.size());
	return path.IsVisible(pos) ? true : false;
}

/**Adds point to member variable array mPoints
 * 
 * \param point 
 */
void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
	mPoints.push_back(point);
}

/**
* Destructor
*/
CPolyDrawable::~CPolyDrawable()
{
}
