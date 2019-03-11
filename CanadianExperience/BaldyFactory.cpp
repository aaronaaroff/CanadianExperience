/**
 * \file BaldyFactory.cpp
 *
 * \author Aaron Eshleman
 */


#include "stdafx.h"
#include "BaldyFactory.h"
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
CBaldyFactory::CBaldyFactory()
{
}


/**
 * Destructor
 */
CBaldyFactory::~CBaldyFactory()
{
}

/** This is a concrete factory method that creates our Harold actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CBaldyFactory::Create()
{
	shared_ptr<CActor> actor = make_shared<CActor>(L"Baldy");

	auto shirt = make_shared<CImageDrawable>(L"Shirt", L"images/eleven_dress.png");
	shirt->SetCenter(Point(64, 148));
	shirt->SetPosition(Point(0, -114));
	actor->SetRoot(shirt);


	auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/lleg2.png");
	lleg->SetCenter(Point(11, 9));
	lleg->SetPosition(Point(27, 0));
	shirt->AddChild(lleg);

	auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/rleg2.png");
	rleg->SetCenter(Point(39, 9));
	rleg->SetPosition(Point(-27, 0));
	shirt->AddChild(rleg);

	auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/headb3.png");
	headb->SetCenter(Point(44, 31));
	headb->SetPosition(Point(0, -130));
	shirt->AddChild(headb);
	  
	auto headt = make_shared<CHeadTop>(L"Head Top", L"images/headt3.png");
	headt->SetCenter(Point(50, 94));
	headt->SetPosition(Point(0, -31));
	headb->AddChild(headt);


	auto larm = make_shared<CPolyDrawable>(L"Left Arm");
	larm->SetColor(Color(244, 206, 206));
	larm->SetPosition(Point(50, -125));
	larm->AddPoint(Point(-7, -7));
	larm->AddPoint(Point(-7, 96));
	larm->AddPoint(Point(8, 96));
	larm->AddPoint(Point(8, -7));
	shirt->AddChild(larm);


	auto rarm = make_shared<CPolyDrawable>(L"Right Arm");
	rarm->SetColor(Color(244, 206, 206));
	rarm->SetPosition(Point(-45, -125));
	rarm->AddPoint(Point(-7, -7));
	rarm->AddPoint(Point(-7, 96));
	rarm->AddPoint(Point(8, 96));
	rarm->AddPoint(Point(8, -7));
	shirt->AddChild(rarm);

	auto eggo = make_shared<CImageDrawable>(L"Eggo", L"images/eggo.png");
	eggo->SetCenter(Point(117, 96));
	eggo->SetPosition(Point(-30, 96));
	rarm->AddChild(eggo);

	actor->AddDrawable(larm);
	actor->AddDrawable(rarm);
	actor->AddDrawable(rleg);
	actor->AddDrawable(lleg);
	actor->AddDrawable(shirt);
	actor->AddDrawable(headb);
	actor->AddDrawable(headt);
	actor->AddDrawable(eggo);

	return actor;
}
