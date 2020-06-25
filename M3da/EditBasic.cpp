// EditBasic.cpp : implementation file
//

#include "stdafx.h"
#include "M3da.h"
#include "EditBasic.h"


// CEditBasic

IMPLEMENT_DYNAMIC(CEditBasic, CEdit)

CEditBasic::CEditBasic()
{

}

CEditBasic::~CEditBasic()
{
}


BEGIN_MESSAGE_MAP(CEditBasic, CEdit)
END_MESSAGE_MAP()



// CEditBasic message handlers




BOOL CEditBasic::PreTranslateMessage(MSG* pMsg)
{
  // TODO: Add your specialized code here and/or call the base class

  if (pMsg->wParam == VK_ESCAPE)
  {
    return TRUE;
  }
  else
  {
    return CEdit::PreTranslateMessage(pMsg);
  }
}
