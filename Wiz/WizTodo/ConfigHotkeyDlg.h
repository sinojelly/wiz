// OptionsDatabaseDlg.h : Declaration of the CConfigHotkeyDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

// CConfigHotkeyDlg

#include "TodoSettings.h"

class CConfigHotkeyDlg 
	: public CAxPropertyPageImpl<CConfigHotkeyDlg>
	, public CWinDataExchange<CConfigHotkeyDlg>
{
public:
	CConfigHotkeyDlg()
	{
	}

	~CConfigHotkeyDlg()
	{
	}
private:
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyNewTodoList;
	CWizHotKeyCtrlExWithSettings<CWizKMSettings> m_hotkeyDisplayAllTodoLists;
public:

	enum { IDD = IDD_DIALOG_CONFIG_HOTKEY };

	BEGIN_DDX_MAP(CBackgroundOptsPage)
		DDX_CONTROL(IDC_HOTKEY_CREATE_NEW_TODO_LIST, m_hotkeyNewTodoList)
		DDX_CONTROL(IDC_HOTKEY_DISPLAY_ALL_TODOLISTS, m_hotkeyDisplayAllTodoLists)
    END_DDX_MAP()

	BEGIN_MSG_MAP(CConfigHotkeyDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON_RESTORE_DEFAULTS, BN_CLICKED, OnBnClickedButtonRestoreDefaults)
		CHAIN_MSG_MAP(CAxPropertyPageImpl<CConfigHotkeyDlg>)
	END_MSG_MAP()



	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxPropertyPageImpl<CConfigHotkeyDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		WizTranslationsTranslateWindow(m_hWnd);
		//
		DoDataExchange(FALSE);
		//
		m_hotkeyNewTodoList.SetStateSection(SECTION_HOTKEY_TODO, HOTKEY_NAME_NEW_TODOLIST, HOTKEY_DEFAULT_NEW_TODOLIST);
		m_hotkeyDisplayAllTodoLists.SetStateSection(SECTION_HOTKEY_TODO, HOTKEY_NAME_SHOW_ALL_TODOLISTS, HOTKEY_DEFAULT_SHOW_ALL_TODOLISTS);
		//
		return 1;  // Let the system set the focus
	}

	int OnApply()
	{
		if (!DoDataExchange(TRUE))
			return PSNRET_INVALID;
		//
		m_hotkeyNewTodoList.Save();
		m_hotkeyDisplayAllTodoLists.Save();
		//
		return PSNRET_NOERROR;
	}

	LRESULT OnBnClickedButtonRestoreDefaults(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_hotkeyNewTodoList.SetWindowText(HOTKEY_DEFAULT_NEW_TODOLIST);
		m_hotkeyDisplayAllTodoLists.SetWindowText(HOTKEY_DEFAULT_SHOW_ALL_TODOLISTS);
		//
		return 0;
	}
};


