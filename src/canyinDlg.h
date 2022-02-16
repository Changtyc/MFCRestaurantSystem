
// canyinDlg.h: 头文件
//

#pragma once
#include "CDayPay.h"
#include "CDayCheckDlg.h"


// CcanyinDlg 对话框
class CcanyinDlg : public CDialogEx
{
	// 构造
public:
	CcanyinDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CANYIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CMenu m_menu;
	CImageList m_imageList;
	CToolBar m_toolbar;
	CStatusBar m_statusBar;
	_RecordsetPtr m_pRecord;//数据库数据集

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickelogin();
	afx_msg void OnBnClickeRegister();
	afx_msg void OnBnClickekaitai();
	afx_msg void OnFoodjiajian();
	afx_msg void OnBnClickejiezhang();
	afx_msg void OnClickAbout();
	afx_msg void OnBnClickeGoOut();
	CTabCtrl m_tabR;
	CDayPay m_daypay;
	CDayCheckDlg m_daycheckBill;
	afx_msg void OnDaypay();
	afx_msg void Oncaishiinfomanager();
	afx_msg void Onpeoplemanager();
	afx_msg void Onauthoritychange();
	afx_msg void Ondaycheck();
};
