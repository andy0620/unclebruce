
// test_PswitchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_Pswitch.h"
#include "test_PswitchDlg.h"
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


// Ctest_PswitchDlg 对话框




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


// Ctest_PswitchDlg 消息处理程序

BOOL Ctest_PswitchDlg::OnInitDialog()
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
	m_RegistMode.InsertString(0,"1 Z脉冲上升沿锁存");
	m_RegistMode.InsertString(1,"2 Z脉冲下降沿锁存");
	m_RegistMode.InsertString(2,"3 R0上升沿锁存");
	m_RegistMode.InsertString(3,"4 R0下降沿锁存");
	m_RegistMode.InsertString(4,"14 R1上升沿锁存");
	m_RegistMode.InsertString(5,"15 R1下降沿锁存");
	m_RegistMode.InsertString(6,"18 R2上升沿锁存");
	m_RegistMode.InsertString(7,"19 R2下降沿锁存");
	m_RegistMode.InsertString(8,"20 R3上升沿锁存");
	m_RegistMode.InsertString(9,"21 R3下降沿锁存");
	m_RegistMode.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctest_PswitchDlg::OnPaint()
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
HCURSOR Ctest_PswitchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest_PswitchDlg::OnCbnDropdownIplist()			//下拉刷新IP
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


void Ctest_PswitchDlg::OnBnClickedOpen()
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


void Ctest_PswitchDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL != g_handle)
	{
		KillTimer(0);						//关定时器
		ZAux_Close(g_handle);
		g_handle = NULL;
		SetWindowText("未链接");
	}
}

void Ctest_PswitchDlg::ShowPswtichList()			//刷新位置列表
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

	m_PosList.InsertColumn(0,_T("编号"),LVCFMT_CENTER,70);
	m_PosList.InsertColumn(1,_T("位置"),LVCFMT_CENTER,100);
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
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列

	if (m_Row != 0 && m_Col ==1) //如果选择的;
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


void Ctest_PswitchDlg::OnEnKillfocusPedit()			//数据修改完成
{
	CString tempstr;
	m_EDIT.GetWindowText(tempstr);						//得到用户输入的新的内容
	m_PosList.SetItemText(m_Row,m_Col,tempstr);		  //设置编辑框的新内容

	fPointPos[m_Row] = atof(tempstr);
	m_EDIT.ShowWindow(SW_HIDE); 
}



void Ctest_PswitchDlg::OnBnClickedRadioOpen()		//开启位置比较
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL != g_handle)
	{
		m_POS_IfOpen = FALSE;
	}
	UpdateData(FALSE);
}


void Ctest_PswitchDlg::OnBnClickedRadioClose()		//关闭位置比较
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(NULL != g_handle)
	{
		m_POS_IfOpen = TRUE;
	}
	UpdateData(FALSE);
}


void Ctest_PswitchDlg::OnBnClickedTimerOpen()			//定时器启动
{
	UpdateData(TRUE);
	if(NULL != g_handle)
	{
		UpdateData(TRUE);
		m_Timer_IfOpen = FALSE;
	}
	UpdateData(FALSE);
}


void Ctest_PswitchDlg::OnBnClickedTimerClose()			//定时器停止
{
	UpdateData(TRUE);
	if(NULL != g_handle)
	{
		UpdateData(TRUE);
		m_Timer_IfOpen = TRUE;
	}
	UpdateData(FALSE);
}

void Ctest_PswitchDlg::OnBnClickedStartmove()			//运动
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	m_RegistCount = 0;
	ShowRegistList();
	UpdateData(TRUE);
	int iret = ZAux_Direct_SetUnits(g_handle, m_AxisNum, 100);
	iret = ZAux_Direct_SetSpeed(g_handle, m_AxisNum, 100);
	iret = ZAux_Direct_SetAccel(g_handle, m_AxisNum, 2000);

	iret = ZAux_Direct_HwPswitch2(g_handle, m_AxisNum, 2, 0, 0, 0, 0, 0, 0);					//清除前面的比较输出指令
	if (m_POS_IfOpen == false)           //比较完成一次后需要重新调用HwPswitch           
	{
		iret = ZAux_Direct_SetTable(g_handle, m_POS_StartTable, m_POS_EndTable, fPointPos);     //将比较点填入TABLE
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("SetTable失败 返回值：%d"),iret);
			MessageBox(tempstr);
			return;
		}
		iret = ZAux_Direct_HwPswitch2(g_handle, m_AxisNum, 1, m_POS_out, m_POS_OutStatus, m_POS_StartTable, m_POS_EndTable, m_PSO_dir, 0);
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("HwPswitch2失败 返回值：%d"),iret);
			MessageBox(tempstr);
			return;
		}
	}
	else
	{
		int iret = 0;
		iret = ZAux_Direct_HwPswitch2(g_handle, m_AxisNum, 2, 0, 0, 0, 0, 0, 0);				//清除比较输出指令
		if(iret != ERR_OK)
		{
			CString tempstr;
			tempstr.Format(_T("HwPswitch2失败 返回值：%d"),iret);
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
			tempstr.Format(_T("HwTimer失败 返回值：%d"),iret);
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
			tempstr.Format(_T("HwTimer失败 返回值：%d"),iret);
			MessageBox(tempstr);
			return;
		}
	}

	ZAux_Trigger(g_handle);
	iret = ZAux_Direct_SetDpos(g_handle, m_AxisNum, 0);
	iret = ZAux_Direct_Single_MoveAbs(g_handle, m_AxisNum, m_Start_Pos);
	iret = ZAux_Direct_Single_MoveAbs(g_handle, m_AxisNum, m_End_Pos); 
}

void Ctest_PswitchDlg::OnBnClickedStopmove()			//停止
{
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	UpdateData(TRUE);
    int iret = ZAux_Direct_Single_Cancel(g_handle, m_AxisNum, 2);          
}


void Ctest_PswitchDlg::OnTimer(UINT_PTR nIDEvent)				//定时器刷新
{
	if(NULL != g_handle)
	{	
		CString str;
		if(nIDEvent == 0)
		{
			float Axisdpos = 0;
			int iret = ZAux_Direct_GetDpos(g_handle,m_AxisNum,&Axisdpos);
			str.Format(_T("轴%d坐标：%.3f"), m_AxisNum,Axisdpos);
			SetDlgItemTextA(IDC_STATUS_POS,str);		

			uint32 Op_status = 0;
			iret = ZAux_Direct_GetOp(g_handle,m_POS_out,&Op_status);
			str.Format(_T("输出口%d状态：关闭"), m_POS_out);
			if(Op_status == 1 )
			{
				str.Format(_T("输出口%d状态：打开"), m_POS_out);
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
					iret = ZAux_Direct_GetRegPos(g_handle,m_RegistAxis,&RegistPos);				//获取锁存位置
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
				iret = ZAux_Direct_Regist(g_handle,m_RegistAxis,RegistMode);				//重新触发锁存

			}
			str.Format(_T("锁存触发状态：%d 次数：%d"), MarkStatus,m_RegistCount);
			SetDlgItemTextA(IDC_STATUS_REGIST,str);	
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Ctest_PswitchDlg::OnBnClickedRegistStart()		//启动停止锁存
{
	// TODO: 在此添加控件通知处理程序代码
	if(NULL == g_handle)
	{
		MessageBox(_T("控制器未连接"));
		return;
	}
	int iret = 0;
	UpdateData(TRUE);
	if(m_Regist_IfOpen == FALSE)
	{
		m_RegistCount = 0;

		iret = ZAux_Direct_SetAtype(g_handle,m_RegistAxis,4);				//必须是编码器轴才可以锁存

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
		SetDlgItemTextA(IDC_REGIST_START,_T("停止锁存"));
		((CComboBox *)GetDlgItem(IDC_REGIST_MODE))->EnableWindow(FALSE);
		ShowRegistList();
		
	}
	else
	{
		KillTimer(1);
		m_Regist_IfOpen = FALSE;
		SetDlgItemTextA(IDC_REGIST_START,_T("启动锁存"));
		((CComboBox *)GetDlgItem(IDC_REGIST_MODE))->EnableWindow(TRUE);
	}
}


void Ctest_PswitchDlg::ShowRegistList()			//刷新列表
{
	int cur_item = m_RegistList.GetItemCount();		//清除所有行
	for(int i = 0;i<cur_item;i++)			
	{
		m_RegistList.DeleteItem(0);
	}

	int cur_subitem = m_RegistList.GetHeaderCtrl()->GetItemCount();	//清除所有列
	for(int i = 0;i<cur_subitem;i++)			
	{
		m_RegistList.DeleteColumn(0);
	}

	m_RegistList.InsertColumn(0,_T("编号"),LVCFMT_CENTER,70);
	m_RegistList.InsertColumn(1,_T("位置"),LVCFMT_CENTER,100);
	m_RegistList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
