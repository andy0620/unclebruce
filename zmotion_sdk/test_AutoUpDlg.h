
// test_AutoUpDlg.h : ͷ�ļ�
//

#pragma once


// Ctest_AutoUpDlg �Ի���
class Ctest_AutoUpDlg : public CDialogEx
{
// ����
public:
	Ctest_AutoUpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_AUTOUP_DIALOG };

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
