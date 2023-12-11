
// MainFrm.h : interface of the CMainFrame class
//
#include "InputPane.h"
#pragma once

class CMainFrame : public CFrameWndEx
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
  void sizeCbar();
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
  CInputPane        m_Input;
  CMFCToolBar       m_Draw;
  CMFCToolBar       m_Create;
	CMFCToolBar       m_Edit;
	CMFCToolBar       m_FE;
	CMFCToolBar       m_Group;
  CMFCToolBar       m_Qwanta;
  CMFCToolBar       m_BC;
  CMFCToolBar       m_ELTYPE;
  CMFCToolBar       m_POST;
  CMFCToolBar       m_Projection;
  CMFCToolBar       m_Utils;
  CMFCToolBar       m_QFilter;
  CMFCToolBar       m_DIMS;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
  //afx_msg void OnUpdatePage(CCmdUI *pCmdUI);  //ADDED BY ME 
	DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnSize(UINT nType, int cx, int cy);
//  afx_msg void OnMeshFreetrimesh();
//  afx_msg void OnToolsElementmasssummation();
};


