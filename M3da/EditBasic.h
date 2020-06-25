#pragma once


// CEditBasic

class CEditBasic : public CEdit
{
	DECLARE_DYNAMIC(CEditBasic)

public:
	CEditBasic();
	virtual ~CEditBasic();

protected:
	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
};


