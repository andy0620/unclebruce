
// test_CamDlg.h : 头文件
//

#pragma once


// Ctest_CamDlg 对话框
class Ctest_CamDlg : public CDialogEx
{
// 构造
public:
	Ctest_CamDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_TEST_CAM_DIALOG };

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
	void ShowPswtichList();
	afx_msg void OnCbnDropdownIplist();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMoveStop();
	afx_msg void OnBnClickedMoveCam();
	CListCtrl m_PosList;
	int m_AxisMaster;
	int m_Axis_Slave;
	float m_CamMoveSp;
	float m_CamMoveDist;

	float m_MoveLinkPara[3][4];
	float m_MoveSLinkPara[3][4];

	afx_msg void OnBnClickedMoveSyn();
	afx_msg void OnBnClickedStopSyn();
	BOOL m_SynMode;
	float m_LinkPos;
	float m_LinkSp;
};
