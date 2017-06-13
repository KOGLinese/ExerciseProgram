
// sbDlg.h : 头文件
//

#pragma once


// CsbDlg 对话框
class CsbDlg : public CDialogEx
{
// 构造
public:
	CsbDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
