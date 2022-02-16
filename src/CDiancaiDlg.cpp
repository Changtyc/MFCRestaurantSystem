// CDiancaiDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CDiancaiDlg.h"
#include "afxdialogex.h"

#include "CFoodNumDlg.h"


// CDiancaiDlg 对话框
extern CcanyinApp theApp;

IMPLEMENT_DYNAMIC(CDiancaiDlg, CDialogEx)

CDiancaiDlg::CDiancaiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Diancai, pParent)
	, m_deskName(_T(""))
{

}

CDiancaiDlg::~CDiancaiDlg()
{
}

void CDiancaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_deskSelect, m_deskName);
	DDX_Control(pDX, IDC_diancai1, m_foodMenu);
	DDX_Control(pDX, IDC_diancai2, m_FoodOrder);
}


BEGIN_MESSAGE_MAP(CDiancaiDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONjiacai, &CDiancaiDlg::OnBnClickedButtonjiacai)
	ON_BN_CLICKED(IDC_BUTTONjiancai, &CDiancaiDlg::OnBnClickedButtonjiancai)
	ON_NOTIFY(NM_DBLCLK, IDC_diancai1, &CDiancaiDlg::OnDblclkDiancai1)
	ON_NOTIFY(NM_DBLCLK, IDC_diancai2, &CDiancaiDlg::OnDblclkDiancai2)
	ON_BN_CLICKED(IDC_diancaiComfirm, &CDiancaiDlg::OnBnClickeddiancaicomfirm)
	ON_BN_CLICKED(IDC_daincaiCancel, &CDiancaiDlg::OnBnClickeddaincaicancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_diancai1, &CDiancaiDlg::OnLvnItemchangeddiancai1)
END_MESSAGE_MAP()


// CDiancaiDlg 消息处理程序


BOOL CDiancaiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 设置图标
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3)), TRUE);
	//更新桌号
	UpdateData(TRUE);
	//为列表控件设置格式
	m_foodMenu.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	m_FoodOrder.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_foodMenu.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_foodMenu.InsertColumn(1, _T("价格/元"), LVCFMT_LEFT, 100, 1);
	m_FoodOrder.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_FoodOrder.InsertColumn(1, _T("数量/盘"), LVCFMT_LEFT, 100, 1);
	//更新菜谱
	_bstr_t sql = "select * from caishiinfo";
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	int i = 0;
	while (m_pRecord->adoEOF == 0) {
		CString caiming, jiage;
		caiming = (char*)(_bstr_t)m_pRecord->GetCollect("菜名");
		jiage = (char*)(_bstr_t)m_pRecord->GetCollect("菜价");
		m_foodMenu.InsertItem(i, "");
		m_foodMenu.SetItemText(i, 0, caiming);
		m_foodMenu.SetItemText(i, 1, jiage);
		m_pRecord->MoveNext();
		++i;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



//点击加菜
void CDiancaiDlg::OnBnClickedButtonjiacai()
{
	// TODO: 在此添加控件通知处理程序代码
	CFoodNumDlg foodnum;
	int i = m_foodMenu.GetSelectionMark();//获取序号
	if (i >= 0) {
		if (foodnum.DoModal() == IDOK) {
			CString str = m_foodMenu.GetItemText(i, 0);
			m_FoodOrder.InsertItem(0, "");
			m_FoodOrder.SetItemText(0, 0, str);
			m_FoodOrder.SetItemText(0, 1, foodnum.m_foodNum);
		}
		else {
			return;
		}
	}
	else {
		AfxMessageBox("请选择菜品！");
	}

}


void CDiancaiDlg::OnBnClickedButtonjiancai()
{
	// TODO: 在此添加控件通知处理程序代码
	CFoodNumDlg foodnum;
	int i = m_FoodOrder.GetSelectionMark();//获取序号
	if (i >= 0) {
		m_FoodOrder.DeleteItem(i);
	}
	else {
		AfxMessageBox("请选择需要移除的菜品！");
	}
}


void CDiancaiDlg::OnDblclkDiancai1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonjiacai();
	*pResult = 0;
}


void CDiancaiDlg::OnDblclkDiancai2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonjiancai();
	*pResult = 0;
}



//确认按钮，插入数据库
void CDiancaiDlg::OnBnClickeddiancaicomfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = m_FoodOrder.GetItemCount();
	if (i == 0) {
		AfxMessageBox(_T("请点菜！"));
		return;
	}
	//更改桌子使用状态
	int name_desk = atoi(m_deskName);
	CString sql;
	int status_desk = 1;
	//注意查询的时候类型和accdb的数据类型一致，否则报错。
	sql.Format(_T("update tableuse set [TableUsedID]= %d where [桌号]= %d"), status_desk, name_desk);
	theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);


	//插入paybill里面
	double total_value;//消费
	int food_num;
	for (int n = 0; n < i; ++n) {
		CString str1 = m_FoodOrder.GetItemText(n, 0);//菜名
		CString str2 = m_FoodOrder.GetItemText(n, 1);//数量
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
	AfxMessageBox(_T("点菜成功！"));
	CDialog::OnOK();
}


void CDiancaiDlg::OnBnClickeddaincaicancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}



void CDiancaiDlg::OnLvnItemchangeddiancai1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
