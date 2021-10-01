// WndBitmapMenu.cpp : implementation file
//

#include "stdafx.h"
#include "WndBitmapMenu.h"


// CWndBitmapMenu dialog

IMPLEMENT_DYNAMIC(CWndBitmapMenu, CDialog)

CWndBitmapMenu::CWndBitmapMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CWndBitmapMenu::IDD, pParent)
{

}

CWndBitmapMenu::~CWndBitmapMenu()
{
}

void CWndBitmapMenu::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT_WIDTH, m_editWidth);
  DDX_Control(pDX, IDC_EDIT_HEIGHT, m_editHeight);
  DDX_Control(pDX, IDC_COMBO_PIXEL, m_comboPixel);
}

BEGIN_MESSAGE_MAP(CWndBitmapMenu, CDialog)
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BUTTON1, &CWndBitmapMenu::OnBnClickedButton1)
END_MESSAGE_MAP()

int const PixelFormats[] = {
  PixelFormat1bppIndexed,
  PixelFormat4bppIndexed,
  PixelFormat8bppIndexed,
  PixelFormat16bppGrayScale,
  PixelFormat16bppRGB555,
  PixelFormat16bppRGB565,
  PixelFormat16bppARGB1555,
  PixelFormat24bppRGB,
  PixelFormat32bppRGB,
  PixelFormat32bppARGB,
  PixelFormat32bppPARGB,
  PixelFormat48bppRGB,
  PixelFormat64bppARGB,
  PixelFormat64bppPARGB
};

int const PixelSizes[] = {
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  3,
  4,
  4,
  4,
  6,
  8,
  8
};

void CWndBitmapMenu::OnShowWindow( BOOL bShow, UINT nStatus ) {
  CDialog::OnShowWindow( bShow, nStatus );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "Monochrome (1-bit per pixel)" ),
                            0 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "16-color (4-bits per pixel)" ),
                            1 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "256-color (8-bits per pixel)" ),
                            2 );
/*
  m_comboPixel.SetItemData( m_comboPixel.AddString( "Grayscale (16-bits per pixel)" ),
                            3 );
*/
  m_comboPixel.SetItemData( m_comboPixel.AddString( "RGB555 (16-bits per pixel)" ),
                            4 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "RGB565 (16-bits per pixel)" ),
                            5 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "ARGB1555 (16-bits per pixel)" ),
                            6 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "RGB (24-bits per pixel)" ),
                            7 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "RGB (32-bits per pixel)" ),
                            8 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "ARGB (32-bits per pixel)" ),
                            9 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "PARGB (32-bits per pixel)" ),
                            10 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "RGB (48-bits per pixel)" ),
                            11 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "ARGB (64-bits per pixel)" ),
                            12 );

  m_comboPixel.SetItemData( m_comboPixel.AddString( "PARGB (64-bits per pixel)" ),
                            13 );

  CRect r;
  m_comboPixel.GetWindowRect( r );
  ScreenToClient( r );

  m_comboPixel.SetWindowPos( this, 0, 0, r.Width(), 200, SWP_NOZORDER | SWP_NOMOVE );
  m_comboPixel.SetCurSel( 0 );

  m_editWidth.SetWindowText( "1" );
  m_editHeight.SetWindowText( "1" );
}

void CWndBitmapMenu::OnBnClickedButton1() {
  CString text;
  DWORD pixelFormatId = m_comboPixel.GetItemData( m_comboPixel.GetCurSel() ),
        width,
        height,
        bytes;

  bool read = false;

  m_editWidth.GetWindowText( text );
  width = atoi( text );

  m_editHeight.GetWindowText( text );
  height = atoi( text );

  if ( width <= 0 || height <= 0 ) {
    MessageBox( "Invalid bitmap dimensions.", 0, MB_ICONERROR );
    return;
  }
  
  bytes = (width * height) * PixelSizes[pixelFormatId];

  if ( bytes != m_addressEnd - m_addressStart ) {
    read = ( MessageBox( "Wrong number of bytes selected.\nRead as many bytes as needed ?", 0,
                         MB_OK | MB_ICONERROR | MB_YESNO ) == IDYES );
  } else
    read = true;

  if ( read ) {
    CWndViewer viewer;
    viewer.m_bitmapWidth = width;
    viewer.m_bitmapHeight = height;
    viewer.m_bitmapAddress = m_addressStart;
    viewer.m_bitmapSize = bytes;
    viewer.m_pixelFormatId = pixelFormatId;

    viewer.DoModal();
  }
}

//////////////////////////////////////////////////////////////////////////

void CWndBitmapMenu::SetAddresses( int aStart, int aEnd ) {
  m_addressStart = aStart;
  m_addressEnd = aEnd;
}