#pragma once


// CRegistDlg 对话框

class CRegistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegistDlg)

public:
	CRegistDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegistDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Register };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedregister();
	_RecordsetPtr m_pRecord;//数据库数据集
	CString m_Name;
	CString m_Password;
	CString m_Comfirm;
	afx_msg void OnBnClickedcancelr();
};
