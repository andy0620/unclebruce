
// test_UserSubDlg.h : 头文件
//

#pragma once


// Ctest_UserSubDlg 对话框
class Ctest_UserSubDlg : public CDialogEx
{
// 构造
public:
	Ctest_UserSubDlg(CWnd* pParent = NULL);	// 标准构造函数

	CString sCaptureTraceout;
	void AppendTextOut(CString& sTrace);

// 对话框数据
	enum { IDD = IDD_TEST_USERSUB_DIALOG };

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
	afx_msg void OnCbnDropdownIplist();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCmd();
	afx_msg void OnBnClickedCmd1();
	afx_msg void OnBnClickedGosub();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
