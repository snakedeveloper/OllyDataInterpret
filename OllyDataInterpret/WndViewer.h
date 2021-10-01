#pragma once


// CWndViewer dialog

class CWndViewer : public CDialog
{
	DECLARE_DYNAMIC(CWndViewer)
  DWORD m_bitmapWidth;
  DWORD m_bitmapHeight;
  DWORD m_bitmapAddress;
  DWORD m_bitmapSize;
  DWORD m_pixelFormatId;
  Gdiplus::Bitmap* m_bitmap;
  BYTE* m_bitmapBuffer;
  HDC m_dcMemory;
  HBITMAP m_dcBitmap;
public:
	CWndViewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWndViewer();

// Dialog Data
	enum { IDD = IDD_VIEWER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnPaint();
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg void OnSize(UINT nType, int cx, int cy);
};
