
// test_PswitchDlg.h : ͷ�ļ�
//

#pragma once


// Ctest_PswitchDlg �Ի���
class Ctest_PswitchDlg : public CDialogEx
{
// ����
public:
	Ctest_PswitchDlg(CWnd* pParent = NULL);	// ��׼���캯��

	int m_Row,m_Col;
	int iTotalPoint;
	float fPointPos[1000];

// �Ի�������
	enum { IDD = IDD_TEST_PSWITCH_DIALOG };

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

	void ShowPswtichList();
	void ShowRegistList();

	afx_msg void OnCbnDropdownIplist();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedRadioOpen();
	afx_msg void OnBnClickedRadioClose();
	int RegistMode;
	int m_AxisNum;
	int m_PSO_dir;
	int m_POS_out;
	float m_End_Pos;
	int m_Timer_Num;
	int m_POS_EndTable;
	float m_Start_Pos;
	int m_POS_StartTable;
	int m_Timer_Valid;
	int m_Timer_Cycle;
	BOOL m_Timer_IfOpen;
	BOOL m_POS_IfOpen;
	int m_POS_OutStatus;
	CListCtrl m_PosList;
	CComboBox m_RegistMode;
	int m_RegistAxis;
	BOOL m_Regist_IfOpen;
	int m_RegistCount;
	CEdit m_EDIT;
	afx_msg void OnNMDblclkPoslist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusPedit();
	afx_msg void OnBnClickedStartmove();
	afx_msg void OnBnClickedTimerOpen();
	afx_msg void OnBnClickedTimerClose();
	afx_msg void OnBnClickedStopmove();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRegistStart();
	CListCtrl m_RegistList;
};
