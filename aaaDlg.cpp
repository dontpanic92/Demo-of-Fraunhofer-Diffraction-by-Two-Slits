// aaaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "aaa.h"
#include "aaaDlg.h"
#include <cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAaaDlg dialog

CAaaDlg::CAaaDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAaaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAaaDlg)
	m_d = 0.0;
	m_lambda = 0.0;
	m_multi = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAaaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAaaDlg)
	DDX_Text(pDX, IDC_EDIT1, m_d);
	DDX_Text(pDX, IDC_EDIT2, m_lambda);
	DDX_Text(pDX, IDC_EDIT3, m_multi);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAaaDlg, CDialog)
//{{AFX_MSG_MAP(CAaaDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_DRAWITEM()
ON_BN_CLICKED(IDC_ANIM, OnAnim)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON2, OnLambdaAnim)
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAaaDlg message handlers

BOOL CAaaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_d = 0.0015;
	m_lambda = 632.8;
	m_multi = 3;
	type = 3;
	anim = false;
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAaaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAaaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAaaDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDCtl == IDC_STATIC1){
		CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		CDC memdc;
		memdc.CreateCompatibleDC(pDC);
		
		CRect rc;
		::GetClientRect(::GetDlgItem(this->GetSafeHwnd(), IDC_STATIC1), &rc);
		
		
		CBitmap MemBitmap;
		MemBitmap.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
		memdc.SelectObject(&MemBitmap);
		memdc.FillSolidRect(rc, RGB(255, 255, 255));
		
		memdc.FillSolidRect(rc, RGB(255, 255, 255));
		memdc.MoveTo(20, 20);
		memdc.LineTo(20, 300);
		memdc.LineTo(500, 300);
		memdc.MoveTo(20, 300);
		draw.init(20, 20, 280, 4, m_d, m_multi, m_lambda);
		Draw::Para para = draw.getNext();
		while(para.x < 500)
		{
			memdc.LineTo(para.x, para.y);
			memdc.FillSolidRect(para.x, 320, 1, 40, RGB(0.1 * sqrt(para.I  * 100 / 4) * 255, 0, 0));
			para = draw.getNext();
		}
		
		CString s;
		s.Format("²ÎÊý:\nd = %f mm\nd = %fa\n¦Ë = %f nm", para.d, para.multi, para.lambda);
		::SetWindowText(::GetDlgItem(this->GetSafeHwnd(), IDC_STATIC2), s);
		
		if(type == 0){
			m_d += 0.0001;
			if(m_d > 0.01)
				m_d = 0.0005;
		}
		else if(type == 1){
			m_lambda += 10;
			if(m_lambda > 2700)
				m_lambda = 500;
		}else if(type == 2){
			m_multi += 0.1;
			if(m_multi > 20)
				m_multi = 1;
		}
		
		pDC->BitBlt(0,0,rc.Width(),rc.Height(),&memdc,0,0,SRCCOPY);
		MemBitmap.DeleteObject();
		memdc.DeleteDC();
		return;
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CAaaDlg::OnAnim() 
{
	UpdateData();
	KillTimer(0);
	// TODO: Add your control notification handler code here
	if(!anim || type != 0){
		type = 0;
		m_d = 0.0005;
		SetTimer(0, 50, NULL);
		anim = true;
	}else{
		anim = false;
	}
}

void CAaaDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 0){
		::InvalidateRect(::GetDlgItem(this->GetSafeHwnd(), IDC_STATIC1), NULL, FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void CAaaDlg::OnLambdaAnim() 
{
	UpdateData();
	KillTimer(0);
	// TODO: Add your control notification handler code here
	if(!anim || type != 1){
		type = 1;
		m_lambda = 500;
		SetTimer(0, 50, NULL);
		anim = true;
	}else{
		anim = false;
	}
}

void CAaaDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	KillTimer(0);
	type = 3;
	anim = false;
	::InvalidateRect(::GetDlgItem(this->GetSafeHwnd(), IDC_STATIC1), NULL, FALSE);
}

void CAaaDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	KillTimer(0);
	if(!anim || type != 2){
		type = 2;
		m_multi = 1;
		SetTimer(0, 50, NULL);
		anim = true;
	}else{
		anim = false;
	}
}