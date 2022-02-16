// CChangeAuthDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CChangeAuthDlg.h"
#include "afxdialogex.h"


// CChangeAuthDlg 对话框


IMPLEMENT_DYNAMIC(CChangeAuthDlg, CDialogEx)

CChangeAuthDlg::CChangeAuthDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_personQuanxian, pParent)
	, m_nameGet(_T(""))
{

}

CChangeAuthDlg::~CChangeAuthDlg()
{
}

void CChangeAuthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOauthority, m_authority);
	DDX_Control(pDX, IDC_EDIT_userName, m_name);
	DDX_Control(pDX, IDC_LISTpersonAuthority, m_showName);
	DDX_Text(pDX, IDC_EDIT_userName, m_nameGet);
}


BEGIN_MESSAGE_MAP(CChangeAuthDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTpersonAuthority, &CChangeAuthDlg::OnDblclkListpersonauthority)
	ON_BN_CLICKED(IDC_BUTTON_updateAutho, &CChangeAuthDlg::OnBnClickedButtonupdateautho)
END_MESSAGE_MAP()


// CChangeAuthDlg 消息处理程序


BOOL CChangeAuthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON6)), TRUE);
	//初始化下拉框
	CString dp[3];
	dp[0] = _T("0");
	dp[1] = _T("1");
	dp[2] = _T("2");
	for (int i = 0; i < 3; ++i) {
		m_authority.AddString(dp[i]);
	}
	m_authority.InsertString(0, _T("Start"));
	m_authority.SetCurSel(0);

	//初始化列控件
	m_showName.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_showName.InsertColumn(0, _T("用户"), LVCFMT_LEFT, 100, 0);
	m_showName.InsertColumn(1, _T("权限"), LVCFMT_LEFT, 100, 1);

	_bstr_t sql = "select * from Login";
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_pRecord->adoEOF == 0)
	{
		CString use1 = (char*)(_bstr_t)m_pRecord->GetCollect("UserName");
		CString quanxian = (char*)(_bstr_t)m_pRecord->GetCollect("power");
		m_showName.InsertItem(0, "");
		m_showName.SetItemText(0, 0, use1);
		m_showName.SetItemText(0, 1, quanxian);
		m_pRecord->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//双击框选人名
void CChangeAuthDlg::OnDblclkListpersonauthority(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int i = m_showName.GetSelectionMark();//获取序号
	CString name1 = m_showName.GetItemText(i, 0);
	m_name.SetWindowTextA(name1);
	*pResult = 0;
}


void CChangeAuthDlg::OnBnClickedButtonupdateautho()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_authority.GetLBText(m_authority.GetCurSel(), str);
	if (str == "Start") {
		AfxMessageBox(_T("请选择权限！"));
		return;
	}
	int Autho_change = atoi(str);
	UpdateData(TRUE);
	CString user_name = m_nameGet;
	CString sql;
	sql.Format("update Login set [power]=%d where [UserName]='%s'", Autho_change, user_name);
	theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
	CDialog::OnOK();
}
