#pragma once
#include "afxwin.h"
#include "WndViewer.h"

// CWndBitmapMenu dialog

class CWndBitmapMenu : public CDialog
{
	DECLARE_DYNAMIC(CWndBitmapMenu)

public:
	CWndBitmapMenu(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWndBitmapMenu();

// Dialog Data
	enum { IDD = IDD_BITMAPMENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  CEdit m_editWidth;
  CEdit m_editHeight;
  CComboBox m_comboPixel;
  DWORD m_addressStart;
  DWORD m_addressEnd;
  //  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg void OnBnClickedButton1();
  void SetAddresses( int aStart, int aEnd );
};
