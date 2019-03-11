#include "stdafx.h"
#include "CppUnitTest.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{

	class CAnimChannelAngleMock : public CAnimChannelAngle
	{
	public:
		CAnimChannelAngleMock() : CAnimChannelAngle() {}
	};
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestConstructor)
		{	
			CAnimChannelAngleMock anim;
		}

		TEST_METHOD(TestNameGetterAndSetter)
		{
			CAnimChannelAngleMock anim;
			Assert::AreEqual(std::wstring(L""), anim.GetName());

			anim.SetName(L"Jerald");
			Assert::AreEqual(std::wstring(L"Jerald"), anim.GetName());

		}
	};
}