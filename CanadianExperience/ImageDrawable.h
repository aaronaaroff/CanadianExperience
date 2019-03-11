/**
 * \file ImageDrawable.h
 *
 * \author Aaron Eshleman
 *
 * A drawable based on images.
 *
 * This class has an image and draws that image 
 * 
 */

#pragma once
#include "Drawable.h"
#include <string>

using namespace std;


/**
 *   This class has an image and draws that image 
 */
class CImageDrawable :
	public CDrawable
{
public:
	/** Constructor
	* \param name The drawable name */
	CImageDrawable(wstring name, wstring filename);

	/** \brief Default constructor disabled */
	CImageDrawable() = delete;
	/** \brief Copy constructor disabled */
	CImageDrawable(const CImageDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CImageDrawable &) = delete;

	virtual void Draw(Gdiplus::Graphics *graphics) override;
	bool HitTest(Gdiplus::Point pos) override;

	/** Set the center for this picture
	* \param center The new center*/
	void SetCenter(Gdiplus::Point center) { mCenter = center; }

	/** Get the center for this picture
	* \returns The center*/
	Gdiplus::Point GetCenter() const { return mCenter; }

	/** Destructor
	*/
	virtual ~CImageDrawable();
protected:
	/// The image for this drawable
	std::unique_ptr<Gdiplus::Bitmap> mImage;
private:
	///center of image
	Gdiplus::Point mCenter = Gdiplus::Point(0, 0);
};

