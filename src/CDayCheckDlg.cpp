// CDayCheckDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CDayCheckDlg.h"
#include "afxdialogex.h"

#include "canyinDlg.h"

// CDayCheckDlg 对话框

IMPLEMENT_DYNAMIC(CDayCheckDlg, CDialogEx)

CDayCheckDlg::CDayCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DayCheckDlg, pParent)
{

}

CDayCheckDlg::~CDayCheckDlg()
{
}

void CDayCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTdaybill, m_daybill);
}


BEGIN_MESSAGE_MAP(CDayCheckDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONdaybillcheck, &CDayCheckDlg::OnBnClickedButtondaybillcheck)
	ON_BN_CLICKED(IDC_BUTTONcheckNew, &CDayCheckDlg::OnBnClickedButtonchecknew)
END_MESSAGE_MAP()


// CDayCheckDlg 消息处理程序


BOOL CDayCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5)), TRUE);
	//为列表控件设置格式
	m_daybill.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_daybill.InsertColumn(0, _T("日期"), LVCFMT_LEFT, 175, 0);
	m_daybill.InsertColumn(1, _T("收入/元"), LVCFMT_LEFT, 100, 1);

	//查询数据
	_bstr_t sql = "select * from dayBill";
	m_ptrRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_ptrRecord->adoEOF == 0)
	{
		CString date1, Value1;
		date1 = m_ptrRecord->GetCollect("日期");
		Value1 = m_ptrRecord->GetCollect("收入");
		m_daybill.InsertItem(0, "");
		m_daybill.SetItemText(0, 0, date1);
		m_daybill.SetItemText(0, 1, Value1);
		m_ptrRecord->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDayCheckDlg::OnBnClickedButtondaybillcheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CcanyinDlg* pWin = (CcanyinDlg*)AfxGetMainWnd();
	pWin->m_daypay.ShowWindow(SW_HIDE);
	pWin->m_daycheckBill.ShowWindow(SW_HIDE);
}


void CDayCheckDlg::OnBnClickedButtonchecknew()
{
	// TODO: 在此添加控件通知处理程序代码
	m_daybill.DeleteAllItems();
	_bstr_t sql = "select * from dayBill";
	m_ptrRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_ptrRecord->adoEOF == 0)
	{
		CString date1, Value1;
		date1 = m_ptrRecord->GetCollect("日期");
		Value1 = m_ptrRecord->GetCollect("收入");
		m_daybill.InsertItem(0, "");
		m_daybill.SetItemText(0, 0, date1);
		m_daybill.SetItemText(0, 1, Value1);
		m_ptrRecord->MoveNext();
	}
	AfxMessageBox(_T("更新成功！"));
}
