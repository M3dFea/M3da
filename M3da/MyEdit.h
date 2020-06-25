#pragma once


// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnEnChange();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnClose();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
};


