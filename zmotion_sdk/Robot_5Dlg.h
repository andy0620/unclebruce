
// Robot_5Dlg.h : ͷ�ļ�
//

#pragma once


// CRobot_5Dlg �Ի���
class CRobot_5Dlg : public CDialogEx
{
// ����
public:
	CRobot_5Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	int GetNumFromText(int nid);
	void SetNumToText(int nid, int inum);
	int Robot_Status;
// �Ի�������
	enum { IDD = IDD_ROBOT_5_DIALOG };

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
