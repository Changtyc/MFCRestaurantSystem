#pragma once


// CIndeFoodDlg 对话框

class CIndeFoodDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIndeFoodDlg)

public:
	CIndeFoodDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CIndeFoodDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FoodIndeDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CComboBox m_dropList;
	CListCtrl m_FoodMenu1;
	//	CButton m_FoodDece;
	virtual BOOL OnInitDialog();
	CListCtrl m_FoodDecrease;
	afx_msg void OnSelchangeDesknamelist();
	afx_msg void OnBnClickedjia1();
	afx_msg void OnBnClickedjian1();
	afx_msg void OnDblclkJiacai(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkJiancai(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancelfood();
	afx_msg void OnBnClickedcomfirmfood();
};
