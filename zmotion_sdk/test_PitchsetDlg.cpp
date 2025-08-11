
// test_PitchsetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_Pitchset.h"
#include "test_PitchsetDlg.h"
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


// Ctest_PitchsetDlg 对话框




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


// Ctest_PitchsetDlg 消息处理程序

BOOL Ctest_PitchsetDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctest_PitchsetDlg::OnPaint()
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
HCURSOR Ctest_PitchsetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_PitchsetDlg::OnCbnDropdownIplist()			//下拉刷新IP
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
		MessageBox(_T("链接失败"));
		SetWindowText("未链接");
		return;
	}

	SetWindowText("已链接");
	SetTimer(0,100,NULL);
}


void Ctest_PitchsetDlg::OnBnClickedClose()
{
	if(NULL != g_handle)
	{
		KillTimer(0);						//关定时器
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("未链接");
	}
}


void Ctest_PitchsetDlg::ShowPosList()			//刷新位置列表
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

	m_PosList.InsertColumn(0,_T("编号"),LVCFMT_CENTER,45);
	m_PosList.InsertColumn(1,_T("位置"),LVCFMT_CENTER,100);
	m_PosList.InsertColumn(2,_T("正向补偿表"),LVCFMT_CENTER,100);
	m_PosList.InsertColumn(3,_T("反向补偿表"),LVCFMT_CENTER,100);
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
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列

	if (m_Row >= 0 && (m_Col ==2 || m_Col ==3)) //如果选择的;
	{
		m_PosList.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；
		m_EDIT.SetParent(&m_PosList);//转换坐标为列表框中的坐标
		m_EDIT.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_EDIT.SetWindowText(m_PosList.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；
		m_EDIT.ShowWindow(SW_SHOW);//显示Edit控件；
		m_EDIT.SetFocus();//设置Edit焦点
		m_EDIT.ShowCaret();//显示光标
		m_EDIT.SetSel(-1);//将光标移动到最后
	}	
	*pResult = 0;
}


void Ctest_PitchsetDlg::OnEnKillfocusPedit()			//数据修改完成
{
	CString tempstr;
	m_EDIT.GetWindowText(tempstr);						//得到用户输入的新的内容
	m_PosList.SetItemText(m_Row,m_Col,tempstr);		  //设置编辑框的新内容

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

void Ctest_PitchsetDlg::OnBnClickedEnablePitch()		//开启关闭补偿
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}

	int iret = 0;
	UpdateData(TRUE);
	if(m_Enable)
	{
		if(m_RadioMode.GetCheck())			//单向
		{
			iret = ZAux_Direct_Pitchset(g_handle,m_iAxis,1,m_StartPos,m_MaxPoint,m_DisOne,m_TableStart,fFwdDist);
		}
		else								//双向
		{
			iret = ZAux_Direct_Pitchset2(g_handle,m_iAxis,1,m_StartPos,m_MaxPoint,m_DisOne,m_TableStart,fFwdDist,m_TableStart+m_MaxPoint,fRevDist);
		}
	}
	else		//关闭螺距补偿
	{
			iret = ZAux_Direct_Pitchset(g_handle,m_iAxis,0,m_StartPos,m_MaxPoint,m_DisOne,m_TableStart,fFwdDist);
	}
}


//定时器刷新状态
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

			tempstr.Format(_T("命令位置：%.3f"), fval);
			SetDlgItemTextA(IDC_SHOW_DPOS,tempstr);
			
			iret = ZAux_Direct_GetMpos(g_handle,m_iAxis,&fval);
			tempstr.Format(_T("反馈位置：%.3f"), fval);
			SetDlgItemTextA(IDC_SHOW_MPOS,tempstr);
		}


		if(nIDEvent == 1  && (RunTestFlag == false)) 
		{
			RunTestFlag = true;

			if(m_MoveDir == true)		//正向运动
			{
				iret = ZAux_Direct_Single_MoveAbs(g_handle,m_iAxis,m_StartPos);
				iret = ZAux_Direct_MoveDelay(g_handle,m_iAxis,m_DelayTime);
				while(AxisIsMoveing(m_iAxis))	//等待轴运动停止
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
					while(AxisIsMoveing(m_iAxis))		//等待轴运动停止
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
					while(AxisIsMoveing(m_iAxis))		//等待轴运动停止
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
				while(AxisIsMoveing(m_iAxis))	//等待轴运动停止
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

//轴是否运动中
bool  Ctest_PitchsetDlg::AxisIsMoveing(int iaxis)
{
	int AxisIdle = 0;
	ZAux_Direct_GetIfIdle(g_handle,iaxis,&AxisIdle);

	if(AxisIdle == 0) return true;

	return false;

}



//启动测试
void Ctest_PitchsetDlg::OnBnClickedBtnRun()
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}	


	UpdateData(TRUE);

	int iret  = 0;
	iret = ZAux_Direct_SetAtype(g_handle,m_iAxis,4);				//设置轴类型  脉冲+编码器反馈轴
	iret = ZAux_Direct_SetUnits(g_handle,m_iAxis,m_Units);			//设置脉冲当量
	iret = ZAux_Direct_SetSpeed(g_handle,m_iAxis,m_speed);
	iret = ZAux_Direct_SetAccel(g_handle,m_iAxis,m_accel);
	iret = ZAux_Direct_SetDecel(g_handle,m_iAxis,m_Decel);

	SetTimer(1,1,NULL);				//定时器内去发送运动
}

//停止运行
void Ctest_PitchsetDlg::OnBnClickedBtnStop()
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}


	KillTimer(1);
	RunTestFlag = false;	

	int iret  = 0;
	iret = ZAux_Direct_Single_Cancel(g_handle,m_iAxis,3);

}


//回零复位
void Ctest_PitchsetDlg::OnBnClickedBtnHome()
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}

	UpdateData(TRUE);

	int iret  = 0;
	iret = ZAux_Direct_SetAtype(g_handle,m_iAxis,4);				//设置轴类型  脉冲+编码器反馈轴
	iret = ZAux_Direct_SetUnits(g_handle,m_iAxis,m_Units);			//设置脉冲当量
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

