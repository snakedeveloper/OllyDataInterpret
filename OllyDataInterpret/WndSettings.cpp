// WndSettings.cpp : implementation file
//

#include "stdafx.h"
#include "dllmain.h"
#include "WndSettings.h"


// CWndSettings dialog

IMPLEMENT_DYNAMIC(CWndSettings, CDialog)

CWndSettings::CWndSettings(CWnd* pParent): CDialog(CWndSettings::IDD, pParent) , v_labels(FALSE)
  , v_bool(FALSE)
  , v_sByte(FALSE)
  , v_uByte(FALSE)
  , v_sWord(FALSE)
  , v_uWord(FALSE)
  , v_uDWord(FALSE)
  , v_sQWord(FALSE)
  , v_uQWord(FALSE)
  , v_float(FALSE)
  , v_double(FALSE)
  , v_bits(FALSE)
  , v_sDWord(FALSE)
  , v_selStart(0)
  , v_selBlock(0)
{
  
}

CWndSettings::~CWndSettings() {
}

void CWndSettings::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Check(pDX, IDC_CHECK_LABELS, v_labels);
  DDX_Check(pDX, IDC_CHECK_BOOL, v_bool);
  DDX_Check(pDX, IDC_CHECK_SBYTE, v_sByte);
  DDX_Check(pDX, IDC_CHECK_UBYTE, v_uByte);
  DDX_Check(pDX, IDC_CHECK_SWORD, v_sWord);
  DDX_Check(pDX, IDC_CHECK_UWORD, v_uWord);
  DDX_Check(pDX, IDC_CHECK_UDWORD, v_uDWord);
  DDX_Check(pDX, IDC_CHECK_SQWORD, v_sQWord);
  DDX_Check(pDX, IDC_CHECK_UQWORD, v_uQWord);
  DDX_Check(pDX, IDC_CHECK_FLOAT, v_float);
  DDX_Check(pDX, IDC_CHECK_DOUBLE, v_double);
  DDX_Check(pDX, IDC_CHECK_BITS, v_bits);
  DDX_Check(pDX, IDC_CHECK_SDWORD, v_sDWord);
  DDX_Check(pDX, IDC_RADIO_SELECTBLOCK, v_selBlock);
  DDX_Check(pDX, IDC_RADIO_SELECTSTART, v_selStart);
}


BEGIN_MESSAGE_MAP(CWndSettings, CDialog)
  ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CWndSettings message handlers

void CWndSettings::OnShowWindow(BOOL bShow, UINT nStatus) {
  CDialog::OnShowWindow(bShow, nStatus);

  //::CheckRadioButton( GetSafeHwnd(), IDC_)
}
