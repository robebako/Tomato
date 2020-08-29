#pragma once


// CAddProject dialog

class CAddProject : public CDialogEx
{
	DECLARE_DYNAMIC(CAddProject)

public:
	CAddProject(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddProject();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_PROJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString project_name;
	virtual BOOL OnInitDialog();
};
