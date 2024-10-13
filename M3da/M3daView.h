
// M3daView.h : interface of the CM3daView class
//


#pragma once


class CM3daView : public CView
{
protected: // create from serialization only
	CM3daView();
	DECLARE_DYNCREATE(CM3daView)

// Attributes
public:
	CM3daDoc* GetDocument() const;

// Operations
public:
	CClientDC* ClientDC;
	CPoint m_PointOld;		//old move point
	CPoint m_PointNew;		//new move point
    CPoint m_PointDown;
	int m_iMouseButStat;	//mouse button status   	
	int m_iWidth;			// client width
	int m_iHeight;			// client height
	CRect m_rcClient;		// client area in screen coords
	int m_iFuncKey;
    void ClearScr();
	BOOL bF;

	void m_UpdateTriad(int iMag);
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CM3daView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnMove(int x, int y);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnViewDisplayall();
  afx_msg void OnViewDisplayselected();
  afx_msg void OnViewDisplaygroup();
  afx_msg void OnViewLine();
  afx_msg void OnViewShaded();
  afx_msg void OnViewLocateeye();
  afx_msg void OnViewResetview();
//  afx_msg BOOL OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnViewZoomall();
  afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnViewTop();
  afx_msg void OnViewFront();
  afx_msg void OnViewLeftxy();
  afx_msg void OnViewBack();
  afx_msg void OnViewRight();
  afx_msg void OnViewBottomxz();
  afx_msg void OnProjwp();
  afx_msg void OnProjFront();
  afx_msg void OnProjBottomxz();
  afx_msg void OnProjTop();
  afx_msg void OnProjLeftxy();
  afx_msg void OnProjRight();
  afx_msg void OnProjBack();
  afx_msg void OnProjso1();
  afx_msg void OnPropiso2();
  afx_msg void OnEditUndo();
  afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
  afx_msg void OnEditRedo();
  afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in M3daView.cpp
inline CM3daDoc* CM3daView::GetDocument() const
   { return reinterpret_cast<CM3daDoc*>(m_pDocument); }
#endif

