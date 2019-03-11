/**
 * \file ViewTimeline.h
 *
 * \author Aaron Eshleman
 *
 * View window for the animation timeline
 */

#pragma once
#include "PictureObserver.h"

class CMainFrame;

/** View window for the animation timeline */
class CViewTimeline : public CScrollView, public CPictureObserver
{
	DECLARE_DYNCREATE(CViewTimeline)

public:
    static const int Height = 90;      ///< Height to make this window

protected:
	CViewTimeline();           // protected constructor used by dynamic creation
	virtual ~CViewTimeline();


protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEditSetkeyframe();
    afx_msg void OnEditDeletekeyframe();

	/**
	* Set the mainFrame pointer
	* \param mainFrame Pointer to the CMainFrame window
	*/
	void SetMainFrame(CMainFrame *mainFrame) { mMainFrame = mainFrame; }

	virtual void UpdateObserver() override;

private:
	/// The main frame window that uses this view
	CMainFrame  *mMainFrame = nullptr;

	/// Bitmap image for the pointer
	std::unique_ptr<Gdiplus::Bitmap> mPointer;

	/// Flag to indicate we are moving the pointer
	bool mMovingPointer = false;

	///Indicate if play from beginnign is clicked
	bool mBeginning = false;

	///timer in timeline 
	UINT_PTR mTimer;

	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPlayPlay();
	afx_msg void OnPlayPlayfrombeginning();
	afx_msg void OnPlayStop();
};


