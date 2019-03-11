/**
 * \file CanadianExperience.h
 *
 * \author Aaron Eshleman
 *
 * Program application class
 */

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


/** Program application class */
class CCanadianExperienceApp : public CWinApp
{
public:
	CCanadianExperienceApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
    /// GDI startup input variable used later for shutdown
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;

    /// The GDIplus access token
    ULONG_PTR gdiplusToken;
};

extern CCanadianExperienceApp theApp;
