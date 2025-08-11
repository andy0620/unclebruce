
// Test_CycleUpDlg.h : 头文件
//

#pragma once


// CTest_CycleUpDlg 对话框
class CTest_CycleUpDlg : public CDialogEx
{
// 构造
public:
	CTest_CycleUpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_CYCLEUP_DIALOG };

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
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedButton1();
	BOOL m_If_StartUp;
	int m_CyclePort;
	int m_CycleTime;

	int m_CyclePara[3];
	int m_CycleParaStart[3];
	int m_CycleParaNum[3];
	BOOL m_CycleParaEnAble[3];
	int m_CycleCount;
	afx_msg void OnBnClickedBtnCycleup();
	afx_msg void OnBnClickedCheckStart();

	void GetCycleStr();
	void GetCycleInfo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void AppendTextOut(CString& sTrace);
	CEdit m_CycleMessages;
};
