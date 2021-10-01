#pragma once
#include "afxwin.h"

class CWndInterpret : public CDialog {
    DECLARE_DYNAMIC(CWndInterpret)
    
  public:
    CWndInterpret( CWnd* pParent = NULL );   // standard constructor
    virtual ~CWndInterpret();
    
    // Dialog Data
    enum { IDD = IDD_DATAINTERPRET };
    
  protected:
    virtual void DoDataExchange( CDataExchange* pDX) ;    // DDX/DDV support
    
    DECLARE_MESSAGE_MAP()

public: 
    void RenameLabels( bool aCStyleLabels );

    CEdit m_editBool;
    CEdit m_editSByte;
    CEdit m_editUByte;
    CEdit m_editSWord;
    CEdit m_editUWord;
    CEdit m_editSDword;
    CEdit m_editUDword;
    CEdit m_editSQWord;
    CEdit m_editUQWord;
    CEdit m_editFloat;
    CEdit m_editDouble;
    CStatic m_labelSelection;
    CEdit m_editBinary;
    CString m_textBool;
    CString m_textSByte;
    CString m_textUByte;
    CString m_textSWord;
    CString m_textUWord;
    CString m_textSDWord;
    CString m_textUDWord;
    CString m_textSQWord;
    CString m_textUQWord;
    CString m_textFloat;
    CString m_textDouble;
    CStatic m_labelBool;
    CStatic m_labelSByte;
    CStatic m_labelUByte;
    CStatic m_labelSWord;
    CStatic m_labelUWord;
    CStatic m_labelSDWord;
    CStatic m_labelUDWord;
    CStatic m_labelSQWord;
    CStatic m_labelUQWord;
    CStatic m_labelFloat;
    CStatic m_labelDouble;
    CStatic m_labelBinary;

    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
    void ViewedTypes( BOOL aBool, BOOL aSByte, BOOL aUByte, BOOL aSWord, BOOL aUWord,
                      BOOL aSDWord, BOOL aUDWord, BOOL aSQWord, BOOL aUQWord,
                      BOOL aFloat, BOOL aDouble, BOOL aBits );
};
