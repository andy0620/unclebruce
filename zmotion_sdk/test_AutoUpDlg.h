
// test_AutoUpDlg.h : 头文件
//

#pragma once


// Ctest_AutoUpDlg 对话框
class Ctest_AutoUpDlg : public CDialogEx
{
// 构造
public:
	Ctest_AutoUpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_AUTOUP_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedCheck1();
	CEdit m_AutoUpMessage;
	void AppendTextOut(CString& sTrace);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_AutoUpCode;
	int m_AutoUpTime;
	afx_msg void OnBnClickedBtnClear();
};
