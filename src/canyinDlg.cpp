
// canyinDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "canyin.h"
#include "canyinDlg.h"
#include "afxdialogex.h"

#include "CRegistDlg.h"
#include "CLoginDlg.h"
#include "CKaitaiDlg.h"
#include "CIndeFoodDlg.h"
#include "CPayDlg.h"
#include "CFoodMenuDlg.h"
#include "CPersonManagerDlg.h"
#include "CChangeAuthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CcanyinApp theApp;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcanyinDlg 对话框
CcanyinDlg::CcanyinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CANYIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
}

void CcanyinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_forchaxun, m_tabR);
}

BEGIN_MESSAGE_MAP(CcanyinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(9000, &CcanyinDlg::OnBnClickelogin)
	ON_BN_CLICKED(9001, &CcanyinDlg::OnBnClickekaitai)
	ON_BN_CLICKED(9002, &CcanyinDlg::OnBnClickejiezhang)
	ON_BN_CLICKED(9003, &CcanyinDlg::OnDaypay)
	ON_BN_CLICKED(9004, &CcanyinDlg::OnBnClickeRegister)
	ON_BN_CLICKED(9005, &CcanyinDlg::OnBnClickeGoOut)
	ON_COMMAND(ID_Foodjiajian, &CcanyinDlg::OnFoodjiajian)
	ON_COMMAND(ID_AboutUs, &CcanyinDlg::OnClickAbout)
	ON_COMMAND(ID_LOgin1, &CcanyinDlg::OnBnClickelogin)
	ON_COMMAND(ID_kaitai1, &CcanyinDlg::OnBnClickekaitai)
	ON_COMMAND(ID_Pay, &CcanyinDlg::OnBnClickejiezhang)
	ON_COMMAND(ID_DayPay, &CcanyinDlg::OnDaypay)
	ON_COMMAND(ID_caishiinfoManager, &CcanyinDlg::Oncaishiinfomanager)
	ON_COMMAND(ID_peopleManager, &CcanyinDlg::Onpeoplemanager)
	ON_COMMAND(ID_authorityChange, &CcanyinDlg::Onauthoritychange)
	ON_COMMAND(ID_dayCheck, &CcanyinDlg::Ondaycheck)
END_MESSAGE_MAP()


void CcanyinDlg::OnBnClickeGoOut() {
	CDialog::OnCancel();
}

void CcanyinDlg::OnClickAbout() {
	CAboutDlg about1;
	about1.DoModal();
}

//结账消息
void CcanyinDlg::OnBnClickejiezhang() {
	CPayDlg jiezhang;
	jiezhang.DoModal();
}


//开台消息响应
void CcanyinDlg::OnBnClickekaitai() {
	CKaitaiDlg kaitai;
	kaitai.DoModal();
}


//登录消息响应
void CcanyinDlg::OnBnClickelogin() {
	CLoginDlg denglu;
	if (denglu.DoModal() == IDOK) {
		//验证权限
		CString Sql = "select * from Login where [UserName]='" + theApp.userName + "'";
		m_pRecord = theApp.m_pConnection->Execute((_bstr_t)Sql, NULL, adCmdText);
		CString Str = (char*)(_bstr_t)m_pRecord->GetCollect("power");
		int power_value = atoi(Str);
		//经理
		if (power_value == 2) {
			//更改按钮
			CMenu * pMenu = GetMenu();
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			m_toolbar.GetToolBarCtrl().EnableButton(9001, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9002, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9003, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9004, TRUE);
			CString show_title = _T("餐饮管理系统       登录人员：") + theApp.userName + _T(" 经理");
			SetWindowText(show_title);
		}
		//领班
		else if (power_value == 1) {
			CMenu * pMenu = GetMenu();
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			m_toolbar.GetToolBarCtrl().EnableButton(9001, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9002, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9003, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9004, TRUE);
			pMenu->GetSubMenu(1)->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			CString show_title = _T("餐饮管理系统       登录人员：") + theApp.userName + _T(" 领班");
			SetWindowText(show_title);
		}
		//员工
		else if (power_value == 0) {
			CMenu * pMenu = GetMenu();
			pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
			pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			m_toolbar.GetToolBarCtrl().EnableButton(9001, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9002, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9003, TRUE);
			m_toolbar.GetToolBarCtrl().EnableButton(9004, FALSE);
			pMenu->GetSubMenu(1)->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
			CString show_title = _T("餐饮管理系统       登录人员：") + theApp.userName + _T(" 员工");
			SetWindowText(show_title);
		}
	}
}

//注册消息响应
void CcanyinDlg::OnBnClickeRegister() {
	CRegistDlg zhuce;
	zhuce.DoModal();//显示对话框
}

// CcanyinDlg 消息处理程序

BOOL CcanyinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//添加菜单
	m_menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_menu);

	//添加工具栏
	m_imageList.Create(32, 32, ILC_COLOR24 | ILC_MASK, 1, 1);//创建图像列表
	//关联图像
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	//数组控制工具栏个数
	UINT Array[6];
	for (int i = 0; i < 6; ++i) {
		Array[i] = 9000 + i;//给工具栏的按钮下索引ID
	}
	m_toolbar.Create(this);//创建工具栏
	m_toolbar.SetButtons(Array, 6);//设置六个按钮
	//给按钮添加文本
	m_toolbar.SetButtonText(0, _T("系统登录"));
	m_toolbar.SetButtonText(1, _T("开台"));
	m_toolbar.SetButtonText(2, _T("顾客买单"));
	m_toolbar.SetButtonText(3, _T("本日收入"));
	m_toolbar.SetButtonText(4, _T("员工注册"));
	m_toolbar.SetButtonText(5, _T("退出系统"));
	m_toolbar.GetToolBarCtrl().SetButtonWidth(60, 120);//设置按钮宽度
	m_toolbar.GetToolBarCtrl().SetImageList(&m_imageList);//将工具栏和图像连接
	m_toolbar.SetSizes(CSize(70, 60), CSize(28, 40));//设置按钮大小贺图像宽度
	m_toolbar.EnableToolTips(TRUE);//激活鼠标提示功能


	//数组控制状态栏个数
	UINT statusArray[4];

	for (int i = 0; i < 4; ++i) {
		statusArray[i] = 10000 + i;//给状态栏添加索引
	}
	m_statusBar.Create(this);//添加状态栏
	m_statusBar.SetIndicators(statusArray, 4);
	for (int i = 0; i < 4; ++i) {
		m_statusBar.SetPaneInfo(i, statusArray[i], 0, 120);//给每个状态栏设置宽度
	}
	CTime Time;
	Time = CTime::GetCurrentTime();
	CString Str = Time.Format("%Y-%m-%d");
	m_statusBar.SetPaneInfo(2, statusArray[2], 0, 400);
	m_statusBar.SetPaneText(0, _T("餐饮管理系统"));
	m_statusBar.SetPaneText(2, _T("当前日期: ") + Str);
	m_statusBar.SetPaneText(3, _T("版本: version1.0"));

	//显示工具栏和状态栏
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	//按钮置黑
	CMenu* pMenu = GetMenu();
	pMenu->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	//pMenu->GetSubMenu(1)->GetSubMenu(1)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(2)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
	pMenu->GetSubMenu(3)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);
	m_toolbar.GetToolBarCtrl().EnableButton(9001, false);
	m_toolbar.GetToolBarCtrl().EnableButton(9002, false);
	m_toolbar.GetToolBarCtrl().EnableButton(9003, false);
	m_toolbar.GetToolBarCtrl().EnableButton(9004, false);

	//tab初始化
	m_daypay.Create(IDD_DayPayDlg, &m_tabR);
	m_daycheckBill.Create(IDD_DayCheckDlg, &m_tabR);
	m_daypay.ShowWindow(SW_HIDE);
	m_daycheckBill.ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcanyinDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcanyinDlg::OnPaint()
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
HCURSOR CcanyinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcanyinDlg::OnFoodjiajian()
{
	// TODO: 在此添加命令处理程序代码
	CIndeFoodDlg jiajiancai;
	jiajiancai.DoModal();

}


//日结账
void CcanyinDlg::OnDaypay()
{
	// TODO: 在此添加命令处理程序代码
	//显示对话框
	CRect ret1;
	m_tabR.GetClientRect(&ret1);
	int redu = 75;
	ret1.top += redu;
	ret1.left += redu;
	ret1.right -= redu;
	ret1.bottom -= redu;
	m_daypay.MoveWindow(&ret1);
	m_daypay.ShowWindow(SW_SHOW);
}


//菜式信息
void CcanyinDlg::Oncaishiinfomanager()
{
	// TODO: 在此添加命令处理程序代码
	CFoodMenuDlg caishi;
	if (caishi.DoModal() == IDOK) {
		AfxMessageBox(_T("菜单修改完成！"));
	}
}



//员工管理
void CcanyinDlg::Onpeoplemanager()
{
	// TODO: 在此添加命令处理程序代码
	CPersonManagerDlg personma;
	if (personma.DoModal() == IDOK) {
		AfxMessageBox(_T("删除完成！"));
	}
}


void CcanyinDlg::Onauthoritychange()
{
	// TODO: 在此添加命令处理程序代码
	CChangeAuthDlg quanxian;
	if (quanxian.DoModal() == IDOK) {
		AfxMessageBox(_T("更新成功！"));
	}
}



void CcanyinDlg::Ondaycheck()
{
	// TODO: 在此添加命令处理程序代码
	CRect ret1;
	m_tabR.GetClientRect(&ret1);
	ret1.top += 60;
	ret1.left += 150;
	ret1.right -= 0;
	ret1.bottom -= 0;
	m_daycheckBill.MoveWindow(&ret1);
	m_daycheckBill.ShowWindow(SW_SHOW);
}
