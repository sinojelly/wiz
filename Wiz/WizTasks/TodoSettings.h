#pragma once


const LPCTSTR SECTION_TODO = _T("WizTodo");


inline BOOL IsShowTaskbarButtons()
{
	CWizKMSettings settings;
	return settings.GetBool(SECTION_TODO, _T("ShowTaskbarButtons"), FALSE);
}

inline BOOL SetShowTaskbarButtons(BOOL b)
{
	CWizKMSettings settings;
	return settings.SetBool(SECTION_TODO, _T("ShowTaskbarButtons"), b);
}


const LPCTSTR SECTION_HOTKEY_TODO = _T("WizTodoHotKey");

const LPCTSTR HOTKEY_NAME_NEW_TODOLIST = _T("NewTodoList");
const LPCTSTR HOTKEY_NAME_SHOW_ALL_TODOLISTS = _T("ShowAllTodoLists");

const LPCTSTR HOTKEY_DEFAULT_NEW_TODOLIST = _T("Ctrl+Alt+O");
const LPCTSTR HOTKEY_DEFAULT_SHOW_ALL_TODOLISTS = _T("Ctrl+Alt+Y");
inline CString GetDoubleClickAction()
{
	CWizKMSettings settings;
	return settings.GetStr(SECTION_TODO, _T("DoubleClickAction"), _T("ShowAllTodoLists"));
}

inline BOOL SetDoubleClickAction(LPCTSTR lpszButtonName)
{
	CWizKMSettings settings;
	return settings.SetStr(SECTION_TODO, _T("DoubleClickAction"), lpszButtonName);
}

inline BOOL SetVisibleTodoLists(const CWizStdStringArray& arrayGUID)
{
	CString strGUIDs;
	::WizStringArrayToText(arrayGUID, strGUIDs, _T(";"));
	//
	CWizKMSettings settings;
	return settings.SetStr(SECTION_TODO, _T("VisibleTodoLists"), strGUIDs);
}

inline BOOL GetVisibleTodoLists(CWizStdStringArray& arrayGUID)
{
	;
	CWizKMSettings settings;
	CString strGUIDs = settings.GetStr(SECTION_TODO, _T("VisibleTodoLists"));
	//
	return ::WizSplitTextToArray(strGUIDs, _T(';'), arrayGUID);
}

