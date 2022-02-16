#pragma once


// CDiancaiDlg 对话框

class CDiancaiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDiancaiDlg)

public:
	CDiancaiDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDiancaiDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_Diancai
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CString m_deskName;//桌号，由开台对话框赋予
	CListCtrl m_foodMenu;
	CListCtrl m_FoodOrder;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonjiacai();
	afx_msg void OnBnClickedButtonjiancai();
	afx_msg void OnDblclkDiancai1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkDiancai2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickeddiancaicomfirm();
	afx_msg void OnBnClickeddaincaicancel();
	afx_msg void OnLvnItemchangeddiancai1(NMHDR *pNMHDR, LRESULT *pResult);
};
