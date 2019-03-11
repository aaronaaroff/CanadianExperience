/**
 * \file Drawable.h
 *
 * \author Aaron Eshleman
 *
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor.Drawable parts can be moved
 * independently.
 * 
 */



#pragma once

#include <string>
#include <vector>
#include <memory>
#include "AnimChannelAngle.h"

class CActor;
class CTimeline;

/**
 * A drawable is one part of an actor. Drawable parts can be moved
* independently.
 */
class CDrawable
{
public:
	virtual ~CDrawable();

	/** \brief Default constructor disabled */
	CDrawable() = delete;
	/** \brief Copy constructor disabled */
	CDrawable(const CDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CDrawable &) = delete;

	void SetActor(CActor *actor);


	/**Virtual and abstract draw function
	*\param graphics Pointer to the graphics */
	virtual void Draw(Gdiplus::Graphics *graphics) = 0;
	void Place(Gdiplus::Point offset, double rotate);
	void AddChild(std::shared_ptr<CDrawable> child);

	/**Determines if drawable was clicked
	*\param pos The position of click
	*\returns bool */
	virtual bool HitTest(Gdiplus::Point pos) = 0;

	/**Determines if drawable is movable
	*\returns false */
	virtual bool IsMovable() {	return false; } 

	void Move(Gdiplus::Point delta);

	/** Set the drawable position
	* \param pos The new drawable position*/
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Get the drawable position
	* \returns The drawable position*/
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** Set the rotation angle in radians
	* \param r The new rotation angle in radians*/
	void SetRotation(double r) { mRotation = r; }

	/** Get the rotation angle in radians
	* \returns The rotation angle in radians*/
	double GetRotation() const { return mRotation; }

	/** Get the drawable name
	* \returns The drawable name */
	std::wstring GetName() const { return mName; }

	/** Set the parent for this picture
	* \param parent The new parent*/
	void SetParent(CDrawable *parent) { mParent = parent; }

	/** Get the parent for this picture
	* \returns The parent*/
	CDrawable* GetParent() const { return mParent; }

	virtual void SetTimeline(CTimeline * timeline);

	virtual void SetKeyframe();

	virtual void GetKeyframe();

	/** The angle animation channel
	* \returns Pointer to animation channel */
	CAnimChannelAngle *GetAngleChannel() { return &mChannel; }

protected:
	///The actual postion in the drawing
	Gdiplus::Point mPlacedPosition = Gdiplus::Point(0, 0);

	///The actual rotation in the drawing
	double mPlacedR = 0;

	CDrawable(const std::wstring &name);

	Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);

private:
	/// The position of this drawable relative to its parent
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

	///actor name
	std::wstring mName;

	///drawable rotation
	double mRotation = 0;

	/// The actor using this drawable
	CActor *mActor = nullptr;
	
	/// collection of children associated with this picture
	std::vector<std::shared_ptr<CDrawable>> mChildren;

	///parent associated with this picture
	CDrawable *mParent = nullptr;

	/// The animation channel for animating the angle of this drawable
	CAnimChannelAngle mChannel;
};

