
// test_UserSubDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_UserSub.h"
#include "test_UserSubDlg.h"
#include "afxdialogex.h"
#include "zauxdll2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ZMC_HANDLE       g_handle = NULL;				//控制器链接句柄


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


// Ctest_UserSubDlg 对话框




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


// Ctest_UserSubDlg 消息处理程序

BOOL Ctest_UserSubDlg::OnInitDialog()
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
	SetWindowText("未链接");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctest_UserSubDlg::OnPaint()
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
HCURSOR Ctest_UserSubDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_UserSubDlg::OnCbnDropdownIplist()
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


void Ctest_UserSubDlg::OnBnClickedOpen()			//控制器连接
{
	// TODO: 在此添加控件通知处理程序代码
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


void Ctest_UserSubDlg::OnBnClickedClose()				//控制器断开
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL != g_handle)
	{
		KillTimer(1);						//关定时器
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("未链接");
	}
}


void Ctest_UserSubDlg::OnBnClickedClear()					//清空显示字符
{
	// TODO: 在此添加控件通知处理程序代码
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

	//过大则删除部分
	if(nLen > 1000000)
	{
		//删除5000行
		nLen = pTraceEidt->LineIndex(1000);
		//不滚动
		pTraceEidt->SetSel(0, nLen, true);
		pTraceEidt->ReplaceSel("");

		nLen   =   pTraceEidt->GetWindowTextLength();
	}

	pTraceEidt->SetSel(nLen,   nLen, false);
	pTraceEidt->ReplaceSel(stemp);      
}

void Ctest_UserSubDlg::OnBnClickedCmd()				//DirectCommand在线命令
{
	// TODO: 在此添加控件通知处理程序代码
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

		//0长直接返回
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
			stemp1.Format("返回错误码：%d\r\n返回字符串：%s \r\n",iresult,cmdbuffAck);
			stemp += stemp1;
			AppendTextOut(stemp);
		}
		else
		{
			CString stemp1;
			CString stemp = ">>";
			stemp += buffer;
			stemp+= "\r\n";
			stemp1.Format("返回错误码：%d \r\n",iresult);
			stemp += stemp1;
			AppendTextOut(stemp);
		}        

		//把命令重新选择住
		CEdit *pedit;
		pedit = (CEdit *)GetDlgItem(IDC_EDIT_CMD);
		pedit->SetSel(0, -1);
	}

	return;
}


void Ctest_UserSubDlg::OnBnClickedCmd1()			//Execute在线命令
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

		//0长直接返回
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
			stemp1.Format("返回错误码：%d\r\n返回字符串：%s \r\n",iresult,cmdbuffAck);
			stemp += stemp1;
			AppendTextOut(stemp);
		}
		else
		{
			CString stemp1;
			CString stemp = ">>";
			stemp += buffer;
			stemp+= "\r\n";
			stemp1.Format("返回错误码：%d\r\n返回字符串：%s \r\n",iresult,cmdbuffAck);
			stemp += stemp1;
			AppendTextOut(stemp);
		}        

		//把命令重新选择住
		CEdit *pedit;
		pedit = (CEdit *)GetDlgItem(IDC_EDIT_CMD);
		pedit->SetSel(0, -1);
	}

	return;
}

//自定义单轴运动指令
/*BASIC语法
speed(iaxis)=fSpeed
Accel(iaxis)=fAcc
Move(fpos) axis(iaxis)  / MoveAbs(fpos) axis(iaxis)
*/
int Func_AxisMove(ZMC_HANDLE Handle, int iAxis ,float fSpeed,float fAcc,float fpos,float imode)
{
	char  cmdbuff[2048];
	char  tempbuff[2048];
	char  cmdbuffAck[2048];
	//生成命令  speed(iaxis)=fSpeed
	sprintf(cmdbuff, "SPEED(%d) = %.3f\r\n",iAxis,fSpeed);

	//生成命令   Accel(iaxis)=fAcc
	sprintf(tempbuff, "Accel(%d) = %.3f\r\n",iAxis,fAcc);
	strcat(cmdbuff, tempbuff);

	//生成命令   Move(fpos) axis(iaxis)  / MoveAbs(fpos) axis(iaxis)
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

	//调用命令执行函数
	return ZAux_DirectCommand(Handle, cmdbuff, cmdbuffAck, 2048);
	//return ZAux_Execute(Handle, cmdbuff, cmdbuffAck, 2048);
}


void Ctest_UserSubDlg::OnBnClickedGosub()			//调用自定SUB
{
	// TODO: 在此添加控件通知处理程序代码
	int iret = 0;
	if(NULL != g_handle)
	{
		iret = Func_AxisMove(g_handle,0,50,1000,100,0);		//轴0 以速度50加速度1000 相对运动100
		CString str;
		str.Format(_T("%d"), iret);
		SetDlgItemTextA(IDC_RETURN,str);
	}

}


void Ctest_UserSubDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(NULL != g_handle)
	{
		float Axisdpos = 0;
		int iret = ZAux_Direct_GetDpos(g_handle,0,&Axisdpos);
		CString str;
		str.Format(_T("轴0坐标：%.3f"), Axisdpos);
		SetDlgItemTextA(IDC_AXISDPOS,str);
	}
	CDialogEx::OnTimer(nIDEvent);
}
