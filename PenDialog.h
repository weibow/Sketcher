#pragma once


// CPenDialog �Ի���

class CPenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenDialog)

public:
	CPenDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPenDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PENWIDTH_DLG };
#endif
	enum {IDD = IDD_PENWIDTH_DLG};
	int m_PenWidth;		//Record the current pen width

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
