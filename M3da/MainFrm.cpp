
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "M3da.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
CEditBasic* Edit1;
CEditBasic* Edit2;
CMyEdit* Edit3;
CString     sText;
CString     sTextMSG;
CString     sTextMSG2;
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
  ON_WM_SIZE()
  //ON_UPDATE_COMMAND_UI(ID_INDC_LC, &CMainFrame::OnUpdatePage)
//  ON_COMMAND(ID_MESH_FREETRIMESH, &CMainFrame::OnMeshFreetrimesh)
//ON_COMMAND(ID_TOOLS_ELEMENTMASSSUMMATION, &CMainFrame::OnToolsElementmasssummation)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDC_LC,
    ID_INDC_BC,
	ID_INDICATOR_TS,
};
//ID_INDC_LC,
//ID_INDC_BC,
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

//ADDED BY ME
//void CMainFrame::OnUpdatePage(CCmdUI *pCmdUI)
//{
//    pCmdUI->Enable(); 
//    CString strPage;
//    strPage.Format(_T("LC: %d"), -1); 
//    //strPage.Format(_T("Page %d"), m_nPage); 
 //   pCmdUI->SetText(strPage); 
//    this->
//}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int iIDR;
	iIDR=IDR_DRAW;
	iIDR = IDR_CREATE;
	iIDR = IDR_EDIT;
	iIDR = IDR_FE;
	iIDR = IDR_GROUP;
	iIDR = IDR_BC;
	iIDR = IDR_ELTYPE;
	iIDR = IDR_POST;
	iIDR = IDR_PROJ;
	iIDR = IDR_UTILITIES;
	iIDR = IDR_QFILTER;
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

    // Roy note the new CreateEx calls are not the same as
	// the first
	// each new added tool bar requires a new ID
	// specified on the following line
	if (!m_Draw.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+1) ||
		  !m_Draw.LoadToolBar(IDR_DRAW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
   


	if (!m_Create.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+2) ||
		  !m_Create.LoadToolBar(IDR_CREATE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_Edit.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+3) ||
		  !m_Edit.LoadToolBar(IDR_EDIT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_FE.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+4) ||
		  !m_FE.LoadToolBar(IDR_FE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_Group.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+5) ||
		!m_Group.LoadToolBar(IDR_GROUP))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  if (!m_BC.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+6) ||
		  !m_BC.LoadToolBar(IDR_BC))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  if (!m_ELTYPE.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+7) ||
		  !m_ELTYPE.LoadToolBar(IDR_ELTYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  if (!m_POST.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+8) ||
		  !m_POST.LoadToolBar(IDR_POST))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  if (!m_Projection.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 9) ||
    !m_Projection.LoadToolBar(IDR_PROJ))
  {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }
  if (!m_Utils.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 10) ||
    !m_Utils.LoadToolBar(IDR_UTILITIES))
  {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }
	if (!m_QFilter.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1,1,1,1), AFX_IDW_MENUBAR+11) ||
		!m_QFilter.LoadToolBar(IDR_QFILTER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_DIMS.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_MENUBAR + 12) ||
		!m_DIMS.LoadToolBar(IDR_DIMS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


  
	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strToolBarName2;
	int iIDS;
	iIDS = IDS_DRAW;
	bNameValid = strToolBarName2.LoadString(IDS_DRAW);  //IDS_DRAW
	//ASSERT(bNameValid);
	m_Draw.SetWindowText("Draw");

	CString strToolBarName3;
	bNameValid = strToolBarName3.LoadString(IDS_CREATE2);
	//ASSERT(bNameValid);
    m_Create.SetWindowText("Create");

    CString  strToolBarName4;
	bNameValid = strToolBarName4.LoadString(IDS_EDIT);
	//ASSERT(bNameValid);
    m_Edit.SetWindowText("Edit");

	CString  strToolBarName5;
	bNameValid = strToolBarName5.LoadString(IDS_FE);
	//ASSERT(bNameValid);
    m_FE.SetWindowText("F.E.");

	CString  strToolBarName6;
	bNameValid = strToolBarName6.LoadString(IDS_GROUP);
	//ASSERT(bNameValid);
    m_Group.SetWindowText("Groups");

	CString  strToolBarName7;
    bNameValid = strToolBarName7.LoadString(IDS_BC);
	//ASSERT(bNameValid);
    m_BC.SetWindowText("Boundary Conditions");

	CString  strToolBarName8;
    bNameValid = strToolBarName8.LoadString(IDS_ELTYPE);
	//ASSERT(bNameValid);
    m_ELTYPE.SetWindowText("Element Types");

	CString  strToolBarName9;
    bNameValid = strToolBarName9.LoadString(IDS_POST);
	//ASSERT(bNameValid);
    m_POST.SetWindowText("Post Processing");

    m_Projection.SetWindowText("Project");
    m_Utils.SetWindowText("Utils");
    m_QFilter.SetWindowText("Quick Filter");
	m_DIMS.SetWindowText("Dimension");

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_Draw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	m_Create.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_Edit.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	m_FE.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	m_Group.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_BC.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_ELTYPE.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_POST.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_Projection.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_Utils.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_QFilter.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  m_DIMS.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
  //m_Qwanta.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
  CRect R;
  this->GetWindowRect(&R);
  R.top=500;
  //BOOL brc=m_Input.Create("Input",this,R,TRUE,IDD_INPUT,WS_CHILD | WS_VISIBLE ,AFX_CBRS_REGULAR_TABS,AFX_DEFAULT_DOCKING_PANE_STYLE,NULL);
   //BOOL brc=m_Input.Create("Input", this, R, FALSE, IDD_INPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT| CBRS_FLOAT_MULTI);
 	if (!m_Input.Create("Input", this, CRect(0, 0, 100, 100), FALSE, IDD_INPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create input window\n");
		return FALSE; // failed to create
	} 

	
 Edit1=&m_Input.Edit1;
 Edit2=&m_Input.Edit2;
 Edit3=&m_Input.Edit3;

 m_Input.EnableDocking(CBRS_ALIGN_ANY);
 DockPane(&m_Input);

 m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
 m_Draw.EnableDocking(CBRS_ALIGN_ANY);
 m_Create.EnableDocking(CBRS_ALIGN_ANY);
 m_Edit.EnableDocking(CBRS_ALIGN_ANY);
 m_FE.EnableDocking(CBRS_ALIGN_ANY);
 m_Group.EnableDocking(CBRS_ALIGN_ANY);
 m_BC.EnableDocking(CBRS_ALIGN_ANY);
 m_ELTYPE.EnableDocking(CBRS_ALIGN_ANY);
 m_POST.EnableDocking(CBRS_ALIGN_ANY);
 m_Projection.EnableDocking(CBRS_ALIGN_ANY);
 m_Utils.EnableDocking(CBRS_ALIGN_ANY);
 m_QFilter.EnableDocking(CBRS_ALIGN_ANY);
 m_DIMS.EnableDocking(CBRS_ALIGN_ANY);
 //m_Qwanta.EnableDocking(CBRS_ALIGN_ANY);
 EnableDocking(CBRS_ALIGN_ANY);
  //AA.EnableDocking(CBRS_BOTTOM);
 DockPane(&m_wndMenuBar);
 DockPane(&m_wndToolBar);
 DockPane(&m_Draw);
 DockPane(&m_Create);
 DockPane(&m_Edit);
 DockPane(&m_FE);
 DockPane(&m_Group);
 DockPane(&m_BC);
 DockPane(&m_ELTYPE);
 DockPane(&m_POST);
 DockPane(&m_Projection);
 DockPane(&m_Utils);
 DockPane(&m_QFilter);
 DockPane(&m_DIMS);
 //DockPane(&m_Qwanta);
	// enable Visual Studio 2005 style docking window behavior
//	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}


	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

  //
	//DockControlBar(&AA);

  //sizeCbar();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

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

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void SetFocus()
{
Edit3->SetFocus();
}

void outtext2(CString AAA)
{

CString strText, strNewText;
Edit1->GetWindowText(strText);
AAA.Remove(13);
strNewText.Format("%s\r\n",AAA);
strText += strNewText;
Edit1->SetWindowText(strText);
int NoOff = Edit1->GetLineCount();
Edit1->LineScroll(NoOff,0);

}

void outtext1(CString AAA)
{

CString strText, strNewText;
Edit2->GetWindowText(strText);
strNewText.Format("%s\r\n",AAA);
strText += strNewText;
Edit2->SetWindowText(strText);
int NoOff = Edit2->GetLineCount();
Edit2->LineScroll(NoOff,0);
}


void outtextMSG(CString AAA)
{
  CString a;
  CString b;
  Edit3->GetWindowText(b);
  int iRetPos = b.Find(13);
  while (iRetPos != -1)
  {
    a = b.Left(iRetPos);
    b = b.Right(b.GetLength()-iRetPos-2);
	//a.MakeUpper();
	if (a.Find("//")==-1)
	{
	 outtext2(a);
     SendMsg(a);
	}
    a ="";
    Edit3->SetWindowText(a);
    iRetPos = b.Find(13);
  }	
  b="";
  a="";
}

void outtextMSG2(CString AAA)
{
CString  strNewText;
strNewText.Format("%s\r",AAA);
outtext2(strNewText);
SendMsg(AAA);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
  CFrameWndEx::OnSize(nType, cx, cy);
  //sizeCbar();
  // TODO: Add your message handler code here
}


//void CMainFrame::OnMeshFreetrimesh()
//{
//	// TODO: Add your command handler code here
//}


//void CMainFrame::OnToolsElementmasssummation()
//{
//  // TODO: Add your command handler code here
//}
