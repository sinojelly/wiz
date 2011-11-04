#pragma once


const LPCTSTR SECTION_TODO = _T("WizTodo");


inline BOOL IsShowTaskbarButtons()
{
	return WizKMGetSettings().GetBool(SECTION_TODO, _T("ShowTaskbarButtons"), FALSE);
}

inline BOOL SetShowTaskbarButtons(BOOL b)
{
	return WizKMGetSettings().SetBool(SECTION_TODO, _T("ShowTaskbarButtons"), b, 0);
}


const LPCTSTR SECTION_HOTKEY_TODO = _T("WizTodoHotKey");

const LPCTSTR HOTKEY_NAME_NEW_TODOLIST = _T("NewTodoList");
const LPCTSTR HOTKEY_NAME_SHOW_ALL_TODOLISTS = _T("ShowAllTodoLists");

const LPCTSTR HOTKEY_DEFAULT_NEW_TODOLIST = _T("Ctrl+Alt+O");
const LPCTSTR HOTKEY_DEFAULT_SHOW_ALL_TODOLISTS = _T("Ctrl+Alt+Y");
inline CString GetDoubleClickAction()
{
	return WizKMGetSettings().GetStr(SECTION_TODO, _T("DoubleClickAction"), _T("ShowAllTodoLists"));
}

inline BOOL SetDoubleClickAction(LPCTSTR lpszButtonName)
{
	return WizKMGetSettings().SetStr(SECTION_TODO, _T("DoubleClickAction"), lpszButtonName, 0);
}

inline BOOL SetVisibleTodoLists(CWizKMDatabase& db, const CWizStdStringArray& arrayGUID)
{
	CString strGUIDs;
	::WizStringArrayToText(arrayGUID, strGUIDs, _T(";"));
	//
	return db.SetMeta(SECTION_TODO, _T("VisibleTodoLists"), strGUIDs);
}

inline BOOL GetVisibleTodoLists(CWizKMDatabase& db, CWizStdStringArray& arrayGUID)
{
	CString strGUIDs = db.GetMeta(SECTION_TODO, _T("VisibleTodoLists"));
	//
	return ::WizSplitTextToArray(strGUIDs, _T(';'), arrayGUID);
}

