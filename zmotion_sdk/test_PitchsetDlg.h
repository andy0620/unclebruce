
// test_PitchsetDlg.h : 头文件
//

#pragma once


// Ctest_PitchsetDlg 对话框
class Ctest_PitchsetDlg : public CDialogEx
{
// 构造
public:
	Ctest_PitchsetDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_PITCHSET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	bool RunTestFlag;

	int m_Row,m_Col;
	float fPointPos[1000];
	float fFwdDist[1000];
	float fRevDist[1000];
	void ShowPosList();
	bool  AxisIsMoveing(int iaxis);


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
	afx_msg void OnNMDblclkPoslist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusPedit();
	CEdit m_EDIT;
	CListCtrl m_PosList;
	float m_StartPos;
	float m_DisOne;
	UINT m_TableStart;
	UINT m_MaxPoint;
	int m_Enable;
	afx_msg void OnEnChangeEditStartpos1();
	afx_msg void OnEnChangeEditTotalnum();
	afx_msg void OnEnChangeEditStepdist();
	afx_msg void OnBnClickedEnablePitch();
	CButton m_RadioMode;
	int m_iAxis;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditAxis();
	afx_msg void OnBnClickedBtnRun();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnHome();
	float m_accel;
	float m_creep;
//	CEdit m_DatumIn;
	float m_Decel;
	int m_DatumIn;
	UINT m_DelayTime;
	float m_speed;
	float m_Units;
	BOOL m_DatumInInvert;
	int m_homeMode;
	BOOL m_MoveDir;
};
