#pragma once


// CWndSettings dialog

class CWndSettings : public CDialog {
    DECLARE_DYNAMIC(CWndSettings)
    
  public:
    CWndSettings(CWnd* pParent = NULL);   // standard constructor
    virtual ~CWndSettings();
    
    // Dialog Data
    enum { IDD = IDD_SETTINGS };
    
  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
    DECLARE_MESSAGE_MAP()
  public:
    BOOL v_labels;
    BOOL v_bool;
    BOOL v_sByte;
    BOOL v_uByte;
    BOOL v_sWord;
    BOOL v_uWord;
    BOOL v_uDWord;
    BOOL v_sQWord;
    BOOL v_uQWord;
    BOOL v_float;
    BOOL v_double;
    BOOL v_bits;
    BOOL v_sDWord;
    int v_selStart;
    int v_selBlock;
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
