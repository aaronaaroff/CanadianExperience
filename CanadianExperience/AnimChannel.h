/**
 * \file AnimChannel.h
 *
 * \author Aaron Eshleman
 *
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 * 
 */


#pragma once
#include <string>
#include <memory>
#include <vector>

class CTimeline;

/**
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class CAnimChannel
{
public:
	CAnimChannel();

	/** \brief Copy constructor disabled */
	CAnimChannel(const CAnimChannel &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannel &) = delete;

	/** Get the animation name
	* \returns The animation name */
	std::wstring GetName() const { return mName; }

	/** Set the name for this animation
	* \param name The new name*/
	void SetName(std::wstring name) { mName = name; }

	/** Get the animation timeline
	* \returns The animation timeline */
	CTimeline* GetTimeline() const { return mTimeline; }

	/** Set the timeline for this animation
	* \param timeline The new timeline*/
	void SetTimeline(CTimeline* timeline) { mTimeline = timeline; }

	bool IsValid();

	virtual ~CAnimChannel();

	/** Class that represents a keyframe */
	class Keyframe
	{
	public:

		/** Get the keyframe
		* \returns The animation frame */
		int GetFrame() const { return mFrame; }

		/** Set the frame for this keyframe
		* \param frame The new frame*/
		void SetFrame(int frame) { mFrame = frame; }

		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() = 0;
		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() = 0;
		/** Use this keyframe as the angle */
		virtual void UseOnly() = 0;

	protected:
		/// current frame
		int mFrame;

		/** Constructor
		* \param channel Channel we are associated with */
		Keyframe(CAnimChannel *channel) : mChannel(channel) {}

		/** \brief Default constructor disabled */
		Keyframe() = delete;
		/** \brief Copy constructor disabled */
		Keyframe(const Keyframe &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const Keyframe &) = delete;


	private:
		/// The channel this keyframe is associated with
		CAnimChannel *mChannel;

	};

	void SetFrame(int currFrame);

	void DeleteKeyframe();
 

protected:
	virtual void Tween(double t);

	void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);
private:
	/// name of channel 
	std::wstring mName;
	/// keyframe one for this animation
	int mKeyframe1 = -1;
	/// keyframe two for this animation
	int mKeyframe2 = -1;

	/// The timeline object
	CTimeline *mTimeline = nullptr;

	/// The collection of keyframes for this channel
	std::vector<std::shared_ptr<Keyframe>> mKeyframes;

};

