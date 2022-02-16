// CPersonManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CPersonManagerDlg.h"
#include "afxdialogex.h"


// CPersonManagerDlg 对话框

extern CcanyinApp theApp;

IMPLEMENT_DYNAMIC(CPersonManagerDlg, CDialogEx)

CPersonManagerDlg::CPersonManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PersonManager, pParent)
{

}

CPersonManagerDlg::~CPersonManagerDlg()
{
}

void CPersonManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOuser, m_personAll);
}


BEGIN_MESSAGE_MAP(CPersonManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONdeleteuser, &CPersonManagerDlg::OnBnClickedButtondeleteuser)
END_MESSAGE_MAP()


// CPersonManagerDlg 消息处理程序


BOOL CPersonManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5)), TRUE);
	//初始化下拉框
	_bstr_t sql = "select * from Login";
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	while (m_pRecord->adoEOF == 0)
	{
		CString zhuohao = (char*)(_bstr_t)m_pRecord->GetCollect("UserName");
		m_personAll.AddString(zhuohao);
		m_pRecord->MoveNext();
	}
	//设置默认下拉
	m_personAll.InsertString(0, _T("Start"));
	m_personAll.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPersonManagerDlg::OnBnClickedButtondeleteuser()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_personAll.DeleteString(0);
	CString str1;
	m_personAll.GetLBText(m_personAll.GetCurSel(), str1);
	int i = m_personAll.GetCurSel();
	if (str1 == _T("Start")) {
		AfxMessageBox(_T("请先选择用户！"));
		return;
	}
	CString sql;
	sql.Format("delete from Login where [UserName]='%s'", str1);
	theApp.m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
	m_personAll.DeleteString(i);
	CDialog::OnOK();
}
