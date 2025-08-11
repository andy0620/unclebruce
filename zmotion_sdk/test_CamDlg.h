
// test_CamDlg.h : ͷ�ļ�
//

#pragma once


// Ctest_CamDlg �Ի���
class Ctest_CamDlg : public CDialogEx
{
// ����
public:
	Ctest_CamDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_TEST_CAM_DIALOG };

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
