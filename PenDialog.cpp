// PenDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Sketcher.h"
#include "PenDialog.h"
#include "afxdialogex.h"


// CPenDialog 对话框

IMPLEMENT_DYNAMIC(CPenDialog, CDialogEx)

CPenDialog::CPenDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PENWIDTH_DLG, pParent), m_PenWidth{}
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialogEx)
	ON_BN_CLICKED(IDC_PENWIDTH0, &CPenDialog::OnBnClickedPenwidth0)
	ON_BN_CLICKED(IDC_PENWIDTH1, &CPenDialog::OnBnClickedPenwidth1)
	ON_BN_CLICKED(IDC_PENWIDTH2, &CPenDialog::OnBnClickedPenwidth2)
	ON_BN_CLICKED(IDC_PENWIDTH3, &CPenDialog::OnBnClickedPenwidth3)
	ON_BN_CLICKED(IDC_PENWIDTH4, &CPenDialog::OnBnClickedPenwidth4)
	ON_BN_CLICKED(IDC_PENWIDTH5, &CPenDialog::OnBnClickedPenwidth5)
END_MESSAGE_MAP()


// CPenDialog 消息处理程序


BOOL CPenDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	switch (m_PenWidth)
	{
	case 1:
		CheckDlgButton(IDC_PENWIDTH1, BST_CHECKED);
		break;
	case 2:
		CheckDlgButton(IDC_PENWIDTH2, BST_CHECKED);
		break;
	case 3:
		CheckDlgButton(IDC_PENWIDTH3, BST_CHECKED);
		break;
	case 4:
		CheckDlgButton(IDC_PENWIDTH4, BST_CHECKED);
		break;
	case 5:
		CheckDlgButton(IDC_PENWIDTH5, BST_CHECKED);
		break;
	default:
		CheckDlgButton(IDC_PENWIDTH0, BST_CHECKED);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPenDialog::OnBnClickedPenwidth0()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PenWidth = 0;
}


void CPenDialog::OnBnClickedPenwidth1()
{	
	// TODO: 在此添加控件通知处理程序代码
	m_PenWidth = 1;
}


void CPenDialog::OnBnClickedPenwidth2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PenWidth = 2;
}


void CPenDialog::OnBnClickedPenwidth3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PenWidth = 3;
}


void CPenDialog::OnBnClickedPenwidth4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PenWidth = 4;
}


void CPenDialog::OnBnClickedPenwidth5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PenWidth = 5;
}
