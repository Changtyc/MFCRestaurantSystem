#pragma once


// CDayCheckDlg 对话框

class CDayCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDayCheckDlg)

public:
	CDayCheckDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDayCheckDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DayCheckDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_ptrRecord;
	CListCtrl m_daybill;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtondaybillcheck();
	afx_msg void OnBnClickedButtonchecknew();
};
