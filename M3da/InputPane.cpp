// InputPane.cpp : implementation file
//

#include "stdafx.h"
#include "M3da.h"
#include "InputPane.h"


// CInputPane

IMPLEMENT_DYNAMIC(CInputPane, CDockablePane)

CInputPane::CInputPane()
{

}

CInputPane::~CInputPane()
{
}


BEGIN_MESSAGE_MAP(CInputPane, CDockablePane)
  ON_WM_CREATE()
  ON_WM_SIZE()
//  ON_WM_CLOSE()
END_MESSAGE_MAP()



// CInputPane message handlers



int CInputPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CDockablePane::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  Add your specialized creation code here
	//m_Font.CreateStockObject(DEFAULT_GUI_FONT);
	CRect rectDummy(10,10,50,500);
	rectDummy.SetRectEmpty();
  
	// Create tabs window:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}
  CRect AAA(10,10,500,150);
  Edit1.Create(ES_AUTOVSCROLL |WS_VSCROLL|WS_BORDER|WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN ,AAA,&m_wndTabs,IDS_EDIT1);
  Edit2.Create(ES_AUTOVSCROLL |WS_VSCROLL|WS_BORDER|WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN ,AAA,&m_wndTabs,IDS_EDIT2);
  Edit3.Create(ES_AUTOVSCROLL | WS_BORDER|WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_WANTRETURN ,AAA,&m_wndTabs,IDS_EDIT3);
  return 0;
}



void CInputPane::OnSize(UINT nType, int cx, int cy)
{
  CDockablePane::OnSize(nType, cx, cy);
  m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
  // TODO: Add your message handler code here

CRect CbarSz;
this->GetWindowRect(&CbarSz);

// avoids overlapping with the arrow controls on the bottom left
CbarSz.DeflateRect(0, 10);

int h = CbarSz.Height();
int w = CbarSz.Width();
int TxtH = 25;
Edit1.MoveWindow(5,5,w/2-5,h-TxtH-10,  TRUE );
Edit2.MoveWindow(w/2+5,5,w/2-10,h-10,  TRUE );
Edit3.MoveWindow(5,h-TxtH-5,w/2-5,TxtH,  TRUE );

}


//void CInputPane::OnClose()
//{
//  // TODO: Add your message handler code here and/or call default
//
//  //CDockablePane::OnClose();
//}
