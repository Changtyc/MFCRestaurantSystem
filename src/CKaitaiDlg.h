#pragma once


// CKaitaiDlg 对话框

class CKaitaiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKaitaiDlg)

public:
	CKaitaiDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CKaitaiDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_kaitaiDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CListCtrl m_DeskList;
	CString m_deskNum;
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListDesk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCanceldesk();
	afx_msg void OnBnClickedSelect();
};
