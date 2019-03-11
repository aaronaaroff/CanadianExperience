/**
 * \file Actor.cpp
 *
 * \author Aaron Eshleman
 */

#include "stdafx.h"
#include "Actor.h"
#include "Timeline.h"
#include "Picture.h"

using namespace Gdiplus;



/**Constructor
 * 
 * \param name 
 */
CActor::CActor(const std::wstring & name) : mName(name)
{
}

/**
 * Destructor
 */
CActor::~CActor()
{
}


/**Set the root drawable for the actor
 * 
 * \param root 
 */
void CActor::SetRoot(std::shared_ptr<CDrawable> root)
{
	mRoot = root;
}

/**Draw this actor
 * 
 * \param graphics 
 */
void CActor::Draw(Gdiplus::Graphics * graphics)
{
	// Don't draw if not enabled
	if (!mEnabled)
		return;

	// This takes care of determining the absolute placement
	// of all of the child drawables. We have to determine this 
	// in tree order, which may not be the order we draw.
	if (mRoot != nullptr)
		mRoot->Place(mPosition, 0);

	for (auto drawable : mDrawablesInOrder)
	{
		drawable->Draw(graphics);
	}
}

/**Test to see if a mouse click is on this actor.
 * 
 * \param pos 
 * \returns bool
 */
std::shared_ptr<CDrawable> CActor::HitTest(Gdiplus::Point pos)
{
	// If not enabled or not clickable, we indicate no hit.
	if (!mClickable || !mEnabled)
		return nullptr;

	// Since this list is in drawing order, we realy want to know the last thing drawn
	// under the mouse, since it will be on top. So, we reverse iterate over the list.
	for (auto d = mDrawablesInOrder.rbegin(); d != mDrawablesInOrder.rend(); d++)
	{
		auto drawable = *d;
		if (drawable->HitTest(pos))
			return drawable;
	}

	return nullptr;
}

/**Add a drawable to this actor
 * 
 * \param drawable 
 */
void CActor::AddDrawable(std::shared_ptr<CDrawable> drawable)
{
	mDrawablesInOrder.push_back(drawable);
	drawable->SetActor(this);
}

/**
* Set the picture link for this actor.
*
* This is telling the actor what
* picture to use.
*
* Also tells all child drawables what the timeline is.
* \param picture The picture we are using.
*/
void CActor::SetPicture(CPicture *picture)
{
	mPicture = picture;

	CTimeline *timeline = mPicture->GetTimeline();
	timeline->AddChannel(&mChannel);

	// Set the timeline for all drawables. This links the channels to
	// the timeline system.
	for (auto drawable : mDrawablesInOrder)
	{
		drawable->SetTimeline(mPicture->GetTimeline());
	}
}

/** Set a keyframe on an actor.
*/
void CActor::SetKeyframe()
{
	mChannel.SetKeyframe(mPosition);

	for (auto drawable : mDrawablesInOrder)
	{
		drawable->SetKeyframe();
		
	}
}

/** brief Get a keyframe for an actor.
*/
void CActor::GetKeyframe()
{
	for (auto drawable : mDrawablesInOrder)
	{
		drawable->GetKeyframe();
	}

	if (mChannel.IsValid())
	{
		mPosition = mChannel.GetPosition();
	}
}