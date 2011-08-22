// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "WizShowDesktop.h"

#include "../Globals/WizKMCalendarEvents.h"

#include "../../WizGlobals/WizTrayIconImpl.h"

#include <set>

class CTodoDlg;
class CRemindEventDlg;

typedef std::vector<CTodoDlg*> CTodoDlgArray;
typedef std::vector<CRemindEventDlg*> CRemindEventDlgArray;
typedef std::set<CString> CReminderEventGUISSet;
typedef std::map<UINT, CComPtr<IWizDocument> > CDocumentMenuIDMap;

#define UM_PROCESS_COMMANDLINE		(WM_USER + 3001)
#define UM_REFRESH_EVENTS			(WM_USER + 3002)
#define UM_REFRESH_TODOLISTS		(WM_USER + 3003)
#define UM_SAVE_TODOLISTS_STATUS	(WM_USER + 3004)


const UINT UM_CALENDAREVENTMODIFIED = ::RegisterWindowMessage(WIZKM_CALENDAR_EVENT_MODIFIED_MESSAGE_NAME);

class CMainDlg 
	: public CAxDialogImpl<CMainDlg>
	, public CMessageFilter
	, public CIdleHandler
	, public CWizTrayIconImpl<CMainDlg>
	, public CWizKMSyncSimpleMessageBase<CMainDlg>
{
public:
	CMainDlg(LPCTSTR lpszCommandLine);
	~CMainDlg();
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();
	//
	virtual void OnTrayPrepareMenu(HMENU hMenu);
	virtual void OnTrayLButtonDblclk();
	//
	BOOL OpenDatabase();
private:
	CTodoDlgArray m_arrayTodoList;
	CRemindEventDlgArray m_arrayRemindEvent;
	CDocumentMenuIDMap m_mapDocumentMenuID;
	//
	CWizEventArray m_arrayEvent;
	CReminderEventGUISSet m_setReminded;
	//
	CWizKMDatabaseEx m_db;
	//
	CString m_strCommandLine;
	//
	CWizKMDatabaseWindow m_databaseWindow;
	//
	DWORD m_dwLastSyncTickCount;
	//
	BOOL m_bSyncEnabled;
	UINT m_nSyncMinutes;
	//
	BOOL m_bSuspend;
	//
	CWizHotKeyHelper m_hotkeys;
public:
	void RegisterAllHotkeys();
private:
	void ResetEvents();
	//
	void DestroyAllRemindEvent();
	void DestroyAllTodoLists();
	//
	void CheckReminder();
	void RemindEvent(IWizEvent* pEvent);
	//
	void AutoSync();
	void Sync();
	//
	CTodoDlg* CreateNewTodoDlg(IWizDocument* pDoc, LPCTSTR lpszTitle);
	//
	void ResetSyncTickCount();
	void OnPowerResume();
	void OnPowerSuspend();
	//
	void RefreshEvents();
	void RefreshTodoLists();
	void LoadSettings();
	//
	void ShowTodoList(IWizDocument* pDocument);
	//
	void SaveTodoListsStatus();
	void LoadTodoListsStatus();
private:
	static CMainDlg* m_spMainDlg;
public:
	static CMainDlg* GetMainDlg();
public:
	void DoPaint(CDCHandle dc);
	//
	void CloseDialog(int nVal);
	//
	void OnSyncEnd(int nExitCode, UINT nFlags);
	//
	static BOOL WriteCommandLineToReg(LPCTSTR lpszCommandLine);
	static BOOL ReadCommandLineToReg(CString& strCommandLine, BOOL bClear);
	//
	void ProcessCommandLine(LPCTSTR lpszCommandLine, BOOL bPrompt = FALSE);
public:
	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_QUERYENDSESSION, OnQueryEndSession)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
		MESSAGE_HANDLER(UM_REFRESH_EVENTS, OnRefreshEvents)
		MESSAGE_HANDLER(UM_PROCESS_COMMANDLINE, OnProcessCommandLine)
		MESSAGE_HANDLER(UM_CALENDAREVENTMODIFIED, OnCalendarEventModified)
		MESSAGE_HANDLER(UM_REFRESH_TODOLISTS, OnRefreshTodoLists)
		MESSAGE_HANDLER(UM_SAVE_TODOLISTS_STATUS, OnSaveTodoListsStatus)
		MESSAGE_HANDLER(WIZ_UM_CLOSE_WINDOW_FOR_AUTO_UPDATE, OnCloseWindowForAutoUpdate)
		MESSAGE_HANDLER(WM_POWERBROADCAST, OnPowerBroadcast)
		MESSAGE_HANDLER(WIZ_UM_SHOW_DESKTOP_EVENTS, OnShowDesktop)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(ID_TRAY_NEW_TODOLIST, OnTrayNewTodoList)
		COMMAND_ID_HANDLER(ID_TRAY_SHOW_ALL_TODOLISTS, OnTrayShowAllTodolists)
		COMMAND_ID_HANDLER(ID_TRAY_EXIT, OnTrayExit)
		COMMAND_ID_HANDLER(ID_HELP_MANUAL, OnHelpManual)
		COMMAND_ID_HANDLER(ID_HELP_ABOUT, OnHelpAbout)
		COMMAND_ID_HANDLER(ID_TRAY_OPTIONS, OnTrayOptions)
		COMMAND_ID_HANDLER(ID_TRAY_WIZCALENDAR, OnTrayWizCalendar)
		COMMAND_ID_HANDLER(ID_TRAY_SYNC, OnTraySync)
		COMMAND_RANGE_HANDLER(ID_TODO_LIST_BEGIN, ID_TODO_LIST_END, OnTodoList)
		REFLECT_NOTIFICATIONS()
		COMMAND_ID_HANDLER(ID_HIDDEN_NEWBLANKTODOLIST, OnHiddenNewblanktodolist)
		CHAIN_MSG_MAP(CWizKMSyncSimpleMessageBase)
		CHAIN_MSG_MAP( CWizTrayIconImpl<CMainDlg>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnQueryEndSession(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPowerBroadcast(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnProcessCommandLine(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCalendarEventModified(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnHotKey(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnIsHotKeyRegistered(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSaveTodoListsStatus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnHelpManual(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnHelpAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayNewTodoList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayShowAllTodolists(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTodoList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTrayWizCalendar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnRefreshEvents(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRefreshTodoLists(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTraySync(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseWindowForAutoUpdate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnHiddenNewblanktodolist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnShowDesktop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};


inline CMainDlg* WizGetMainDlg()
{
	return CMainDlg::GetMainDlg();
}
