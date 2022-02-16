#pragma once


// CDayPay 对话框

class CDayPay : public CDialogEx
{
	DECLARE_DYNAMIC(CDayPay)

public:
	CDayPay(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDayPay();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DayPayDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	afx_msg void OnBnClickedButtonyiyue();
	afx_msg void OnBnClickedButtonchaxun();
	CString m_dateNow;
	CString m_shouruDay;
	CListCtrl m_Listdate;
	virtual BOOL OnInitDialog();
};
