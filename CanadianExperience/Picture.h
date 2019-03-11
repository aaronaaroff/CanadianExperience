/**
* The picture we are drawing.
*
* There will be one picture object that contains all of
* our actors, which then contains the drawables.
*/

#pragma once
#include <vector>
#include "Actor.h"
#include "Timeline.h"
 
class CPictureObserver;

/**
 * There will be one picture object that contains all of
 *   our actors, which then contains the drawables.
 */
class CPicture
{
public:
	CPicture();
	virtual ~CPicture();
	/// Copy Constructor (Disabled)
	CPicture(const CPicture &) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPicture &) = delete;

	/** The picture size
	* \returns Size */
	Gdiplus::Size GetSize() { return mSize; }

	/** The picture size
	* \param size The new picture size */
	void SetSize(Gdiplus::Size size) { mSize = size; }

	void AddObserver(CPictureObserver *observer);

	/** The picture actor
	* \param actor Actor pointer to be added to vector*/
	void AddActor(std::shared_ptr<CActor> actor);
	void RemoveObserver(CPictureObserver *observer);
	void UpdateObservers();

	/**Draw function
	*\param graphics Pointer to the graphics */
	void Draw(Gdiplus::Graphics *graphics);

	void  SetAnimationTime(double time);

	/** Get a pointer to the Timeline object
	* \returns Pointer to the Timeline object
	*/
	CTimeline *GetTimeline() { return &mTimeline; }


	/** Iterator that iterates over the actors associated with this picture */
	class Iter
	{
	public:
		/** Constructor
		* \param picture The picture we are iterating over 
		* \param pos The position within the iteration */
		Iter(CPicture *picture, int pos) : mPicture(picture), mPos(pos) {}

		/** Test for end of the iterator
		* \param other The other side of the operation
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CActor> operator *() const { return mPicture->mActors[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}


	private:
		CPicture *mPicture = nullptr;   ///< Picture we are iterating over
		int mPos;       ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mActors.size()); }

private:
	/// The picture size
	Gdiplus::Size mSize = Gdiplus::Size(800, 600);

	/// The observers of this picture
	std::vector<CPictureObserver *> mObservers;

	/// The actors associated with this picture
	std::vector<std::shared_ptr<CActor>> mActors;

	/// The animation timeline
	CTimeline mTimeline;
};

