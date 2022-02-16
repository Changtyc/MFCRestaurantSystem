// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


//声明全局变量theApp
extern CcanyinApp theApp;

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LoginDlg, pParent)
	, m_Name(_T(""))
	, m_Secret(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_Secret);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_Login, &CLoginDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_Cancel, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_Name.IsEmpty() || m_Secret.IsEmpty()) {
		AfxMessageBox(_T("用户名和密码不能为空"));
		return;
	}
	_bstr_t sqlToExecute = "select * from Login where [UserName]='" + m_Name + "' and [password]='" + m_Secret + "'";

	m_pRecord = theApp.m_pConnection->Execute(sqlToExecute, NULL, adCmdText);
	if (m_pRecord->adoEOF) {
		AfxMessageBox(_T("用户名或密码不正确!"));
		m_Name = _T("");
		m_Secret = _T("");
		UpdateData(false);
	}
	else {
		theApp.userName = m_Name;
		theApp.pwd = m_Secret;
		AfxMessageBox(_T("登录成功！"));
		CDialog::OnOK();
		return;
	}

}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


//添加回车处理消息
BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedLogin();
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
