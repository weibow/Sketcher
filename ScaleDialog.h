#pragma once
#include "afxcmn.h"


// CScaleDialog �Ի���

class CScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScaleDialog();

// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPIN_DLG };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Scale the current view scale
	int m_Scale;
	CSpinButtonCtrl m_Spin;
	virtual BOOL OnInitDialog();
};
