// CFoodNumDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CFoodNumDlg.h"
#include "afxdialogex.h"


// CFoodNumDlg 对话框

IMPLEMENT_DYNAMIC(CFoodNumDlg, CDialogEx)

CFoodNumDlg::CFoodNumDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_foodNum, pParent)
	, m_foodNum(_T(""))
{
}

CFoodNumDlg::~CFoodNumDlg()
{
}

void CFoodNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITfoodNum, m_foodNum);
}


BEGIN_MESSAGE_MAP(CFoodNumDlg, CDialogEx)
	ON_BN_CLICKED(IDC_foodcom, &CFoodNumDlg::OnBnClickedfoodcom)
	ON_BN_CLICKED(IDC_foodcancel, &CFoodNumDlg::OnBnClickedfoodcancel)
END_MESSAGE_MAP()


// CFoodNumDlg 消息处理程序

void CFoodNumDlg::OnBnClickedfoodcom()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_foodNum.IsEmpty() || m_foodNum == "0") {
		AfxMessageBox(_T("数量应大于等于1！"));
		return;
	}
	//否则返回正确的值
	CDialog::OnOK();
}


void CFoodNumDlg::OnBnClickedfoodcancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


BOOL CFoodNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3)), TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
