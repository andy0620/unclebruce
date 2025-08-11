
// test_AutoUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_AutoUp.h"
#include "test_AutoUpDlg.h"
#include "afxdialogex.h"

#include "zauxdll2.h"


ZMC_HANDLE G_ZmcHandle;		//成功连接的HANDLE句柄
CString ShowMessage;

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


// Ctest_AutoUpDlg 对话框




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


// Ctest_AutoUpDlg 消息处理程序

BOOL Ctest_AutoUpDlg::OnInitDialog()
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
	(GetDlgItem(IDC_UpCmd))->SetWindowText("TOSTR(speed(0),6,3) + \" \"+TOSTR(accel(0),6,3)");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctest_AutoUpDlg::OnPaint()
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
HCURSOR Ctest_AutoUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_AutoUpDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Ctest_AutoUpDlg::OnCbnDropdownCombo1()
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


void Ctest_AutoUpDlg::OnBnClickedBtnOpen()				//连接控制器
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


void Ctest_AutoUpDlg::OnBnClickedBtnClose()					//断开连接
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


void Ctest_AutoUpDlg::OnBnClickedBtnDown()					//下载BAS程序
{
	int32 	ret;
	CString m_strOpenFileName;
	CFile	openfile;

	if(NULL == G_ZmcHandle)
	{
		MessageBox(_T("控制器未连接"));
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

		//下载BAS程序到ROM
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

	//过大则删除部分
	if(nLen > 1000000)
	{
		//删除5000行
		nLen = m_AutoUpMessage.LineIndex(1000);
		//不滚动
		m_AutoUpMessage.SetSel(0, nLen, true);
		m_AutoUpMessage.ReplaceSel("");

		nLen   =   m_AutoUpMessage.GetWindowTextLength();
	}

	m_AutoUpMessage.SetSel(nLen,   nLen, false);
	m_AutoUpMessage.ReplaceSel(stemp);      
}


/******************** 回调函数测试******************************************/
void  ZmcAutoCallBaceTest(ZMC_HANDLE handle,int32 itypecode, int32 idatalength, uint8 *pdata)	
{

	ShowMessage.Format("Code:%d Info:%s \r\n", itypecode, (char*)pdata);	

}

void Ctest_AutoUpDlg::OnBnClickedCheck1()				//开启关闭主动上报
{
	// TODO: 在此添加控件通知处理程序代码
	int iresult= 0 ;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);

	if( pBtn->GetCheck())
	{
		UpdateData(TRUE);
		CString strtemp;
		(GetDlgItem(IDC_UpCmd))->GetWindowText(strtemp);

		char  cmdbuff[2048];
		char  cmdbuffAck[2048];
		sprintf(cmdbuff, "AutoCmdString =%s",strtemp);										//生成主动上报命令
		int iresult =  ZAux_Execute(G_ZmcHandle,cmdbuff,cmdbuffAck,1024);

		iresult = ZAux_SetAutoUpCallBack(G_ZmcHandle,ZmcAutoCallBaceTest);			//主动上报回调函数

		//修改BAS全局变量,
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"AutoUpTime",m_AutoUpTime);				//上报间隔时间
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"AutoUpCode",m_AutoUpCode);				//上报功能码
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"If_EnableAutoUp",1);			//上报使能		
		SetTimer(1,100,NULL);
	}
	else
	{
		iresult = ZAux_Direct_SetUserVar(G_ZmcHandle,"If_EnableAutoUp",0);			//关闭上报使能		
		KillTimer(1);
	}


}


void Ctest_AutoUpDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码
	ShowMessage.Empty();
	SetDlgItemText(IDC_UPMESSAGE,ShowMessage);
}
