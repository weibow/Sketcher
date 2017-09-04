// ComDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Sketcher.h"
#include "ComDialog.h"
#include "afxdialogex.h"


// CComDialog 对话框

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


// CComDialog 消息处理程序
