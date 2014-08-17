// aaaDlg.h : header file
//

#if !defined(AFX_AAADLG_H__2AC8A877_6966_40EB_8C66_CFC19560DF9C__INCLUDED_)
#define AFX_AAADLG_H__2AC8A877_6966_40EB_8C66_CFC19560DF9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "draw.h"
/////////////////////////////////////////////////////////////////////////////
// CAaaDlg dialog

class CAaaDlg : public CDialog
{
// Construction
public:
	CAaaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAaaDlg)
	enum { IDD = IDD_AAA_DIALOG };
	double	m_d;
	double	m_lambda;
	double	m_multi;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAaaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	Draw draw;
	int type;
	bool anim;

	// Generated message map functions
	//{{AFX_MSG(CAaaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnAnim();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLambdaAnim();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AAADLG_H__2AC8A877_6966_40EB_8C66_CFC19560DF9C__INCLUDED_)
