// CKaitaiDlg.cpp: 实现文件
//

#include "pch.h"
#include "canyin.h"
#include "CKaitaiDlg.h"
#include "afxdialogex.h"

#include "CDiancaiDlg.h"


// CKaitaiDlg 对话框

IMPLEMENT_DYNAMIC(CKaitaiDlg, CDialogEx)

CKaitaiDlg::CKaitaiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_kaitaiDlg, pParent)
	, m_deskNum(_T(""))
{

}

CKaitaiDlg::~CKaitaiDlg()
{
}

void CKaitaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_desk, m_DeskList);
	DDX_Text(pDX, IDC_Desk, m_deskNum);
}


BEGIN_MESSAGE_MAP(CKaitaiDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_desk, &CKaitaiDlg::OnDblclkListDesk)
	ON_BN_CLICKED(IDC_Cancel_desk, &CKaitaiDlg::OnBnClickedCanceldesk)
	ON_BN_CLICKED(IDC_Select, &CKaitaiDlg::OnBnClickedSelect)
END_MESSAGE_MAP()


// CKaitaiDlg 消息处理程序

//初始化列表
BOOL CKaitaiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置窗口图标
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2)), TRUE);
	//为列表控件设置格式
	m_DeskList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_ONECLICKACTIVATE);
	//添加列
	m_DeskList.InsertColumn(0, _T("桌号"), LVCFMT_LEFT, 100, 0);
	m_DeskList.InsertColumn(1, _T("状态"), LVCFMT_LEFT, 100, 1);

	//查询数据
	_bstr_t sql = "select * from tableuse";
	m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
	int i = 0;//控制列表显示
	while (m_pRecord->adoEOF == 0)
	{
		CString str = (char *)(_bstr_t)m_pRecord->GetCollect("桌号");
		int useid = atoi((char *)(_bstr_t)m_pRecord->GetCollect("TableUsedID"));
		m_DeskList.InsertItem(i, "");//插入一行
		m_DeskList.SetItemText(i, 0, str);
		if (useid == 0) {
			m_DeskList.SetItemText(i, 1, "空闲中");
		}
		if (useid == 1) {
			m_DeskList.SetItemText(i, 1, "使用中");
		}
		i++;
		m_pRecord->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



//处理列表双击事件
void CKaitaiDlg::OnDblclkListDesk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	//获取所在行第一列的文本
	str = m_DeskList.GetItemText(m_DeskList.GetSelectionMark(), 0);
	m_deskNum = str;
	UpdateData(FALSE);
	*pResult = 0;
}


void CKaitaiDlg::OnBnClickedCanceldesk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


//选择台号
void CKaitaiDlg::OnBnClickedSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_deskNum.IsEmpty()) {
		AfxMessageBox(_T("桌号不能为空！"));
	}
	else {
		_bstr_t sql = "select * from tableuse where [TableUsedID]=1";
		m_pRecord = theApp.m_pConnection->Execute(sql, NULL, adCmdText);
		CString value1;
		while (m_pRecord->adoEOF == 0)
		{
			value1 = (char *)(_bstr_t)m_pRecord->GetCollect("桌号");
			if (m_deskNum == value1) {
				AfxMessageBox(_T("本桌已被使用！"));
				m_deskNum = _T("");
				UpdateData(FALSE);
				return;
			}
			m_pRecord->MoveNext();
		}
		//证明没被使用，进入点菜界面
		m_pRecord = NULL;//指针初始化
		CDiancaiDlg diancai1;
		diancai1.m_deskName = m_deskNum;//赋予桌号
		if (diancai1.DoModal() == IDOK)
		{
			CDialog::OnOK();//点菜完成，退出
		}
	}
}
