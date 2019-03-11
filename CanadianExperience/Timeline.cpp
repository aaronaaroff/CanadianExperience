/**
 * \file Timeline.cpp
 *
 * \author Aaron Eshleman
 */



#include "stdafx.h"
#include "Timeline.h"
#include <cmath>
#include "AnimChannel.h"


CTimeline::CTimeline()
{
}


/**pushes back channel to vecotr and sets timeline
 * 
 * \param channel 
 */
 void CTimeline::AddChannel(CAnimChannel * channel)
 {
	 mChannels.push_back(channel);
	 channel->SetTimeline(this);
 }


/**
 * Loops thru channels to delete a chosen keyframe
 */
 void CTimeline::DeleteKeyframe()
 {
	 for (auto channel : mChannels)
	 {
		 channel->DeleteKeyframe();
	 }
 }

 /** Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 * \param t
 */
 void CTimeline::SetCurrentTime(double t)
 {
	 // Set the time
	 mCurrentTime = t;

	 for (auto channel : mChannels)
	 {
		 channel->SetFrame(GetCurrentFrame());
	 }
 }

 CTimeline::~CTimeline()
{
}
