
// test_AutoUpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test_AutoUp.h"
#include "test_AutoUpDlg.h"
#include "afxdialogex.h"

#include "zauxdll2.h"


ZMC_HANDLE G_ZmcHandle;		//�ɹ����ӵ�HANDLE���
CString ShowMessage;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Ctest_AutoUpDlg �Ի���




Ctest_AutoUpDlg::Ctest_AutoUpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_AutoUpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_AutoUpCode = 1;
	m_AutoUpTime = 1000;
}

void Ctest_AutoUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UPMESSAGE, m_AutoUpMessage);
	DDX_Text(pDX, IDC_EDIT_CODE, m_AutoUpCode);
	DDX_Text(pDX, IDC_EDIT_TIME, m_AutoUpTime);
}

BEGIN_MESSAGE_MAP(Ctest_AutoUpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COMBO1, &Ctest_AutoUpDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BTN_OPEN, &Ctest_AutoUpDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &Ctest_AutoUpDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_DOWN, &Ctest_AutoUpDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_CHECK1, &Ctest_AutoUpDlg::OnBnClickedCheck1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &Ctest_AutoUpDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// Ctest_AutoUpDlg ��Ϣ�������

BOOL Ctest_AutoUpDlg::OnInitDialog()
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
	(GetDlgItem(IDC_UpCmd))->SetWindowText("TOSTR(speed(0),6,3) + \" \"+TOSTR(accel(0),6,3)");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ctest_AutoUpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest_AutoUpDlg::OnPaint()
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
HCURSOR Ctest_AutoUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_AutoUpDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Ctest_AutoUpDlg::OnCbnDropdownCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	m_pEthList = (CComboBox *)GetDlgItem(IDC_COMBO1);
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

		if('\0' == buffer2[0])
		{
			return;
		}

		//����
		m_pEthList->AddString(buffer2);
	}

	return;
}


void Ctest_AutoUpDlg::OnBnClickedBtnOpen()				//���ӿ�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char   buffer[256];
	int32 iresult;

	GetDlgItemText(IDC_COMBO1,buffer,255);
	buffer[255] = '\0';


	//�ж��Ƿ��Ѿ�����
	if(G_ZmcHandle != NULL)
	{
		iresult = ZAux_Close(G_ZmcHandle);
		G_ZmcHandle = 0;
	}

	iresult = ZAux_OpenEth(buffer, &G_ZmcHandle);
	if(ERR_SUCCESS != iresult)
	{
		G_ZmcHandle = NULL;

		MessageBox(_T("����ʧ��"));
		SetWindowText("����ʧ��");
		return;
	}
	SetWindowText("���ӳɹ�");

	//
	CComboBox   *m_pEthList;
	m_pEthList = (CComboBox *)GetDlgItem(IDC_COMBO1);
	if(NULL == m_pEthList)
	{
		return;
	}

	//
	if(CB_ERR != m_pEthList->FindString(0, buffer))
	{
		return;
	}

	//����
	m_pEthList->AddString(buffer);
}


void Ctest_AutoUpDlg::OnBnClickedBtnClose()					//�Ͽ�����
{
	int32 iresult;
	//�ж��Ƿ��Ѿ�����
	if(G_ZmcHandle != NULL)
	{
		iresult = ZAux_Close(G_ZmcHandle);
		G_ZmcHandle = 0;
		SetWindowText("���ӶϿ�");
	}
}


void Ctest_AutoUpDlg::OnBnClickedBtnDown()					//����BAS����
{
	int32 	ret;
	CString m_strOpenFileName;
	CFile	openfile;

	if(NULL == G_ZmcHandle)
	{
		MessageBox(_T("������δ����"));
		return;
	}

	CFileDialog fileopen(true, ".bas", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"Basic Files (*.bas)|*.bas|All Files (*.*)|*.*||", NULL);
	if(fileopen.DoModal()==IDOK)
	{
		m_strOpenFileName = fileopen.GetPathName();
		if(!openfile.Open(fileopen.GetPathName(), openfile.modeRead|openfile.modeNoInherit, NULL))
		{
			this->MessageBox("Open Failed!");
			return ;
		}
		openfile.Close();

		//����BAS����ROM
		ret = ZAux_BasDown(G_ZmcHandle,m_strOpenFileName,1);
		if(ret !=0)
		{
			this->MessageBox("DownLoad File Failed!");
			return ;		
		}

		this->MessageBox("DownLoad File Success!");
	}	
}

void Ctest_AutoUpDlg::AppendTextOut(CString& sTrace)
{
	CString stemp ;
	stemp = sTrace;

	stemp.Replace("\n","\r\n");

	int   nLen   =   m_AutoUpMessage.GetWindowTextLength();

	m_AutoUpMessage.SetLimitText(2000000);

	//������ɾ������
	if(nLen > 1000000)
	{
		//ɾ��5000��
		nLen = m_AutoUpMessage.LineIndex(1000);
		//������
		m_AutoUpMessage.SetSel(0, nLen, true);
		m_AutoUpMessage.ReplaceSel("");

		nLen   =   m_AutoUpMessage.GetWindowTextLength();
	}

	m_AutoUpMessage.SetSel(nLen,   nLen, false);
	m_AutoUpMessage.ReplaceSel(stemp);      
}


/******************** �ص���������******************************************/
void  ZmcAutoCallBaceTest(ZMC_HANDLE handle,int32 itypecode, int32 idatalength, uint8 *pdata)	
{

	ShowMessage.Format("Code:%d Info:%s \r\n", itypecode, (char*)pdata);	

}

void Ctest_AutoUpDlg::OnBnClickedCheck1()				//�����ر������ϱ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iresult= 0 ;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);

	if( pBtn->GetCheck())
	{
		UpdateData(TRUE);
		CString strtemp;
		(GetDlgItem(IDC_UpCmd))->GetWindowText(strtemp);

		char  cmdbuff[2048];
		char  cmdbuffAck[2048];
		sprintf(cmdbuff, "AutoCmdString =%s",strtemp);										//���������ϱ�����
		int iresult =  ZAux_Execute(G_ZmcHandle,cmdbuff,cmdbuffAck,1024);

		iresult = ZAux_SetAutoUpCallBack(G_ZmcHandle,ZmcAutoCallBaceTest);			//�����ϱ��ص�����

		//�޸�BASȫ�ֱ���,
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"AutoUpTime",m_AutoUpTime);				//�ϱ����ʱ��
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"AutoUpCode",m_AutoUpCode);				//�ϱ�������
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"If_EnableAutoUp",1);			//�ϱ�ʹ��		
		SetTimer(1,100,NULL);
	}
	else
	{
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"If_EnableAutoUp",0);			//�ر��ϱ�ʹ��		
		KillTimer(1);
	}


}


void Ctest_AutoUpDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 1)
	{
		if(ShowMessage.GetLength() > 0)
		{
			AppendTextOut(ShowMessage);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Ctest_AutoUpDlg::OnBnClickedBtnClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowMessage.Empty();
	SetDlgItemText(IDC_UPMESSAGE,ShowMessage);
}
