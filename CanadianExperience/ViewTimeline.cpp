/**
 * \file ViewTimeline.cpp
 *
 * \author Aaron Eshleman
 */


#include "stdafx.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include "Timeline.h"
#include "Picture.h"

#include <sstream>

#include "MainFrm.h"

using namespace std;
using namespace Gdiplus;


/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;


IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{
	mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
	assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}




/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
	// Get the timeline
	CTimeline *timeline = GetPicture()->GetTimeline();

	// Set the scroll system correctly
	CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
	SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 8);

	CRect rect;
	GetClientRect(&rect);
	int hit = rect.Height();
	int wid = rect.Width();

	int tickNum = 0;
	Pen tickpen(Color(0, 0, 0), 1);


	// Draws ticks on timeline
	while (tickNum != timeline->GetNumFrames()) 
	{
		double drawPointer = double(tickNum) / timeline->GetFrameRate();
		bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;

		if (onSecond)
		{
			// Convert the tick number to seconds in a string
			std::wstringstream str;
			str << tickNum / timeline->GetFrameRate();
			std::wstring wstr = str.str();

			RectF size;
			PointF origin(0.0f, 0.0f);
			graphics.MeasureString(wstr.c_str(), wstr.size(),
				&font, origin, &size);

			SolidBrush brush(Color(0, 0, 0));
			graphics.DrawString(wstr.c_str(),  // String to draw
				-1,         // String length, -1 means it figures it out on its own
				&font,      // The font to use
				PointF(BorderLeft + (tickNum * TickSpacing) - (wstr.size()*5), BorderTop + TickLong),   // Where to draw
				&brush);    // The brush to draw the text with

			graphics.DrawLine(&tickpen, BorderLeft + (tickNum * TickSpacing), BorderTop, BorderLeft + (tickNum * TickSpacing), BorderTop + TickLong);
		}
		else
		{
			graphics.DrawLine(&tickpen,BorderLeft + (tickNum * TickSpacing), BorderTop, BorderLeft + (tickNum * TickSpacing), BorderTop + TickShort);
		}


		tickNum++;
	}


	graphics.DrawImage(mPointer.get(), int(timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing + BorderLeft) - mPointer->GetWidth()/2, BorderTop, mPointer->GetWidth(), mPointer->GetHeight());
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle the Edit>Set Keyframe menu option */
 void CViewTimeline::OnEditSetkeyframe()
 {
	 for (auto actor : *GetPicture())
	 {
		 actor->SetKeyframe();
	 }
 }


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
	 std::shared_ptr<CPicture> picture = GetPicture();
	 CTimeline* timeline = picture->GetTimeline();
	 timeline->DeleteKeyframe();
	 picture->SetAnimationTime(timeline->GetCurrentTime());
 }

 /**
 * When Play is pressed
 */
 void CViewTimeline::OnPlayPlay()
 {
	 std::shared_ptr<CPicture> picture = GetPicture();
	 CTimeline* timeline = picture->GetTimeline();
	 mTimer = SetTimer(1, timeline->GetFrameRate(), nullptr);

	 /*
	 * Initialize the elapsed time system
	 */
	 LARGE_INTEGER time, freq;
	 QueryPerformanceCounter(&time);
	 QueryPerformanceFrequency(&freq);

	 mLastTime = time.QuadPart;
	 mTimeFreq = double(freq.QuadPart);

 }


 /**
 * When Play from beginning
 */
 void CViewTimeline::OnPlayPlayfrombeginning()
 {
	 mBeginning = true;

	 std::shared_ptr<CPicture> picture = GetPicture();
	 CTimeline* timeline = picture->GetTimeline();
	 mTimer = SetTimer(1, timeline->GetFrameRate(), nullptr);

	 /*
	 * Initialize the elapsed time system
	 */
	 LARGE_INTEGER time, freq;
	 QueryPerformanceCounter(&time);
	 QueryPerformanceFrequency(&freq);

	 mLastTime = time.QuadPart;
	 mTimeFreq = double(freq.QuadPart);
 }


 /**
 * When Stop is pressed
 */
 void CViewTimeline::OnPlayStop()
 {
	 KillTimer(mTimer);
 }

 /** Force an update of this window when the picture changes.
 */
 void CViewTimeline::UpdateObserver()
 {
	 UpdateWindow();
	 Invalidate();
 }



 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
	 ON_WM_LBUTTONDOWN()
	 ON_WM_MOUSEMOVE()
	 ON_WM_TIMER()
	 ON_COMMAND(ID_PLAY_PLAY, &CViewTimeline::OnPlayPlay)
	 ON_COMMAND(ID_PLAY_PLAYFROMBEGINNING, &CViewTimeline::OnPlayPlayfrombeginning)
	 ON_COMMAND(ID_PLAY_STOP, &CViewTimeline::OnPlayStop)
 END_MESSAGE_MAP()
 

/**Event Handler for L Button Down
 * 
 * \param nFlags 
 * \param point 
 */
 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);

	 int x = point.x;

	 // Get the timeline
	 CTimeline *timeline = GetPicture()->GetTimeline();
	 int pointerX = (int)(timeline->GetCurrentTime() *
		 timeline->GetFrameRate() * TickSpacing + BorderLeft);

	 mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
		 x <= pointerX + (int)mPointer->GetWidth() / 2;


	 __super::OnLButtonDown(nFlags, point);
 }



/**Event handler when mouse is moved on the timeline, executes when pointer is clicked
 * 
 * \param nFlags 
 * \param point 
 */
 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);
	 double time = 0;
	 CTimeline *timeline = GetPicture()->GetTimeline();
	 std::shared_ptr<CPicture> picture = GetPicture();
	 

	 if (mMovingPointer)
	 {
		 // If an item is being moved, we only continue to 
		 // move it while the left button is down.
		 if (nFlags & MK_LBUTTON)
		 {
			 // calculates time using x location of the mouse
			 time = double((point.x - BorderLeft)) / (timeline->GetFrameRate() * TickSpacing);

			 // calls setAnimation time which in turn calls updateobservers  and sets current time for this timeline.
			 if (time >= 0 && time <= timeline->GetDuration())
			 {
				 picture->SetAnimationTime(time);
			 }
		 }
		 else
		 {
			 // When the left button is released, we release the
			 // item.
			 mMovingPointer = false;
		 }

	 }


	 __super::OnMouseMove(nFlags, point);
 }


/**Timer event
 * 
 * \param nIDEvent 
 */
 void CViewTimeline::OnTimer(UINT_PTR nIDEvent)
 {
	 /*
	 * Compute the elapsed time since the last draw
	 */
	 LARGE_INTEGER time;
	 QueryPerformanceCounter(&time);
	 long long diff = time.QuadPart - mLastTime;
	 double elapsed = double(diff) / mTimeFreq;
	 mLastTime = time.QuadPart;

	 if (mBeginning)
	 {
		 GetPicture()->SetAnimationTime(0);
		 mBeginning = false;

	 }

	 CTimeline *timeline = GetPicture()->GetTimeline();

	 GetPicture()->SetAnimationTime(elapsed + timeline->GetCurrentTime());

	 if (timeline->GetCurrentTime() > timeline->GetDuration())
	 {
		 OnPlayStop();
	 }

	 Invalidate();
	 __super::OnTimer(nIDEvent);
 }



