// CDayPay.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CDayPay.h"
#include "afxdialogex.h"


#include "canyinDlg.h"

// CDayPay 对话框
extern CcanyinApp theApp;


IMPLEMENT_DYNAMIC(CDayPay, CDialogEx)

CDayPay::CDayPay(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DayPayDlg, pParent)
	, m_dateNow(_T(""))
	, m_shouruDay(_T(""))
{

}

CDayPay::~CDayPay()
{
}

void CDayPay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITdate, m_dateNow);
	DDX_Text(pDX, IDC_EDITshouruday, m_shouruDay);
	DDX_Control(pDX, IDC_LIST_dayshouru, m_Listdate);
}


BEGIN_MESSAGE_MAP(CDayPay, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONyiyue, &CDayPay::OnBnClickedButtonyiyue)
	ON_BN_CLICKED(IDC_BUTTONchaxun, &CDayPay::OnBnClickedButtonchaxun)
END_MESSAGE_MAP()


// CDayPay 消息处理程序


//退出显示
void CDayPay::OnBnClickedButtonyiyue()
{
	CcanyinDlg* pWin = (CcanyinDlg*)AfxGetMainWnd();
	pWin->m_daypay.ShowWindow(SW_HIDE);
	pWin->m_daycheckBill.ShowWindow(SW_HIDE);
}



//查询添加
void CDayPay::OnBnClickedButtonchaxun()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString dayTime = m_time.Format(_T("%Y-%m-%d"));
	CString sql;
	sql.Format("select * from shouru where [日期]='%s'", dayTime);
	m_pRecord = theApp.m_pConnection->Execute((_bstr_t)(sql), NULL, adCmdText);
	double ret = 0;
	m_Listdate.DeleteAllItems();//删除原信息
	while (m_pRecord->adoEOF == 0)
	{
		CString value1, shijian;
		shijian = (char*)(_bstr_t)m_pRecord->GetCollect("时间");
		value1 = (char*)(_bstr_t)m_pRecord->GetCollect("收入");
		m_Listdate.InsertItem(0, "");
		m_Listdate.SetItemText(0, 0, shijian);
		m_Listdate.SetItemText(0, 1, value1);
		ret += atof(value1);
		m_pRecord->MoveNext();
	}
	CString show_value;
	show_value.Format("%lf", ret);
	m_shouruDay = show_value;
	m_dateNow = dayTime;
	UpdateData(FALSE);

	//插入或更新数据
	CString sql1;
	sql1.Format("select * from dayBill where [日期]='%s'", dayTime);
	m_pRecord = NULL;
	m_pRecord = theApp.m_pConnection->Execute((_bstr_t)sql1, NULL, adCmdText);
	//更新
	if (m_pRecord->adoEOF == 0) {
		sql1.Format("update dayBill set [收入]= %f where [日期]='%s'", ret, dayTime);
		theApp.m_pConnection->Execute((_bstr_t)sql1, NULL, adCmdText);
	}
	//插入
	else {
		sql1.Format("insert into dayBill([收入],[日期]) values(%f,'%s')", ret, dayTime);
		theApp.m_pConnection->Execute((_bstr_t)sql1, NULL, adCmdText);
	}
	AfxMessageBox(_T("更新完成！"));

}


BOOL CDayPay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Listdate.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_Listdate.InsertColumn(0, _T("时间"), LVCFMT_LEFT, 210, 0);
	m_Listdate.InsertColumn(1, _T("收入/元"), LVCFMT_LEFT, 100, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
