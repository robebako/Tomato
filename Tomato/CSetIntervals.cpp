// CSetIntervals.cpp : implementation file
//

#include "pch.h"
#include "Tomato.h"
#include "CSetIntervals.h"
#include "afxdialogex.h"


// CSetIntervals dialog

IMPLEMENT_DYNAMIC(CSetIntervals, CDialogEx)

CSetIntervals::CSetIntervals(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_INTERVALS, pParent)
	, work_interval(0)
	, pause_interval(0)
{

}

CSetIntervals::~CSetIntervals()
{
}

void CSetIntervals::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, work_interval);
	DDV_MinMaxInt(pDX, work_interval, 1, 60);
	DDX_Text(pDX, IDC_EDIT2, pause_interval);
	DDV_MinMaxInt(pDX, pause_interval, 1, 60);
}


BEGIN_MESSAGE_MAP(CSetIntervals, CDialogEx)
END_MESSAGE_MAP()


// CSetIntervals message handlers
