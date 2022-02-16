
// canyin.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "canyin.h"
#include "canyinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcanyinApp

BEGIN_MESSAGE_MAP(CcanyinApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CcanyinApp 构造

CcanyinApp::CcanyinApp() :userName(_T(""))
, pwd(_T(""))
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CcanyinApp 对象

CcanyinApp theApp;


// CcanyinApp 初始化

BOOL CcanyinApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	//连接数据库----
	::CoInitialize(NULL);
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			m_pConnection->ConnectionTimeout = 3;
			//使用accdb格式
			CString conStr = _T("Provider=Microsoft.ACE.OLEDB.12.0;")
				_T("Data Source=canyin.accdb;")
				_T("Jet OLEDB:Database Password=");
			hr = m_pConnection->Open((_bstr_t)conStr, "", "", adModeUnknown);

			//用mdb格式
			//hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=canyin2.mdb", "", "", adModeUnknown);	//连接数据库

		}
	}
	catch (_com_error e)
	{
		CString temp;
		temp.Format(_T("连接数据库错误信息:%s"), e.ErrorMessage());
		::MessageBox(NULL, temp, _T("提示信息"), NULL);
		return false;
	}
	//连接数据库-----

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CcanyinDlg dlg;
	m_pMainWnd = &dlg;//设置指针
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



//菜式管理按钮
//void CcanyinApp::Oncaishiinfomanager()
//{
//	// TODO: 在此添加命令处理程序代码
//}


//员工管理按钮
//void CcanyinApp::Onpeoplemanager()
//{
//	// TODO: 在此添加命令处理程序代码
//}
