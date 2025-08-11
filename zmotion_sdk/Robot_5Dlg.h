
// Robot_5Dlg.h : 头文件
//

#pragma once


// CRobot_5Dlg 对话框
class CRobot_5Dlg : public CDialogEx
{
// 构造
public:
	CRobot_5Dlg(CWnd* pParent = NULL);	// 标准构造函数

	int GetNumFromText(int nid);
	void SetNumToText(int nid, int inum);
	int Robot_Status;
// 对话框数据
	enum { IDD = IDD_ROBOT_5_DIALOG };

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
	afx_msg void OnCbnDropdownComList();
	afx_msg void OnBnClickedComOpen();
	afx_msg void OnCbnDropdownIplist();
	afx_msg void OnBnClickedEthOpen();
	afx_msg void OnBnClickedCloseConnet();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRobotFrame();
	afx_msg void OnBnClickedRobotInit();
	afx_msg void OnBnClickedRobotReframe();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	float Robot_Para[4];
	float Axis_Speed[12];
	float Axis_Acc[12];
};
