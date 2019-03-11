/**
 * \file EmptyTest.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(EmptyTest)
	{
	public:
        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}

	};
}