/**
 * \file HeadTop.h
 *
 * \author Aaron Eshleman
 *
 * Class derives from ImageDrawable 
 * draws the head top part of image
 *
 */

#pragma once
#include "ImageDrawable.h"
#include "AnimChannelPosition.h"



/**
 * draws the head top part of image
 */
class CHeadTop :
	public CImageDrawable
{
public:
	/** Constructor
	* \param name The drawable name */
	CHeadTop(wstring name, wstring filename);

	/** \brief Default constructor disabled */
	CHeadTop() = delete;
	/** \brief Copy constructor disabled */
	CHeadTop(const CHeadTop &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CHeadTop &) = delete;

	virtual void Draw(Gdiplus::Graphics *graphics) override;
	bool IsMovable() override;

	Gdiplus::Point TransformPoint(Gdiplus::Point p);

	void DrawEyebrow(Gdiplus::Graphics *graphics, int x, int y, int x1, int y1);

	void DrawRotatingEclipse(Gdiplus::Graphics *graphics, int x, int y);

	void SetKeyframe() override;

	void GetKeyframe() override;

	virtual void SetTimeline(CTimeline * timeline) override;

	/** Destructor
	*/
	~CHeadTop();

private:
	/// The animation channel for animating position of this head top drawable
	CAnimChannelPosition mChannel;

	/// The actor using this drawable
	CActor *mActor = nullptr;
};



