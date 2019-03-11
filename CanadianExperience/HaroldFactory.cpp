/**
 * \file HaroldFactory.cpp
 *
 * \author Aaron Eshleman
 */


#include "stdafx.h"
#include "HaroldFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"
#include <memory>

using namespace std;
using namespace Gdiplus;


/**
 * Constructor
 */
CHaroldFactory::CHaroldFactory()
{
}


/**
 * Destructor
 */
CHaroldFactory::~CHaroldFactory()
{
}

/** This is a concrete factory method that creates our Harold actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CHaroldFactory::Create()
{
	shared_ptr<CActor> actor = make_shared<CActor>(L"Harold");

	auto shirt = make_shared<CImageDrawable>(L"Shirt", L"images/harold_shirt.png");
	shirt->SetCenter(Point(44, 138));
	shirt->SetPosition(Point(0, -114));
	actor->SetRoot(shirt);

	auto vest = make_shared<CImageDrawable>(L"Vest", L"images/harold_vest.png");
	vest->SetCenter(Point(44, 138));
	shirt->AddChild(vest);

	auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/harold_lleg.png");
	lleg->SetCenter(Point(11, 9));
	lleg->SetPosition(Point(27, 0));
	shirt->AddChild(lleg);

	auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/harold_rleg.png");
	rleg->SetCenter(Point(39, 9));
	rleg->SetPosition(Point(-27, 0));
	shirt->AddChild(rleg);

	auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/harold_headb.png");
	headb->SetCenter(Point(44, 31));
	headb->SetPosition(Point(0, -130));
	shirt->AddChild(headb);

	auto headt = make_shared<CHeadTop>(L"Head Top", L"images/harold_headt_blank.png");
	headt->SetCenter(Point(55, 109));
	headt->SetPosition(Point(0, -31));
	headb->AddChild(headt);

	auto larm = make_shared<CPolyDrawable>(L"Left Arm");
	larm->SetColor(Color(60, 174, 184));
	larm->SetPosition(Point(50, -130));
	larm->AddPoint(Point(-7, -7));
	larm->AddPoint(Point(-7, 96));
	larm->AddPoint(Point(8, 96));
	larm->AddPoint(Point(8, -7));
	shirt->AddChild(larm);


	auto rarm = make_shared<CPolyDrawable>(L"Right Arm");
	rarm->SetColor(Color(60, 174, 184));
	rarm->SetPosition(Point(-45, -130));
	rarm->AddPoint(Point(-7, -7));
	rarm->AddPoint(Point(-7, 96));
	rarm->AddPoint(Point(8, 96));
	rarm->AddPoint(Point(8, -7));
	shirt->AddChild(rarm);

	auto lhand = make_shared<CPolyDrawable>(L"Left Hand");
	lhand->SetColor(Color(253, 218, 180));
	lhand->SetPosition(Point(0, 96));
	lhand->AddPoint(Point(-12, -2));
	lhand->AddPoint(Point(-12, 17));
	lhand->AddPoint(Point(11, 17));
	lhand->AddPoint(Point(11, -2));
	larm->AddChild(lhand);

	auto rhand = make_shared<CPolyDrawable>(L"Right Hand");
	rhand->SetColor(Color(253, 218, 180));
	rhand->SetPosition(Point(0, 96));
	rhand->AddPoint(Point(-12, -2));
	rhand->AddPoint(Point(-12, 17));
	rhand->AddPoint(Point(11, 17));
	rhand->AddPoint(Point(11, -2));
	rarm->AddChild(rhand);


	actor->AddDrawable(larm);
	actor->AddDrawable(rarm);
	actor->AddDrawable(rhand);
	actor->AddDrawable(lhand);
	actor->AddDrawable(rleg);
	actor->AddDrawable(lleg);
	actor->AddDrawable(shirt);
	actor->AddDrawable(vest);
	actor->AddDrawable(headb);
	actor->AddDrawable(headt);

	return actor;

}