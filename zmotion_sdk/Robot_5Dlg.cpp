
// Robot_5Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Robot_5.h"
#include "Robot_5Dlg.h"
#include "afxdialogex.h"

#include "zauxdll2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ZMC_HANDLE G_CardNum;		//�ɹ����ӵ�HANDLE���

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


// CRobot_5Dlg �Ի���




CRobot_5Dlg::CRobot_5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRobot_5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Robot_Para[0] = 10.0;
	Robot_Para[1] = 10000.0;
	Robot_Para[2] = 10000.0;
	Robot_Para[3] = 10000.0;

	for(int i =0;i<12;i++)
	{
		 Axis_Speed[i] = 100;
		 Axis_Acc[i] = 1000;
	}
}

void CRobot_5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for(int i =0;i<4;i++)
	{
		DDX_Text(pDX, IDC_ROBOTPARA1+i, Robot_Para[i]);
	}

	for(int i =0;i<3;i++)
	{
		DDX_Text(pDX, IDC_J0_SPEED+i, Axis_Speed[i]);
		DDX_Text(pDX, IDC_J0_ACC+i, Axis_Acc[i]);

		DDX_Text(pDX, IDC_X_SPEED+i, Axis_Speed[6+i]);
		DDX_Text(pDX, IDC_X_ACC+i, Axis_Acc[6+i]);
	}
}

BEGIN_MESSAGE_MAP(CRobot_5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COM_LIST, &CRobot_5Dlg::OnCbnDropdownComList)
	ON_BN_CLICKED(IDC_COM_OPEN, &CRobot_5Dlg::OnBnClickedComOpen)
	ON_CBN_DROPDOWN(IDC_IPLIST, &CRobot_5Dlg::OnCbnDropdownIplist)
	ON_BN_CLICKED(IDC_ETH_OPEN, &CRobot_5Dlg::OnBnClickedEthOpen)
	ON_BN_CLICKED(IDC_CLOSE_CONNET, &CRobot_5Dlg::OnBnClickedCloseConnet)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ROBOT_FRAME, &CRobot_5Dlg::OnBnClickedRobotFrame)
	ON_BN_CLICKED(IDC_ROBOT_INIT, &CRobot_5Dlg::OnBnClickedRobotInit)
	ON_BN_CLICKED(IDC_ROBOT_REFRAME, &CRobot_5Dlg::OnBnClickedRobotReframe)
END_MESSAGE_MAP()


// CRobot_5Dlg ��Ϣ�������

BOOL CRobot_5Dlg::OnInitDialog()
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
	Robot_Status = 0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRobot_5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRobot_5Dlg::OnPaint()
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
HCURSOR CRobot_5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CRobot_5Dlg::GetNumFromText(int nid)
{
	char   buffer[256];

	GetDlgItemTextA(nid,buffer,255);
	buffer[255] = '\0';

	return atoi(buffer);
}

void CRobot_5Dlg::SetNumToText(int nid, int inum)
{
	CString  stemp;
	stemp.Format("%d", inum);
	SetDlgItemText(nid,stemp);
	return;
}

//��������COM��
void CRobot_5Dlg::OnCbnDropdownComList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#define MAX_CONNECTES 49    
	uint8 i, icomid, ivalid;
	HANDLE _hCommHandle;//���ھ��
	int32 iresult;
	int index, lastindex;

	CString Comname;
	CComboBox	*m_pComList;

	m_pComList = (CComboBox	*)GetDlgItem(IDC_COM_LIST);
	if(NULL == m_pComList)
	{
		return;
	}

	lastindex = m_pComList->GetCurSel();
	if(CB_ERR == lastindex)
	{
		lastindex = 0;  //ȱʡѡ���һ��
	}

	//m_pComList->ResetContent();

	//����ˢ�´����б�, ���Բ�ɾ��ԭ����
	for(i =0; i < MAX_CONNECTES; i++)
	{
		icomid=i+1;
		Comname.Format("%d",icomid);
		//
		if(CB_ERR != m_pComList->FindString(0, Comname))
		{
			continue;
		}

		Comname.Format("\\\\.\\COM%d",icomid);


		//
		_hCommHandle = ::CreateFile(
			Comname,
			GENERIC_READ,
			FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			0,	
			NULL
			);

		if(_hCommHandle != INVALID_HANDLE_VALUE)
		{
			Comname.Format("%d",icomid);
			index = m_pComList->AddString(Comname);

			CloseHandle(_hCommHandle);
		}

	}

	index = m_pComList->GetCurSel();
	if(CB_ERR == index && (CB_ERR != lastindex))
	{
		m_pComList->SetCurSel(lastindex);
	}
}

//COM�����ӿ�����
void CRobot_5Dlg::OnBnClickedComOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int32 iresult;
	uint8 icomid;
	CString comstring;

	icomid = GetNumFromText(IDC_COM_LIST);

	comstring.Format("COM%d", icomid);		//COM������
	//�жϵ�ǰID�Ƿ��Ѿ�����

	//�ж��Ƿ��Ѿ�����
	if(G_CardNum != NULL)
	{
		iresult = ZAux_Close(G_CardNum);
		G_CardNum = 0;
	}
	iresult = ZAux_OpenCom(icomid, &G_CardNum);
	if(ERR_SUCCESS != iresult)
	{

		MessageBox(_T("����ʧ��"));
		SetWindowText(_T("����ʧ��"));
		return;		
	}

	SetWindowText(_T("���ӳɹ�"));
	SetTimer(0,100,NULL);
	OnBnClickedRobotInit();


	CString Comname;
	CComboBox   *m_pComList;

	m_pComList = (CComboBox *)GetDlgItem(IDC_COM_LIST);
	if(NULL == m_pComList)
	{
		return;
	}

	Comname.Format("%d",icomid);
	//
	if(CB_ERR != m_pComList->FindString(0, Comname))
	{
		return;
	}
	//����
	m_pComList->AddString(Comname);
}

//����IP
void CRobot_5Dlg::OnCbnDropdownIplist()
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

		if('\0' == buffer2[0])
		{
			return;
		}

		//����
		m_pEthList->AddString(buffer2);
	}

	return;
}

//��̫�����ӿ�����
void CRobot_5Dlg::OnBnClickedEthOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char   buffer[256];
	int32 iresult;

	GetDlgItemText(IDC_IPLIST,buffer,255);
	buffer[255] = '\0';

	//�ж��Ƿ��Ѿ�����
	if(G_CardNum != NULL)
	{
		iresult = ZAux_Close(G_CardNum);
		G_CardNum = 0;
	}

	iresult = ZAux_OpenEth(buffer, &G_CardNum);
	if(ERR_SUCCESS != iresult)
	{
		G_CardNum = NULL;

		MessageBox(_T("����ʧ��"));
		SetWindowText(_T("����ʧ��"));
		return;
	}
	SetWindowText(_T("���ӳɹ�"));
	SetTimer(0,100,NULL);
	OnBnClickedRobotInit();

	//
	CComboBox   *m_pEthList;
	m_pEthList = (CComboBox *)GetDlgItem(IDC_IPLIST);
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

//�Ͽ�����
void CRobot_5Dlg::OnBnClickedCloseConnet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int32 iresult;
	//�ж��Ƿ��Ѿ�����
	if(G_CardNum != NULL)
	{
		iresult = ZAux_Close(G_CardNum);
		G_CardNum = 0;
		SetWindowText(_T("���ӶϿ�"));
	}
}


//��ʱ��ˢ����Ϣ
void CRobot_5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(G_CardNum !=NULL)
	{
		int iret = 0;
		float fDpos[12];
		int   iAxisMtype[2];
		iret = ZAux_Direct_GetAllAxisPara(G_CardNum,"dpos",12,fDpos);
		iret = ZAux_Direct_GetMtype(G_CardNum,0,&iAxisMtype[0]);
		iret = ZAux_Direct_GetMtype(G_CardNum,6,&iAxisMtype[1]);

		CString tempStr;
		tempStr.Format("J0:%.1f\t J1:%.1f\t J2:%.1f\t",fDpos[0],fDpos[1],fDpos[2]);
		GetDlgItem(IDC_J_POS)->SetWindowText(tempStr); //��ʾ���ؼ�

		tempStr.Format("X:%.1f\t Y:%.1f\t R:%.1f\t",fDpos[6],fDpos[7],fDpos[8]);
		GetDlgItem(IDC_W_POS)->SetWindowText(tempStr); //��ʾ���ؼ�

		if(iAxisMtype[0] == 33)
		{
			tempStr = "���״̬";
			for(int i = 0;i<6;i++)
			{
				GetDlgItem(IDC_J0_FWD+i)->EnableWindow(FALSE);	
				GetDlgItem(IDC_X_FWD+i)->EnableWindow(TRUE);	
			}
			Robot_Status = 1;
		}
		else if(iAxisMtype[1] == 34)
		{
			tempStr = "����״̬";	
			for(int i = 0;i<6;i++)
			{
				GetDlgItem(IDC_J0_FWD+i)->EnableWindow(TRUE);	
				GetDlgItem(IDC_X_FWD+i)->EnableWindow(FALSE);	
			}
			Robot_Status = 2;
		}
		else
		{
			tempStr = "δӳ��";		
			for(int i = 0;i<6;i++)
			{
				GetDlgItem(IDC_J0_FWD+i)->EnableWindow(TRUE);	
				GetDlgItem(IDC_X_FWD+i)->EnableWindow(TRUE);	
			}
			Robot_Status = 0;
		}

		GetDlgItem(IDC_ROBOT_STATUS)->SetWindowText(tempStr); //��ʾ���ؼ�
	}

	CDialogEx::OnTimer(nIDEvent);
}

//�����޸Ļ�е�ֲ���
void CRobot_5Dlg::OnBnClickedRobotInit()
{
	if(G_CardNum == NULL)
	{
		return;
	}

	UpdateData(TRUE);
	int iret = 0;
	int iaxis = 0;

	int jAxis_Units[3] = {100,100,100};
	int VirAxis_Units[3] = {1000,1000,100};			//����XY���ó�1000��ʾ��ȷ��0.001MM����ת����ʵ��R��һ��

	//��ʼ���ؽ������
	for(int i =0;i<3;i++ )
	{
		iret = ZAux_Direct_SetAtype(G_CardNum,i,1);
		iret = ZAux_Direct_SetUnits(G_CardNum,i,jAxis_Units[i]);
		iret = ZAux_Direct_SetClutchRate(G_CardNum,i,0);				//ʹ�ùؽ�����ٶȺͼ��ٶ����� �������ٶ�
	}

	//��ʼ�����������
	for(int i =0;i<3;i++ )
	{
		iaxis = i + 6;
		iret = ZAux_Direct_SetAtype(G_CardNum,iaxis,0);					//���ó�������
		iret = ZAux_Direct_SetUnits(G_CardNum,iaxis,VirAxis_Units[i]);
	}

	//���û�е������TABLE
	iret = ZAux_Direct_SetTable(G_CardNum,0,4,Robot_Para);

}

//��е�����
void CRobot_5Dlg::OnBnClickedRobotFrame()
{
	if(G_CardNum == NULL)
	{
		return;
	}


	int iret = 0;
	int jAxis_List[3] = {0,1,2};
	int VirAxis_List[3] = {6,7,8};

	if(Robot_Status != 1)		//��ǰ�������״̬
	{
		iret = ZAux_Direct_Connframe(G_CardNum,3,jAxis_List,5,0,3,VirAxis_List);
	}
}

//��е������
void CRobot_5Dlg::OnBnClickedRobotReframe()
{
	if(G_CardNum == NULL)
	{
		return;
	}

	int iret = 0;
	int jAxis_List[3] = {0,1,2};
	int VirAxis_List[3] = {6,7,8};

	if(Robot_Status == 1)		//��ǰ�����״̬
	{
		iret = ZAux_Direct_Connreframe(G_CardNum,3,VirAxis_List,5,0,3,jAxis_List);
	}

}

//MFC��Ϣ����,����㶯
BOOL CRobot_5Dlg::PreTranslateMessage(MSG* pMsg)
{
	int iresult;

	if(pMsg->message == WM_LBUTTONDOWN)
	{
		UpdateData(TRUE);
		int iaxis = 0;
		for(int i =0 ;i<3;i++)
		{	
			if(pMsg->hwnd == GetDlgItem(IDC_J0_FWD + i)->m_hWnd)		//�ؽ�������
			{
				iaxis = i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,1);
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_X_FWD + i)->m_hWnd)	//����������
			{
				iaxis = 6+i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,1);	
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_J0_REV + i)->m_hWnd)	//�ؽ���������
			{
				iaxis = i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,-1);	
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_X_REV + i)->m_hWnd)	//���⸺����
			{
				iaxis = 6+i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,-1);	
			}
		}

	}

	if(pMsg->message == WM_LBUTTONUP)			//��ť�ɿ�
	{
		int iaxis = 0;
		for(int i =0 ;i<3;i++)
		{	
			int iaxis = 0;
			for(int i =0 ;i<3;i++)
			{	
				if(pMsg->hwnd == GetDlgItem(IDC_J0_FWD + i)->m_hWnd)		//�ؽ�������
				{
					iaxis = i;
				}
				else if(pMsg->hwnd == GetDlgItem(IDC_X_FWD + i)->m_hWnd)	//����������
				{
					iaxis = 6+i;
				}
				else if(pMsg->hwnd == GetDlgItem(IDC_J0_REV + i)->m_hWnd)	//�ؽ���������
				{
					iaxis = i;
				}
				else if(pMsg->hwnd == GetDlgItem(IDC_X_REV + i)->m_hWnd)	//���⸺����
				{
					iaxis = 6+i;
				}
			}

				iresult = ZAux_Direct_Single_Cancel(G_CardNum,iaxis,2);	
				if(iresult != ERR_OK)
				{
					iresult = ZAux_Direct_Single_Cancel(G_CardNum,iaxis,2);		
				}	
		}
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}
