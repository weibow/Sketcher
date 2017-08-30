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
