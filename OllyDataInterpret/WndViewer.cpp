// WndViewer.cpp : implementation file
//

#include "stdafx.h"
#include "WndViewer.h"

using namespace Gdiplus;

// CWndViewer dialog

IMPLEMENT_DYNAMIC(CWndViewer, CDialog)

CWndViewer::CWndViewer(CWnd* pParent /*=NULL*/)
	: CDialog(CWndViewer::IDD, pParent), m_bitmap( NULL ), m_bitmapBuffer( NULL )
{

}

CWndViewer::~CWndViewer()
{
  if ( m_bitmap )
    delete m_bitmap;

  if ( m_bitmapBuffer )
    delete [] m_bitmapBuffer;
}

void CWndViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWndViewer, CDialog)
  ON_WM_PAINT()
  ON_WM_SHOWWINDOW()
  ON_WM_SIZE()
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


// CWndViewer message handlers

void CWndViewer::OnPaint() {
  if ( !m_bitmap )
    return;

  CRect rect;
  GetClientRect( rect );
  Graphics canvas( m_dcMemory );
  SolidBrush bLight( (ARGB) Color::White );
  SolidBrush bDark( (ARGB) Color::LightGray );

  canvas.SetCompositingQuality( CompositingQualityAssumeLinear );
  canvas.SetInterpolationMode( InterpolationModeNearestNeighbor );
  canvas.SetSmoothingMode( SmoothingModeNone );
  canvas.SetPixelOffsetMode( PixelOffsetModeNone );

  //////////////////////////////////////////////////////////////////////////

  int i, j, idx, chessSize = 32;

  // Calculate number of columns and rows for checkerboard
  int rectCol = ((rect.Width() / chessSize) / 2) + 1; // Only half of columns will be drawn
  int rectRow = ((rect.Height() / chessSize)) + 1;

  // Allocate rectangles
  Rect* grayRects = new Rect[rectCol * rectRow];

  // Fill rect members with proper data (positions & sizes)
  for ( j = 0; j < rectRow; j++ ) {
    for ( i = 0; i < rectCol; i++ ) {
      idx = i + (j * rectCol); // Calc index
      grayRects[idx].X = ((i * 2 * chessSize) + (j % 2) * chessSize);
      grayRects[idx].Y = (j * chessSize);

      if ( grayRects[idx].X >= rect.Width() ||
        grayRects[idx].Y >= rect.Height() )
        continue;

      if ( grayRects[idx].X + chessSize > rect.Width() )
        grayRects[idx].Width = (rect.Width() - grayRects[idx].X);
      else
        grayRects[idx].Width = chessSize;

      if ( grayRects[idx].Y + chessSize > rect.Height() )
        grayRects[idx].Height = (rect.Height() - grayRects[idx].Y);
      else
        grayRects[idx].Height = chessSize;
    }
  }

  canvas.Clear( (ARGB) Color::Gray );
  canvas.FillRectangle( &bLight, 0, 0, rect.Width(), rect.Height() );
  canvas.FillRectangles( &bDark, grayRects, rectCol * rectRow );

  delete [] grayRects;

  //////////////////////////////////////////////////////////////////////////

  canvas.DrawImage( m_bitmap, Rect( 0, 0, m_bitmapWidth, m_bitmapHeight ) );

  CPaintDC dc( this );
  BitBlt( dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), m_dcMemory, 0, 0, SRCCOPY );
}

void CWndViewer::OnShowWindow(BOOL bShow, UINT nStatus) {
  m_bitmapBuffer = new BYTE[m_bitmapSize];
  DWORD bytesRead = Readmemory( m_bitmapBuffer, m_bitmapAddress, m_bitmapSize, MM_SILENT );

  if ( bytesRead == m_bitmapSize ) {
    m_bitmap = new Bitmap( m_bitmapWidth, m_bitmapHeight,
                           m_bitmapWidth * PixelSizes[m_pixelFormatId],
                           PixelFormats[m_pixelFormatId], m_bitmapBuffer );
  } else {
    MessageBox( "Cannot read memory!" );
    PostMessage( WM_CLOSE );
    CDialog::OnShowWindow(FALSE, nStatus);

    return;
  }

  HDC hdc = ::GetDC( GetSafeHwnd() );
  m_dcMemory = CreateCompatibleDC( hdc );
  m_dcBitmap = CreateCompatibleBitmap( hdc, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) );
  SelectObject( m_dcMemory, m_dcBitmap );
  ::ReleaseDC( GetSafeHwnd(), hdc );

  SetWindowPos( this, 0, 0, 640, 480, SWP_NOZORDER );
  CDialog::OnShowWindow(TRUE, nStatus);

}

void CWndViewer::OnSize( UINT nType, int cx, int cy ) {
  CDialog::OnSize(nType, cx, cy);

  InvalidateRect( NULL, false );
}
