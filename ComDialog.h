#pragma once


// CComDialog 对话框

class CComDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CComDialog)

public:
	CComDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CComDialog();

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_DLG };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
