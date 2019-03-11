#include "stdafx.h"
#include <memory>
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "ImageDrawable.h"
#include "BaldyFactory.h"

#include "Picture.h"

using namespace std;
using namespace Gdiplus;


/**
 * Constructor
 */
CPictureFactory::CPictureFactory()
{
}


/**
 * Destructor
 */
CPictureFactory::~CPictureFactory()
{
}

/** This is a concrete factory method that creates our Picture
* \returns Pointer to an picture object.
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
	shared_ptr<CPicture> picture = make_shared<CPicture>();

	// Create the background and add it
	auto background = make_shared<CActor>(L"Background");
	background->SetClickable(false);
	background->SetPosition(Point(-100, 0));
	auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/strangerthings-background.png");
	background->AddDrawable(backgroundI);
	background->SetRoot(backgroundI);
	picture->AddActor(background);

	// Create and add Harold
	CHaroldFactory factory;
	auto harold = factory.Create();

	//Create and add Baldy
	CBaldyFactory factory2;
	auto baldy = factory2.Create();

	// This is where Harold will start out.
	harold->SetPosition(Point(400, 500));

	baldy->SetPosition(Point(600, 500));

	picture->AddActor(harold);
	picture->AddActor(baldy);


	return picture;
}
