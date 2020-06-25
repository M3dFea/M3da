#pragma once

#include "MyEdit.h"
#include "EditBasic.h"
// CInputPane

class CInputPane : public CDockablePane
{
	DECLARE_DYNAMIC(CInputPane)

public:
	CInputPane();
	virtual ~CInputPane();
  CMFCTabCtrl	m_wndTabs;
  CEditBasic Edit1;
  CEditBasic Edit2;
  CMyEdit Edit3;

protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
//  afx_msg void OnClose();
};


