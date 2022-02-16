// CFoodMenuDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CFoodMenuDlg.h"
#include "afxdialogex.h"


// CFoodMenuDlg 对话框
extern CcanyinApp theApp;

IMPLEMENT_DYNAMIC(CFoodMenuDlg, CDialogEx)

CFoodMenuDlg::CFoodMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_updatecaishi, pParent)
	, m_foodName(_T(""))
	, m_FoodValue(_T(""))
{

}

CFoodMenuDlg::~CFoodMenuDlg()
{
}

void CFoodMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITcaiName, m_foodName);
	DDX_Text(pDX, IDC_EDITcaiValue, m_FoodValue);
	DDX_Control(pDX, IDC_LISTFoodCHANGE, m_MenuShow);
}


BEGIN_MESSAGE_MAP(CFoodMenuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONInsertFood, &CFoodMenuDlg::OnBnClickedButtoninsertfood)
	ON_BN_CLICKED(IDC_BUTTONdeleteFood, &CFoodMenuDlg::OnBnClickedButtondeletefood)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTFoodCHANGE, &CFoodMenuDlg::OnDblclkListfoodchange)
	ON_BN_CLICKED(IDC_BUTTONexitFood, &CFoodMenuDlg::OnBnClickedButtonexitfood)
	ON_BN_CLICKED(IDC_BUTTONchangeFood, &CFoodMenuDlg::OnBnClickedButtonchangefood)
END_MESSAGE_MAP()


// CFoodMenuDlg 消息处理程序


BOOL CFoodMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置窗口图标
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5)), TRUE);
	//为列表控件设置格式
	m_MenuShow.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_MenuShow.InsertColumn(0, _T("菜名"), LVCFMT_LEFT, 100, 0);
	m_MenuShow.InsertColumn(1, _T("价格"), LVCFMT_LEFT, 100, 1);

	//查询数据
	_bstr_t sql = "select * from caishiinfo";
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_pRecord->adoEOF == 0)
	{
		CString value1, caiming1;
		caiming1 = (char*)(_bstr_t)m_pRecord->GetCollect("菜名");
		value1 = (char*)(_bstr_t)m_pRecord->GetCollect("菜价");
		m_MenuShow.InsertItem(0, "");
		m_MenuShow.SetItemText(0, 0, caiming1);
		m_MenuShow.SetItemText(0, 1, value1);
		m_pRecord->MoveNext();
	}




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//添加
void CFoodMenuDlg::OnBnClickedButtoninsertfood()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_foodName.IsEmpty() || m_FoodValue.IsEmpty()) {
		AfxMessageBox(_T("菜名和菜价不能为空！"));
		return;
	}
	m_MenuShow.InsertItem(0, "");
	m_MenuShow.SetItemText(0, 0, m_foodName);
	m_MenuShow.SetItemText(0, 1, m_FoodValue);
	m_foodName = _T("");
	m_FoodValue = _T("");
	UpdateData(FALSE);

}


void CFoodMenuDlg::OnBnClickedButtondeletefood()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_MenuShow.GetSelectionMark();//获取序号
	if (i >= 0) {
		m_MenuShow.DeleteItem(i);

	}
	else {
		AfxMessageBox(_T("请选择菜品！"));
	}
}


//双击处理程序
void CFoodMenuDlg::OnDblclkListfoodchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtondeletefood();
	*pResult = 0;
}


void CFoodMenuDlg::OnBnClickedButtonexitfood()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


//保存数据
void CFoodMenuDlg::OnBnClickedButtonchangefood()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_MenuShow.GetItemCount();
	_bstr_t sql = "delete from caishiinfo";
	theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	if (n > 0) {
		for (int i = 0; i < n; ++i) {
			CString str1 = m_MenuShow.GetItemText(i, 0);//菜名
			CString str2 = m_MenuShow.GetItemText(i, 1);//价格
			_bstr_t sql1 = "insert into caishiinfo([菜名],[菜价]) values('" + str1 + "','" + str2 + "')";
			theApp.m_pConnection->Execute(sql1, NULL, adCmdText);
		}
	}
	CDialog::OnOK();
}
