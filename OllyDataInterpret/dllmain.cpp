// OllyDataInterpret.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "dllmain.h"

#define EXPORTED extern "C" __declspec( dllexport )

using namespace Gdiplus;

CApplication application;
HWND g_ollyWindow;
WNDPROC g_pOllyProc;
bool g_hookInstall = true;
int g_selectionStart = 0, g_selectionEnd = 0;

ULONG_PTR g_gdipToken;

void OllySelectEventHandler();

/************************************************************************/
/* Utils                                                                */
/************************************************************************/

void BinaryString( char buffer[9], char aByte ) {
  buffer[8] = ' ';

  for ( int i = 0; i < 8; i++ )
    buffer[i] = ( ((aByte >> (7 - i)) & 1) + '0' );

}

void BinaryStringEx( CString& aOutput, const char* aBuffer, DWORD aBufferSize ) {
  char* temp = new char[aBufferSize * 9 + 1];

  for ( DWORD i = 0; i < aBufferSize; i++ ) {
    BinaryString( &temp[i * 9], aBuffer[i] );
  }

  temp[aBufferSize * 9] = 0;
  aOutput = temp;
  delete [] temp;
}

const char* BoolAsString( BOOL aBool ) {
  return ( aBool ? "1" : "0" );
}

/************************************************************************/
/* CApplication                                                         */
/************************************************************************/

CApplication::CApplication() {
}

BOOL CApplication::InitInstance() {
  CWinApp::InitInstance();
  m_pWndInterpret = new CWndInterpret;
  
  return TRUE;
}

void CApplication::SetClipboardText( CString& aString ) {
  if ( OpenClipboard( m_ollyMainHwnd ) ) {
    int length = aString.GetLength();
    HANDLE hMemory = GlobalAlloc( 0, length + 1 );
    
    memcpy( hMemory, aString.GetBuffer(), length );
    
    EmptyClipboard();
    SetClipboardData( CF_TEXT, hMemory );
    CloseClipboard();
    
    GlobalFree( hMemory );
  }
}

void CApplication::InitWindows() {
  CRect ollyPos, diPos;
  GetWindowRect( m_ollyMainHwnd, &ollyPos );
  m_pWndInterpret->GetWindowRect( &diPos );
  m_pWndInterpret->SetWindowPos( NULL,
                                 ollyPos.left + ollyPos.Width() - diPos.Width() - 20,
                                 ollyPos.top +  ollyPos.Height() - diPos.Height() - 20,
                                 0, 0, SWP_NOSIZE | SWP_NOZORDER );
}

void CApplication::UpdateInterpreter( DWORD aSelStart, DWORD aSelEnd ) {
  if ( !m_pWndInterpret->IsWindowVisible() )
    return;
    
  DWORD size = aSelEnd - aSelStart;
  CString temp;
  char buffer[8];
  Readmemory( buffer, aSelStart, 8, MM_SILENT );
  
  temp.Format( "Selection: %.8X - %.8X (%u/0x%X bytes)",
               aSelStart, aSelEnd, size, size );
               
  m_pWndInterpret->m_labelSelection.SetWindowText( temp );
  
  BinaryStringEx( temp, buffer, min( size, 8 ) );
  m_pWndInterpret->m_editBinary.SetWindowText( temp );

  if ( !m_readBlock )
    size = 8;
  
  if ( size >= 8 ) {
    temp.Format( "%I64d", *(__int64*) buffer );
    m_pWndInterpret->m_editSQWord.SetWindowText( temp );
    temp.Format( "%I64u", *(unsigned __int64*) buffer );
    m_pWndInterpret->m_editUQWord.SetWindowText( temp );
    
    try {
      temp.Format( "%.16g", *(double*) buffer );
    } catch (...) {
      m_pWndInterpret->m_editFloat.SetWindowText( "Error..." );
    }
    
    m_pWndInterpret->m_editDouble.SetWindowText( temp );
  } else {
    m_pWndInterpret->m_editSQWord.SetWindowText( "" );
    m_pWndInterpret->m_editUQWord.SetWindowText( "" );
    m_pWndInterpret->m_editDouble.SetWindowText( "" );
  }
  
  if ( size >= 4 ) {
    temp.Format( "%d", *(long*) buffer );
    m_pWndInterpret->m_editSDword.SetWindowText( temp );
    temp.Format( "%u", *(DWORD*) buffer );
    m_pWndInterpret->m_editUDword.SetWindowText( temp );
    
    try {
      temp.Format( "%.16g", *(float*) buffer );
    } catch (...) {
      m_pWndInterpret->m_editFloat.SetWindowText( "Error..." );
    }
    
    m_pWndInterpret->m_editFloat.SetWindowText( temp );
  } else {
    m_pWndInterpret->m_editSDword.SetWindowText( "" );
    m_pWndInterpret->m_editUDword.SetWindowText( "" );
    m_pWndInterpret->m_editFloat.SetWindowText( "" );
  }
  
  if ( size >= 2 ) {
    temp.Format( "%d", (int) *(short*) buffer );
    m_pWndInterpret->m_editSWord.SetWindowText( temp );
    temp.Format( "%u", *(WORD*) buffer );
    m_pWndInterpret->m_editUWord.SetWindowText( temp );
  } else {
    m_pWndInterpret->m_editSWord.SetWindowText( "" );
    m_pWndInterpret->m_editUWord.SetWindowText( "" );
  }
  
  if ( size >= 1 ) {
    temp.Format( "%d", *(signed char*) buffer );
    m_pWndInterpret->m_editSByte.SetWindowText( temp );
    temp.Format( "%u", *(BYTE*) buffer );
    m_pWndInterpret->m_editUByte.SetWindowText( temp );
    temp.Format( "%s", ( *(BYTE*) buffer? "true" : "false" ) );
    m_pWndInterpret->m_editBool.SetWindowText( temp );
  } else {
    m_pWndInterpret->m_editSByte.SetWindowText( "" );
    m_pWndInterpret->m_editUByte.SetWindowText( "" );
    m_pWndInterpret->m_editBool.SetWindowText( "" );
  }

}

void CApplication::ShowSettings() {
  m_pWndInterpret->EnableWindow( FALSE );
  
  CWndSettings settings;
  LoadSettings( &settings );

  if ( settings.DoModal() == IDOK ) {
    m_pWndInterpret->RenameLabels( settings.v_labels != 0 );
    m_pWndInterpret->ViewedTypes( settings.v_bool, settings.v_sByte, settings.v_uByte,
                                  settings.v_sWord, settings.v_uWord, settings.v_sDWord,
                                  settings.v_uDWord, settings.v_sQWord, settings.v_uQWord,
                                  settings.v_float, settings.v_double, settings.v_bits );

    m_readBlock = ( settings.v_selBlock != 0 );

    SaveSettings( settings.v_labels, settings.v_bool, settings.v_sByte, settings.v_uByte,
                  settings.v_sWord, settings.v_uWord, settings.v_sDWord,
                  settings.v_uDWord, settings.v_sQWord, settings.v_uQWord,
                  settings.v_float, settings.v_double, settings.v_bits, settings.v_selBlock == BST_CHECKED );
  }
  
  m_pWndInterpret->EnableWindow();
}

void CApplication::SaveSettings( BOOL aCLabels, BOOL aBool, BOOL aSByte, BOOL aUByte, BOOL aSWord, BOOL aUWord,
                                 BOOL aSDWord, BOOL aUDWord, BOOL aSQWord, BOOL aUQWord,
                                 BOOL aFloat, BOOL aDouble, BOOL aBits, BOOL aReadBlock ) {
  static const char* const section = "OllyDataInterpret";

  CString file = GetIniPath();

  WritePrivateProfileString( section, "C type names", BoolAsString( aCLabels ), file );
  WritePrivateProfileString( section, "Bool", BoolAsString( aBool ), file );
  WritePrivateProfileString( section, "Signed byte", BoolAsString( aSByte ), file );
  WritePrivateProfileString( section, "Unsigned byte", BoolAsString( aUByte ), file );
  WritePrivateProfileString( section, "Signed word", BoolAsString( aSWord ), file );
  WritePrivateProfileString( section, "Unsigned word", BoolAsString( aUWord ), file );
  WritePrivateProfileString( section, "Signed DWORD", BoolAsString( aSDWord ), file );
  WritePrivateProfileString( section, "Unsigned DWORD", BoolAsString( aUDWord ), file );
  WritePrivateProfileString( section, "Signed QWORD", BoolAsString( aSQWord ), file );
  WritePrivateProfileString( section, "Unsigned QWORD", BoolAsString( aUQWord ), file );
  WritePrivateProfileString( section, "Float", BoolAsString( aFloat ), file );
  WritePrivateProfileString( section, "Double", BoolAsString( aDouble ), file );
  WritePrivateProfileString( section, "Bits", BoolAsString( aBits ), file );
  WritePrivateProfileString( section, "Read mode", BoolAsString( aReadBlock ), file );
}

void CApplication::LoadSettings( CWndSettings* aSettingsWin = NULL ) {
  CString file = GetIniPath();
  static const char* const section = "OllyDataInterpret";

  BOOL v_bool, v_sByte, v_uByte, v_sWord, v_uWord, v_sDWord,
    v_uDWord, v_sQWord, v_uQWord, v_float, v_double, v_bits, v_labels;

  char temp[2];

  GetPrivateProfileString( section, "C type names", "0", temp, 2, file );
  v_labels = ( *temp != '0' );

  GetPrivateProfileString( section, "Bool", "0", temp, 2, file );
  v_bool = ( *temp != '0' );

  GetPrivateProfileString( section, "Signed byte", "1", temp, 2, file );
  v_sByte = ( *temp != '0' );

  GetPrivateProfileString( section, "Unsigned byte", "1", temp, 2, file );
  v_uByte = ( *temp != '0' );

  GetPrivateProfileString( section, "Signed word", "1", temp, 2, file );
  v_sWord = ( *temp != '0' );

  GetPrivateProfileString( section, "Unsigned word", "1", temp, 2, file );
  v_uWord = ( *temp != '0' );

  GetPrivateProfileString( section, "Signed DWORD", "1", temp, 2, file );
  v_sDWord = ( *temp != '0' );

  GetPrivateProfileString( section, "Unsigned DWORD", "1", temp, 2, file );
  v_uDWord = ( *temp != '0' );

  GetPrivateProfileString( section, "Signed QWORD", "1", temp, 2, file );
  v_sQWord = ( *temp != '0' );

  GetPrivateProfileString( section, "Unsigned QWORD", "1", temp, 2, file );
  v_uQWord = ( *temp != '0' );

  GetPrivateProfileString( section, "Float", "1", temp, 2, file );
  v_float = ( *temp != '0' );

  GetPrivateProfileString( section, "Double", "1", temp, 2, file );
  v_double = ( *temp != '0' );

  GetPrivateProfileString( section, "Bits", "0", temp, 2, file );
  v_bits = ( *temp != '0' );

  if ( aSettingsWin == NULL ) {
    GetPrivateProfileString( section, "Visible", "1", temp, 2, file );
    m_pWndInterpret->ShowWindow( ( *temp != '0' ? SW_SHOW : SW_HIDE ) );

    GetPrivateProfileString( section, "Read mode", "1", temp, 2, file );
    m_readBlock = ( *temp != '0' );

    m_pWndInterpret->RenameLabels( v_labels != 0 );
    m_pWndInterpret->ViewedTypes( v_bool, v_sByte, v_uByte, v_sWord, v_uWord, v_sDWord,
      v_uDWord, v_sQWord, v_uQWord, v_float, v_double, v_bits );
  } else {
    aSettingsWin->v_bool = v_bool;
    aSettingsWin->v_sByte = v_sByte;
    aSettingsWin->v_uByte = v_uByte;
    aSettingsWin->v_sWord = v_sWord;
    aSettingsWin->v_uWord = v_uWord;
    aSettingsWin->v_sDWord = v_sDWord;
    aSettingsWin->v_uDWord = v_uDWord;
    aSettingsWin->v_sQWord = v_sQWord;
    aSettingsWin->v_uQWord = v_uQWord;
    aSettingsWin->v_float = v_float;
    aSettingsWin->v_double = v_double;
    aSettingsWin->v_bits = v_bits;
    aSettingsWin->v_labels = v_labels;

    GetPrivateProfileString( section, "Read mode", "1", temp, 2, file );
    ( *temp != '0' ? aSettingsWin->v_selBlock : aSettingsWin->v_selStart ) = BST_CHECKED;
  }
}

void CApplication::SaveWindowState() {
  CString file = GetIniPath();
  char* s = ( m_pWndInterpret->IsWindowVisible() ? "1" : "0" );
  WritePrivateProfileString( "OllyDataInterpret", "Visible", s, file );
}

CString CApplication::GetIniPath() {
  static const char* const filename = "ollydbg.ini";

  char buffer[MAX_PATH];
  GetModuleFileNameA( NULL, buffer, MAX_PATH );

  CString file = buffer;
  file = file.Left( file.ReverseFind('\\') + 1 );
  file += filename;

  return file;
}


void CApplication::ShowBitmapViewer() {
  CWndBitmapMenu wnd;

  wnd.SetAddresses( g_selectionStart, g_selectionEnd );
  wnd.DoModal();
}

/************************************************************************/
/* Olly events                                                          */
/************************************************************************/

EXPORTED int ODBG_Plugindata( char aPluginName[32] ) {
  strcpy( aPluginName, "OllyDataInterpret" );
  return PLUGIN_VERSION;
}

EXPORTED int ODBG_Plugininit( int aOllyVersion, HWND aOllyHandle, ulong* aFeatures ) {
  if ( aOllyVersion != PLUGIN_VERSION )
    return -1;
    
  application.SetOllyVersion( aOllyVersion );
  application.SetOllyWindow( aOllyHandle );
  application.InitWindows();
  application.LoadSettings();
  
  g_ollyWindow = aOllyHandle;

  GdiplusStartupInput gdipsi;
  GdiplusStartup( &g_gdipToken, &gdipsi, NULL );
 
  // g_hookInstall is true, thus, hook will be installed rather
  // than handling event
  OllySelectEventHandler();
  return 0;
}

EXPORTED int ODBG_Pluginclose() {
  application.SaveWindowState();

  GdiplusShutdown( g_gdipToken );
  return 0;
}

EXPORTED int ODBG_Pluginshortcut( int aOrigin, int aCtrlPressed, int aAltPressed, int aShiftPressed, int aKey, void* aItem ) {
  if ( (aOrigin == PM_DUMP || aOrigin == PM_DISASM || aOrigin == PM_CPUDUMP || aOrigin == PM_CPUSTACK ) &&
       aItem && aCtrlPressed && aKey == 'X' ) {
       
    t_dump& dump = *(t_dump*) aItem;
    CString temp;
    temp.Format( "%.8X", dump.sel0 );
    application.SetClipboardText( temp );
    Infoline( "Address %s copied to clipboard.", temp );
    return 1;
  }
  
  if ( aOrigin == PM_MAIN ) {
    if ( aCtrlPressed && aKey == 'I' ) {
      application.ToggleInterpreter();
      return 1;
    }
    
    if ( aCtrlPressed && aKey == 'X' ) {
      CString temp;
      temp.Format( "%.8X", g_selectionStart );
      application.SetClipboardText( temp );
      Infoline( "Address %s copied to clipboard.", temp );
      return 1;
    }
  }
  
  return 0;
}

EXPORTED int ODBG_Pluginmenu( int aOrigin, char aData[4096], void* aItem ) {
  if ( aOrigin == PM_MAIN ) {
    strcpy( aData, "1 Show/hide data interpreter window\tCTRL+I,2 Settings...|3 About" );
    return 1;
  }

  if ( aOrigin == PM_CPUDUMP || aOrigin == PM_DUMP || aOrigin == PM_DISASM || aOrigin == PM_CPUSTACK ) {
    strcpy( aData, "|1 Copy selected address\tCTRL+X,2 View selected bytes as bitmap|" );
    return 1;
  }

  return 0;
}


EXPORTED void ODBG_Pluginaction( int aOrigin, int aAction, void* aItem ) {
  switch ( aOrigin ) {
    case PM_MAIN:
      switch ( aAction ) {
        case 1:
          application.ToggleInterpreter();
          break;
          
        case 2:
          application.ShowSettings();
          break;
          
        case 3:
          MessageBox( g_ollyWindow,
                      "OllyDataInterpret v1.0\n\nWritten by Snake (http://www.sgames.ovh.org)",
                      "About", MB_OK | MB_ICONINFORMATION );
          break;
      }
      break;

    case PM_CPUDUMP:
    case PM_DUMP:
    case PM_DISASM:
    case PM_CPUSTACK:
      switch ( aAction ) {
        case 1: {
          CString temp;
          temp.Format( "%.8X", g_selectionStart );
          application.SetClipboardText( temp );
          Infoline( "Address %s copied to clipboard.", temp );
          break;
        }

        case 2:
          application.ShowBitmapViewer();
          break;
      }
      break;
  }
}

/************************************************************************/
/* Hooked selection event                                               */
/************************************************************************/

void __stdcall OllySelectEvent( DWORD aAddressStart, DWORD aAddressEnd ) {
  g_selectionStart = aAddressStart;
  g_selectionEnd = aAddressEnd;
  application.UpdateInterpreter( aAddressStart, aAddressEnd );
}

void* g_selectEventRetAddr = (void*) 0x0044FC52;
void* g_selectEventAddr = OllySelectEventHandler;
void* g_pVirtualProtect = VirtualProtect;

void __declspec( naked ) OllySelectEventHandler() {
  __asm {
    cmp    byte ptr ds:[g_hookInstall], 1
    jne    HandleEvent
    sub    esp, 4
    push   esp
    push   40h
    push   06h
    push   0044FC4Ch
    call   [g_pVirtualProtect]
    
    push   esp
    push   40h
    push   06h
    push   PreviousInstruction
    call   [g_pVirtualProtect]
    
    add    esp, 4
    
    mov    eax, PreviousInstruction
    push   dword ptr ds:[0044FC4Ch]
    pop    dword ptr ds:[eax]
    push   word ptr ds:[0044FC50h]
    pop    word ptr ds:[eax + 4]
    
    mov    word ptr ds:[0044FC4Ch], 25FFh
    mov    eax, offset g_selectEventAddr
    mov    dword ptr ds:[0044FC4Eh], eax
    
    mov    byte ptr ds:[g_hookInstall], 0
    ret
    
    HandleEvent:
    pushad
    push   ecx
    push   edx
    call   [OllySelectEvent]
    popad
    
    PreviousInstruction:
    nop
    nop
    nop
    nop
    nop
    nop
    
    jmp   dword ptr ds:[g_selectEventRetAddr]
  }
}

