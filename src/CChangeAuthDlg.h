#pragma once


// CChangeAuthDlg 对话框

class CChangeAuthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeAuthDlg)

public:
	CChangeAuthDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangeAuthDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_personQuanxian };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CComboBox m_authority;
	CEdit m_name;
	CListCtrl m_showName;
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListpersonauthority(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonupdateautho();
	CString m_nameGet;
};
