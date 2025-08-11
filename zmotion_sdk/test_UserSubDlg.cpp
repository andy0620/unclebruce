
// test_UserSubDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test_UserSub.h"
#include "test_UserSubDlg.h"
#include "afxdialogex.h"
#include "zauxdll2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ZMC_HANDLE       g_handle = NULL;				//���������Ӿ��


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctest_UserSubDlg �Ի���




Ctest_UserSubDlg::Ctest_UserSubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_UserSubDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest_UserSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest_UserSubDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_IPLIST, &Ctest_UserSubDlg::OnCbnDropdownIplist)
	ON_BN_CLICKED(IDC_OPEN, &Ctest_UserSubDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &Ctest_UserSubDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_CLEAR, &Ctest_UserSubDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_CMD, &Ctest_UserSubDlg::OnBnClickedCmd)
	ON_BN_CLICKED(IDC_CMD1, &Ctest_UserSubDlg::OnBnClickedCmd1)
	ON_BN_CLICKED(IDC_GOSUB, &Ctest_UserSubDlg::OnBnClickedGosub)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Ctest_UserSubDlg ��Ϣ�������

BOOL Ctest_UserSubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText("δ����");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ctest_UserSubDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ctest_UserSubDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ctest_UserSubDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_UserSubDlg::OnCbnDropdownIplist()
{
	//�Զ�����IP��ַ
	char buffer[10240];
	int32 iresult;

	//
	iresult = ZAux_SearchEthlist(buffer, 10230, 100);
	if(ERR_OK != iresult)
	{
		return;
	}

	//
	CComboBox   *m_pEthList;

	m_pEthList = (CComboBox *)GetDlgItem(IDC_IPLIST);
	if(NULL == m_pEthList)
	{
		return;
	}

	//���ַ���ת������
	int ipos =0;
	const char * pstring;
	pstring = buffer;

	for(int j= 0; j< 20;j++)
	{
		char buffer2[256];
		buffer2[0] = '\0';

		//�����ո�
		while(' ' == pstring[0])
		{
			pstring++;
		}

		ipos = sscanf(pstring , "%s", &buffer2);
		if(EOF  == ipos)
		{
			break;
		}

		//�����ַ�
		while((' ' != pstring[0]) && ('\t' != pstring[0]) && ('\0' != pstring[0]))
		{
			pstring++;
		}

		//
		if(CB_ERR != m_pEthList->FindString(0, buffer2))
		{
			continue;
		}

		if('\0' == buffer2)
		{
			return;
		}

		//����
		m_pEthList->AddString(buffer2);
	}

	return;
}


void Ctest_UserSubDlg::OnBnClickedOpen()			//����������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char   buffer[256]; 
	int32 iresult;

	if(NULL != g_handle)
	{
		ZAux_Close(g_handle);
		g_handle = NULL;
	}

	GetDlgItemText(IDC_IPLIST,buffer,255);
	buffer[255] = '\0';

	iresult = ZAux_OpenEth(buffer, &g_handle);
	if(ERR_SUCCESS != iresult)
	{
		g_handle = NULL;
		MessageBox(_T("����ʧ��"));
		SetWindowText("δ����");
		return;
	}

	SetWindowText("������");
	SetTimer(0,100,NULL);

}


void Ctest_UserSubDlg::OnBnClickedClose()				//�������Ͽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL != g_handle)
	{
		KillTimer(1);						//�ض�ʱ��
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("δ����");
	}
}


void Ctest_UserSubDlg::OnBnClickedClear()					//�����ʾ�ַ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sCaptureTraceout.Empty();
	SetDlgItemText(IDC_EDIT_SHOW,sCaptureTraceout);
}

void Ctest_UserSubDlg::AppendTextOut(CString& sTrace)
{
	CString stemp ;
	stemp = sTrace;
	CEdit	*pTraceEidt;

	stemp.Replace("\n","\r\n");

	pTraceEidt = (CEdit *)GetDlgItem(IDC_EDIT_SHOW);
	int   nLen   =   pTraceEidt->GetWindowTextLength();

	pTraceEidt->SetLimitText(2000000);

	//������ɾ������
	if(nLen > 1000000)
	{
		//ɾ��5000��
		nLen = pTraceEidt->LineIndex(1000);
		//������
		pTraceEidt->SetSel(0, nLen, true);
		pTraceEidt->ReplaceSel("");

		nLen   =   pTraceEidt->GetWindowTextLength();
	}

	pTraceEidt->SetSel(nLen,   nLen, false);
	pTraceEidt->ReplaceSel(stemp);      
}

void Ctest_UserSubDlg::OnBnClickedCmd()				//DirectCommand��������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char   buffer[513];
	int32 iresult;

	if(NULL == g_handle)
	{
		MessageBox(_T("Connect First!"));
		return;
	}

	if(NULL != g_handle)
	{
		GetDlgItemText(IDC_EDIT_CMD,buffer,512);
		buffer[512] = '\0';

		//0��ֱ�ӷ���
		if(0 == strlen(buffer))
		{
			return;
		}

		char  cmdbuffAck[2048];
		iresult = ZAux_DirectCommand(g_handle, buffer,cmdbuffAck ,2048);
		if(ERR_OK == iresult)
		{
			CString stemp1;
			CString stemp = ">>";
			stemp += buffer;
			stemp+= "\r\n";
			stemp1.Format("���ش����룺%d\r\n�����ַ�����%s \r\n",iresult,cmdbuffAck);
			stemp += stemp1;
			AppendTextOut(stemp);
		}
		else
		{
			CString stemp1;
			CString stemp = ">>";
			stemp += buffer;
			stemp+= "\r\n";
			stemp1.Format("���ش����룺%d \r\n",iresult);
			stemp += stemp1;
			AppendTextOut(stemp);
		}        

		//����������ѡ��ס
		CEdit *pedit;
		pedit = (CEdit *)GetDlgItem(IDC_EDIT_CMD);
		pedit->SetSel(0, -1);
	}

	return;
}


void Ctest_UserSubDlg::OnBnClickedCmd1()			//Execute��������
{
	char   buffer[513];
	int32 iresult;

	if(NULL == g_handle)
	{
		MessageBox(_T("Connect First!"));
		return;
	}

	if(NULL != g_handle)
	{
		GetDlgItemText(IDC_EDIT_CMD,buffer,512);
		buffer[512] = '\0';

		//0��ֱ�ӷ���
		if(0 == strlen(buffer))
		{
			return;
		}

		char  cmdbuffAck[2048];
		iresult = ZAux_Execute(g_handle, buffer,cmdbuffAck ,2048);
		if(ERR_OK == iresult)
		{
			CString stemp1;
			CString stemp = ">>";
			stemp += buffer;
			stemp+= "\r\n";
			stemp1.Format("���ش����룺%d\r\n�����ַ�����%s \r\n",iresult,cmdbuffAck);
			stemp += stemp1;
			AppendTextOut(stemp);
		}
		else
		{
			CString stemp1;
			CString stemp = ">>";
			stemp += buffer;
			stemp+= "\r\n";
			stemp1.Format("���ش����룺%d\r\n�����ַ�����%s \r\n",iresult,cmdbuffAck);
			stemp += stemp1;
			AppendTextOut(stemp);
		}        

		//����������ѡ��ס
		CEdit *pedit;
		pedit = (CEdit *)GetDlgItem(IDC_EDIT_CMD);
		pedit->SetSel(0, -1);
	}

	return;
}

//�Զ��嵥���˶�ָ��
/*BASIC�﷨
speed(iaxis)=fSpeed
Accel(iaxis)=fAcc
Move(fpos) axis(iaxis)  / MoveAbs(fpos) axis(iaxis)
*/
int Func_AxisMove(ZMC_HANDLE Handle, int iAxis ,float fSpeed,float fAcc,float fpos,float imode)
{
	char  cmdbuff[2048];
	char  tempbuff[2048];
	char  cmdbuffAck[2048];
	//��������  speed(iaxis)=fSpeed
	sprintf(cmdbuff, "SPEED(%d) = %.3f\r\n",iAxis,fSpeed);

	//��������   Accel(iaxis)=fAcc
	sprintf(tempbuff, "Accel(%d) = %.3f\r\n",iAxis,fAcc);
	strcat(cmdbuff, tempbuff);

	//��������   Move(fpos) axis(iaxis)  / MoveAbs(fpos) axis(iaxis)
	if(imode == 0)
	{
		sprintf(tempbuff, "Move(%.3f) Axis(%d)\r\n",fpos,iAxis);
		strcat(cmdbuff, tempbuff);	
	}
	else
	{
		sprintf(tempbuff, "MoveAbs(%.3f) Axis(%d)\r\n",fpos,iAxis);
		strcat(cmdbuff, tempbuff);	
	}

	//��������ִ�к���
	return ZAux_DirectCommand(Handle, cmdbuff, cmdbuffAck, 2048);
	//return ZAux_Execute(Handle, cmdbuff, cmdbuffAck, 2048);
}


void Ctest_UserSubDlg::OnBnClickedGosub()			//�����Զ�SUB
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iret = 0;
	if(NULL != g_handle)
	{
		iret = Func_AxisMove(g_handle,0,50,1000,100,0);		//��0 ���ٶ�50���ٶ�1000 ����˶�100
		CString str;
		str.Format(_T("%d"), iret);
		SetDlgItemTextA(IDC_RETURN,str);
	}

}


void Ctest_UserSubDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(NULL != g_handle)
	{
		float Axisdpos = 0;
		int iret = ZAux_Direct_GetDpos(g_handle,0,&Axisdpos);
		CString str;
		str.Format(_T("��0���꣺%.3f"), Axisdpos);
		SetDlgItemTextA(IDC_AXISDPOS,str);
	}
	CDialogEx::OnTimer(nIDEvent);
}
