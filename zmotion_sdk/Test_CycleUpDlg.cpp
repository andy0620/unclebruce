
// Test_CycleUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test_CycleUp.h"
#include "Test_CycleUpDlg.h"
#include "afxdialogex.h"


#include "zauxdll2.h"


ZMC_HANDLE G_ZmcHandle;		//成功连接的HANDLE句柄

CString ShowMessage;
char Str_CycleCmd[1000];	
int ifirsttimeus = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTest_CycleUpDlg 对话框




CTest_CycleUpDlg::CTest_CycleUpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTest_CycleUpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_CyclePort = 0;
	m_CycleTime = 10;


	for(int i = 0 ;i<3;i++)
	{
		m_CyclePara[i]=i;
		m_CycleParaStart[i] = 0;
		m_CycleParaNum[i] = 5;
		m_CycleParaEnAble[i] = true;
	}
	m_CycleCount = 0;
}

void CTest_CycleUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_START, m_If_StartUp);
	DDX_Text(pDX, IDC_EDIT_PORT, m_CyclePort);
	DDX_Text(pDX, IDC_EDIT_TIME, m_CycleTime);

	for(int i = 0 ;i<3;i++)
	{
		DDX_CBIndex(pDX, IDC_PARALIST1+i*4, m_CyclePara[i]);
		DDX_Text(pDX, IDC_START1+i*4, m_CycleParaStart[i]);
		DDX_Text(pDX, IDC_PARALEN1+i*4, m_CycleParaNum[i]);
		DDX_Check(pDX, IDC_CYCLE_ENABLE1+i*4, m_CycleParaEnAble[i]);
	}



	DDX_Text(pDX, IDC_EDIT_COUNT, m_CycleCount);
	DDX_Control(pDX, IDC_SHOWMESSAGE, m_CycleMessages);
}

BEGIN_MESSAGE_MAP(CTest_CycleUpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COMBO1, &CTest_CycleUpDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CTest_CycleUpDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CTest_CycleUpDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BUTTON1, &CTest_CycleUpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_CycleUp, &CTest_CycleUpDlg::OnBnClickedBtnCycleup)
	ON_BN_CLICKED(IDC_CHECK_START, &CTest_CycleUpDlg::OnBnClickedCheckStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTest_CycleUpDlg 消息处理程序

BOOL CTest_CycleUpDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTest_CycleUpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTest_CycleUpDlg::OnPaint()
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
HCURSOR CTest_CycleUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//下拉搜索IP
void CTest_CycleUpDlg::OnCbnDropdownCombo1()
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

	m_pEthList = (CComboBox *)GetDlgItem(IDC_COMBO1);
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


//连接控制器
void CTest_CycleUpDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	char   buffer[256];
	int32 iresult;

	GetDlgItemText(IDC_COMBO1,buffer,255);
	buffer[255] = '\0';


	//判断是否已经连接
	if(G_ZmcHandle != NULL)
	{
		iresult = ZAux_Close(G_ZmcHandle);
		G_ZmcHandle = 0;
	}

	iresult = ZAux_OpenEth(buffer, &G_ZmcHandle);
	if(ERR_SUCCESS != iresult)
	{
		G_ZmcHandle = NULL;

		MessageBox(_T("连接失败"));
		SetWindowText("连接失败");
		return;
	}
	SetWindowText("连接成功");

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

	//加入
	m_pEthList->AddString(buffer);
}

//断开控制器
void CTest_CycleUpDlg::OnBnClickedBtnClose()
{
	int32 iresult;
	//判断是否已经连接
	if(G_ZmcHandle != NULL)
	{
		iresult = ZAux_Close(G_ZmcHandle);
		G_ZmcHandle = 0;
		SetWindowText("连接断开");
	}
}

//清空消息
void CTest_CycleUpDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowMessage.Empty();
	SetDlgItemText(IDC_SHOWMESSAGE,ShowMessage);

	m_CycleCount = 0;
	UpdateData(false);			//刷新显示
}

//强制上报一次
void CTest_CycleUpDlg::OnBnClickedBtnCycleup()
{
	if(NULL == G_ZmcHandle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}

	UpdateData(true);	
	int iret = ZAux_CycleUpForceOnce(G_ZmcHandle, m_CyclePort);
	if(ERR_SUCCESS != iret)
	{
		MessageBox(_T("周期上报刷新失败！"));
		return;
	}
}


//开启关闭上报
void CTest_CycleUpDlg::OnBnClickedCheckStart()
{
	if(NULL == G_ZmcHandle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}

	CString tempstr;
	UpdateData(true);	
	int iret = 0;
	if(m_If_StartUp)				//开启上报
	{
		GetCycleStr();
		iret = ZAux_CycleUpEnable(G_ZmcHandle,m_CyclePort,m_CycleTime,Str_CycleCmd);
		if(ERR_SUCCESS != iret)
		{
			tempstr.Format("周期上报打开失败！错误码：%d 命令：%s\r\n",iret,Str_CycleCmd);
			AppendTextOut(tempstr);
			return;
		}
		tempstr.Format("周期上报开始！ 命令：%s\r\n",Str_CycleCmd);
		AppendTextOut(tempstr);
		ifirsttimeus = GetTickCount();
		SetTimer(1,1,NULL);
	}
	else
	{
		m_CycleCount = ZAux_CycleUpGetRecvTimes(G_ZmcHandle,m_CyclePort);
		iret = ZAux_CycleUpDisable(G_ZmcHandle,m_CyclePort);
		if(ERR_SUCCESS != iret)
		{
			tempstr.Format("周期上报关闭失败！错误码：%d \r\n",iret);
			AppendTextOut(tempstr);
			return;
		}
		tempstr.Format("周期上报关闭-上报用时:%dms, 上报次数:%d ,平均时间：%.3fms\r\n",(GetTickCount() - ifirsttimeus),m_CycleCount,(float)(GetTickCount() - ifirsttimeus)/m_CycleCount);
		AppendTextOut(tempstr);
		KillTimer(1);
	}
}

//获取上报参数
void CTest_CycleUpDlg::GetCycleStr()
{

	memset(Str_CycleCmd,0,sizeof(Str_CycleCmd));
	CString TempString = "";
	int ilen = 0;

	if(m_CycleParaEnAble[0])
	{
		switch(m_CyclePara[0])
		{
			case 0:				//AXISSTATUS
				TempString.Format("AXISSTATUS(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 1:				//DPOS		
				TempString.Format("DPOS(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 2:				//IDLE		
				TempString.Format("IDLE(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 3:				//IN	
				TempString.Format("IN(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 4:				//MODBUS_REG
				TempString.Format("MODBUS_REG(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 5:				//MPOS	
				TempString.Format("MPOS(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 6:				//OP	
				TempString.Format("OP(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			case 7:				//TABLE	
				TempString.Format("TABLE(%d,%d),",m_CycleParaStart[0],m_CycleParaNum[0]);
				break;
			default:
				break;
		}
	}

	ilen += TempString.GetLength();
	memcpy(Str_CycleCmd,TempString.GetBuffer(0),TempString.GetLength()*sizeof(TCHAR));

	if(m_CycleParaEnAble[1])
	{
		switch(m_CyclePara[1])
		{
		case 0:				//AXISSTATUS
			TempString.Format("AXISSTATUS(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 1:				//DPOS		
			TempString.Format("DPOS(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 2:				//IDLE		
			TempString.Format("IDLE(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 3:				//IN	
			TempString.Format("IN(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 4:				//MODBUS_REG
			TempString.Format("MODBUS_REG(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 5:				//MPOS	
			TempString.Format("MPOS(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 6:				//OP	
			TempString.Format("OP(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		case 7:				//TABLE	
			TempString.Format("TABLE(%d,%d),",m_CycleParaStart[1],m_CycleParaNum[1]);
			break;
		default:
			break;
		}
	}


	if((ilen + TempString.GetLength()) < 1000)
	{
		memcpy(&Str_CycleCmd[ilen],TempString.GetBuffer(0),TempString.GetLength()*sizeof(TCHAR));
		ilen += TempString.GetLength();
	}


	if(m_CycleParaEnAble[2])
	{
		switch(m_CyclePara[2])
		{
		case 0:				//AXISSTATUS
			TempString.Format("AXISSTATUS(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 1:				//DPOS		
			TempString.Format("DPOS(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 2:				//IDLE		
			TempString.Format("IDLE(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 3:				//IN	
			TempString.Format("IN(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 4:				//MODBUS_REG
			TempString.Format("MODBUS_REG(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 5:				//MPOS	
			TempString.Format("MPOS(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 6:				//OP	
			TempString.Format("OP(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		case 7:				//TABLE	
			TempString.Format("TABLE(%d,%d)",m_CycleParaStart[2],m_CycleParaNum[2]);
			break;
		default:
			break;
		}
	}

	if((ilen + TempString.GetLength()) < 1000)
	{
		memcpy(&Str_CycleCmd[ilen],TempString.GetBuffer(0),TempString.GetLength()*sizeof(TCHAR));
		ilen += TempString.GetLength();
	}

}



//定时器刷新
void CTest_CycleUpDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString tempstr;
	int iret = 0;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		iret = ZAux_CycleUpGetRecvTimes(G_ZmcHandle,m_CyclePort);
		if(iret != m_CycleCount)
		{
			tempstr.Format("%d",iret);
			(GetDlgItem(IDC_EDIT_COUNT))->SetWindowText(tempstr);
			GetCycleInfo();
			m_CycleCount=iret;
		}

	}
	CDialogEx::OnTimer(nIDEvent);
}

//获取上报结果
void CTest_CycleUpDlg::GetCycleInfo()
{
	CString ParaString = "";
	CString TempString = "";
	CString ShowString = "";
	int iret = 0;
	int ival = 0;

	for(int inum=0;inum<3;inum++)
	{
		ShowString ="";
		if(m_CycleParaEnAble[inum])
		{
			switch(m_CyclePara[inum])
			{
			case 0:				//AXISSTATUS
				ParaString = "AXISSTATUS";
				break;
			case 1:				//DPOS		
				ParaString = "DPOS";
				break;
			case 2:				//IDLE		
				ParaString = "IDLE";
				break;
			case 3:				//IN	
				ParaString = "IN";
				break;
			case 4:				//MODBUS_REG
				ParaString = "MODBUS_REG";
				break;
			case 5:				//MPOS	
				ParaString = "MPOS";
				break;
			case 6:				//OP	
				ParaString = "OP";
				break;
			case 7:				//TABLE	
				ParaString = "TABLE";
				break;
			default:
				break;
			}

			ShowString += ParaString;
			for(int i =0;i<m_CycleParaNum[inum];i++ )
			{
				iret = ZAux_CycleUpReadBuffInt(G_ZmcHandle,m_CyclePort,ParaString,m_CycleParaStart[inum] +i,&ival);				//获取周期上报信息
				if(ERR_SUCCESS != iret)
				{
					MessageBox(_T("周期上报读取失败！"));
					return;
				}
				
				TempString.Format(" %d",ival);
				ShowString +=TempString;
			}
			ShowString +="\r\n";
			AppendTextOut(ShowString);
		}
	}

}


void CTest_CycleUpDlg::AppendTextOut(CString& sTrace)
{
	CString stemp ;
	stemp = sTrace;

	stemp.Replace("\n","\r\n");

	int   nLen   =   m_CycleMessages.GetWindowTextLength();

	m_CycleMessages.SetLimitText(2000000);

	//过大则删除部分
	if(nLen > 1000000)
	{
		//删除5000行
		nLen = m_CycleMessages.LineIndex(1000);
		//不滚动
		m_CycleMessages.SetSel(0, nLen, true);
		m_CycleMessages.ReplaceSel("");

		nLen   =   m_CycleMessages.GetWindowTextLength();
	}

	m_CycleMessages.SetSel(nLen,   nLen, false);
	m_CycleMessages.ReplaceSel(stemp);      
}
