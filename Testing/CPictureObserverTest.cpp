#include "stdafx.h"
#include "CppUnitTest.h"
#include "PictureObserver.h"
#include "Picture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/**This class implements the base class functionality for an observer in the observer pattern. */
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		CPictureObserverMock() : CPictureObserver() {}

		virtual void UpdateObserver() override { mUpdated = true; }


		bool mUpdated = false;


	};

	TEST_CLASS(CPictureObserverTest)
	{
	public:

		TEST_METHOD(TestCPictureObserverConstruct)
		{
			CPictureObserverMock observer;
		}


		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);
		}

		TEST_METHOD(TestCPictureObserverGetPicture)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			Assert::IsTrue(observer.GetPicture() == picture);
		}

		TEST_METHOD(TestCPictureObserverTwoObservers)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create mock observer objects
			CPictureObserverMock observer1;
			CPictureObserverMock observer2;

			// And set it for the observer:
			observer1.SetPicture(picture);
			observer2.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);
			Assert::IsTrue(observer2.mUpdated);
		}

		TEST_METHOD(TestCPictureObserverDestroyedObservers)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create mock observer objects
			CPictureObserverMock observer1;
			observer1.SetPicture(picture);

			{
				CPictureObserverMock observer2;

				// And set it for the observer:
				observer2.SetPicture(picture);
			}

			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);
		}

	};
}