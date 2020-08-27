#pragma once


// CSetIntervals dialog

class CSetIntervals : public CDialogEx
{
	DECLARE_DYNAMIC(CSetIntervals)

public:
	CSetIntervals(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSetIntervals();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_INTERVALS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int work_interval;
	int pause_interval;
};
