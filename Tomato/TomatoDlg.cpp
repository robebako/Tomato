
// TomatoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tomato.h"
#include "TomatoDlg.h"
#include "afxdialogex.h"
#include "CSetIntervals.h"
#include "CAddProject.h"

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
	DDX_Control(pDX, IDC_LIST1, listctrl);
}

BEGIN_MESSAGE_MAP(CTomatoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CTomatoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTomatoDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CTomatoDlg::OnBnClickedButton3)
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

	//set default values for work minutes edit and pause minutes edit
	CTomatoApp* pApp = (CTomatoApp*)AfxGetApp();
	CString mins;
	mins.Format(_T("%d"), pApp->work_interval);
	work_min_edit.SetWindowTextW(mins);
	mins.Format(_T("%d"), pApp->pause_interval);
	pause_min_edit.SetWindowTextW(mins);

	//set default work minutes for timer display edit
	timer_mins = pApp->work_interval;
	strMin.Format(_T("%d"), timer_mins);
	strSec.Format(_T("0%d"), timer_secs);
	m_strTimer.Format(_T("%s : %s"), strMin, strSec);
	timer_edit.SetWindowTextW(m_strTimer);

	//initialize list control
	listctrl.InsertColumn(0, _T("Project"),LVCFMT_LEFT,110);
	listctrl.InsertColumn(1, _T("Total minutes worked"), LVCFMT_CENTER,120);

	//disable START button if no project in project list
	if (combo.GetCount() < 1)
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	//change display font of timer edit
	CFont myFont;
	myFont.CreateFontW(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));
	timer_edit.SetFont(&myFont,TRUE);

	//load custom icon
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);

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



void CTomatoDlg::SetTimerMinutes(int timer_mins)
{
	timer_secs = 0;
	if (timer_mins < 10)
		strMin.Format(_T("0%d"), timer_mins);
	else
		strMin.Format(_T("%d"), timer_mins);
	strSec.Format(_T("0%d"), timer_secs);
	m_strTimer.Format(_T("%s : %s"), strMin, strSec);
	timer_edit.SetWindowTextW(m_strTimer);
}

void CTomatoDlg::OnBnClickedButton2()
{
	if (!worksession_on && !timer_on)
	{
		CSetIntervals dlg;
		CTomatoApp* pApp = (CTomatoApp*)AfxGetApp();
		dlg.work_interval = pApp->work_interval;
		dlg.pause_interval = pApp->pause_interval;
		if (dlg.DoModal() == IDOK)
		{
			pApp->work_interval = dlg.work_interval;
			pApp->pause_interval = dlg.pause_interval;
			CString mins;
			mins.Format(_T("%d"), pApp->work_interval);
			work_min_edit.SetWindowTextW(mins);
			mins.Format(_T("%d"), pApp->pause_interval);
			pause_min_edit.SetWindowTextW(mins);
			SetTimerMinutes(pApp->work_interval);
		}
	}
}


void CTomatoDlg::OnBnClickedButton1()
{
	CTomatoApp* pApp = (CTomatoApp*)AfxGetApp();

	if(!timer_on)
	{
		if (!worksession_on)
		{
			timer_mins = pApp->work_interval;
			SetTimer(1, 50, 0);
			timer_on = true;
			combo.EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"STOP WORKSESSION");
			worksession_on=true;
		}
	}
	else
	{
		if (worksession_on)
		{
			if (MessageBox(L"Quit-really?", L"Abort session", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				KillTimer(1);
				timer_on = false;
				worksession_on = false;
				timer_mins = pApp->work_interval;
				timer_secs = 0;
				if (timer_mins < 10)
					strMin.Format(_T("0%d"), timer_mins);
				else
					strMin.Format(_T("%d"), timer_mins);
				strSec.Format(_T("0%d"), timer_secs);
				m_strTimer.Format(_T("%s : %s"), strMin, strSec);
				timer_edit.SetWindowTextW(m_strTimer);
				GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"START WRK SESSION");
				combo.EnableWindow(TRUE);
			}
		}
		else
		{
			if (MessageBox(L"Quit-really?", L"Abort session", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				KillTimer(1);
				timer_on = false;
				SetTimerMinutes(pApp->work_interval);
				GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"START WORK SESSION");
			}
		}

	}
}


void CTomatoDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (timer_mins != 0 || timer_secs != 0)
	{
		if (timer_secs == 0)
		{
			--timer_mins;
			timer_secs = 59;
		}
		else
		{
			--timer_secs;
		}
		if(timer_mins<10)
			strMin.Format(_T("0%d"), timer_mins);
		else
			strMin.Format(_T("%d"), timer_mins);
		if(timer_secs<10)
			strSec.Format(_T("0%d"), timer_secs);
		else
			strSec.Format(_T("%d"), timer_secs);
		m_strTimer.Format(_T("%s : %s"), strMin, strSec);
		timer_edit.SetWindowTextW(m_strTimer);
	}

	else
	{
		//when timer is over
		CTomatoApp* pApp = (CTomatoApp*)AfxGetApp();
		timer_on = false;
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"START WORK SESSION");
		if( worksession_on)
		{
			KillTimer(1);
			worksession_on = false;
			CString curSelItem;
			combo.GetLBText(combo.GetCurSel(), curSelItem);
			pApp->works[curSelItem] += pApp->work_interval;
			combo.EnableWindow(TRUE);
			LVFINDINFO info;
			int nIndex;
			//update list control
			info.flags = LVFI_PARTIAL | LVFI_STRING;
			info.psz = curSelItem;
			nIndex = listctrl.FindItem(&info);
			CString mins;  
			mins.Format(_T("%d"),pApp->works[curSelItem]);
			listctrl.SetItemText(nIndex, 1, mins);
			if (MessageBox(L"Work session has ended!\nStart pause?", L"Notice", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				timer_mins = pApp->pause_interval;
				SetTimer(1, 50, 0);
				timer_on = true;
				GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"STOP PAUSE SESSION");
			}
			else
			{
				SetTimerMinutes(pApp->work_interval);
			}
		}
		else
		{
			KillTimer(1);
			MessageBox(L"Pause has ended!", L"Notice");
			SetTimerMinutes(pApp->work_interval);
		}
	}
}


void CTomatoDlg::OnBnClickedButton3()
{
	static int cntr = 0;
	if (!worksession_on)
	{
		CAddProject dlg;
		if (dlg.DoModal() == IDOK)
		{
			CTomatoApp* pApp = (CTomatoApp*)AfxGetApp();
			if (!dlg.project_name.IsEmpty())
			{
				GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
				if (!pApp->works.insert({ dlg.project_name,0 }).second)
					MessageBox(L"Project by that name already exists!");
				else
				{
					combo.AddString(dlg.project_name);
					combo.SetCurSel(0);
					CString mins;
					mins.Format(_T("%d"), 0);
					listctrl.InsertItem(cntr, dlg.project_name);
					listctrl.SetItemText(cntr++, 1, mins);
				}
				
			}
		}
	}
}
