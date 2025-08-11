
// test_PitchsetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test_Pitchset.h"
#include "test_PitchsetDlg.h"
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


// Ctest_PitchsetDlg �Ի���




Ctest_PitchsetDlg::Ctest_PitchsetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_PitchsetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_StartPos = 0.0f;
	m_DisOne = 10.0f;
	m_TableStart = 0;
	m_MaxPoint = 20;
	m_Enable = 0;
	m_iAxis = 0;
	m_accel = 1000.0f;
	m_creep = 10.0f;
	m_Decel = 0.0f;
	m_DatumIn = 0;
	m_DelayTime = 1000;
	m_speed = 100.0f;
	m_Units = 1.0f;
	m_homeMode = 4;
}

void Ctest_PitchsetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POSLIST, m_PosList);
	DDX_Text(pDX, IDC_EDIT_StartPos1, m_StartPos);
	DDX_Text(pDX, IDC_EDIT_StepDist, m_DisOne);
	DDX_Text(pDX, IDC_EDIT_TabStart, m_TableStart);
	DDX_Text(pDX, IDC_EDIT_TotalNum, m_MaxPoint);
	DDX_Check(pDX, IDC_ENABLE_PITCH, m_Enable);
	DDX_Control(pDX, IDC_PEDIT, m_EDIT);
	DDX_Control(pDX, IDC_RADIO1, m_RadioMode);
	DDX_Text(pDX, IDC_EDIT_AXIS, m_iAxis);
	DDX_Text(pDX, IDC_EDIT_ACC, m_accel);
	DDX_Text(pDX, IDC_EDIT_CREEP, m_creep);
	//  DDX_Control(pDX, IDC_EDIT_DatumIn, m_DatumIn);
	DDX_Text(pDX, IDC_EDIT_DEC, m_Decel);
	DDX_Text(pDX, IDC_EDIT_DatumIn, m_DatumIn);
	DDX_Text(pDX, IDC_EDIT_DELAYTIME, m_DelayTime);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_speed);
	DDX_Text(pDX, IDC_EDIT_UNITS, m_Units);
	DDX_Check(pDX, IDC_IN_INVERT, m_DatumInInvert);
	DDX_Text(pDX, IDC_EDIT_HomeMode, m_homeMode);
	DDX_Check(pDX, IDC_CHECK_DIR, m_MoveDir);
}

BEGIN_MESSAGE_MAP(Ctest_PitchsetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_IPLIST, &Ctest_PitchsetDlg::OnCbnDropdownIplist)
	ON_BN_CLICKED(IDC_OPEN, &Ctest_PitchsetDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &Ctest_PitchsetDlg::OnBnClickedClose)
	ON_NOTIFY(NM_DBLCLK, IDC_POSLIST, &Ctest_PitchsetDlg::OnNMDblclkPoslist)
	ON_EN_KILLFOCUS(IDC_PEDIT, &Ctest_PitchsetDlg::OnEnKillfocusPedit)
	ON_EN_CHANGE(IDC_EDIT_StartPos1, &Ctest_PitchsetDlg::OnEnChangeEditStartpos1)
	ON_EN_CHANGE(IDC_EDIT_TotalNum, &Ctest_PitchsetDlg::OnEnChangeEditTotalnum)
	ON_EN_CHANGE(IDC_EDIT_StepDist, &Ctest_PitchsetDlg::OnEnChangeEditStepdist)
	ON_BN_CLICKED(IDC_ENABLE_PITCH, &Ctest_PitchsetDlg::OnBnClickedEnablePitch)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_AXIS, &Ctest_PitchsetDlg::OnEnChangeEditAxis)
	ON_BN_CLICKED(IDC_BTN_RUN, &Ctest_PitchsetDlg::OnBnClickedBtnRun)
	ON_BN_CLICKED(IDC_BTN_STOP, &Ctest_PitchsetDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_HOME, &Ctest_PitchsetDlg::OnBnClickedBtnHome)
END_MESSAGE_MAP()


// Ctest_PitchsetDlg ��Ϣ�������

BOOL Ctest_PitchsetDlg::OnInitDialog()
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

	for(int i = 0;i<1000;i++)
	{
		fFwdDist[i] = 0;
		fRevDist[i] = 0;
	}

	ShowPosList();
	m_RadioMode.SetCheck(TRUE);
	m_MoveDir =TRUE;
	RunTestFlag = false;
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ctest_PitchsetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest_PitchsetDlg::OnPaint()
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
HCURSOR Ctest_PitchsetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_PitchsetDlg::OnCbnDropdownIplist()			//����ˢ��IP
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


void Ctest_PitchsetDlg::OnBnClickedOpen()
{
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


void Ctest_PitchsetDlg::OnBnClickedClose()
{
	if(NULL != g_handle)
	{
		KillTimer(0);						//�ض�ʱ��
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("δ����");
	}
}


void Ctest_PitchsetDlg::ShowPosList()			//ˢ��λ���б�
{
	int cur_item = m_PosList.GetItemCount();		//���������
	for(int i = 0;i<cur_item;i++)			
	{
		m_PosList.DeleteItem(0);
	}

	int cur_subitem = m_PosList.GetHeaderCtrl()->GetItemCount();	//���������
	for(int i = 0;i<cur_subitem;i++)			
	{
		m_PosList.DeleteColumn(0);
	}

	m_PosList.InsertColumn(0,_T("���"),LVCFMT_CENTER,45);
	m_PosList.InsertColumn(1,_T("λ��"),LVCFMT_CENTER,100);
	m_PosList.InsertColumn(2,_T("���򲹳���"),LVCFMT_CENTER,100);
	m_PosList.InsertColumn(3,_T("���򲹳���"),LVCFMT_CENTER,100);
	m_PosList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	for (int iItem = 0; iItem < m_MaxPoint; iItem++)
	{
		m_PosList.InsertItem(iItem,"");

		CString tempstr;
		tempstr.Format(_T("%d"), iItem);
		m_PosList.SetItemText(iItem,0,tempstr);

		fPointPos[iItem] = m_StartPos + (iItem +1) * m_DisOne; 
		tempstr.Format(_T("%.3f"), fPointPos[iItem]);
		m_PosList.SetItemText(iItem,1,tempstr);

		tempstr.Format(_T("%.0f"), fFwdDist[iItem]);
		m_PosList.SetItemText(iItem,2,tempstr);

		tempstr.Format(_T("%.0f"), fRevDist[iItem]);
		m_PosList.SetItemText(iItem,3,tempstr);
	}
}


void Ctest_PitchsetDlg::OnNMDblclkPoslist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//���ѡ�е���
	m_Col = pNMListView->iSubItem;//���ѡ����

	if (m_Row >= 0 && (m_Col ==2 || m_Col ==3)) //���ѡ���;
	{
		m_PosList.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//��������RECT��
		m_EDIT.SetParent(&m_PosList);//ת������Ϊ�б���е�����
		m_EDIT.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;
		m_EDIT.SetWindowText(m_PosList.GetItemText(m_Row,m_Col));//���������е�ֵ����Edit�ؼ��У�
		m_EDIT.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���
		m_EDIT.SetFocus();//����Edit����
		m_EDIT.ShowCaret();//��ʾ���
		m_EDIT.SetSel(-1);//������ƶ������
	}	
	*pResult = 0;
}


void Ctest_PitchsetDlg::OnEnKillfocusPedit()			//�����޸����
{
	CString tempstr;
	m_EDIT.GetWindowText(tempstr);						//�õ��û�������µ�����
	m_PosList.SetItemText(m_Row,m_Col,tempstr);		  //���ñ༭���������

	if(m_Col == 2)
	{
		fFwdDist[m_Row] = atof(tempstr);
	}
	else if(m_Col ==3)
	{
		fRevDist[m_Row] = atof(tempstr);
	}

	m_EDIT.ShowWindow(SW_HIDE); 
}

void Ctest_PitchsetDlg::OnEnChangeEditStartpos1()
{
	UpdateData(TRUE);
	ShowPosList();
}


void Ctest_PitchsetDlg::OnEnChangeEditTotalnum()
{
	UpdateData(TRUE);
	ShowPosList();
}


void Ctest_PitchsetDlg::OnEnChangeEditStepdist()
{
	UpdateData(TRUE);
	ShowPosList();
}

void Ctest_PitchsetDlg::OnEnChangeEditAxis()
{
	UpdateData(TRUE);
}

void Ctest_PitchsetDlg::OnBnClickedEnablePitch()		//�����رղ���
{
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}

	int iret = 0;
	UpdateData(TRUE);
	if(m_Enable)
	{
		if(m_RadioMode.GetCheck())			//����
		{
			iret = ZAux_Direct_Pitchset(g_handle,m_iAxis,1,m_StartPos,m_MaxPoint,m_DisOne,m_TableStart,fFwdDist);
		}
		else								//˫��
		{
			iret = ZAux_Direct_Pitchset2(g_handle,m_iAxis,1,m_StartPos,m_MaxPoint,m_DisOne,m_TableStart,fFwdDist,m_TableStart+m_MaxPoint,fRevDist);
		}
	}
	else		//�ر��ݾಹ��
	{
			iret = ZAux_Direct_Pitchset(g_handle,m_iAxis,0,m_StartPos,m_MaxPoint,m_DisOne,m_TableStart,fFwdDist);
	}
}


//��ʱ��ˢ��״̬
void Ctest_PitchsetDlg::OnTimer(UINT_PTR nIDEvent)
{
	int iret = 0;
	if(NULL != g_handle)
	{
		if(nIDEvent == 0)
		{
			CString tempstr;
			float fval = 0;
			iret = ZAux_Direct_GetDpos(g_handle,m_iAxis,&fval);

			tempstr.Format(_T("����λ�ã�%.3f"), fval);
			SetDlgItemTextA(IDC_SHOW_DPOS,tempstr);
			
			iret = ZAux_Direct_GetMpos(g_handle,m_iAxis,&fval);
			tempstr.Format(_T("����λ�ã�%.3f"), fval);
			SetDlgItemTextA(IDC_SHOW_MPOS,tempstr);
		}


		if(nIDEvent == 1  && (RunTestFlag == false)) 
		{
			RunTestFlag = true;

			if(m_MoveDir == true)		//�����˶�
			{
				iret = ZAux_Direct_Single_MoveAbs(g_handle,m_iAxis,m_StartPos);
				iret = ZAux_Direct_MoveDelay(g_handle,m_iAxis,m_DelayTime);
				while(AxisIsMoveing(m_iAxis))	//�ȴ����˶�ֹͣ
				{
					MSG  msg; 
					if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE)) 
					{ 
						::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);   
					} 
					if(RunTestFlag == false) 
					{
						KillTimer(1);
						return;
					}
				}

				for(int ipoint = 0;ipoint<m_MaxPoint;)
				{
					iret = ZAux_Direct_Single_MoveAbs(g_handle,m_iAxis,fPointPos[ipoint]);
					iret = ZAux_Direct_MoveDelay(g_handle,m_iAxis,m_DelayTime);
					while(AxisIsMoveing(m_iAxis))		//�ȴ����˶�ֹͣ
					{
						MSG  msg; 
						if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE)) 
						{ 
							::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);   
						} 
						if(RunTestFlag == false) 
						{
							KillTimer(1);
							return;
						}

					}
					if(iret == 0)
					{
						ipoint++; 
					}
				}
			}
			else
			{
				for(int ipoint = m_MaxPoint - 1;ipoint>=0;)
				{
					iret = ZAux_Direct_Single_MoveAbs(g_handle,m_iAxis,fPointPos[ipoint]);
					iret = ZAux_Direct_MoveDelay(g_handle,m_iAxis,m_DelayTime);
					while(AxisIsMoveing(m_iAxis))		//�ȴ����˶�ֹͣ
					{
						MSG  msg; 
						if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE)) 
						{ 
							::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);   
						} 
						if(RunTestFlag == false) 
						{
							KillTimer(1);
							return;
						}
					}
					if(iret == 0)
					{
						ipoint--; 
					}
				}

				iret = ZAux_Direct_Single_MoveAbs(g_handle,m_iAxis,m_StartPos);
				iret = ZAux_Direct_MoveDelay(g_handle,m_iAxis,m_DelayTime);
				while(AxisIsMoveing(m_iAxis))	//�ȴ����˶�ֹͣ
				{
					MSG  msg; 
					if (PeekMessage(&msg,(HWND)NULL, 0, 0, PM_REMOVE)) 
					{ 
						::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);   
					} 
					if(RunTestFlag == false) 
					{
						KillTimer(1);
						return;
					}
				}
			}


			RunTestFlag = false;
			KillTimer(1);

		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

//���Ƿ��˶���
bool  Ctest_PitchsetDlg::AxisIsMoveing(int iaxis)
{
	int AxisIdle = 0;
	ZAux_Direct_GetIfIdle(g_handle,iaxis,&AxisIdle);

	if(AxisIdle == 0) return true;

	return false;

}



//��������
void Ctest_PitchsetDlg::OnBnClickedBtnRun()
{
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}	


	UpdateData(TRUE);

	int iret  = 0;
	iret = ZAux_Direct_SetAtype(g_handle,m_iAxis,4);				//����������  ����+������������
	iret = ZAux_Direct_SetUnits(g_handle,m_iAxis,m_Units);			//�������嵱��
	iret = ZAux_Direct_SetSpeed(g_handle,m_iAxis,m_speed);
	iret = ZAux_Direct_SetAccel(g_handle,m_iAxis,m_accel);
	iret = ZAux_Direct_SetDecel(g_handle,m_iAxis,m_Decel);

	SetTimer(1,1,NULL);				//��ʱ����ȥ�����˶�
}

//ֹͣ����
void Ctest_PitchsetDlg::OnBnClickedBtnStop()
{
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}


	KillTimer(1);
	RunTestFlag = false;	

	int iret  = 0;
	iret = ZAux_Direct_Single_Cancel(g_handle,m_iAxis,3);

}


//���㸴λ
void Ctest_PitchsetDlg::OnBnClickedBtnHome()
{
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}

	UpdateData(TRUE);

	int iret  = 0;
	iret = ZAux_Direct_SetAtype(g_handle,m_iAxis,4);				//����������  ����+������������
	iret = ZAux_Direct_SetUnits(g_handle,m_iAxis,m_Units);			//�������嵱��
	iret = ZAux_Direct_SetSpeed(g_handle,m_iAxis,m_speed);
	iret = ZAux_Direct_SetAccel(g_handle,m_iAxis,m_accel);
	iret = ZAux_Direct_SetDecel(g_handle,m_iAxis,m_Decel);
	iret = ZAux_Direct_SetCreep(g_handle,m_iAxis,m_creep);
	iret = ZAux_Direct_SetDatumIn(g_handle,m_iAxis,m_DatumIn);

	if(m_DatumInInvert)
	{
		iret = ZAux_Direct_SetInvertIn(g_handle,m_DatumIn,0);
	}
	else
	{
		iret = ZAux_Direct_SetInvertIn(g_handle,m_DatumIn,1);
	}

	iret = ZAux_Direct_Single_Datum(g_handle,m_iAxis,m_homeMode);
}

