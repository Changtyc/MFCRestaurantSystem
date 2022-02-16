// CIndeFoodDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CIndeFoodDlg.h"
#include "afxdialogex.h"

#include "CFoodNumDlg.h"


// CIndeFoodDlg 对话框

extern CcanyinApp theApp;


IMPLEMENT_DYNAMIC(CIndeFoodDlg, CDialogEx)

CIndeFoodDlg::CIndeFoodDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FoodIndeDlg, pParent)
{

}

CIndeFoodDlg::~CIndeFoodDlg()
{
}

void CIndeFoodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DesknameList, m_dropList);
	DDX_Control(pDX, IDC_jiacai, m_FoodMenu1);
	DDX_Control(pDX, IDC_jiancai, m_FoodDecrease);
}


BEGIN_MESSAGE_MAP(CIndeFoodDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_DesknameList, &CIndeFoodDlg::OnSelchangeDesknamelist)
	ON_BN_CLICKED(IDC_jia1, &CIndeFoodDlg::OnBnClickedjia1)
	ON_BN_CLICKED(IDC_jian1, &CIndeFoodDlg::OnBnClickedjian1)
	ON_NOTIFY(NM_DBLCLK, IDC_jiacai, &CIndeFoodDlg::OnDblclkJiacai)
	ON_NOTIFY(NM_DBLCLK, IDC_jiancai, &CIndeFoodDlg::OnDblclkJiancai)
	ON_BN_CLICKED(IDC_CancelFood, &CIndeFoodDlg::OnBnClickedCancelfood)
	ON_BN_CLICKED(IDC_comfirmFood, &CIndeFoodDlg::OnBnClickedcomfirmfood)
END_MESSAGE_MAP()


// CIndeFoodDlg 消息处理程序


BOOL CIndeFoodDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//添加图标
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON4)), TRUE);
	//初始化下拉框
	_bstr_t sql = "select distinct 桌号 from paybill";//去除重复的桌号
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_pRecord->adoEOF == 0)
	{
		CString zhuohao = (char*)(_bstr_t)m_pRecord->GetCollect("桌号");
		m_dropList.AddString(zhuohao);
		m_pRecord->MoveNext();
	}
	//设置默认下拉
	m_dropList.InsertString(0, _T("Start"));
	m_dropList.SetCurSel(0);

	//添加菜单
	m_FoodMenu1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	m_FoodDecrease.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_FoodMenu1.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_FoodMenu1.InsertColumn(1, _T("价格/元"), LVCFMT_LEFT, 100, 1);
	m_FoodDecrease.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_FoodDecrease.InsertColumn(1, _T("数量/盘"), LVCFMT_LEFT, 100, 1);
	//更新菜谱
	sql = "select * from caishiinfo";
	m_pRecord = NULL;
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	int i = 0;
	while (m_pRecord->adoEOF == 0) {
		CString caiming, jiage;
		caiming = (char*)(_bstr_t)m_pRecord->GetCollect("菜名");
		jiage = (char*)(_bstr_t)m_pRecord->GetCollect("菜价");
		m_FoodMenu1.InsertItem(i, "");
		m_FoodMenu1.SetItemText(i, 0, caiming);
		m_FoodMenu1.SetItemText(i, 1, jiage);
		m_pRecord->MoveNext();
		++i;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//下拉框变化消息处理
void CIndeFoodDlg::OnSelchangeDesknamelist()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_dropList.GetLBText(m_dropList.GetCurSel(), str);
	if (str == "Start") {
		m_FoodDecrease.DeleteAllItems();
		return;
	}
	int deskname = atoi(str);
	CString sql;
	sql.Format(_T("select * from paybill where 桌号= %d"), deskname);
	m_pRecord = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
	m_FoodDecrease.DeleteAllItems();//下单全部情况
	while (m_pRecord->adoEOF == 0) {
		CString caiming, shuliang;
		caiming = (char*)(_bstr_t)m_pRecord->GetCollect("菜名");
		shuliang = (char*)(_bstr_t)m_pRecord->GetCollect("数量");
		m_FoodDecrease.InsertItem(0, "");
		m_FoodDecrease.SetItemText(0, 0, caiming);
		m_FoodDecrease.SetItemText(0, 1, shuliang);
		m_pRecord->MoveNext();
	}
}


//点击加菜
void CIndeFoodDlg::OnBnClickedjia1()
{
	// TODO: 在此添加控件通知处理程序代码
	//先判断有没有选择好桌号
	CString str1;
	m_dropList.GetLBText(m_dropList.GetCurSel(), str1);
	if (str1 == _T("Start")) {
		AfxMessageBox(_T("请先选择桌号！"));
		return;
	}


	CFoodNumDlg foodnum;
	int i = m_FoodMenu1.GetSelectionMark();//获取序号
	if (i >= 0) {
		if (foodnum.DoModal() == IDOK) {
			CString str = m_FoodMenu1.GetItemText(i, 0);
			LVFINDINFO info;
			info.flags = LVFI_STRING;
			info.psz = str;
			int index = m_FoodDecrease.FindItem(&info);
			if (index == -1) {
				//表示没有，加一行
				m_FoodDecrease.InsertItem(0, "");
				m_FoodDecrease.SetItemText(0, 0, str);
				m_FoodDecrease.SetItemText(0, 1, foodnum.m_foodNum);
			}
			else
			{
				m_FoodDecrease.SetItemText(index, 1, foodnum.m_foodNum);
			}
		}
		else {
			return;
		}
	}
	else {
		AfxMessageBox("请选择菜品！");
	}
}


void CIndeFoodDlg::OnBnClickedjian1()
{
	// TODO: 在此添加控件通知处理程序代码
	//先判断有没有选择好桌号
	CString str1;
	m_dropList.GetLBText(m_dropList.GetCurSel(), str1);
	if (str1 == _T("Start")) {
		AfxMessageBox(_T("请先选择桌号！"));
		return;
	}

	CFoodNumDlg foodnum;
	int i = m_FoodDecrease.GetSelectionMark();//获取序号
	if (i >= 0) {
		m_FoodDecrease.DeleteItem(i);
	}
	else {
		AfxMessageBox("请选择需要移除的菜品！");
	}

}


void CIndeFoodDlg::OnDblclkJiacai(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedjia1();
	*pResult = 0;
}


void CIndeFoodDlg::OnDblclkJiancai(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedjian1();
	*pResult = 0;
}


void CIndeFoodDlg::OnBnClickedCancelfood()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


//确定按钮，更改数据库
void CIndeFoodDlg::OnBnClickedcomfirmfood()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1;
	m_dropList.GetLBText(m_dropList.GetCurSel(), str1);
	if (str1 == _T("Start")) {
		AfxMessageBox(_T("请先选择桌号！"));
		return;
	}
	int i = m_FoodDecrease.GetItemCount();
	if (i == 0) {
		AfxMessageBox(_T("请点菜！"));
		return;
	}

	//删除原数据库
	int name_desk = atoi(str1);
	CString sql;
	//注意查询的时候类型和accdb的数据类型一致，否则报错。
	sql.Format(_T("delete from paybill where [桌号]= %d"), name_desk);
	theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);

	//重新插入paybill里面
	double total_value;//消费
	int food_num;
	for (int n = 0; n < i; ++n) {
		CString str1 = m_FoodDecrease.GetItemText(n, 0);//菜名
		CString str2 = m_FoodDecrease.GetItemText(n, 1);//数量
		_bstr_t sql1 = "select * from caishiinfo where [菜名]='" + str1 + "'";
		m_pRecord = NULL;
		m_pRecord = theApp.m_pConnection->Execute(sql1, NULL, adCmdText);
		CString caijia1 = (char *)(_bstr_t)m_pRecord->GetCollect("菜价");
		food_num = atoi(str2);
		total_value = atof(caijia1)*food_num;
		CString sql2;
		sql2.Format(_T("insert into paybill([桌号],[菜名],[数量],[消费]) values(%d,'%s',%d,%lf)"), name_desk, str1,
			food_num, total_value);
		theApp.m_pConnection->Execute((_bstr_t)sql2, NULL, adCmdText);
	}
	AfxMessageBox(_T("加减菜成功！"));
	CDialog::OnOK();
}
