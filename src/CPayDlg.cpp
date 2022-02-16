// CPayDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CPayDlg.h"
#include "afxdialogex.h"
#include <vector>
#include<numeric>

using namespace std;

// CPayDlg 对话框

extern CcanyinApp theApp;

IMPLEMENT_DYNAMIC(CPayDlg, CDialogEx)

CPayDlg::CPayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_jiezhangDlg, pParent)
	, m_get(_T(""))
	, m_theoryGet(_T(""))
	, m_send(_T(""))
{

}

CPayDlg::~CPayDlg()
{
}

void CPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTjiezhang, m_xiaofeiMenu);
	DDX_Text(pDX, IDC_EDITshishou, m_get);
	DDX_Text(pDX, IDC_EDITyingshou, m_theoryGet);
	DDX_Text(pDX, IDC_EDITzhaoling, m_send);
	DDX_Control(pDX, IDC_jiezhangdeskName, m_nameDesk);
}


BEGIN_MESSAGE_MAP(CPayDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_jiezhangdeskName, &CPayDlg::OnSelchangeJiezhangdeskname)
	//	ON_EN_CHANGE(IDC_EDITshishou, &CPayDlg::OnEnChangeEditshishou)
	ON_EN_CHANGE(IDC_EDITshishou, &CPayDlg::OnChangeEditshishou)
	ON_BN_CLICKED(IDC_BUTTONtuichu, &CPayDlg::OnBnClickedButtontuichu)
	ON_BN_CLICKED(IDC_BUTTONjiezhang, &CPayDlg::OnBnClickedButtonjiezhang)
END_MESSAGE_MAP()


// CPayDlg 消息处理程序


BOOL CPayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化下拉框
	// 添加图标
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5)), TRUE);
	//初始化下拉框
	_bstr_t sql = "select distinct 桌号 from paybill";//去除重复的桌号
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_pRecord->adoEOF == 0)
	{
		CString zhuohao = (char*)(_bstr_t)m_pRecord->GetCollect("桌号");
		m_nameDesk.AddString(zhuohao);
		m_pRecord->MoveNext();
	}
	//设置默认下拉
	m_nameDesk.InsertString(0, _T("Start"));
	m_nameDesk.SetCurSel(0);

	//初始化列表
	m_xiaofeiMenu.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_xiaofeiMenu.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 120, 0);
	m_xiaofeiMenu.InsertColumn(1, _T("数量"), LVCFMT_LEFT, 120, 1);
	m_xiaofeiMenu.InsertColumn(2, _T("消费/元"), LVCFMT_LEFT, 120, 2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPayDlg::OnSelchangeJiezhangdeskname()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_nameDesk.GetLBText(m_nameDesk.GetCurSel(), str);
	if (str == "Start") {
		m_xiaofeiMenu.DeleteAllItems();
		return;
	}
	int deskname = atoi(str);
	CString sql;
	sql.Format(_T("select * from paybill where 桌号= %d"), deskname);
	m_pRecord = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
	m_xiaofeiMenu.DeleteAllItems();//下单全部情况
	vector<double> value_all;
	while (m_pRecord->adoEOF == 0) {
		CString caiming, shuliang, totalValue;
		caiming = (char*)(_bstr_t)m_pRecord->GetCollect("菜名");
		shuliang = (char*)(_bstr_t)m_pRecord->GetCollect("数量");
		totalValue = (char*)(_bstr_t)m_pRecord->GetCollect("消费");
		double value1 = static_cast<double>(atof(totalValue));
		value_all.emplace_back(value1);
		m_xiaofeiMenu.InsertItem(0, "");
		m_xiaofeiMenu.SetItemText(0, 0, caiming);
		m_xiaofeiMenu.SetItemText(0, 1, shuliang);
		m_xiaofeiMenu.SetItemText(0, 2, totalValue);
		m_pRecord->MoveNext();
	}
	double ret = 0;
	for (auto &i : value_all) {
		ret += i;
	}
	CString showValue;
	showValue.Format("%lf", ret);
	m_theoryGet = showValue;
	m_send = _T("");
	m_get = _T("");
	UpdateData(FALSE);
}




void CPayDlg::OnChangeEditshishou()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	double ret = static_cast<double>(atof(m_get) - atof(m_theoryGet));
	CString show;
	show.Format("%lf", ret);
	m_send = show;
	UpdateData(FALSE);
}


void CPayDlg::OnBnClickedButtontuichu()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


//确认按钮，插入数据库
void CPayDlg::OnBnClickedButtonjiezhang()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取总数
	UpdateData(TRUE);
	double value_all = static_cast<double>(atof(m_theoryGet));
	double reduce_val = static_cast<double>(atof(m_send));
	if (reduce_val < 0) {
		AfxMessageBox(_T("钱不够！"));
		return;
	}

	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString m_strDateTime = m_time.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString dayTime = m_time.Format(_T("%Y-%m-%d"));
	CString monthTime = m_time.Format(_T("%Y-%m"));

	//插入数据
	CString sql2;
	sql2.Format(_T("insert into shouru([日期],[月份],[时间],[收入]) values('%s','%s','%s',%lf)"), dayTime, monthTime, m_strDateTime, value_all);
	m_pRecord = NULL;
	m_pRecord = theApp.m_pConnection->Execute((_bstr_t)sql2, NULL, adCmdText);

	//删除
	CString str;
	m_nameDesk.GetLBText(m_nameDesk.GetCurSel(), str);
	int deskname = atoi(str);
	CString sql;
	sql.Format(_T("delete from paybill where 桌号= %d"), deskname);
	m_pRecord = NULL;
	m_pRecord = theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);

	//更改桌号使用
	int status_desk = 0;
	CString sql1;
	//注意查询的时候类型和accdb的数据类型一致，否则报错。
	sql1.Format(_T("update tableuse set [TableUsedID]= %d where [桌号]= %d"), status_desk, deskname);
	theApp.m_pConnection->Execute((_bstr_t)sql1, NULL, adCmdText);

	AfxMessageBox(_T("结账成功"));
	CDialog::OnOK();
}
