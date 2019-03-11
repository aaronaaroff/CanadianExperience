/**
 * \file Actor.h
 *
 * \author Aaron Eshleman
 *
 * Class for actors in our drawings
 */



#pragma once

#include "Drawable.h"
#include "AnimChannelPosition.h"
#include <string>
#include <memory>
#include <vector>

class CPicture;

/**
 * An actor is some graphical object that consists of
* one or more parts. Actors can be animated.
 */
class CActor
{
public:
	CActor(const std::wstring &name);

	/** Default constructor disabled */
	CActor() = delete;
	/** Copy constructor disabled */
	CActor(const CActor &) = delete;
	/** Assignment operator disabled */
	void operator=(const CActor &) = delete;

	virtual ~CActor();

	void SetRoot(std::shared_ptr<CDrawable> root);
	void Draw(Gdiplus::Graphics *graphics);
	std::shared_ptr<CDrawable> HitTest(Gdiplus::Point pos);
	void AddDrawable(std::shared_ptr<CDrawable> drawable);

	/** Get the actor name
	* \returns Actor name */
	std::wstring GetName() const { return mName; }

	/** Actor is enabled
	* \returns enabled status */
	bool IsEnabled() const { return mEnabled; }

	/** Set Actor Enabled
	* \param enabled New enabled status */
	void SetEnabled(bool enabled) { mEnabled = enabled; }

	/** Returns actor's position as a point
	* \returns point */
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** Set Actor position
	* \param position New position */
	void SetPosition(Gdiplus::Point position) { mPosition = position; }

	/** Actor is clickable
	* \returns clickable status */
	bool IsClickable() const { return mClickable; }

	/** Set Actor Clickable
	* \param clickable New status */
	void SetClickable(bool clickable) { mClickable = clickable; }

	/** Returns picture actor is associated to
	* \returns CPicture */
	CPicture* GetPicture() { return mPicture; }

	/** Set Actor's picture
	* \param picture New picture */
	void SetPicture(CPicture* picture);

	/** The position animation channel
	* \returns Pointer to animation channel */
	CAnimChannelPosition *GetPositionChannel() { return &mChannel; }

	void SetKeyframe();

	void GetKeyframe();

private:
	///actor name
	std::wstring mName;

	/// true if actor is enabled
	bool mEnabled = true;

	/// actor position (x, y)
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

	///if actor is clickable
	bool mClickable = true;

	/// The root drawable
	std::shared_ptr<CDrawable> mRoot;

	/// The drawables in drawing order
	std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;

	/// pointer to the picture associated with this actor
	CPicture *mPicture = nullptr;

	/// The animation channel for animating position of this actor
	CAnimChannelPosition mChannel;

};

