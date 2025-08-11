
// test_CamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_Cam.h"
#include "test_CamDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "zauxdll2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ZMC_HANDLE       g_handle = NULL;				//控制器链接句柄

#define PI 3.1415926								
#define MAX_POINT 720							//凸轮表点数
float fPointPos[MAX_POINT];

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


// Ctest_CamDlg 对话框




Ctest_CamDlg::Ctest_CamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_CamDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_AxisMaster = 0;
	m_Axis_Slave = 1;
	m_CamMoveSp = 100.0f;
	m_CamMoveDist = 1000.0f;
	m_SynMode = FALSE;
	m_MoveLinkPara[0][0] = 50.0;
	m_MoveLinkPara[0][1] = 100.0;
	m_MoveLinkPara[0][2] = 100.0;
	m_MoveLinkPara[0][3] = 0;

	m_MoveLinkPara[1][0] = 200.0;
	m_MoveLinkPara[1][1] = 200.0;
	m_MoveLinkPara[1][2] = 0;
	m_MoveLinkPara[1][3] = 0;

	m_MoveLinkPara[2][0] = 50.0;
	m_MoveLinkPara[2][1] = 100.0;
	m_MoveLinkPara[2][2] = 0.0;
	m_MoveLinkPara[2][3] = 100;

	m_MoveSLinkPara[0][0] = 50.0;
	m_MoveSLinkPara[0][1] = 100.0;
	m_MoveSLinkPara[0][2] = 0;
	m_MoveSLinkPara[0][3] = 1;

	m_MoveSLinkPara[1][0] = 200.0;
	m_MoveSLinkPara[1][1] = 200.0;
	m_MoveSLinkPara[1][2] = 1.0;
	m_MoveSLinkPara[1][3] = 1.0;

	m_MoveSLinkPara[2][0] = 50.0;
	m_MoveSLinkPara[2][1] = 100.0;
	m_MoveSLinkPara[2][2] = 1.0;
	m_MoveSLinkPara[2][3] = 0.0;
	m_LinkPos = 1000.0f;
	m_LinkSp = 100.0f;
}

void Ctest_CamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABLELIST, m_PosList);
	DDX_Text(pDX, IDC_AXIS_MASTER, m_AxisMaster);
	DDX_Text(pDX, IDC_AXIS_SLAVE, m_Axis_Slave);
	DDX_Text(pDX, IDC_MOVE_SP, m_CamMoveSp);
	DDX_Text(pDX, IDC_MOVE_POS, m_CamMoveDist);

	for(int i = 0;i<4;i++)
	{
		DDX_Text(pDX, IDC_LINKACC_PARA1 + i, m_MoveLinkPara[0][i]);
		DDX_Text(pDX, IDC_LINKSYN_PARA1 + i, m_MoveLinkPara[1][i]);
		DDX_Text(pDX, IDC_LINKDEC_PARA1 + i, m_MoveLinkPara[2][i]);
		DDX_Text(pDX, IDC_SLINKACC_PARA1 + i, m_MoveSLinkPara[0][i]);
		DDX_Text(pDX, IDC_SLINKSYN_PARA1 + i, m_MoveSLinkPara[1][i]);
		DDX_Text(pDX, IDC_SLINKDEC_PARA1 + i, m_MoveSLinkPara[2][i]);
	}
	DDX_Radio(pDX, IDC_SYN_MODE, m_SynMode);
	DDX_Text(pDX, IDC_MOVE_POS2, m_LinkPos);
	DDX_Text(pDX, IDC_MOVE_SP2, m_LinkSp);
}

BEGIN_MESSAGE_MAP(Ctest_CamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_IPLIST, &Ctest_CamDlg::OnCbnDropdownIplist)
	ON_BN_CLICKED(IDC_OPEN, &Ctest_CamDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &Ctest_CamDlg::OnBnClickedClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MOVE_STOP, &Ctest_CamDlg::OnBnClickedMoveStop)
	ON_BN_CLICKED(IDC_MOVE_CAM, &Ctest_CamDlg::OnBnClickedMoveCam)
	ON_BN_CLICKED(IDC_MOVE_SYN, &Ctest_CamDlg::OnBnClickedMoveSyn)
	ON_BN_CLICKED(IDC_STOP_SYN, &Ctest_CamDlg::OnBnClickedStopSyn)
END_MESSAGE_MAP()


// Ctest_CamDlg 消息处理程序

BOOL Ctest_CamDlg::OnInitDialog()
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
	ShowPswtichList();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctest_CamDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest_CamDlg::OnPaint()
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
HCURSOR Ctest_CamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_CamDlg::OnCbnDropdownIplist()				//下拉搜索IP
{
	//自动搜索IP地址
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

		if('\0' == buffer2)
		{
			return;
		}

		//加入
		m_pEthList->AddString(buffer2);
	}

	return;
}


void Ctest_CamDlg::OnBnClickedOpen()					//连接
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
		MessageBox(_T("链接失败"));
		SetWindowText("未链接");
		return;
	}

	SetWindowText("已链接");
	SetTimer(0,100,NULL);
}


void Ctest_CamDlg::OnBnClickedClose()					//断开
{
	if(NULL != g_handle)
	{
		KillTimer(0);						//关定时器
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("未链接");
	}
}


void Ctest_CamDlg::OnTimer(UINT_PTR nIDEvent)			//定时器刷新
{


	CDialogEx::OnTimer(nIDEvent);
}


void Ctest_CamDlg::ShowPswtichList()			//TABLE数据显示
{
	int cur_item = m_PosList.GetItemCount();		//清除所有行
	for(int i = 0;i<cur_item;i++)			
	{
		m_PosList.DeleteItem(0);
	}

	int cur_subitem = m_PosList.GetHeaderCtrl()->GetItemCount();	//清除所有列
	for(int i = 0;i<cur_subitem;i++)			
	{
		m_PosList.DeleteColumn(0);
	}

	m_PosList.InsertColumn(0,_T("编号"),LVCFMT_CENTER,32);
	m_PosList.InsertColumn(1,_T("位置"),LVCFMT_CENTER,120);
	m_PosList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	for (int iItem = 0; iItem < MAX_POINT; iItem++)
	{
		m_PosList.InsertItem(iItem,"");

		CString tempstr;
		tempstr.Format(_T("%d"), iItem);
		m_PosList.SetItemText(iItem,0,tempstr);

		fPointPos[iItem]  = iItem  + 1000 * (1-cos(iItem *PI/180));		//生成从轴位置曲线

		tempstr.Format(_T("%.3f"), fPointPos[iItem]);
		m_PosList.SetItemText(iItem,1,tempstr);

	}
}

void Ctest_CamDlg::OnBnClickedMoveCam()				//启动运动
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	int iret = 0;
	UpdateData(TRUE);
	//设置轴参数
	float AxisSlave_Units = 100;
	iret = ZAux_Direct_SetUnits(g_handle,m_AxisMaster,1000);
	iret = ZAux_Direct_SetUnits(g_handle,m_Axis_Slave,AxisSlave_Units);

	iret = ZAux_Direct_SetTable(g_handle,0,MAX_POINT,fPointPos);														//填写从轴凸轮轨迹到TABLE
	iret = ZAux_Direct_Cambox(g_handle,m_Axis_Slave,0,MAX_POINT-1,AxisSlave_Units,m_CamMoveDist,m_AxisMaster,0,0);		//调用凸轮运动

	ZAux_Trigger(g_handle);
	iret = ZAux_Direct_SetSpeed(g_handle,m_AxisMaster,m_CamMoveSp);									//启动主轴运动
	iret = ZAux_Direct_Single_Move(g_handle,m_AxisMaster,m_CamMoveDist);
}


void Ctest_CamDlg::OnBnClickedMoveStop()			//停止运动
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	int iret = 0;
	UpdateData(TRUE);
	iret = ZAux_Direct_Single_Cancel(g_handle,m_AxisMaster,2);

}


void Ctest_CamDlg::OnBnClickedMoveSyn()					//同步运动
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	int iret = 0;
	UpdateData(TRUE);
	if(m_SynMode == FALSE)							//MOVELINK
	{
		iret = ZAux_Direct_SetMerge(g_handle,m_Axis_Slave,1);
		iret = ZAux_Direct_Movelink(g_handle,m_Axis_Slave,m_MoveLinkPara[0][0],m_MoveLinkPara[0][1],m_MoveLinkPara[0][2],m_MoveLinkPara[0][3],m_AxisMaster,0,0);		//从轴加速运动自同步
		iret = ZAux_Direct_MoveOp(g_handle,m_Axis_Slave,0,1);				//速度同步后打开飞剪
		iret = ZAux_Direct_Movelink(g_handle,m_Axis_Slave,m_MoveLinkPara[1][0],m_MoveLinkPara[1][1],m_MoveLinkPara[1][2],m_MoveLinkPara[1][3],m_AxisMaster,0,0);		//匀速同步跟随段
		iret = ZAux_Direct_MoveOp(g_handle,m_Axis_Slave,0,0);				//关闭飞剪
		iret = ZAux_Direct_Movelink(g_handle,m_Axis_Slave,m_MoveLinkPara[2][0],m_MoveLinkPara[2][1],m_MoveLinkPara[2][2],m_MoveLinkPara[2][3],m_AxisMaster,0,0);		//减速段
	}
	else											//MOVESLINK
	{
		iret = ZAux_Direct_SetMerge(g_handle,m_Axis_Slave,1);
		iret = ZAux_Direct_Moveslink(g_handle,m_Axis_Slave,m_MoveSLinkPara[0][0],m_MoveSLinkPara[0][1],m_MoveSLinkPara[0][2],m_MoveSLinkPara[0][3],m_AxisMaster,0,0);		//从轴加速运动自同步
		iret = ZAux_Direct_MoveOp(g_handle,m_Axis_Slave,0,1);				//速度同步后打开飞剪
		iret = ZAux_Direct_Moveslink(g_handle,m_Axis_Slave,m_MoveSLinkPara[1][0],m_MoveSLinkPara[1][1],m_MoveSLinkPara[1][2],m_MoveSLinkPara[1][3],m_AxisMaster,0,0);		//匀速同步跟随段
		iret = ZAux_Direct_MoveOp(g_handle,m_Axis_Slave,0,0);				//关闭飞剪
		iret = ZAux_Direct_Moveslink(g_handle,m_Axis_Slave,m_MoveSLinkPara[2][0],m_MoveSLinkPara[2][1],m_MoveSLinkPara[2][2],m_MoveSLinkPara[2][3],m_AxisMaster,0,0);		//减速段
	}

	ZAux_Trigger(g_handle);
	iret = ZAux_Direct_SetSpeed(g_handle,m_AxisMaster,m_LinkSp);									//启动主轴运动，模拟触发同步跟随，
	iret = ZAux_Direct_Single_Move(g_handle,m_AxisMaster,m_LinkPos);
}


void Ctest_CamDlg::OnBnClickedStopSyn()					//停止运动
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	int iret = 0;
	UpdateData(TRUE);
	iret = ZAux_Direct_Single_Cancel(g_handle,m_AxisMaster,2);
}
