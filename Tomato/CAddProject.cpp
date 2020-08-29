// CAddProject.cpp : implementation file
//

#include "pch.h"
#include "Tomato.h"
#include "CAddProject.h"
#include "afxdialogex.h"


// CAddProject dialog

IMPLEMENT_DYNAMIC(CAddProject, CDialogEx)

CAddProject::CAddProject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_PROJECT, pParent)
	, project_name(_T(""))
{

}

CAddProject::~CAddProject()
{
}

void CAddProject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, project_name);
	DDV_MaxChars(pDX, project_name, 25);
}


BEGIN_MESSAGE_MAP(CAddProject, CDialogEx)
END_MESSAGE_MAP()


// CAddProject message handlers


BOOL CAddProject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
