
// test_UserSubDlg.h : ͷ�ļ�
//

#pragma once


// Ctest_UserSubDlg �Ի���
class Ctest_UserSubDlg : public CDialogEx
{
// ����
public:
	Ctest_UserSubDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CString sCaptureTraceout;
	void AppendTextOut(CString& sTrace);

// �Ի�������
	enum { IDD = IDD_TEST_USERSUB_DIALOG };

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
	afx_msg void OnCbnDropdownIplist();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedCmd();
	afx_msg void OnBnClickedCmd1();
	afx_msg void OnBnClickedGosub();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
