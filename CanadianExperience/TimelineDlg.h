/**
 * \file TimelineDlg.h
 *
 * \author Aaron Eshleman
 *
 * Keeps track of the dialog box for Timeline settings
 * Dialog box that changes timeline settings
 *
 */



#pragma once
class CTimeline;


/**
 * Dialog box that changes timeline settings
 */
class CTimelineDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDlg)

public:
	CTimelineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimelineDlg();

	void SetTimeline(CTimeline * timeline);

	void Take();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	/// Number of frames input form dialog box
	int mNumFrames;

	/// The timeline we are editing
	CTimeline *mTimeline = nullptr;

	/// Frame Rate inputted from dlg box
	int mFrameRate;
};
