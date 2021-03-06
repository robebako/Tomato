
// TomatoDlg.h : header file
//

#pragma once


// CTomatoDlg dialog
class CTomatoDlg : public CDialogEx
{
// Construction
public:
	CTomatoDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOMATO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo;
	CEdit work_min_edit, pause_min_edit;
	int timer_mins, timer_secs=0;
	CString strMin, strSec, m_strTimer;
	CEdit timer_edit;
	bool timer_on = false, worksession_on=false;
	afx_msg
		void SetTimerMinutes(int mins);
	void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	CListCtrl listctrl;
};
