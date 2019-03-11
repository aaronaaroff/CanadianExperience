#include "stdafx.h"
#include "CppUnitTest.h"
#include "ImageDrawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CImageDrawableTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}


		TEST_METHOD(CImageDrawableTestCenter)
		{
			CImageDrawable imageDrawable(L"Shirt", L"images/harold_shirt.png");

			Assert::IsTrue(imageDrawable.GetName() == L"Shirt");

			Assert::AreEqual(0, imageDrawable.GetCenter().X);
			Assert::AreEqual(0, imageDrawable.GetCenter().Y);

			imageDrawable.SetCenter(Gdiplus::Point(234, 569));
			Assert::AreEqual(234, imageDrawable.GetCenter().X);
			Assert::AreEqual(569, imageDrawable.GetCenter().Y);
		}

	};
}