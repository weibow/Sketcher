// ComDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sketcher.h"
#include "ComDialog.h"
#include "afxdialogex.h"


// CComDialog �Ի���

IMPLEMENT_DYNAMIC(CComDialog, CDialogEx)

CComDialog::CComDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIAL_PORT, pParent)
{

}

CComDialog::~CComDialog()
{
}

void CComDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComDialog, CDialogEx)
END_MESSAGE_MAP()


// CComDialog ��Ϣ�������
