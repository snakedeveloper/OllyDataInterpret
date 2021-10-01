#pragma once
#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "DataInterpret.h"
#include "WndSettings.h"
#include "WndBitmapMenu.h"

class CApplication : public CWinApp {
  public:
    CApplication();
    
    virtual BOOL InitInstance();
 
    void SetOllyVersion( int aVersion ) {
      m_ollyVersion = aVersion;
    }
    
    void SetOllyWindow( HWND aHandle ) {
      m_ollyMainHwnd = aHandle;
    }
    
    void ToggleInterpreter() {
      m_pWndInterpret->ShowWindow( ( m_pWndInterpret->IsWindowVisible() ? SW_HIDE : SW_SHOWNOACTIVATE ) );
    }

    void ShowSettings();
    void SaveSettings( BOOL aCLabels, BOOL aBool, BOOL aSByte, BOOL aUByte, BOOL aSWord, BOOL aUWord,
                       BOOL aSDWord, BOOL aUDWord, BOOL aSQWord, BOOL aUQWord,
                       BOOL aFloat, BOOL aDouble, BOOL aBits, BOOL aReadBlock );

    CString GetIniPath();

    void LoadSettings( CWndSettings* aSettingsWin );

    void ShowBitmapViewer();
    
    //////////////////////////////////////////////////////////////////////////
    
    void ShowMessage( CString& aMessage ) {
      MessageBox( m_ollyMainHwnd, aMessage, "Message", MB_OK );
    }
    
    void SetClipboardText( CString& aString );
    void InitWindows();
    void UpdateInterpreter( DWORD aSelStart, DWORD aSelEnd );
    void SaveWindowState();

  private:
    CWndInterpret* m_pWndInterpret;
    
    int m_ollyVersion;
    HWND m_ollyMainHwnd;
    bool m_readBlock;
};
