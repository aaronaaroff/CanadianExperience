#include "stdafx.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		TEST_METHOD(TestNumFramesGetterandSetter)
		{
			CTimeline timeline;

			Assert::AreEqual(timeline.GetNumFrames(), 300);

			timeline.SetNumFrames(500);

			Assert::AreEqual(timeline.GetNumFrames(), 500);
		}

		TEST_METHOD(TestFrameRateGetterandSetter)
		{
			CTimeline timeline;

			Assert::AreEqual(timeline.GetFrameRate(), 30);

			timeline.SetFrameRate(500);

			Assert::AreEqual(timeline.GetFrameRate(), 500);
		}

		TEST_METHOD(TestCurrentTimeGetterandSetter)
		{
			CTimeline timeline;

			Assert::AreEqual(timeline.GetCurrentTime(), 0.0);

			timeline.SetCurrentTime(50.0);

			Assert::AreEqual(timeline.GetCurrentTime(), 50.0);
		}

		TEST_METHOD(TestCTimelineGetDuration)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

			// Changed duration
			timeline.SetFrameRate(375);
			Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

			timeline.SetNumFrames(789);
			Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
		}

		TEST_METHOD(TestCTimelineGetCurrentFrame)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(0, timeline.GetCurrentFrame());

			// Changed time
			timeline.SetCurrentTime(9.27);
			Assert::AreEqual(278, timeline.GetCurrentFrame());
		}

		TEST_METHOD(TestCTimelineAdd)
		{
			CTimeline timeline;
			CAnimChannelAngle channel;

			timeline.AddChannel(&channel);
			Assert::IsTrue(&timeline == channel.GetTimeline());
		}

	};
}