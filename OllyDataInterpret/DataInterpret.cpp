#include "stdafx.h"
#include "DataInterpret.h"

IMPLEMENT_DYNAMIC( CWndInterpret, CDialog )

CWndInterpret::CWndInterpret( CWnd* pParent ): CDialog( CWndInterpret::IDD, pParent ) , m_textBool(_T(""))
, m_textSByte(_T(""))
, m_textUByte(_T(""))
, m_textSWord(_T(""))
, m_textUWord(_T(""))
, m_textSDWord(_T(""))
, m_textUDWord(_T(""))
, m_textSQWord(_T(""))
, m_textUQWord(_T(""))
, m_textFloat(_T(""))
, m_textDouble(_T(""))
{
  Create( IDD );
}

CWndInterpret::~CWndInterpret() {

}

void CWndInterpret::DoDataExchange( CDataExchange* pDX ) {
  CDialog::DoDataExchange( pDX );
  DDX_Control(pDX, IDC_EDIT_BOOL, m_editBool);
  DDX_Control(pDX, IDC_EDIT_SBYTE, m_editSByte);
  DDX_Control(pDX, IDC_EDIT_UBYTE, m_editUByte);
  DDX_Control(pDX, IDC_EDIT_SWORD, m_editSWord);
  DDX_Control(pDX, IDC_EDIT_UWORD, m_editUWord);
  DDX_Control(pDX, IDC_EDIT_SDWORD, m_editSDword);
  DDX_Control(pDX, IDC_EDIT_UDWORD, m_editUDword);
  DDX_Control(pDX, IDC_EDIT_SQWORD, m_editSQWord);
  DDX_Control(pDX, IDC_EDIT_UQWORD, m_editUQWord);
  DDX_Control(pDX, IDC_EDIT_FLOAT, m_editFloat);
  DDX_Control(pDX, IDC_EDIT_DOUBLE, m_editDouble);
  DDX_Control(pDX, IDC_TEXT_SEL, m_labelSelection);
  DDX_Control(pDX, IDC_EDIT_BINARY, m_editBinary);
  DDX_Text(pDX, IDC_STATIC_BOOL, m_textBool);
  DDX_Text(pDX, IDC_STATIC_SBYTE, m_textSByte);
  DDX_Text(pDX, IDC_STATIC_UBYTE, m_textUByte);
  DDX_Text(pDX, IDC_STATIC_SWORD, m_textSWord);
  DDX_Text(pDX, IDC_STATIC_UWORD, m_textUWord);
  DDX_Text(pDX, IDC_STATIC_SDWORD, m_textSDWord);
  DDX_Text(pDX, IDC_STATIC_UDWORD, m_textUDWord);
  DDX_Text(pDX, IDC_STATIC_SQWORD, m_textSQWord);
  DDX_Text(pDX, IDC_STATIC_UQWORD, m_textUQWord);
  DDX_Text(pDX, IDC_STATIC_FLOAT, m_textFloat);
  DDX_Text(pDX, IDC_STATIC_DOUBLE, m_textDouble);
  DDX_Control(pDX, IDC_STATIC_BOOL, m_labelBool);
  DDX_Control(pDX, IDC_STATIC_SBYTE, m_labelSByte);
  DDX_Control(pDX, IDC_STATIC_UBYTE, m_labelUByte);
  DDX_Control(pDX, IDC_STATIC_SWORD, m_labelSWord);
  DDX_Control(pDX, IDC_STATIC_UWORD, m_labelUWord);
  DDX_Control(pDX, IDC_STATIC_SDWORD, m_labelSDWord);
  DDX_Control(pDX, IDC_STATIC_UDWORD, m_labelUDWord);
  DDX_Control(pDX, IDC_STATIC_SQWORD, m_labelSQWord);
  DDX_Control(pDX, IDC_STATIC_UQWORD, m_labelUQWord);
  DDX_Control(pDX, IDC_STATIC_FLOAT, m_labelFloat);
  DDX_Control(pDX, IDC_STATIC_DOUBLE, m_labelDouble);
  DDX_Control(pDX, IDC_STATIC_BINARY, m_labelBinary);
}


BEGIN_MESSAGE_MAP( CWndInterpret, CDialog )
  ON_WM_SIZE()
  ON_WM_SIZING()
END_MESSAGE_MAP()


// CDataInterpret message handlers


/************************************************************************/
/* Implementation                                                       */
/************************************************************************/

void CWndInterpret::RenameLabels( bool aCStyleLabels ) {
  if ( aCStyleLabels ) {
    m_textBool = "bool:";
    m_textSByte = "char:";
    m_textUByte = "unsigned char:";
    m_textSWord = "short:";
    m_textUWord = "unsigned short:";
    m_textSDWord = "long:";
    m_textUDWord = "unsigned long:";
    m_textSQWord = "long long:";
    m_textUQWord = "unsigned long long:";
    m_textFloat = "float:";
    m_textDouble = "double:";
  } else {
    m_textBool = "Boolean:";
    m_textSByte = "Signed byte:";
    m_textUByte = "Unsigned byte:";
    m_textSWord = "Signed word:";
    m_textUWord = "Unsigned word:";
    m_textSDWord = "Signed DWORD:";
    m_textUDWord = "Unsigned DWORD:";
    m_textSQWord = "Signed QWORD:";
    m_textUQWord = "Unsigned QWORD:";
    m_textFloat = "Single-precision FP:";
    m_textDouble = "Double-precision FP:";
  }

  UpdateData( FALSE );
}

void CWndInterpret::OnSize( UINT nType, int cx, int cy ) {
   CDialog::OnSize( nType, cx, cy );

  if ( !IsWindowVisible() )
    return;

  CRect rect, dialogRect;
  GetClientRect( dialogRect );

  m_editBool.GetWindowRect( rect );
  ScreenToClient( &rect );
  int width = (dialogRect.Width() - rect.left) - 5,
      height = rect.Height();

  m_editBool.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editSByte.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editUByte.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editSWord.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editUWord.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editSDword.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editUDword.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editSQWord.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editUQWord.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editFloat.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editDouble.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );
  m_editBinary.SetWindowPos( this, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER );

  m_labelSelection.GetWindowRect( rect );
  ScreenToClient( &rect );
  m_labelSelection.SetWindowPos( this, 0, 0, 
                                 (dialogRect.Width() - rect.left) - 5, rect.Height(),
                                 SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED );
  m_labelSelection.Invalidate();
}

void CWndInterpret::OnSizing( UINT fwSide, LPRECT rect ) {
  CDialog::OnSizing( fwSide, rect );

  if ( (rect->right - rect->left) < 220 )
    rect->right = rect->left + 220;

  CRect r;
  GetWindowRect( r );

  if ( (rect->bottom - rect->top) != r.Height() ) {
    rect->top = r.top;
    rect->bottom = r.bottom;
  }
}

inline int Visibility( BOOL aVisible ) {
  return ( aVisible ? SW_SHOW : SW_HIDE );
}

void CWndInterpret::ViewedTypes( BOOL aBool, BOOL aSByte, BOOL aUByte, BOOL aSWord, BOOL aUWord,
                                 BOOL aSDWord, BOOL aUDWord, BOOL aSQWord, BOOL aUQWord,
                                 BOOL aFloat, BOOL aDouble, BOOL aBits ) {

  CRect rect, rectLabel, rectSel;
  m_editBool.GetWindowRect( rect );
  m_labelBool.GetWindowRect( rectLabel );
  m_labelSelection.GetWindowRect( rectSel );
  ScreenToClient( rect );
  ScreenToClient( rectLabel );
  ScreenToClient( rectSel );

  int height = rect.Height() + 2;
  int y = rectSel.bottom + 4;
  
  m_editBool.ShowWindow( Visibility( aBool ) );
  m_labelBool.ShowWindow( Visibility( aBool ) );
  m_editBool.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelBool.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aBool * height;

  m_editSByte.ShowWindow( Visibility( aSByte ) );
  m_labelSByte.ShowWindow( Visibility( aSByte ) );
  m_editSByte.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelSByte.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aSByte * height;

  m_editUByte.ShowWindow( Visibility( aUByte ) );
  m_labelUByte.ShowWindow( Visibility( aUByte ) );
  m_editUByte.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelUByte.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aUByte * height;

  m_editSWord.ShowWindow( Visibility( aSWord ) );
  m_labelSWord.ShowWindow( Visibility( aSWord ) );
  m_editSWord.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelSWord.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aSWord * height;

  m_editUWord.ShowWindow( Visibility( aUWord ) );
  m_labelUWord.ShowWindow( Visibility( aUWord ) );
  m_editUWord.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelUWord.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aUWord * height;

  m_editSDword.ShowWindow( Visibility( aSDWord ) );
  m_labelSDWord.ShowWindow( Visibility( aSDWord ) );
  m_editSDword.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelSDWord.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aSDWord * height;

  m_editUDword.ShowWindow( Visibility( aUDWord ) );
  m_labelUDWord.ShowWindow( Visibility( aUDWord ) );
  m_editUDword.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelUDWord.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aUDWord * height;

  m_editSQWord.ShowWindow( Visibility( aSQWord ) );
  m_labelSQWord.ShowWindow( Visibility( aSQWord ) );
  m_editSQWord.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelSQWord.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aSQWord * height;

  m_editUQWord.ShowWindow( Visibility( aUQWord ) );
  m_labelUQWord.ShowWindow( Visibility( aUQWord ) );
  m_editUQWord.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelUQWord.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aUQWord * height;

  m_editFloat.ShowWindow( Visibility( aFloat ) );
  m_labelFloat.ShowWindow( Visibility( aFloat ) );
  m_editFloat.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelFloat.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aFloat * height;

  m_editDouble.ShowWindow( Visibility( aDouble ) );
  m_labelDouble.ShowWindow( Visibility( aDouble ) );
  m_editDouble.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelDouble.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aDouble * height;

  m_editBinary.ShowWindow( Visibility( aBits ) );
  m_labelBinary.ShowWindow( Visibility( aBits ) );
  m_editBinary.SetWindowPos( this, rect.left, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  m_labelBinary.SetWindowPos( this, rectLabel.left, y + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
  y += aBits * height;

  GetWindowRect( rect );
  SetWindowPos( this, 0, 0, rect.Width(), y + 18 + rectSel.bottom, SWP_NOMOVE | SWP_NOZORDER );
}