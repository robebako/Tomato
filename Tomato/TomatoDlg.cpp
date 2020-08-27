
// TomatoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tomato.h"
#include "TomatoDlg.h"
#include "afxdialogex.h"
#include "CSetIntervals.h"
#include <cstring>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTomatoDlg dialog



CTomatoDlg::CTomatoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOMATO_DIALOG, pParent)
	, m_strTimer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTomatoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo);
	DDX_Control(pDX, IDC_EDIT1, work_min_edit);
	DDX_Control(pDX, IDC_EDIT2, pause_min_edit);
	DDX_Text(pDX, IDC_EDIT3, m_strTimer);
	DDX_Control(pDX, IDC_EDIT3, timer_edit);
}

BEGIN_MESSAGE_MAP(CTomatoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CTomatoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTomatoDlg message handlers

BOOL CTomatoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CTomatoApp* pApp = (CTomatoApp*)AfxGetApp();
	CString mins;
	mins.Format(_T("%d"), pApp->work_interval);
	work_min_edit.SetWindowTextW(mins);
	mins.Format(_T("%d"), pApp->pause_interval);
	pause_min_edit.SetWindowTextW(mins);

	timer_mins = pApp->work_interval;
	strMin.Format(_T("%d"), timer_mins);
	strSec.Format(_T("0%d"), timer_secs);
	m_strTimer.Format(_T("%s : %s"), strMin, strSec);
	timer_edit.SetWindowTextW(m_strTimer);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTomatoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTomatoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTomatoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTomatoDlg::OnBnClickedButton2()
{
	CSetIntervals dlg;
	CTomatoApp* pApp=(CTomatoApp*)AfxGetApp();
	dlg.work_interval = pApp->work_interval;
	dlg.pause_interval = pApp->pause_interval;
	if(dlg.DoModal() == IDOK) 
	{
		pApp->work_interval = dlg.work_interval;
		pApp->pause_interval= dlg.pause_interval;
		CString mins;
		mins.Format(_T("%d"), pApp->work_interval);
		work_min_edit.SetWindowTextW(mins);
		mins.Format(_T("%d"), pApp->pause_interval);
		pause_min_edit.SetWindowTextW(mins);
	}
}
