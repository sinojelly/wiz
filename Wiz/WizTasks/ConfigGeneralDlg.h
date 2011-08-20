// OptionsDatabaseDlg.h : Declaration of the CConfigGeneralDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "TodoSettings.h"

// CConfigGeneralDlg

class CConfigGeneralDlg 
	: public CAxPropertyPageImpl<CConfigGeneralDlg>
	, public CWinDataExchange<CConfigGeneralDlg>
{
public:
	CConfigGeneralDlg()
	{
		m_strTodo = _T("WizTodo");
	}

	~CConfigGeneralDlg()
	{
	}
private:
	CString m_strTodo;
	CButtonImpl m_btnAutoRun;
	CButtonImpl m_btnShowTaskbarButtons;
	CComboBoxImpl m_wndDoubleClickAction;
public:

	enum { IDD = IDD_DIALOG_CONFIG_GENERAL };

	BEGIN_MSG_MAP(CConfigGeneralDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON_SYNC_OPTIONS, BN_CLICKED, OnBnClickedButtonSyncOptions)
		CHAIN_MSG_MAP(CAxPropertyPageImpl<CConfigGeneralDlg>)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CBackgroundOptsPage)
		DDX_CONTROL(IDC_CHECK_AUTO_RUN, m_btnAutoRun)
		DDX_CONTROL(IDC_CHECK_SHOW_TASKBAR_BUTTONS, m_btnShowTaskbarButtons)
		DDX_CONTROL(IDC_COMBO_DOUBLE_CLICK_ACTION, m_wndDoubleClickAction)
    END_DDX_MAP()


	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxPropertyPageImpl<CConfigGeneralDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		WizTranslationsTranslateWindow(m_hWnd);
		//
		DoDataExchange(FALSE);
		//
		m_btnAutoRun.SetCheck(WizIsAutoRun(m_strTodo) ? BST_CHECKED : BST_UNCHECKED);
		m_btnShowTaskbarButtons.SetCheck(IsShowTaskbarButtons() ? BST_CHECKED : BST_UNCHECKED);
		m_btnShowTaskbarButtons.EnableWindow(WizGetSystemVersion() >= svWin7);
		//
		m_wndDoubleClickAction.AddString(WizFormatStringEx0(ID_TRAY_SHOW_ALL_TODOLISTS));
		m_wndDoubleClickAction.AddString(WizFormatStringEx0(ID_TRAY_NEW_TODOLIST));
		//
		CString strActionName = GetDoubleClickAction();
		if (0 == strActionName.CompareNoCase(_T("NewTodoList")))
		{
			m_wndDoubleClickAction.SetCurSel(1);
		}
		else
		{
			m_wndDoubleClickAction.SetCurSel(0);
		}
		//
		return 1;  // Let the system set the focus
	}

	int OnApply()
	{
		if (!DoDataExchange(TRUE))
			return PSNRET_INVALID;
		//
		if (m_btnAutoRun.GetCheck() == BST_CHECKED)
		{
			WizEnableAutoRun(HKEY_CURRENT_USER, m_strTodo, WizGetAppFileName());
		}
		else
		{
			WizDisableAutoRun(m_strTodo);
		}
		//
		SetShowTaskbarButtons(m_btnShowTaskbarButtons.GetCheck() == BST_CHECKED);
		//
		int nActionIndex = m_wndDoubleClickAction.GetCurSel();
		CString strActionName = _T("ShowAllTodoList");
		switch (nActionIndex)
		{
		case 1:
			strActionName = _T("NewTodoList");
			break;
		}
		SetDoubleClickAction(strActionName);
		//
		return PSNRET_NOERROR;
	}
	//
	LRESULT OnBnClickedButtonSyncOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::WizKMOptionsDlg(0x00100000);
		//
		return 0;
	}
};
