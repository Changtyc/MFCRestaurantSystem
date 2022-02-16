
// canyin.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CcanyinApp:
// 有关此类的实现，请参阅 canyin.cpp
//

class CcanyinApp : public CWinApp
{
public:
	CString userName;
	CString pwd;
public:
	CcanyinApp();

	//数据库
public:
	_ConnectionPtr m_pConnection;//连接access数据库的链接对象  

// 重写
public:
	virtual BOOL InitInstance();

	// 实现

	DECLARE_MESSAGE_MAP()
	//	afx_msg void Oncaishiinfomanager();
	//	afx_msg void Onpeoplemanager();
};

extern CcanyinApp theApp;
