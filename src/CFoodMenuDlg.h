#pragma once


// CFoodMenuDlg 对话框

class CFoodMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFoodMenuDlg)

public:
	CFoodMenuDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFoodMenuDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_updatecaishi };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CString m_foodName;
	CString m_FoodValue;
	CListCtrl m_MenuShow;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtoninsertfood();
	afx_msg void OnBnClickedButtondeletefood();
	afx_msg void OnDblclkListfoodchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonexitfood();
	afx_msg void OnBnClickedButtonchangefood();
};
