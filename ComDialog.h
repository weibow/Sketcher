#pragma once


// CComDialog �Ի���

class CComDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CComDialog)

public:
	CComDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CComDialog();

// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_DLG };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
