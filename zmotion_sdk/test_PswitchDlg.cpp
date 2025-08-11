
// test_PswitchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test_Pswitch.h"
#include "test_PswitchDlg.h"
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


// Ctest_PswitchDlg �Ի���




Ctest_PswitchDlg::Ctest_PswitchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_PswitchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_AxisNum = 0;
	m_PSO_dir = -1;
	m_POS_out = 0;
	m_End_Pos = 5000.0f;
	m_Timer_Num = 1;
	m_POS_EndTable = 10;
	m_Start_Pos = 0.0f;
	m_POS_StartTable = 0;
	m_Timer_Valid = 5000;
	m_Timer_Cycle = 10000;
	m_POS_OutStatus = 1;
	m_POS_IfOpen = TRUE;
	m_Timer_IfOpen = TRUE;
	m_Regist_IfOpen = FALSE;
	iTotalPoint = 1000;
	m_RegistAxis = 1;
	m_RegistCount = 0;
	RegistMode = 1;
}

void Ctest_PswitchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AXIS, m_AxisNum);
	DDV_MinMaxInt(pDX, m_AxisNum, 0, 64);
	DDX_Text(pDX, IDC_EDIT_DIR, m_PSO_dir);
	DDX_Text(pDX, IDC_EDIT_OUT, m_POS_out);
	DDX_Text(pDX, IDC_END_POS, m_End_Pos);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Timer_Num);
	DDX_Text(pDX, IDC_END_TABLE, m_POS_EndTable);
	DDX_Text(pDX, IDC_START_POS, m_Start_Pos);
	DDX_Text(pDX, IDC_START_TABLE, m_POS_StartTable);
	DDX_Text(pDX, IDC_VALID_TIMER, m_Timer_Valid);
	DDX_Text(pDX, IDC_CYCLE_TIMER, m_Timer_Cycle);
	DDX_Radio(pDX, IDC_TIMER_OPEN, m_Timer_IfOpen);
	DDX_Radio(pDX, IDC_RADIO_OPEN, m_POS_IfOpen);
	DDX_Text(pDX, IDC_OUT_STATUS, m_POS_OutStatus);
	DDX_Control(pDX, IDC_POSLIST, m_PosList);
	DDX_Control(pDX, IDC_PEDIT, m_EDIT);
	DDX_Control(pDX, IDC_REGIST_MODE, m_RegistMode);
	DDX_Text(pDX, IDC_EDIT_AXIS2, m_RegistAxis);
	DDX_Control(pDX, IDC_REGIST_LIST, m_RegistList);
}

BEGIN_MESSAGE_MAP(Ctest_PswitchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_IPLIST, &Ctest_PswitchDlg::OnCbnDropdownIplist)
	ON_BN_CLICKED(IDC_OPEN, &Ctest_PswitchDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &Ctest_PswitchDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_RADIO_OPEN, &Ctest_PswitchDlg::OnBnClickedRadioOpen)
	ON_BN_CLICKED(IDC_RADIO_CLOSE, &Ctest_PswitchDlg::OnBnClickedRadioClose)
	ON_NOTIFY(NM_DBLCLK, IDC_POSLIST, &Ctest_PswitchDlg::OnNMDblclkPoslist)
	ON_EN_KILLFOCUS(IDC_PEDIT, &Ctest_PswitchDlg::OnEnKillfocusPedit)
	ON_BN_CLICKED(IDC_STARTMOVE, &Ctest_PswitchDlg::OnBnClickedStartmove)
	ON_BN_CLICKED(IDC_TIMER_OPEN, &Ctest_PswitchDlg::OnBnClickedTimerOpen)
	ON_BN_CLICKED(IDC_TIMER_CLOSE, &Ctest_PswitchDlg::OnBnClickedTimerClose)
	ON_BN_CLICKED(IDC_STOPMOVE, &Ctest_PswitchDlg::OnBnClickedStopmove)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REGIST_START, &Ctest_PswitchDlg::OnBnClickedRegistStart)
END_MESSAGE_MAP()


// Ctest_PswitchDlg ��Ϣ�������

BOOL Ctest_PswitchDlg::OnInitDialog()
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
	ShowPswtichList();
	m_RegistMode.InsertString(0,"1 Z��������������");
	m_RegistMode.InsertString(1,"2 Z�����½�������");
	m_RegistMode.InsertString(2,"3 R0����������");
	m_RegistMode.InsertString(3,"4 R0�½�������");
	m_RegistMode.InsertString(4,"14 R1����������");
	m_RegistMode.InsertString(5,"15 R1�½�������");
	m_RegistMode.InsertString(6,"18 R2����������");
	m_RegistMode.InsertString(7,"19 R2�½�������");
	m_RegistMode.InsertString(8,"20 R3����������");
	m_RegistMode.InsertString(9,"21 R3�½�������");
	m_RegistMode.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Ctest_PswitchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest_PswitchDlg::OnPaint()
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
HCURSOR Ctest_PswitchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_PswitchDlg::OnCbnDropdownIplist()			//����ˢ��IP
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


void Ctest_PswitchDlg::OnBnClickedOpen()
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


void Ctest_PswitchDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL != g_handle)
	{
		KillTimer(0);						//�ض�ʱ��
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("δ����");
	}
}

void Ctest_PswitchDlg::ShowPswtichList()			//ˢ��λ���б�
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

	m_PosList.InsertColumn(0,_T("���"),LVCFMT_CENTER,70);
	m_PosList.InsertColumn(1,_T("λ��"),LVCFMT_CENTER,100);
	m_PosList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	for (int iItem = 0; iItem < iTotalPoint; iItem++)
	{
		m_PosList.InsertItem(iItem,"");

		CString tempstr;
		tempstr.Format(_T("%d"), iItem);
		m_PosList.SetItemText(iItem,0,tempstr);


		fPointPos[iItem] = (iItem+1) * 100; 
		tempstr.Format(_T("%.3f"), fPointPos[iItem]);
		m_PosList.SetItemText(iItem,1,tempstr);
        
	}
}


void Ctest_PswitchDlg::OnNMDblclkPoslist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//���ѡ�е���
	m_Col = pNMListView->iSubItem;//���ѡ����

	if (m_Row != 0 && m_Col ==1) //���ѡ���;
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


void Ctest_PswitchDlg::OnEnKillfocusPedit()			//�����޸����
{
	CString tempstr;
	m_EDIT.GetWindowText(tempstr);						//�õ��û�������µ�����
	m_PosList.SetItemText(m_Row,m_Col,tempstr);		  //���ñ༭���������

	fPointPos[m_Row] = atof(tempstr);
	m_EDIT.ShowWindow(SW_HIDE); 
}



void Ctest_PswitchDlg::OnBnClickedRadioOpen()		//����λ�ñȽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL != g_handle)
	{
		m_POS_IfOpen = FALSE;
	}
	UpdateData(FALSE);
}


void Ctest_PswitchDlg::OnBnClickedRadioClose()		//�ر�λ�ñȽ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(NULL != g_handle)
	{
		m_POS_IfOpen = TRUE;
	}
	UpdateData(FALSE);
}


void Ctest_PswitchDlg::OnBnClickedTimerOpen()			//��ʱ������
{
	UpdateData(TRUE);
	if(NULL != g_handle)
	{
		UpdateData(TRUE);
		m_Timer_IfOpen = FALSE;
	}
	UpdateData(FALSE);
}


void Ctest_PswitchDlg::OnBnClickedTimerClose()			//��ʱ��ֹͣ
{
	UpdateData(TRUE);
	if(NULL != g_handle)
	{
		UpdateData(TRUE);
		m_Timer_IfOpen = TRUE;
	}
	UpdateData(FALSE);
}

void Ctest_PswitchDlg::OnBnClickedStartmove()			//�˶�
{
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}
	m_RegistCount = 0;
	ShowRegistList();
	UpdateData(TRUE);
	int iret = ZAux_Direct_SetUnits(g_handle, m_AxisNum, 100);
	iret = ZAux_Direct_SetSpeed(g_handle, m_AxisNum, 100);
	iret = ZAux_Direct_SetAccel(g_handle, m_AxisNum, 2000);

	iret = ZAux_Direct_HwPswitch2(g_handle, m_AxisNum, 2, 0, 0, 0, 0, 0, 0);					//���ǰ��ıȽ����ָ��
	if (m_POS_IfOpen == false)           //�Ƚ����һ�κ���Ҫ���µ���HwPswitch           
	{
		iret = ZAux_Direct_SetTable(g_handle, m_POS_StartTable, m_POS_EndTable, fPointPos);     //���Ƚϵ�����TABLE
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("SetTableʧ�� ����ֵ��%d"),iret);
			MessageBox(tempstr);
			return;
		}
		iret = ZAux_Direct_HwPswitch2(g_handle, m_AxisNum, 1, m_POS_out, m_POS_OutStatus, m_POS_StartTable, m_POS_EndTable, m_PSO_dir, 0);
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("HwPswitch2ʧ�� ����ֵ��%d"),iret);
			MessageBox(tempstr);
			return;
		}
	}
	else
	{
		int iret = 0;
		iret = ZAux_Direct_HwPswitch2(g_handle, m_AxisNum, 2, 0, 0, 0, 0, 0, 0);				//����Ƚ����ָ��
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("HwPswitch2ʧ�� ����ֵ��%d"),iret);
			MessageBox(tempstr);
			return;
		}
	}


	if (m_Timer_IfOpen == false)           //          
	{
		iret = ZAux_Direct_HwTimer(g_handle, 2, m_Timer_Cycle, m_Timer_Valid, m_Timer_Num, (m_POS_OutStatus == 0)?1:0, m_POS_out);
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("HwTimerʧ�� ����ֵ��%d"),iret);
			MessageBox(tempstr);
			return;
		}
	}
	else
	{
		iret = ZAux_Direct_HwTimer(g_handle, 0, m_Timer_Cycle, m_Timer_Valid, m_Timer_Num, (m_POS_OutStatus == 0)?1:0, m_POS_out);
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("HwTimerʧ�� ����ֵ��%d"),iret);
			MessageBox(tempstr);
			return;
		}
	}

	ZAux_Trigger(g_handle);
	iret = ZAux_Direct_SetDpos(g_handle, m_AxisNum, 0);
	iret = ZAux_Direct_Single_MoveAbs(g_handle, m_AxisNum, m_Start_Pos);
	iret = ZAux_Direct_Single_MoveAbs(g_handle, m_AxisNum, m_End_Pos); 
}

void Ctest_PswitchDlg::OnBnClickedStopmove()			//ֹͣ
{
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}
	UpdateData(TRUE);
    int iret = ZAux_Direct_Single_Cancel(g_handle, m_AxisNum, 2);          
}


void Ctest_PswitchDlg::OnTimer(UINT_PTR nIDEvent)				//��ʱ��ˢ��
{
	if(NULL != g_handle)
	{	
		CString str;
		if(nIDEvent == 0)
		{
			float Axisdpos = 0;
			int iret = ZAux_Direct_GetDpos(g_handle,m_AxisNum,&Axisdpos);
			str.Format(_T("��%d���꣺%.3f"), m_AxisNum,Axisdpos);
			SetDlgItemTextA(IDC_STATUS_POS,str);		

			uint32 Op_status = 0;
			iret = ZAux_Direct_GetOp(g_handle,m_POS_out,&Op_status);
			str.Format(_T("�����%d״̬���ر�"), m_POS_out);
			if(Op_status == 1 )
			{
				str.Format(_T("�����%d״̬����"), m_POS_out);
			}
			SetDlgItemTextA(IDC_STATUS_OUT,str);	
		}

		if(nIDEvent == 1)
		{
			int iret = 0;
			int MarkStatus = 0;
			float RegistPos;
			if(RegistMode >= 0 && RegistMode < 4)
			{
				iret = ZAux_Direct_GetMark(g_handle,m_RegistAxis,&MarkStatus);	
			}
			else if(RegistMode >= 14 || RegistMode < 16)
			{
				iret = ZAux_Direct_GetMarkB(g_handle,m_RegistAxis,&MarkStatus);	
			}
			else if(RegistMode >= 18 || RegistMode < 20)
			{	
				float tempc;
				iret = ZAux_Direct_GetParam(g_handle,"MARKC",m_RegistAxis,&tempc);	
				MarkStatus = (int)tempc;
			}
			else if(RegistMode >= 20 || RegistMode < 22)
			{
				float tempd;
				iret = ZAux_Direct_GetParam(g_handle,"MARKD",m_RegistAxis,&tempd);	
				MarkStatus = (int)tempd;
			}


			if(MarkStatus == -1)
			{
				if(RegistMode >= 0 && RegistMode < 4)
				{
					iret = ZAux_Direct_GetRegPos(g_handle,m_RegistAxis,&RegistPos);				//��ȡ����λ��
				}
				else if(RegistMode >= 14 || RegistMode < 16)
				{
					iret = ZAux_Direct_GetRegPosB(g_handle,m_RegistAxis,&RegistPos);	
				}
				else if(RegistMode >= 18 || RegistMode < 20)
				{	
					iret = ZAux_Direct_GetParam(g_handle,"REG_POSC",m_RegistAxis,&RegistPos);	
				}
				else if(RegistMode >= 20 || RegistMode < 22)
				{
					iret = ZAux_Direct_GetParam(g_handle,"REG_POSD",m_RegistAxis,&RegistPos);	
				}
				m_RegistList.InsertItem(m_RegistCount,"");
				str.Format(_T("%d"), m_RegistCount);
				m_RegistList.SetItemText(m_RegistCount,0,str);
				str.Format(_T("%.3f"), RegistPos);
				m_RegistList.SetItemText(m_RegistCount,1,str);
					
				m_RegistCount++;
				iret = ZAux_Direct_Regist(g_handle,m_RegistAxis,RegistMode);				//���´�������

			}
			str.Format(_T("���津��״̬��%d ������%d"), MarkStatus,m_RegistCount);
			SetDlgItemTextA(IDC_STATUS_REGIST,str);	
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Ctest_PswitchDlg::OnBnClickedRegistStart()		//����ֹͣ����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NULL == g_handle)
	{
		MessageBox(_T("������δ����"));
		return;
	}
	int iret = 0;
	UpdateData(TRUE);
	if(m_Regist_IfOpen == FALSE)
	{
		m_RegistCount = 0;

		iret = ZAux_Direct_SetAtype(g_handle,m_RegistAxis,4);				//�����Ǳ�������ſ�������

		int ReglistListSel	= ((CComboBox *)GetDlgItem(IDC_REGIST_MODE))->GetCurSel() ;
		if(ReglistListSel >= 0 && ReglistListSel <=3)
		{
			RegistMode =  ReglistListSel +1;
		}
		else if(ReglistListSel == 4 || ReglistListSel ==5)
		{
			RegistMode = 10 + ReglistListSel;
		}
		else if(ReglistListSel > 5 || ReglistListSel < 9)
		{
			RegistMode = 12 + ReglistListSel;		
		}
		iret = ZAux_Direct_Regist(g_handle,m_RegistAxis,RegistMode);
		SetTimer(1,5,NULL);

		m_Regist_IfOpen = TRUE;
		SetDlgItemTextA(IDC_REGIST_START,_T("ֹͣ����"));
		((CComboBox *)GetDlgItem(IDC_REGIST_MODE))->EnableWindow(FALSE);
		ShowRegistList();
		
	}
	else
	{
		KillTimer(1);
		m_Regist_IfOpen = FALSE;
		SetDlgItemTextA(IDC_REGIST_START,_T("��������"));
		((CComboBox *)GetDlgItem(IDC_REGIST_MODE))->EnableWindow(TRUE);
	}
}


void Ctest_PswitchDlg::ShowRegistList()			//ˢ���б�
{
	int cur_item = m_RegistList.GetItemCount();		//���������
	for(int i = 0;i<cur_item;i++)			
	{
		m_RegistList.DeleteItem(0);
	}

	int cur_subitem = m_RegistList.GetHeaderCtrl()->GetItemCount();	//���������
	for(int i = 0;i<cur_subitem;i++)			
	{
		m_RegistList.DeleteColumn(0);
	}

	m_RegistList.InsertColumn(0,_T("���"),LVCFMT_CENTER,70);
	m_RegistList.InsertColumn(1,_T("λ��"),LVCFMT_CENTER,100);
	m_RegistList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
