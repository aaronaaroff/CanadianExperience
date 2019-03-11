/**
 * \file MainFrm.cpp
 *
 * Implementation of the CMainFrame class
 * \author Aaron Eshleman
 */

#include "stdafx.h"
#include "CanadianExperience.h"

#include "MainFrm.h"
#include "Picture.h"
#include "PictureFactory.h"
#include "TimelineDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_EDIT_MOVE, &CMainFrame::OnEditMove)
    ON_UPDATE_COMMAND_UI(ID_EDIT_MOVE, &CMainFrame::OnUpdateEditMove)
    ON_COMMAND(ID_EDIT_ROTATE, &CMainFrame::OnEditRotate)
    ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATE, &CMainFrame::OnUpdateEditRotate)
	ON_COMMAND(ID_EDIT_TIMELINEPROPERTIES, &CMainFrame::OnEditTimelineproperties)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/** Constructor */
CMainFrame::CMainFrame()
{
}

/** Destructor */
CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockPane(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the edit window
	//m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // Route the command to each of the child windows
    if(mViewEdit->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    {
        return TRUE;
    }

    if (mViewTimeline->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    {
        return TRUE;
    }

	// otherwise, do default handling
	return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    if (!mWndSplitter.CreateStatic(this, 2, 1))
    {
        TRACE("Failed to create splitter window");
        return FALSE;
    }

    CRect rect;

    GetClientRect(&rect);
    mWndSplitter.CreateView(0, 0, RUNTIME_CLASS(CViewEdit), CSize(0, 0), pContext);
    mWndSplitter.CreateView(1, 0, RUNTIME_CLASS(CViewTimeline), CSize(0, 0), pContext);

    mViewTimeline = (CViewTimeline *)mWndSplitter.GetPane(1, 0);
    mViewEdit = (CViewEdit *)mWndSplitter.GetPane(0, 0);

    Initialize();

    return TRUE;
}

/** Handle a Size request from Windows
 * 
 * This function ensures the child windows are the correct size
 * on the screen after the main window is resized 
 * \param nType Type of resizing message
 * \param cx The new width
 * \param cy The new height */
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
    // Upcall the base class version
    CFrameWndEx::OnSize(nType, cx, cy);

    // Get the client area without the toolbar and status bar
    CRect rect;
    GetDockingManager()->GetClientAreaBounds(rect);
    mWndSplitter.MoveWindow(rect);

    // Make the children the right size
    int editHeight = rect.Height() - CViewTimeline::Height;
    if (editHeight < 0) 
    {
        editHeight = 0;
    }
    mWndSplitter.SetRowInfo(0, editHeight, 0);
    mWndSplitter.SetRowInfo(1, CViewTimeline::Height, 0);
    mWndSplitter.RecalcLayout();
}

/** Called to erase the background. Disabled so we don't get flicker 
 * \param pDC A device context 
 * \return FALSE */
BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle the Edit>Mode menu option */
void CMainFrame::OnEditMove()
{
    mMode = Move;
}


/** Update the menu for Edit>Move 
 * \param pCmdUI The pointer to the control user interface */
void CMainFrame::OnUpdateEditMove(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(mMode == Move);
}


/** Handle the Edit>Rotate menu option */
void CMainFrame::OnEditRotate()
{
    mMode = Rotate;
}


/** Update the menu for Edit>Rotate
* \param pCmdUI The pointer to the control user interface */
void CMainFrame::OnUpdateEditRotate(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(mMode == Rotate);
}


/** Code to initialize the system */
void CMainFrame::Initialize()
{
	//
	// Create the picture
	//

	// Create our picture
	CPictureFactory factory;
	mPicture = factory.Create();

	//
	// Create the associations with the child windows 
	//

	mViewEdit->SetMainFrame(this);
	mViewTimeline->SetMainFrame(this);

	// Tell the views about the picture
	mViewEdit->SetPicture(mPicture);
	mViewTimeline->SetPicture(mPicture);

}



void CMainFrame::OnEditTimelineproperties()
{
	CTimelineDlg dlg;
	dlg.SetTimeline(mPicture->GetTimeline());
	if (dlg.DoModal() == IDOK)
	{
		dlg.Take();
		mPicture->UpdateObservers();
	}
}
