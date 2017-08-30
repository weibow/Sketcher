// PenDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sketcher.h"
#include "PenDialog.h"
#include "afxdialogex.h"


// CPenDialog �Ի���

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


// CPenDialog ��Ϣ�������


BOOL CPenDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}
