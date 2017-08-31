#pragma once
#include "afxcmn.h"


// CScaleDialog 对话框

class CScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScaleDialog();

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPIN_DLG };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// Scale the current view scale
	int m_Scale;
	CSpinButtonCtrl m_Spin;
	virtual BOOL OnInitDialog();
};
