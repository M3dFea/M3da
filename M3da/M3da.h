
// M3da.h : main header file for the M3da application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CM3daApp:
// See M3da.cpp for the implementation of this class
//

class CM3daApp : public CWinAppEx
{
public:
	CM3daApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileRunscriptfile();
};
void outtext1(CString AAA);
void outtext2(CString AAA);
void SendMsg(CString AAA);
void SetFocus();
void outtextMSG(CString AAA);
void outtextMSG2(CString AAA);

extern CM3daApp theApp;
