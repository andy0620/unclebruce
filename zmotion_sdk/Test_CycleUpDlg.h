
// Test_CycleUpDlg.h : ͷ�ļ�
//

#pragma once


// CTest_CycleUpDlg �Ի���
class CTest_CycleUpDlg : public CDialogEx
{
// ����
public:
	CTest_CycleUpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_CYCLEUP_DIALOG };

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
