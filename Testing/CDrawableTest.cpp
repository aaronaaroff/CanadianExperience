#include "stdafx.h"
#include "CppUnitTest.h"

#include "Drawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	/**This class implements the base class functionality for a drawable object */

	class CDrawableMock : public CDrawable
	{
	public:
		CDrawableMock(const std::wstring &name) : CDrawable(name) {}

		virtual void Draw(Gdiplus::Graphics *graphics) override {}
		virtual bool HitTest(Gdiplus::Point pos) override { return false; }

	};
	TEST_CLASS(CDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestConstructorAndName)
		{
			CDrawableMock drawable(L"Harold");
			Assert::AreEqual(std::wstring(L"Harold"), drawable.GetName());
		}

		TEST_METHOD(TestPositionSetterAndGetter)
		{
			CDrawableMock drawable(L"Harold");

			Assert::AreEqual(0, drawable.GetPosition().X);
			Assert::AreEqual(0, drawable.GetPosition().Y);

			drawable.SetPosition(Gdiplus::Point(13, 13));

			Assert::AreEqual(13, drawable.GetPosition().X);
			Assert::AreEqual(13, drawable.GetPosition().Y);
		}

		TEST_METHOD(TestRotationGetterAndSetter)
		{
			CDrawableMock drawable(L"Harold");

			Assert::AreEqual(0, drawable.GetRotation(), 0.00001);

			drawable.SetRotation(1.23);
			Assert::AreEqual(1.23, drawable.GetRotation(), 0.00001);

		}
		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			Assert::IsNull(arm->GetParent());
			Assert::IsNull(leg->GetParent());

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}

	};
}