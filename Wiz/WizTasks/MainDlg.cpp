// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

#include "TodoDlg.h"

#include "RemindEventDlg.h"

#include "ConfigHotkeyDlg.h"
#include "ConfigGeneralDlg.h"

#include "TodoSettings.h"

#include "../Globals/WizKMCommonUI.h"

#include "../WizWebCapture/WizWebCapture_i.h"
#include "../WizKMControls/WizKMControls_i.h"

#include "../../WizGlobals/WizPropertySheetEx.h"

#include <algorithm>


#define ID_TIMER_EVENT_REMINDER		101
#define ID_TIMER_CHECK_WINDOW_POS	103

#define WIDTH_LEFT_BAR		16

CMainDlg* CMainDlg::m_spMainDlg = NULL;

CMainDlg::CMainDlg(LPCTSTR lpszCommandLine)
	: m_strCommandLine(lpszCommandLine)
	, m_dwLastSyncTickCount(0)
	, m_bSyncEnabled(TRUE)
	, m_nSyncMinutes(15)
{
	m_bSuspend = FALSE;
	//
	m_spMainDlg = this;
	//
	LoadSettings();
}
//
CMainDlg::~CMainDlg()
{
	m_db.Close();
}

BOOL CMainDlg::OpenDatabase()
{
	if (!m_db.DefaultOpen(WizGetCommandLineValue(m_strCommandLine, _T("DatabasePath"))))
	{
		return FALSE;
	}
	//
	return TRUE;
}

void CMainDlg::LoadSettings()
{
	m_bSyncEnabled = GetSyncEnabled();
	m_nSyncMinutes = GetSyncMinutes();
}
CMainDlg* CMainDlg::GetMainDlg()
{
	ATLASSERT(m_spMainDlg);
	return m_spMainDlg;
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	AutoSync();
	//
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	WizTranslationsTranslateWindow(m_hWnd);
	//
	m_databaseWindow.Register(m_db.GetDatabasePath(), m_hWnd, WIZKM_DATABASE_WINDOW_TODO);
	//
	SetWindowText(_T("WizTasks"));
	//
	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);
	//
	InstallIcon(WizFormatString0(IDS_WIZTODO), hIconSmall, IDR_MENU_TRAY);
	//
	ResetEvents();
	//
	SetTimer(ID_TIMER_EVENT_REMINDER, 1000 * 10);	///每隔10秒检查一次////
	SetTimer(ID_TIMER_CHECK_WINDOW_POS, 1000 * 3);	///每隔3秒检查一次窗口////
	//
	m_dwLastSyncTickCount = GetTickCount() - int((m_nSyncMinutes - 0.5) * 1000 * 60);
	//
	RegisterAllHotkeys();
	//
	ProcessCommandLine(m_strCommandLine);
	/////加载上次关闭的时候，显示在桌面的任务列表////
	LoadTodoListsStatus();
	/////检查是否没有任何任务列表/////
	CheckEmptyTodoList();
	/////检查是否有默认的任务列表/////
	CheckDefaultTodoList();
	//
	WizRegisterShowDesktopEvents(m_hWnd);

	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
	//
	RemoveIcon();
	//
	DestroyAllTodoLists();
	DestroyAllRemindEvent();
	//

	WizDestroyShowDesktopEventsWindow();

	return 0;
}

LRESULT CMainDlg::OnQueryEndSession(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RemoveIcon();

	return TRUE;
}

void CMainDlg::DestroyAllRemindEvent()
{
	for (CRemindEventDlgArray::const_iterator it = m_arrayRemindEvent.begin();
		it != m_arrayRemindEvent.end();
		it++)
	{
		CRemindEventDlg* pDlg = *it;
		if (pDlg->IsWindow())
		{
			pDlg->DestroyWindow();
		}
		//
		delete pDlg;
	}
	//
	m_arrayRemindEvent.clear();
}

void CMainDlg::DestroyAllTodoLists()
{
	try
	{
		for (CTodoDlgArray::const_iterator it = m_arrayTodoList.begin();
			it != m_arrayTodoList.end();
			it++)
		{
			CTodoDlg* pDlg = *it;
			if (pDlg)
			{
				if (pDlg->IsWindow())
				{
					pDlg->DestroyWindow();
				}
				//
				delete pDlg;
			}
		}
		//
		m_arrayTodoList.clear();
	}
	catch (...)
	{
	}
}

void CMainDlg::CheckEmptyTodoList()
{
	/////如果已经显示了任务列表，那么肯定有任务列表了////
	if (!m_arrayTodoList.empty())
		return;

	CWizDocumentArray arrayAllTodoList;
	//
	WizKMGetTodo2Documents(&m_db, WizKMTodoGetInboxLocation(), arrayAllTodoList);
	if (!arrayAllTodoList.empty())
		return;
	//
	CTodoDlg* pDlg = CreateNewTodoDlg(NULL, NULL);
	/////强制保存，自动生成一个任务列表/////
	pDlg->SaveData();
}

void CMainDlg::CheckDefaultTodoList()
{
	CWizDocumentArray arrayAllTodoList;
	//
	WizKMGetTodo2Documents(&m_db, WizKMTodoGetInboxLocation(), arrayAllTodoList);
	ATLASSERT(!arrayAllTodoList.empty());
	//
	bool hasDefault = false;
	for (CWizDocumentArray::const_iterator it = arrayAllTodoList.begin();
		it != arrayAllTodoList.end();
		it++)
	{
		CComPtr<IWizDocument> spDocument = *it;
		bool isDefault = CWizKMDatabase::GetDocumentParam(spDocument, _T("DefaultTodoList")) == _T("1") ? true : false;
		if (isDefault)
		{
			if (hasDefault)
			{
				/////正常情况下不应该出现/////
				ATLASSERT(FALSE);
				CWizKMDatabase::SetDocumentParam(spDocument, _T("DefaultTodoList"), LPCTSTR(_T("0")));
			}
			hasDefault = true;
		}
	}

	if (!hasDefault)
	{
		CWizKMDatabase::SetDocumentParam(*arrayAllTodoList.begin(), _T("DefaultTodoList"), LPCTSTR(_T("1"))); 
	}
}

void CMainDlg::ShowTodoList(IWizDocument* pDocument)
{
	if (!pDocument)
		return;
	//
	CString strGUID = CWizKMDatabase::GetObjectGUID<IWizDocument>(pDocument);
	//
	try
	{
		for (CTodoDlgArray::const_iterator it = m_arrayTodoList.begin();
			it != m_arrayTodoList.end();
			it++)
		{
			CTodoDlg* pDlg = *it;
			if (!pDlg)
			{
				ATLASSERT(FALSE);
				continue;
			}
			//
			CComPtr<IWizDocument> sp = pDlg->GetDocument();
			if (!sp)
				continue;
			//
			CString str = CWizKMDatabase::GetObjectGUID<IWizDocument>(sp);
			if (0 != str.CompareNoCase(strGUID))
				continue;
			//
			if (!pDlg->IsWindow())
			{
				pDlg->Create(NULL);
			}
			//
			pDlg->BringWindowToTopEx();
			//
			return;
		}
	}
	catch (...)
	{
	}
	//
	CTodoDlg* pDlg = CreateNewTodoDlg(pDocument, _T(""));
	pDlg->BringWindowToTopEx();
}

void CMainDlg::SaveTodoListsStatus()
{
	CWizStdStringArray arrayGUID;
	try
	{
		for (CTodoDlgArray::const_iterator it = m_arrayTodoList.begin();
			it != m_arrayTodoList.end();
			it++)
		{
			CTodoDlg* pDlg = *it;
			if (!pDlg)
			{
				ATLASSERT(FALSE);
				continue;
			}
			//
			CComPtr<IWizDocument> sp = pDlg->GetDocument();
			if (!sp)
				continue;
			//
			CString str = CWizKMDatabase::GetObjectGUID<IWizDocument>(sp);
			//
			if (!pDlg->IsWindow())
				continue;
			//
			if (0 == (pDlg->GetStyle() & WS_VISIBLE))
				continue;
			//
			arrayGUID.push_back(str);
		}
	}
	catch (...)
	{
	}
	//
	::SetVisibleTodoLists(arrayGUID);
}
void CMainDlg::LoadTodoListsStatus()
{
	CWizStdStringArray arrayGUID;
	if (!GetVisibleTodoLists(arrayGUID))
		return;
	//
	for (CWizStdStringArray::const_iterator it = arrayGUID.begin();
		it != arrayGUID.end();
		it++)
	{
		CString strGUID = *it;
		CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(strGUID);
		if (!spDocument)
			continue;
		//
		ShowTodoList(spDocument);
	}
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	//CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnTrayExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CloseDialog(IDOK);

	return 0;
}


void CMainDlg::OnTrayPrepareMenu(HMENU hMenu)
{
	CMenuHandle menu(hMenu);
	//
	BOOL bVisible = (GetStyle() & WS_VISIBLE) ? TRUE : FALSE;
	CString strMenuText = WizFormatString0(bVisible ? IDS_MINIMIZE : IDS_RESTORE);
	TCHAR szMenuText[MAX_PATH] = { 0 };
	_tcscpy_s(szMenuText, MAX_PATH, strMenuText);
	//
	BOOL bWizExplorerExists = WizKMExplorerExists();
	//
	if (!bWizExplorerExists)
	{
		for (int i = 18; i >= 12; i--)
		{
			menu.DeleteMenu(i, MF_BYPOSITION);
		}
	}
	//
	m_hotkeys.UpdateHotKeyToMenu(menu);
	//
	CString strActionName = GetDoubleClickAction();
	if (0 == strActionName.CompareNoCase(_T("NewTodoList")))
	{
		m_nDefault = ID_TRAY_NEW_TODOLIST;
	}
	else
	{
		m_nDefault = ID_TRAY_SHOW_ALL_TODOLISTS;
	}
	//
	m_mapDocumentMenuID.clear();
	//
	CWizDocumentArray arrayTodoList;
	WizKMGetTodo2Documents(&m_db, WizKMTodoGetInboxLocation(), arrayTodoList);
	if (!arrayTodoList.empty())
	{
		menu.InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR);
		//
		UINT index = 0;
		for (CWizDocumentArray::const_iterator it = arrayTodoList.begin();
			it != arrayTodoList.end() && index < 20;
			it++)
		{
			CComPtr<IWizDocument> spDocument = *it;
			CString strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
			UINT nID = ID_TODO_LIST_BEGIN + index;

			UINT flags = MF_BYPOSITION | MF_STRING;
			bool isDefault = CWizKMDatabase::GetDocumentParam(spDocument, _T("DefaultTodoList")) == _T("1") ? true : false;
			if (isDefault)
			{
				strTitle += WizFormatString0(IDS_DEFAULT_TODOLIST);
			}
			menu.InsertMenu(index, flags, nID,  strTitle);
			if (isDefault)
			{
				SetMenuDefaultItem(menu, nID, FALSE);
			}

			//
			index++;
			//
			m_mapDocumentMenuID[nID] = spDocument;
		}
	}
}


void CMainDlg::OnTrayLButtonDblclk()
{
	CString strActionName = GetDoubleClickAction();
	//
	if (0 == strActionName.CompareNoCase(_T("NewTodoList")))
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_NEW_TODOLIST, 0), 0);
	}
	else
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_SHOW_ALL_TODOLISTS, 0), 0);
	}
}



LRESULT CMainDlg::OnCalendarEventModified(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	ResetEvents();
	//
	return 0;
}
void CMainDlg::RefreshEvents()
{
	ResetEvents();
}

void CMainDlg::RefreshTodoLists()
{
}

LRESULT CMainDlg::OnRefreshEvents(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RefreshEvents();
	return 0;
}

LRESULT CMainDlg::OnRefreshTodoLists(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RefreshTodoLists();
	return 0;
}

LRESULT CMainDlg::OnSaveTodoListsStatus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	SaveTodoListsStatus();
	return 0;
}

void CMainDlg::RegisterAllHotkeys()
{
	if (m_hotkeys.IsRegistered())
	{
		m_hotkeys.UnregisterAll();
	}
	//
	CWizHotKeyDataArray arrayHotKey;
	//
	CWizKMSettings settings;
	//
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY, HOTKEY_NAME_NEW_TODOLIST, HOTKEY_DEFAULT_NEW_TODOLIST), ID_TRAY_NEW_TODOLIST));
	arrayHotKey.push_back(WIZHOTKEYDATA(settings.GetStr(SECTION_HOTKEY, HOTKEY_NAME_SHOW_ALL_TODOLISTS, HOTKEY_DEFAULT_SHOW_ALL_TODOLISTS), ID_TRAY_SHOW_ALL_TODOLISTS));
	//
	CString strError;
	if (!m_hotkeys.RegisterAll(m_hWnd, arrayHotKey, strError))
	{
		CString strMsg = WizFormatString1(IDS_REGISTER_HOTKEY_FAILED, strError);
		//
		WizKMShowBubbleWindow2Background(WizGetProductName(), strMsg, strMsg, WIZCOLOR_PINK, 10, WIZBUBBLE_SHOWLINKURLASMESSAGE);
	}
}

void CMainDlg::ResetEvents()
{
	m_arrayEvent.clear();
	//
	COleDateTime t = COleDateTime::GetCurrentTime();
	COleDateTime tBegin = t - COleDateTimeSpan(1, 0, 0, 0);		//获得一天前的事件
	COleDateTime tEnd = t + COleDateTimeSpan(3 * 7, 0, 0, 0);		//提前获得三周事件
	//
	m_db.GetCalendarEvents(tBegin, tEnd, m_arrayEvent);
	//
	size_t nEventCount = m_arrayEvent.size();
	for (intptr_t i = nEventCount - 1; i >= 0; i--)
	{
		CComPtr<IWizEvent> spEvent = m_arrayEvent[i];
		//
		long nReminder = -1;
		spEvent->get_Reminder(&nReminder);
		//
		VARIANT_BOOL vbCompleted = VARIANT_FALSE;
		spEvent->get_Completed(&vbCompleted);
		//
		if (-1 == nReminder
			|| vbCompleted)
		{
			m_arrayEvent.erase(m_arrayEvent.begin() + i);
		}
	}
	//
	int nReminderCount = (int)m_arrayRemindEvent.size();
	for (intptr_t i = nReminderCount - 1; i>= 0; i--)
	{
		CRemindEventDlg* pDlg = m_arrayRemindEvent[i];
		if (!pDlg)
			continue;
		//
		if (!pDlg->IsWindow())
		{
			m_arrayRemindEvent.erase(m_arrayRemindEvent.begin() + i);
			continue;
		}
		//
		//
		CComPtr<IWizEvent> spEvent = pDlg->GetEvent();
		if (!spEvent)
			continue;
		//
		spEvent->Reload();
		//
		VARIANT_BOOL vbCompleted = VARIANT_FALSE;
		spEvent->get_Completed(&vbCompleted);
		//
		if (!vbCompleted)
			continue;
		//
		m_arrayRemindEvent.erase(m_arrayRemindEvent.begin() + i);
		//
		pDlg->ShowWindow(SW_HIDE);
		pDlg->DestroyWindow();
		delete pDlg;
	}
}



LRESULT CMainDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	UINT nID = (UINT)wParam;
	//
	bHandled = FALSE;
	//
	if (ID_TIMER_EVENT_REMINDER == nID)
	{
		bHandled = TRUE;
		//
		CheckReminder();
	}
	else if (ID_TIMER_CHECK_WINDOW_POS == nID)
	{
		bHandled = TRUE;
		//
		WizCheckWindowTopMost(m_hWnd);
	}
	//
	return 0;
}

void CMainDlg::CheckReminder()
{
	static COleDateTime tOld = ::WizGetCurrentTime();
	COleDateTime tNow = ::WizGetCurrentTime();
	if (tOld.GetDay() != tNow.GetDay())
	{
		ResetEvents();
		tOld = tNow;
	}
	//
	for (CWizEventArray::const_iterator it = m_arrayEvent.begin();
		it != m_arrayEvent.end();
		it++)
	{
		CComPtr<IWizEvent> spEvent = *it;
		//
		long nReminder = -1;
		spEvent->get_Reminder(&nReminder);
		//
		VARIANT_BOOL vbCompleted = VARIANT_FALSE;
		spEvent->get_Completed(&vbCompleted);
		//
		if (nReminder == -1
			|| vbCompleted)
			continue;
		//
		CComBSTR bstrGUID;
		spEvent->get_GUID(&bstrGUID);
		//
		if (m_setReminded.find(CString(bstrGUID)) != m_setReminded.end())
			continue;
		//
		DATE dtStart = 0;
		spEvent->get_Start(&dtStart);
		//
		COleDateTime tStart = dtStart;
		COleDateTime tBeginReminder = tStart - COleDateTimeSpan(0, 0, 0, nReminder);
		//
		if (COleDateTime::GetCurrentTime() > tBeginReminder)
		{
			RemindEvent(spEvent);
		}
	}
}

void CMainDlg::Sync()
{
	m_dwLastSyncTickCount = GetTickCount();
	WizKMShellSync(m_db.GetDatabasePath(), TRUE);
}
void CMainDlg::AutoSync()
{
	if (!m_bSyncEnabled)
		return;
	if (m_bSuspend)
		return;
	//
	//第一次不检查是否有改变。
	//
	DWORD dwTickCount = GetTickCount();
	if (dwTickCount - m_dwLastSyncTickCount > m_nSyncMinutes * 60 * 1000)
	{
		Sync();
	}
}

void CMainDlg::RemindEvent(IWizEvent* pEvent)
{
	if (!pEvent)
		return;
	//
	CComBSTR bstrGUID;
	pEvent->get_GUID(&bstrGUID);
	//
	CString strGUID(bstrGUID);
	m_setReminded.insert(strGUID);
	//
	CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(strGUID);
	if (!spDocument)
		return;
	//
	//
	CRemindEventDlg* pDlg = new CRemindEventDlg(pEvent);
	//
	pDlg->Create(NULL);
	//
	m_arrayRemindEvent.push_back(pDlg);
	//
	pDlg->ShowWindow(SW_SHOW);
}


LRESULT CMainDlg::OnHelpManual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMWebSiteVisitHelp(_T("wiztasks"));

	return 0;
}

LRESULT CMainDlg::OnHelpAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	WizKMAbout(IDS_WIZTODO);

	return 0;
}


LRESULT CMainDlg::OnHotKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CWaitCursor wait;
	UINT nID = (UINT)wParam;
	if (ID_TRAY_NEW_TODOLIST == nID
		|| ID_TRAY_SHOW_ALL_TODOLISTS == nID
		)
	{
		PostMessage(WM_COMMAND, MAKEWPARAM(nID, 0), 0);
	}
	//
	return 0;
}


LRESULT CMainDlg::OnTrayOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CWizPropertySheetEx ps(IDS_OPTIONS);
	ps.m_psh.dwFlags |= (PSH_NOAPPLYNOW | PSH_NOCONTEXTHELP);
	//
	CConfigHotkeyDlg dlgHotkey;
	CConfigGeneralDlg dlgGeneral;
	//
	ps.AddPage(dlgGeneral);
	ps.AddPage(dlgHotkey);
	//
	if (IDOK != ps.DoModal())
		return 0;
	//
	LoadSettings();
	RegisterAllHotkeys();
	//
	return 0;
}

void CMainDlg::OnSyncEnd(int nExitCode, UINT nFlags)
{
	m_dwLastSyncTickCount = GetTickCount();
	//
	ResetEvents();
	//
	for (CTodoDlgArray::const_iterator it = m_arrayTodoList.begin();
		it != m_arrayTodoList.end();
		it++)
	{
		CTodoDlg* pTodoDlg = *it;
		if (pTodoDlg 
			&& pTodoDlg->IsWindow()
			&& !pTodoDlg->IsModified())
		{
			pTodoDlg->Refresh();
		}
	}
}

LRESULT CMainDlg::OnTrayWizCalendar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CString strParams = WizFormatString1(_T("/DatabasePath=%1"), m_db.GetDatabasePath());
	//
	ShellExecute(NULL, _T("open"), WizGetAppPath() + _T("WizKMCalendar.exe"), strParams, NULL, SW_SHOW);

	return 0;
}

#define WIZTODO_COMMAND_LINE_REG_KEY			(WIZKM_REG_KEY_ROOT + _T("\\Todo"))
#define WIZTODO_COMMAND_LINE_REG_KEY_VALUE		_T("CommandLine")

BOOL CMainDlg::WriteCommandLineToReg(LPCTSTR lpszCommandLine)
{
	return WizRegWriteString(HKEY_CURRENT_USER, WIZTODO_COMMAND_LINE_REG_KEY, WIZTODO_COMMAND_LINE_REG_KEY_VALUE, lpszCommandLine);
}
BOOL CMainDlg::ReadCommandLineToReg(CString& strCommandLine, BOOL bClear)
{
	strCommandLine = WizRegReadStringDef(HKEY_CURRENT_USER, WIZTODO_COMMAND_LINE_REG_KEY, WIZTODO_COMMAND_LINE_REG_KEY_VALUE, _T(""));
	if (bClear)
	{
		WizRegDeleteValue(HKEY_CURRENT_USER, WIZTODO_COMMAND_LINE_REG_KEY, WIZTODO_COMMAND_LINE_REG_KEY_VALUE);
	}
	return TRUE;
}
LRESULT CMainDlg::OnProcessCommandLine(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CString strCommandLine;
	if (!ReadCommandLineToReg(strCommandLine, TRUE))
		return 0;
	//
	ProcessCommandLine(strCommandLine, wParam ? TRUE : FALSE);
	//
	return 0;
}
void CMainDlg::ProcessCommandLine(LPCTSTR lpszCommandLine, BOOL bPrompt /*= FALSE*/)
{
	CString strCommand = ::WizGetCommandLineValue(lpszCommandLine, _T("Command"));
	strCommand.MakeLower();
	//
	if (strCommand.IsEmpty() && bPrompt)
	{
		ShowBalloon(WizFormatString0(IDS_WIZTODO), WizFormatString0(IDS_WIZTODO_IS_RUNNING), 10);
	}
	else if (strCommand == _T("edit_todolist"))
	{
		CString strDocumentGUID = ::WizGetCommandLineValue(lpszCommandLine, _T("DocumentGUID"));
		if (strDocumentGUID.IsEmpty())
			return;
		//
		CComPtr<IWizDocument> spDocument = m_db.GetDocumentByGUID(strDocumentGUID);
		if (!spDocument)
			return;
		//
		/*
		CreateTodoDlg();
		//
		m_pTodoDlg->SetDocument(spDocument);
		m_pTodoDlg->BringWindowToTopEx();
		m_pTodoDlg->CenterWindow(GetDesktopWindow());
		m_pTodoDlg->SetInfoModified(FALSE);
		*/
	}
}



LRESULT CMainDlg::OnHiddenNewblanktodolist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	SetForegroundWindow(m_hWnd);
	//
	CreateNewTodoDlg(NULL, _T(""));

	return 0;
}


LRESULT CMainDlg::OnTrayNewTodoList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetForegroundWindow(m_hWnd);
	//
	CString strTitle;
	if (!WizKMInputBox(IDS_NEW_TODOLIST, IDS_TODOLIST_TITLE_DESCRIPTION, IDS_NEW_TODOLIST_TITLE, strTitle))
		return 0;
	//
	CreateNewTodoDlg(NULL, strTitle);
	//
	return 0;
}

LRESULT CMainDlg::OnTrayShowAllTodolists(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	SetForegroundWindow(m_hWnd);

	CWizDocumentArray arrayTodoList;
	WizKMGetTodo2Documents(&m_db, WizKMTodoGetInboxLocation(), arrayTodoList);
	if (!arrayTodoList.empty())
	{
		UINT index = 0;
		for (CWizDocumentArray::const_iterator it = arrayTodoList.begin();
			it != arrayTodoList.end() && index < 20;
			it++)
		{
			CComPtr<IWizDocument> spDocument = *it;
			ShowTodoList(spDocument);
		}
	}
	SaveTodoListsStatus();
	//
	return 0;
}

LRESULT CMainDlg::OnTodoList(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CDocumentMenuIDMap::const_iterator it = m_mapDocumentMenuID.find(wID);
	if (it == m_mapDocumentMenuID.end())
		return 0;
	//
	CComPtr<IWizDocument> spDocument = it->second;
	if (!spDocument)
		return 0;
	//
	ShowTodoList(spDocument);
	//
	SaveTodoListsStatus();
	//
	return 0;
}

CTodoDlg* CMainDlg::CreateNewTodoDlg(IWizDocument* pDoc, LPCTSTR lpszTitle)
{
	CTodoDlg* pDlg = new CTodoDlg(&m_db, lpszTitle);
	pDlg->Create(NULL);
	//
	if (pDoc)
	{
		pDlg->SetDocument(pDoc);
	}
	else
	{
		pDlg->InitNewTodoList();
	}
	//
	pDlg->ShowWindow(SW_SHOW);
	//
	m_arrayTodoList.push_back(pDlg);
	//
	return pDlg;
}


LRESULT CMainDlg::OnTraySync(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	Sync();
	//
	return 0;
}


LRESULT CMainDlg::OnIsHotKeyRegistered(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_hotkeys.IsRegistered();
}

LRESULT CMainDlg::OnCloseWindowForAutoUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_EXIT, 0), 0);
	return 0;
}

LRESULT CMainDlg::OnPowerBroadcast(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch ((UINT)wParam)
	{
	case PBT_APMSUSPEND:
		OnPowerSuspend();
		break;
	case PBT_APMRESUMEAUTOMATIC:
	case PBT_APMRESUMESUSPEND:
	case PBT_APMRESUMECRITICAL:
		OnPowerResume();
		break;
	}
	//
	return 0;
}
void CMainDlg::ResetSyncTickCount()
{
	m_dwLastSyncTickCount = GetTickCount() - int((m_nSyncMinutes - 1) * 1000 * 60);
}
void CMainDlg::OnPowerResume()
{
	ResetSyncTickCount();
	//
	m_bSuspend = FALSE;
}
void CMainDlg::OnPowerSuspend()
{
	m_bSuspend = TRUE;
}

LRESULT CMainDlg::OnShowDesktop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bool bShowDesktop = wParam ? true : false;
	//
	for (CTodoDlgArray::const_iterator it = m_arrayTodoList.begin();
		it != m_arrayTodoList.end() ;
		it++)
	{
		CTodoDlg *pDlg = *it;
		if ((pDlg->GetDlgState() == statePinDesk) && ((pDlg->GetStyle() & WS_VISIBLE) != 0))
		{
			if (bShowDesktop)
			{
				pDlg->SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | /*SWP_NOACTIVATE | */SWP_NOSENDCHANGING);
				::SetForegroundWindow(pDlg->m_hWnd);
			}
			else
			{
				pDlg->SetWindowPos(HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
			}
		}
	}
	return 0;
}

LRESULT CMainDlg::OnTrayShowCompletedTodoLists(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//// 代码应该不对，运行就会把已完成任务给清空了////
	////之前的代码不对，是因为没有判断一个任务列表是否是已经完成的，结果导致重复收集已完成任务////

	SetForegroundWindow(m_hWnd);

	CWizDocumentArray arrayTodoList;
	WizKMGetTodo2Documents(&m_db, WizKMTodoGetCompletedLocation(), arrayTodoList);
	if (!arrayTodoList.empty())
	{
		UINT index = 0;
		for (CWizDocumentArray::const_iterator it = arrayTodoList.begin();
			it != arrayTodoList.end() && index < 20;
			it++)
		{
			CComPtr<IWizDocument> spDocument = *it;
			ShowTodoList(spDocument);
		}
	}
	SaveTodoListsStatus();

	return 0;
}
