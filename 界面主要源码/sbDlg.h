
// sbDlg.h : ͷ�ļ�
//

#pragma once


// CsbDlg �Ի���
class CsbDlg : public CDialogEx
{
// ����
public:
	CsbDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString ex;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	int sum;
	double input;
	afx_msg void OnBnClickedButton2();
	CString ret;
	afx_msg void OnEnChangeEdit5();
	double ans;
	int right;
};
