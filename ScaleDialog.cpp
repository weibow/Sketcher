// ScaleDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sketcher.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// CScaleDialog �Ի���

IMPLEMENT_DYNAMIC(CScaleDialog, CDialogEx)

CScaleDialog::CScaleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPIN_DLG, pParent)
	, m_Scale(0)
{

}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCALE, m_Scale);
	DDV_MinMaxInt(pDX, m_Scale, 1, 8);
	DDX_Control(pDX, IDC_SPIN_SCALE, m_Spin);
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialogEx)
END_MESSAGE_MAP()


// CScaleDialog ��Ϣ�������


BOOL CScaleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Spin.SetRange(1, 8);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
