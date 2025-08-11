
// Robot_5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Robot_5.h"
#include "Robot_5Dlg.h"
#include "afxdialogex.h"

#include "zauxdll2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ZMC_HANDLE G_CardNum;		//成功连接的HANDLE句柄

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRobot_5Dlg 对话框




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


// CRobot_5Dlg 消息处理程序

BOOL CRobot_5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Robot_Status = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRobot_5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

//下拉搜索COM口
void CRobot_5Dlg::OnCbnDropdownComList()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
#define MAX_CONNECTES 49    
	uint8 i, icomid, ivalid;
	HANDLE _hCommHandle;//串口句柄
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
		lastindex = 0;  //缺省选择第一个
	}

	//m_pComList->ResetContent();

	//重新刷新串口列表, 可以不删除原来的
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

//COM口连接控制器
void CRobot_5Dlg::OnBnClickedComOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	int32 iresult;
	uint8 icomid;
	CString comstring;

	icomid = GetNumFromText(IDC_COM_LIST);

	comstring.Format("COM%d", icomid);		//COM口连接
	//判断当前ID是否已经连接

	//判断是否已经连接
	if(G_CardNum != NULL)
	{
		iresult = ZAux_Close(G_CardNum);
		G_CardNum = 0;
	}
	iresult = ZAux_OpenCom(icomid, &G_CardNum);
	if(ERR_SUCCESS != iresult)
	{

		MessageBox(_T("连接失败"));
		SetWindowText(_T("连接失败"));
		return;		
	}

	SetWindowText(_T("连接成功"));
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
	//加入
	m_pComList->AddString(Comname);
}

//搜索IP
void CRobot_5Dlg::OnCbnDropdownIplist()
{
	// TODO: 在此添加控件通知处理程序代码
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

	//从字符串转换过来
	int ipos =0;
	const char * pstring;
	pstring = buffer;

	for(int j= 0; j< 20;j++)
	{
		char buffer2[256];
		buffer2[0] = '\0';

		//跳过空格
		while(' ' == pstring[0])
		{
			pstring++;
		}

		ipos = sscanf(pstring , "%s", &buffer2);
		if(EOF  == ipos)
		{
			break;
		}

		//跳过字符
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

		//加入
		m_pEthList->AddString(buffer2);
	}

	return;
}

//以太网连接控制器
void CRobot_5Dlg::OnBnClickedEthOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	char   buffer[256];
	int32 iresult;

	GetDlgItemText(IDC_IPLIST,buffer,255);
	buffer[255] = '\0';

	//判断是否已经连接
	if(G_CardNum != NULL)
	{
		iresult = ZAux_Close(G_CardNum);
		G_CardNum = 0;
	}

	iresult = ZAux_OpenEth(buffer, &G_CardNum);
	if(ERR_SUCCESS != iresult)
	{
		G_CardNum = NULL;

		MessageBox(_T("连接失败"));
		SetWindowText(_T("连接失败"));
		return;
	}
	SetWindowText(_T("连接成功"));
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

	//加入
	m_pEthList->AddString(buffer);
}

//断开连接
void CRobot_5Dlg::OnBnClickedCloseConnet()
{
	// TODO: 在此添加控件通知处理程序代码
	int32 iresult;
	//判断是否已经连接
	if(G_CardNum != NULL)
	{
		iresult = ZAux_Close(G_CardNum);
		G_CardNum = 0;
		SetWindowText(_T("连接断开"));
	}
}


//定时器刷新消息
void CRobot_5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		GetDlgItem(IDC_J_POS)->SetWindowText(tempStr); //显示到控件

		tempStr.Format("X:%.1f\t Y:%.1f\t R:%.1f\t",fDpos[6],fDpos[7],fDpos[8]);
		GetDlgItem(IDC_W_POS)->SetWindowText(tempStr); //显示到控件

		if(iAxisMtype[0] == 33)
		{
			tempStr = "逆解状态";
			for(int i = 0;i<6;i++)
			{
				GetDlgItem(IDC_J0_FWD+i)->EnableWindow(FALSE);	
				GetDlgItem(IDC_X_FWD+i)->EnableWindow(TRUE);	
			}
			Robot_Status = 1;
		}
		else if(iAxisMtype[1] == 34)
		{
			tempStr = "正解状态";	
			for(int i = 0;i<6;i++)
			{
				GetDlgItem(IDC_J0_FWD+i)->EnableWindow(TRUE);	
				GetDlgItem(IDC_X_FWD+i)->EnableWindow(FALSE);	
			}
			Robot_Status = 2;
		}
		else
		{
			tempStr = "未映射";		
			for(int i = 0;i<6;i++)
			{
				GetDlgItem(IDC_J0_FWD+i)->EnableWindow(TRUE);	
				GetDlgItem(IDC_X_FWD+i)->EnableWindow(TRUE);	
			}
			Robot_Status = 0;
		}

		GetDlgItem(IDC_ROBOT_STATUS)->SetWindowText(tempStr); //显示到控件
	}

	CDialogEx::OnTimer(nIDEvent);
}

//配置修改机械手参数
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
	int VirAxis_Units[3] = {1000,1000,100};			//虚拟XY设置成1000表示精确到0.001MM，旋转轴与实际R轴一致

	//初始化关节轴参数
	for(int i =0;i<3;i++ )
	{
		iret = ZAux_Direct_SetAtype(G_CardNum,i,1);
		iret = ZAux_Direct_SetUnits(G_CardNum,i,jAxis_Units[i]);
		iret = ZAux_Direct_SetClutchRate(G_CardNum,i,0);				//使用关节轴的速度和加速度限制 虚拟轴速度
	}

	//初始化虚拟轴参数
	for(int i =0;i<3;i++ )
	{
		iaxis = i + 6;
		iret = ZAux_Direct_SetAtype(G_CardNum,iaxis,0);					//设置成虚拟轴
		iret = ZAux_Direct_SetUnits(G_CardNum,iaxis,VirAxis_Units[i]);
	}

	//设置机械参数到TABLE
	iret = ZAux_Direct_SetTable(G_CardNum,0,4,Robot_Para);

}

//机械手逆解
void CRobot_5Dlg::OnBnClickedRobotFrame()
{
	if(G_CardNum == NULL)
	{
		return;
	}


	int iret = 0;
	int jAxis_List[3] = {0,1,2};
	int VirAxis_List[3] = {6,7,8};

	if(Robot_Status != 1)		//当前不在逆解状态
	{
		iret = ZAux_Direct_Connframe(G_CardNum,3,jAxis_List,5,0,3,VirAxis_List);
	}
}

//机械手正解
void CRobot_5Dlg::OnBnClickedRobotReframe()
{
	if(G_CardNum == NULL)
	{
		return;
	}

	int iret = 0;
	int jAxis_List[3] = {0,1,2};
	int VirAxis_List[3] = {6,7,8};

	if(Robot_Status == 1)		//当前在逆解状态
	{
		iret = ZAux_Direct_Connreframe(G_CardNum,3,VirAxis_List,5,0,3,jAxis_List);
	}

}

//MFC消息调度,处理点动
BOOL CRobot_5Dlg::PreTranslateMessage(MSG* pMsg)
{
	int iresult;

	if(pMsg->message == WM_LBUTTONDOWN)
	{
		UpdateData(TRUE);
		int iaxis = 0;
		for(int i =0 ;i<3;i++)
		{	
			if(pMsg->hwnd == GetDlgItem(IDC_J0_FWD + i)->m_hWnd)		//关节正向按下
			{
				iaxis = i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,1);
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_X_FWD + i)->m_hWnd)	//虚拟正向按下
			{
				iaxis = 6+i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,1);	
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_J0_REV + i)->m_hWnd)	//关节正负向按下
			{
				iaxis = i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,-1);	
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_X_REV + i)->m_hWnd)	//虚拟负向按下
			{
				iaxis = 6+i;
				iresult = ZAux_Direct_SetSpeed(G_CardNum,iaxis,Axis_Speed[iaxis]);
				iresult = ZAux_Direct_SetAccel(G_CardNum,iaxis,Axis_Acc[iaxis]);
				iresult = ZAux_Direct_Single_Vmove(G_CardNum,iaxis,-1);	
			}
		}

	}

	if(pMsg->message == WM_LBUTTONUP)			//按钮松开
	{
		int iaxis = 0;
		for(int i =0 ;i<3;i++)
		{	
			int iaxis = 0;
			for(int i =0 ;i<3;i++)
			{	
				if(pMsg->hwnd == GetDlgItem(IDC_J0_FWD + i)->m_hWnd)		//关节正向按下
				{
					iaxis = i;
				}
				else if(pMsg->hwnd == GetDlgItem(IDC_X_FWD + i)->m_hWnd)	//虚拟正向按下
				{
					iaxis = 6+i;
				}
				else if(pMsg->hwnd == GetDlgItem(IDC_J0_REV + i)->m_hWnd)	//关节正负向按下
				{
					iaxis = i;
				}
				else if(pMsg->hwnd == GetDlgItem(IDC_X_REV + i)->m_hWnd)	//虚拟负向按下
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
