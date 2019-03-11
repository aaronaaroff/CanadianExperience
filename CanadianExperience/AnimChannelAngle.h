/**
 * \file AnimChannelAngle.h
 *
 * \author Aaron Eshleman
 *
 *
 * Animation channel for angles.
 * 
 */



#pragma once
#include "AnimChannel.h"

 /**
 * Animation channel for angles.
 */
class CAnimChannelAngle :
	public CAnimChannel
{
public:
	CAnimChannelAngle();

	/** \brief Copy constructor disabled */
	CAnimChannelAngle(const CAnimChannelAngle &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelAngle &) = delete;

	/** Get the animation angle
	* \returns The animation angle */
	double GetAngle() const { return mAngle; }

	virtual ~CAnimChannelAngle();

	/** Class that represents a keyframe */
	class KeyframeAngle :
		public Keyframe
	{
	public:
		/** Constructor
		* \param channel The channel we are for
		* \param angle The angle for the keyframe */
		KeyframeAngle(CAnimChannelAngle *channel, double angle) :
			Keyframe(channel), mChannel(channel), mAngle(angle) {}

		/** \brief Default constructor disabled */
		KeyframeAngle() = delete;
		/** \brief Copy constructor disabled */
		KeyframeAngle(const KeyframeAngle &) = delete;
		/** \brief Assignment operator disabled */ 
		void operator=(const KeyframeAngle &) = delete;

		/** Get the animation angle
		* \returns The animation angle */
		double GetAngle() const { return mAngle; } 

		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mAngle = mAngle; }

	private:
		/// relative angle of the keyframe
		double mAngle = 0;

		/// The channel this keyframe is associated with
		CAnimChannelAngle *mChannel;
	};

	void SetKeyframe(double angle);

protected:

	void Tween(double t);

private:
	/// relative angle of the animation
	double mAngle = 0;

	/// The first angle keyframe
	KeyframeAngle *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeAngle *mKeyframe2 = nullptr;

};

