#pragma once


// CPersonManagerDlg 对话框


class CPersonManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonManagerDlg)

public:
	CPersonManagerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPersonManagerDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PersonManager };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	_RecordsetPtr m_pRecord;//数据库数据集
	CComboBox m_personAll;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtondeleteuser();
};
