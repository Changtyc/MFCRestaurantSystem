// CRegistDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CRegistDlg.h"
#include "afxdialogex.h"


//声明全局变量theApp
extern CcanyinApp theApp;
// CRegistDlg 对话框

IMPLEMENT_DYNAMIC(CRegistDlg, CDialogEx)

CRegistDlg::CRegistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Register, pParent)
	, m_Name(_T(""))
	, m_Password(_T(""))
	, m_Comfirm(_T(""))
{

}

CRegistDlg::~CRegistDlg()
{
}

void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_userName, m_Name);
	DDX_Text(pDX, IDC_passWord, m_Password);
	DDX_Text(pDX, IDC_passWord2, m_Comfirm);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialogEx)
	ON_BN_CLICKED(IDC_register, &CRegistDlg::OnBnClickedregister)
	ON_BN_CLICKED(IDC_cancelR, &CRegistDlg::OnBnClickedcancelr)
END_MESSAGE_MAP()


// CRegistDlg 消息处理程序


void CRegistDlg::OnBnClickedregister()
{
	// TODO: 在此添加控件通知处理程序代码
	//先更新变量
	UpdateData();
	if (m_Name.IsEmpty() || m_Comfirm.IsEmpty() || m_Password.IsEmpty()) {
		AfxMessageBox(_T("用户名和密码不能为空！"));
		return;
	}
	if (m_Password != m_Comfirm) {
		AfxMessageBox(_T("两次密码要相同！"));
		return;
	}
	////检查数据表中用户是否存在，unicode注意加上_T
	CString sql = _T("select * from Login where UserName='" + m_Name + "'");
	_bstr_t sqlToExecute = (_bstr_t)sql;
	m_pRecord = theApp.m_pConnection->Execute(sqlToExecute, NULL, adCmdText);

	if (m_pRecord->adoEOF) {
		//插入用户名、密码和权限，谨记最好加上[]，否则会和sql的关键词混淆报错
		_bstr_t sqlToExecute2 = "insert into Login([UserName],[password],[power]) values('" + m_Name + "','" + m_Password + "',0)";
		theApp.m_pConnection->Execute(sqlToExecute2, NULL, adCmdText);
		AfxMessageBox(_T("注册成功"));
		CDialogEx::OnOK();//退出
	}
	else {
		AfxMessageBox(_T("用户名已存在！"));
		return;
	}
}


//重置按钮
void CRegistDlg::OnBnClickedcancelr()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Name = _T("");
	m_Password = _T("");
	m_Comfirm = _T("");
	UpdateData(FALSE);
}
