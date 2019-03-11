/**
 * \file PolyDrawable.h
 *
 * \author Aaron Eshleman
 *
* A drawable based on polygon images.
*
* This class has a list of points and draws a polygon
* drawable based on those points.
*/

#pragma once
#include <vector>
#include "Drawable.h"


/**
 * This class has a list of points and draws a polygon
* drawable based on those points.
 */
class CPolyDrawable :
	public CDrawable
{
public:
	/** Constructor
	* \param name The drawable name */
	CPolyDrawable::CPolyDrawable(const std::wstring &name);
	/** \brief Default constructor disabled */
	CPolyDrawable() = delete;
	/** \brief Copy constructor disabled */
	CPolyDrawable(const CPolyDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPolyDrawable &) = delete;

	void Draw(Gdiplus::Graphics *graphics) override;
	bool HitTest(Gdiplus::Point pos) override;
	void AddPoint(Gdiplus::Point point);

	/** Set the color
	* \param color The new color*/
	void SetColor(Gdiplus::Color color) { mColor = color; }

	/** Gets the current color
	* \returns The current color*/
	Gdiplus::Color GetColor() const { return mColor; }

	~CPolyDrawable();
private:
	/// The polygon color
	Gdiplus::Color mColor = Gdiplus::Color::Black;

	/// The array of point objects
	std::vector<Gdiplus::Point> mPoints;
};

