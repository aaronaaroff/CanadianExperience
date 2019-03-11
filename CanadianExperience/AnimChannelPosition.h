/**
* \file AnimChannelPosition.h
*
* \author Aaron Eshleman
*
*
* Animation channel for position
*
*/


#pragma once
#include "AnimChannel.h"

using namespace Gdiplus;

/**
 * Animation channel for position
 */
class CAnimChannelPosition :
	public CAnimChannel
{
public:
	CAnimChannelPosition();

	/** \brief Copy constructor disabled */
	CAnimChannelPosition(const CAnimChannelPosition &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelPosition &) = delete;

	/** Get the animation position
	* \returns The animation position */
	Point GetPosition() const { return mPosition; }

	virtual ~CAnimChannelPosition();

	/** Class that represents a keyframe */
	class KeyframePosition :
		public Keyframe
	{
	public:
		/** Constructor
		* \param channel The channel we are for
		* \param position The position for the keyframe */
		KeyframePosition(CAnimChannelPosition *channel, Point position) :
			Keyframe(channel), mChannel(channel), mPosition(position) {}

		/** \brief Default constructor disabled */
		KeyframePosition() = delete;
		/** \brief Copy constructor disabled */
		KeyframePosition(const KeyframePosition &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframePosition &) = delete;

		/** Get the animation position
		* \returns The animation position */
		Point GetPosition() const { return mPosition; }

		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the position */
		virtual void UseOnly() override { mChannel->mPosition = mPosition; }

	private:
		/// relative position of the keyframe
		Point mPosition = Point(0,0);

		/// The channel this keyframe is associated with
		CAnimChannelPosition *mChannel;
	};

	void SetKeyframe(Point position);

protected:

	void Tween(double t);

private:
	/// relative position of the animation
	Point mPosition = Point(0,0);

	/// The first position keyframe
	KeyframePosition *mKeyframe1 = nullptr;

	/// The second position keyframe
	KeyframePosition *mKeyframe2 = nullptr;

};

