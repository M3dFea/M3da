
// M3daView.cpp : implementation of the CM3daView class
//

#include "stdafx.h"
#include "M3da.h"
#include "M3daDoc.h"
#include "M3daView.h"
#include "resource.h"
#include "math.h"
#include "GLOBAL_VARS.h"
DSP_Triad tOrient;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM3daView

IMPLEMENT_DYNCREATE(CM3daView, CView)

BEGIN_MESSAGE_MAP(CM3daView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CM3daView::OnFilePrintPreview)
  ON_WM_KEYDOWN()
  ON_WM_KEYUP()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_LBUTTONDBLCLK()
  ON_WM_MOUSEMOVE()
  ON_WM_SIZE()
  ON_WM_MOVE()
  ON_WM_RBUTTONDOWN()
  ON_WM_RBUTTONUP()
  ON_COMMAND(ID_VIEW_DISPLAYALL, &CM3daView::OnViewDisplayall)
  ON_COMMAND(ID_VIEW_DISPLAYSELECTED, &CM3daView::OnViewDisplayselected)
  ON_COMMAND(ID_VIEW_DISPLAYGROUP, &CM3daView::OnViewDisplaygroup)
  ON_COMMAND(ID_VIEW_LINE, &CM3daView::OnViewLine)
  ON_COMMAND(ID_VIEW_SHADED, &CM3daView::OnViewShaded)
  ON_COMMAND(ID_VIEW_LOCATEEYE, &CM3daView::OnViewLocateeye)
  ON_COMMAND(ID_VIEW_RESETVIEW, &CM3daView::OnViewResetview)
//  ON_WM_MOUSEHWHEEL()
ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONUP()
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_VIEW_ZOOMALL, &CM3daView::OnViewZoomall)
ON_WM_MBUTTONDOWN()
ON_COMMAND(ID_VIEW_TOP, &CM3daView::OnViewTop)
ON_COMMAND(ID_VIEW_FRONT, &CM3daView::OnViewFront)
ON_COMMAND(ID_VIEW_LEFTXY, &CM3daView::OnViewLeftxy)
ON_COMMAND(ID_VIEW_BACK, &CM3daView::OnViewBack)
ON_COMMAND(ID_VIEW_RIGHT, &CM3daView::OnViewRight)
ON_COMMAND(ID_VIEW_BOTTOMXZ, &CM3daView::OnViewBottomxz)
ON_COMMAND(ID_PROJWP, &CM3daView::OnProjwp)
ON_COMMAND(ID_PROJ_FRONT, &CM3daView::OnProjFront)
ON_COMMAND(ID_PROJ_BOTTOMXZ, &CM3daView::OnProjBottomxz)
ON_COMMAND(ID_PROJ_TOP, &CM3daView::OnProjTop)
ON_COMMAND(ID_PROJ_LEFTXY, &CM3daView::OnProjLeftxy)
ON_COMMAND(ID_PROJ_RIGHT, &CM3daView::OnProjRight)
ON_COMMAND(ID_PROJ_BACK, &CM3daView::OnProjBack)
ON_COMMAND(ID_PROJSO1, &CM3daView::OnProjso1)
ON_COMMAND(ID_PROPISO2, &CM3daView::OnPropiso2)
ON_COMMAND(ID_EDIT_UNDO, &CM3daView::OnEditUndo)
ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CM3daView::OnUpdateEditUndo)
ON_COMMAND(ID_EDIT_REDO, &CM3daView::OnEditRedo)
ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CM3daView::OnUpdateEditRedo)
END_MESSAGE_MAP()

// CM3daView construction/destruction

CM3daView::CM3daView()
{
	// TODO: add construction code here
  m_iFuncKey=0;
  bF=TRUE;
  tOrient.Create(1);
}

CM3daView::~CM3daView()
{
}

BOOL CM3daView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CM3daView drawing

void CM3daView::OnDraw(CDC* pDC)
{
int x;
int y;

x=pDC->GetDeviceCaps(VERTRES);
y=pDC->GetDeviceCaps(HORZRES);
m_rcClient = CRect(0, 0, y, x);
GetDocument()->SetScreenMat(m_rcClient);
CM3daDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
pDoc->SetView(this);
if (bF==TRUE)
{
	CDC* pDC2 = this->GetDC();
  pDoc->InitOGL(pDC2);
  bF=FALSE;
}
pDoc->Draw(tOrient.RetrieveMat(),pDC,4);
}


// CM3daView printing


void CM3daView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CM3daView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CM3daView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CM3daView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CM3daView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CM3daView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CM3daView diagnostics

#ifdef _DEBUG
void CM3daView::AssertValid() const
{
	CView::AssertValid();
}

void CM3daView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CM3daDoc* CM3daView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CM3daDoc)));
	return (CM3daDoc*)m_pDocument;
}
#endif //_DEBUG

void CM3daView::m_UpdateTriad(int iMag)
{
double d1;
double d2;
double dWidth = m_rcClient.right-m_rcClient.left;
double dHeight = m_rcClient.bottom-m_rcClient.top;
CPoint point;
double dX1;
double dY1; 
double dZ1;
double dSR;
d1 = m_PointNew.x - m_PointOld.x;
d2 = m_PointNew.y - m_PointOld.y;
double WPSize;
WPSize=GetDocument()->GetWPSize();
if (m_iFuncKey == 1)     // calculate translation
  {	 
  //Calculate a meaningful translation

  dX1 = 2*(d1 / dWidth) * WPSize;
  dY1 = -2*(d2 / dWidth) * WPSize;
  dZ1 = 0;
  tOrient.Trans(dX1,dY1,dZ1);	
  }
else if (m_iFuncKey == 2)   //scale
  {
  double dS = tOrient.GetScl(); // new
  dSR=0.1;
  if (iMag<2)
  {
    dSR = 0.02;
  }
	if (d2 < 0) 
  {
     tOrient.Scl(-dS*dSR);
	}
	else 
  {
	  tOrient.Scl(dS*dSR);
	}
  }
else if (m_iFuncKey == 3)   //scale
  {
  dSR=1;
  if (iMag<2)
  {
    dSR = 0.5;
  }
  d1=180*d1/dHeight*dSR;
  d2=180*d2/dHeight*dSR;
   if (m_PointOld.x > (dWidth*0.8)) 
   {
	   tOrient.Rot(0.0f,0.0f, (float) -d2);
   }
   else
   {
	   tOrient.Rot((float) d2,(float) d1,0.0f);
   }
  }
 
}

void CM3daView::ClearScr()

{
CRect rc;
CDC* pDC = this->GetDC();
GetClientRect(&rc);
CBrush br(RGB(0, 0, 0));
pDC->FillRect(&rc, &br);
ReleaseDC(pDC);

}
// CM3daView message handlers

void CM3daView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  // TODO: Add your message handler code here and/or call default

	if ((nChar == 112) || (nChar == 17))
	{m_iFuncKey = 1;}
	else if (nChar == 113) 
	{m_iFuncKey = 2;}
	else if ((nChar == 114) || (nChar == 16))
	{m_iFuncKey = 3;}
	else if (nChar == 13)
	{m_iFuncKey = 4;}
	else if (nChar == 27)
	{m_iFuncKey = 5;}
	else if (nChar == 46)
	{m_iFuncKey = 6;}
	else
	{m_iFuncKey = 0;}
	m_iMouseButStat=0;
  CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CM3daView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  // TODO: Add your message handler code here and/or call default
if ((m_iFuncKey==1) || (m_iFuncKey==2) || (m_iFuncKey==3))
{
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  CRect C;
  GetDocument()->SetScreenMat(C);
  GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
  ReleaseDC(pDC);
}
else if (m_iFuncKey==4)
{
  outtextMSG2("D");
}
else if (m_iFuncKey==5)
{
  outtextMSG2("C");
}
else if (m_iFuncKey == 6)
{
	GetDocument()->DeleteObjs();
}
else
{

}
m_iFuncKey = 0;
CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CM3daView::OnLButtonDown(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
m_iMouseButStat = 1;
//GetDocument()->SetLineStart(point);
m_PointDown=point;

CView::OnLButtonDown(nFlags, point);
}

void CM3daView::OnLButtonUp(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
    CRect C;
    if (m_iMouseButStat==1)
	{
	  CView::OnLButtonUp(nFlags, point);
	  int iMag;
    int iX,iY;
    iX=point.x - m_PointDown.x;
    iY=point.y - m_PointDown.y;
    double a,b;
    b=iX*iX + iY*iY;
      a =  sqrt(b);
      iMag=(int) a;
      if (iMag>20)
      {
        GetDocument()->SelectBox(m_PointDown,point);
	    CDC* pDC = this->GetDC();
        GetDocument()->SetView(this);
        GetDocument()->SetScreenMat(C);
        GetDocument()->Draw(tOrient.RetrieveMat(),pDC,5);
        ReleaseDC(pDC);

      }
	  else
	  {
        CDC* pDC = this->GetDC();
		//if (GetDocument()->isBlackDisp())
        //  GetDocument()->SetPen(pDC,255,255,255);
		//else
        //  GetDocument()->SetPen(pDC,0,0,0);
        //Draw tick marker
		 CPen* Pen = new CPen(PS_SOLID,1,RGB(255,0,0));
         CPen* OldPen = pDC->SelectObject(Pen);

		pDC->MoveTo(point.x-5,point.y);
        pDC->LineTo(point.x+5,point.y);
        pDC->MoveTo(point.x,point.y-5);
        pDC->LineTo(point.x,point.y+5);
		//GetDocument()->RestorePen(pDC);
        pDC->SelectObject(OldPen);
		delete(Pen);
        ReleaseDC(pDC);
        GetDocument()->DoMsg(1,point, point,"MouseInp");

	  }
	}
	m_iMouseButStat = 0;        
  GetDocument()->SetView(this);
  CView::OnLButtonUp(nFlags, point);
}

void CM3daView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
	GetDocument()->UpTree();
  CView::OnLButtonDblClk(nFlags, point);
}

void CM3daView::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
int iMag = 0;
int iX,iY;
double a,b;
CRect rc;
m_PointNew = point;
if ((m_iFuncKey != 0))
{
  iX=m_PointNew.x - m_PointOld.x;
  iY=m_PointNew.y - m_PointOld.y;
  b=iX*iX+iY*iY;
  a = sqrt(b);
  iMag = (int) a;
  m_UpdateTriad(iMag);
  m_PointOld = m_PointNew;
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(),pDC,3);
  ReleaseDC(pDC);
}
else if (m_iMouseButStat == 1)
{
  iX=m_PointNew.x - m_PointDown.x;
  iY=m_PointNew.y - m_PointDown.y;
  b=iX*iX+iY*iY;
  a = sqrt(b);
  iMag = (int) a;
  //iMag = (int) sqrt(pow(m_PointNew.x - m_PointDown.x,2) + pow(m_PointNew.y - m_PointDown.y,2));
  if (iMag>20)
  {
    CDC* pDC = this->GetDC();
    GetDocument()->SetView(this);
    GetDocument()->Draw(tOrient.RetrieveMat(),pDC,3);
    GetDocument()->DrawDrag(pDC,m_PointDown,point);
    ReleaseDC(pDC);
  }
}
else if(GetDocument()->isDragging())
{
	iX = m_PointNew.x - m_PointDown.x;
	iY = m_PointNew.y - m_PointDown.y;
	b = iX * iX + iY * iY;
	a = sqrt(b);
	iMag = (int)a;
	//iMag = (int) sqrt(pow(m_PointNew.x - m_PointDown.x,2) + pow(m_PointNew.y - m_PointDown.y,2));
	if (iMag > 20)
	{
		CDC* pDC = this->GetDC();
		GetDocument()->SetView(this);
		GetDocument()->DragUpdate(m_PointNew);
		GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 3);
		//GetDocument()->SetLineEnd(m_PointNew);
		//GetDocument()->LineDrag(pDC, m_PointDown, m_PointNew);
		ReleaseDC(pDC);
	}
}


  m_PointOld = point;
  CView::OnMouseMove(nFlags, point);
}

void CM3daView::OnSize(UINT nType, int cx, int cy)
{
  CView::OnSize(nType, cx, cy);
  CRect C;
  GetDocument()->SetView(this);
  GetDocument()->SetScreenMat(C);
  // TODO: Add your message handler code here
}

void CM3daView::OnMove(int x, int y)
{
  CView::OnMove(x, y);
  CRect C;
  //GetDocument()->SetView(this);
  //GetDocument()->SetScreenMat(C);
  // TODO: Add your message handler code here
}

void CM3daView::OnRButtonDown(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
  CView::OnRButtonDown(nFlags, point);
}

void CM3daView::OnViewDisplayall()
{
  // TODO: Add your command handler code here
  //GetDocument()->DspAll();
  if (GetDocument()->isMenuNULL())
    outtextMSG2("DSPALL");
  //CDC* pDC = this->GetDC();
  //GetDocument()->SetView(this);
  //GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
  //ReleaseDC(pDC);	
}

void CM3daView::OnViewDisplayselected()
{
  // TODO: Add your command handler code here
if (GetDocument()->isMenuNULL())
  outtextMSG2("DSPSEL");
  //GetDocument()->DspSel();
  //CDC* pDC = this->GetDC();
  //GetDocument()->SetView(this);
  //GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
  //ReleaseDC(pDC);	
}

void CM3daView::OnViewDisplaygroup()
{
  // TODO: Add your command handler code here
  //GetDocument()->Dsp_Group(); 
//if (GetDocument()->isMenuNULL())
  outtextMSG2("DSPGP");	
}


void CM3daView::OnViewLine()
{
  // TODO: Add your command handler code here
outtext1("Draw Wire Frame.");
//ClearScr();
CDC* pDC = this->GetDC();
GetDocument()->SetView(this);
GetDocument()->SetDrawType(0);
GetDocument()->InvalidateOGL();
GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
ReleaseDC(pDC);	
}



void CM3daView::OnViewShaded()
{
  // TODO: Add your command handler code here
outtext1("Draw Shaded.");
CDC* pDC = this->GetDC();
GetDocument()->SetView(this);
GetDocument()->SetDrawType(1);
GetDocument()->InvalidateOGL();	
GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);	
ReleaseDC(pDC);
}

void CM3daView::OnViewLocateeye()
{
  // TODO: Add your command handler code here
C3dVector vP;
vP=GetDocument()->GetViewPt();
tOrient.SetEye(vP.x,vP.y,vP.z);
CDC* pDC = this->GetDC();
GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
ReleaseDC(pDC);	
}

void CM3daView::OnViewResetview()
{
  // TODO: Add your command handler code here
tOrient.ReSet();
CDC* pDC = this->GetDC();
GetDocument()->SetView(this);
GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
ReleaseDC(pDC);
}

//BOOL CM3daView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//  // This feature requires Windows Vista or greater.
//  // The symbol _WIN32_WINNT must be >= 0x0600.
//  // TODO: Add your message handler code here and/or call default
//  double dSR;
//  double dS = tOrient.GetScl(); // new
//  dSR=0.1;
//	if (zDelta < 0) 
//  {
//     tOrient.Scl(-dS*dSR);
//	}
//	else 
//  {
//	  tOrient.Scl(dS*dSR);
//	}
//  return CView::OnMouseHWheel(nFlags, zDelta, pt);
//}

void CM3daView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  outtextMSG2("C");	
  CView::OnMButtonDblClk(nFlags, point);
}

void CM3daView::OnMButtonUp(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default

  m_iFuncKey = 0;
  CView::OnMButtonUp(nFlags, point);
  outtextMSG2("D");
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
  ReleaseDC(pDC);

}

BOOL CM3daView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  // TODO: Add your message handler code here and/or call default

  double dS = tOrient.GetScl(); // new
  double dSR;
  dSR=0.1;
	if (zDelta < 0) 
  {
     tOrient.Scl(-dS*dSR);
	}
	else 
  {
	  tOrient.Scl(dS*dSR);
	}
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(),pDC,4);
  ReleaseDC(pDC);
  return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CM3daView::OnViewZoomall()
{
	// TODO: Add your command handler code here
C3dVector vP;
int iYExt;
int i;

vP=GetDocument()->GetMeshCentre();
tOrient.SetEye(vP.x,vP.y,vP.z);
CDC* pDC = this->GetDC();
//Centre the mesh and redraw
//GetDocument()->Draw(tOrient.RetrieveMat(),pDC,5);
GetDocument()->SetToScr2(tOrient.RetrieveMat());
//Get the span of the model in pixels

iYExt=GetDocument()->GetMeshYExt();
if (iYExt>0)
{
  tOrient.dSclFact=1;
  GetDocument()->SetToScr2(tOrient.RetrieveMat());
  //GetDocument()->Draw(tOrient.RetrieveMat(),pDC,5);
  double dS;
  iYExt=GetDocument()->GetMeshYExt();
  dS=GetDocument()->GetHeight()/iYExt;
  for(i=10;i>0;i--)
  {
  tOrient.dSclFact=dS/i;
  GetDocument()->Draw(tOrient.RetrieveMat(),pDC,5);
  }
  GetDocument()->SetToScr2(tOrient.RetrieveMat());
}
ReleaseDC(pDC);	
}

void CM3daView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMButtonDown(nFlags, point);
	m_iFuncKey = 1;
}


void CM3daView::OnViewTop()
{

}


void CM3daView::OnViewFront()
{
  // TODO: Add your command handler code here

}


void CM3daView::OnViewLeftxy()
{
  // TODO: Add your command handler code here

}


void CM3daView::OnViewBack()
{
  // TODO: Add your command handler code here


}


void CM3daView::OnViewRight()
{
  // TODO: Add your command handler code here

}


void CM3daView::OnViewBottomxz()
{
  // TODO: Add your command handler code here

}


void CM3daView::OnProjwp()
{
  // TODO: Add your command handler code here
  C3dMatrix mat;
  mat = GetDocument()->GetWPmat();
  tOrient.SetVIEW(mat);
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjFront()
{
  // TODO: Add your command handler code here
  tOrient.SetFrontView();
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjBottomxz()
{
  // TODO: Add your command handler code here
  tOrient.SetBottomView();
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjTop()
{
  // TODO: Add your command handler code here
  tOrient.SetTopView();
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjLeftxy()
{
  // TODO: Add your command handler code here
  tOrient.SetLeftView();
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjRight()
{
  // TODO: Add your command handler code here
  tOrient.SetRightView();
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjBack()
{
  // TODO: Add your command handler code here
  tOrient.SetBackView();
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnProjso1()
{
  // TODO: Add your command handler code here
  C3dMatrix mat;
  mat.MakeUnit();
  
  mat.Rotate(0, 45.0, 0);
  mat.Rotate(-35.564, 0.0, 0);
  tOrient.SetVIEW(mat);
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnPropiso2()
{
  // TODO: Add your command handler code here
  C3dMatrix mat;
  mat.MakeUnit();

  mat.Rotate(0, -45.0, 0);
  mat.Rotate(-35.564, 0.0, 0);
  tOrient.SetVIEW(mat);
  CDC* pDC = this->GetDC();
  GetDocument()->SetView(this);
  GetDocument()->Draw(tOrient.RetrieveMat(), pDC, 4);
  ReleaseDC(pDC);
}


void CM3daView::OnEditUndo()
{
	// TODO: Add your command handler code here
	CM3daDoc* pDoc=NULL;
	pDoc = GetDocument();
	if (pDoc != NULL)
	{
		if (pDoc->bFinalChkPt == FALSE)
		{
			pDoc->CheckPoint();
			pDoc->bFinalChkPt = TRUE;
		}
		pDoc->Undo();
		CDC* pDC = this->GetDC();
		pDoc->Draw(tOrient.RetrieveMat(), pDC, 4);
		ReleaseDC(pDC);
	}
	//pDoc->UpdateAllViews(NULL);
}


void CM3daView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CM3daDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanUndo());
}


void CM3daView::OnEditRedo()
{
	// TODO: Add your command handler code here
	CM3daDoc* pDoc = GetDocument();
	pDoc->Redo();
	pDoc->UpdateAllViews(NULL);
}


void CM3daView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CM3daDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->CanRedo());
}
