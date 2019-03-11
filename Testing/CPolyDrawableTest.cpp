#include "stdafx.h"
#include "CppUnitTest.h"
#include "Drawable.h"
#include "PolyDrawable.h"

#include "Actor.h"
#include "Picture.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CPolyDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestConstructorAndName)
		{
			CPolyDrawable polydrawable(L"Harold");
			Assert::AreEqual(std::wstring(L"Harold"), polydrawable.GetName());
		}

		TEST_METHOD(TestColorGetterAndSetter)
		{
			CPolyDrawable polydrawable(L"Harold");

			Gdiplus::Color color = Gdiplus::Color::Black;

			Gdiplus::Color polycolor = polydrawable.GetColor();

			Assert::AreEqual(color.GetValue(), polycolor.GetValue());

			Gdiplus::Color color2 = Gdiplus::Color::Blue;

			polydrawable.SetColor(Gdiplus::Color::Blue);
			polycolor = polydrawable.GetColor();

			Assert::AreEqual(color2.GetValue(), polycolor.GetValue());



		}

		/** This tests that the animation
		* of the rotation of a drawable works */
		TEST_METHOD(TestCPolyDrawableAnimation)
		{
			// Create a picture object
			auto picture = make_shared<CPicture>();

			// Create an actor and add it to the picture
			auto actor = make_shared<CActor>(L"Actor");

			// Create a drawable for the actor
			auto drawable = make_shared<CPolyDrawable>(L"Drawable");
			actor->SetRoot(drawable);
			actor->AddDrawable(drawable);

			picture->AddActor(actor);

			auto channel = drawable->GetAngleChannel();

			// First we will ensure it works with no keyframes set
			picture->SetAnimationTime(0);
			drawable->SetRotation(1.33);

			// The channel should not be valid
			Assert::IsFalse(channel->IsValid());

			// Getting a keyframe should not changle the angle
			actor->GetKeyframe();
			Assert::AreEqual(1.33, drawable->GetRotation(), 0.00001);

			// Now we'll set one keyframe and see if that works
			picture->SetAnimationTime(1.5);
			drawable->SetRotation(2.7);
			actor->SetKeyframe();

			// Change angle
			drawable->SetRotation(0.3);
			Assert::AreEqual(0.3, drawable->GetRotation(), 0.00001);

			// Wherever we move, now, the keyframe angle should be used
			picture->SetAnimationTime(0);
			Assert::AreEqual(2.7, drawable->GetRotation(), 0.00001);

			drawable->SetRotation(0.3);
			picture->SetAnimationTime(1.5);
			Assert::AreEqual(2.7, drawable->GetRotation(), 0.00001);

			drawable->SetRotation(0.3);
			picture->SetAnimationTime(3);
			Assert::AreEqual(2.7, drawable->GetRotation(), 0.00001);

			// We'll set a second keyframe and see if that works
			picture->SetAnimationTime(3.0);
			drawable->SetRotation(-1.8);
			actor->SetKeyframe();

			// Test before the keyframes
			drawable->SetRotation(0.3);
			picture->SetAnimationTime(0);
			Assert::AreEqual(2.7, drawable->GetRotation(), 0.00001);

			// Test at first keyframe
			drawable->SetRotation(0.3);
			picture->SetAnimationTime(1.5);
			Assert::AreEqual(2.7, drawable->GetRotation(), 0.00001);

			// Test at second keyframe
			drawable->SetRotation(0.3);
			picture->SetAnimationTime(3.0);
			Assert::AreEqual(-1.8, drawable->GetRotation(), 0.00001);

			// Test after second keyframe
			drawable->SetRotation(0.3);
			picture->SetAnimationTime(4);
			Assert::AreEqual(-1.8, drawable->GetRotation(), 0.00001);

			// Test between the two keyframs
			drawable->SetRotation(0.3);
			picture->SetAnimationTime(2.25);    // Halfway between the two keyframes
			Assert::AreEqual((2.7 + -1.8) / 2, drawable->GetRotation(), 0.00001);

			drawable->SetRotation(0.3);
			picture->SetAnimationTime(2.0);    // 1/3 between the two keyframes
			Assert::AreEqual(2.7 + 1.0 / 3.0 * (-1.8 - 2.7), drawable->GetRotation(), 0.00001);

		}

	};
}