#pragma once


// CPayDlg 对话框

class CPayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPayDlg)

public:
	CPayDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPayDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_jiezhangDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CListCtrl m_xiaofeiMenu;
	//	CEdit m_get;
	CString m_get;
	CString m_theoryGet;
	CString m_send;
	CComboBox m_nameDesk;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeJiezhangdeskname();
	//	afx_msg void OnEnChangeEditshishou();
	afx_msg void OnChangeEditshishou();
	afx_msg void OnBnClickedButtontuichu();
	afx_msg void OnBnClickedButtonjiezhang();
};
