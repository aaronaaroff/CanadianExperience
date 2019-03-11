// TimelineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CanadianExperience.h"
#include "TimelineDlg.h"
#include "Timeline.h"
#include "afxdialogex.h"


// CTimelineDlg dialog

IMPLEMENT_DYNAMIC(CTimelineDlg, CDialog)


/**Constructor
 * 
 * \param pParent 
 */
CTimelineDlg::CTimelineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, mNumFrames(0)
	, mFrameRate(0)
{

}

CTimelineDlg::~CTimelineDlg()
{
}


/**Do the data exchange just read the function
 * 
 * \param pDX 
 */
void CTimelineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMFRAMES, mNumFrames);
	DDV_MinMaxInt(pDX, mNumFrames, 10, 10000);
	DDX_Text(pDX, IDC_FRAME_RATE, mFrameRate);
	DDV_MinMaxInt(pDX, mFrameRate, 1, 60);
}


BEGIN_MESSAGE_MAP(CTimelineDlg, CDialog)
END_MESSAGE_MAP()


// CTimelineDlg message handlers

/**
* Pass a timeline object to this dialog box class.
* \param timeline The timeline object.
*/
void CTimelineDlg::SetTimeline(CTimeline *timeline)
{
	mTimeline = timeline;
	mNumFrames = mTimeline->GetNumFrames();
	mFrameRate = mTimeline->GetFrameRate();
}

/** Transfer dialog values to the Timeline object
*/
void CTimelineDlg::Take()
{
	mTimeline->SetNumFrames(mNumFrames);
	mTimeline->SetFrameRate(mFrameRate);
}