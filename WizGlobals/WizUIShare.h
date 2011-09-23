#ifndef _WIZUISHARE_H_
#define _WIZUISHARE_H_

#pragma once



#define WIZ_ALIGN_BOTTOM	0
#define WIZ_ALIGN_TOP		1
#define WIZ_ALIGN_LEFT		2
#define WIZ_ALIGN_RIGHT		3

int WizGetTaskBarHeight(int& nAlign);
void WizSetInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex, HWND hWnd);
BOOL WizIsInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex);
RECT WizGetInfoWindowRect(HWND hwnd, LPCTSTR lpszRegKey, int& nInfoWndIndex);





inline void WizHotKeyCtrlValueToHotKey(DWORD dwValue, UINT& nModifiers, UINT& nKey)
{
	BYTE byMod = HIBYTE(dwValue);
	BYTE byKey = LOBYTE(dwValue);
	//
	nModifiers = 0;
	nKey = byKey;
	//
	if (byMod & HOTKEYF_ALT)
	{
		nModifiers |= MOD_ALT;
	}
	if (byMod & HOTKEYF_CONTROL)
	{
		nModifiers |= MOD_CONTROL;
	}
	if (byMod & HOTKEYF_SHIFT)
	{
		nModifiers |= MOD_SHIFT;
	}
}

inline BOOL WizTextToHotKey(LPCTSTR lpsz, UINT& nModifiers, UINT& nKey)
{
	nModifiers = 0;
	nKey = 0;
	//
	CString str(lpsz);
	if (str.IsEmpty())
		return FALSE;
	//
	str.MakeUpper();
	//
	if (-1 != str.Find(_T("CTRL")))
		nModifiers |= MOD_CONTROL;
	if (-1 != str.Find(_T("ALT")))
		nModifiers |= MOD_ALT;
	if (-1 != str.Find(_T("SHIFT")))
		nModifiers |= MOD_SHIFT;
	if (-1 != str.Find(_T("WIN")))
		nModifiers |= MOD_WIN;
	//
	str.Replace(_T("CTRL"), _T(""));
	str.Replace(_T("ALT"), _T(""));
	str.Replace(_T("SHIFT"), _T(""));
	str.Replace(_T("WIN"), _T(""));
	//
	str.Replace(_T("+"), _T(""));
	str.Replace(_T(" "), _T(""));
	str.Trim();
	//
	if (str.IsEmpty())
		return FALSE;
	//
	if (str == _T("ENTER"))
	{
		nKey = VK_RETURN;
		return TRUE;
	}
	else if (str == _T("ESC"))
	{
		nKey = VK_ESCAPE;
		return TRUE;
	}
	else if (str == _T("PRINTSCREEN"))
	{
		nKey = VK_SNAPSHOT;
		return TRUE;
	}
	else if (str == _T("INSERT"))
	{
		nKey = VK_INSERT;
		return TRUE;
	}
	else if (str == _T("DEL"))
	{
		nKey = VK_DELETE;
		return TRUE;
	}
	else if (str == _T("HOME"))
	{
		nKey = VK_HOME;
		return TRUE;
	}
	else if (str == _T("END"))
	{
		nKey = VK_END;
		return TRUE;
	}
	else if (str == _T("BACKSPACE"))
	{
		nKey = VK_BACK;
		return TRUE;
	}
	else if (str == _T("PAGEUP"))
	{
		nKey = VK_PRIOR;
		return TRUE;
	}
	else if (str == _T("PAGEDOWN"))
	{
		nKey = VK_NEXT;
		return TRUE;
	}
	//
	if (str.GetLength() == 1)
		nKey = str[0];
	else
	{
		if (str[0] != 'F')
			return FALSE;
		//
		str.Delete(0);
		//
		int nNum = _ttoi(str);
		if (nNum == 0)
			return FALSE;
		//
		nKey = VK_F1 + (nNum - 1);
	}
	//
	return TRUE;
}


inline CString WizHotKeyCtrlValueToText(DWORD dwValue)
{
	UINT nKey = 0;
	UINT nMod = 0;
	WizHotKeyCtrlValueToHotKey(dwValue, nMod, nKey);

	CString str;
	if (nMod & MOD_CONTROL)
	{
		str += _T("Ctrl+");
	}
	if (nMod & MOD_SHIFT)
	{
		str += _T("Shift+");
	}
	if (nMod & MOD_ALT)
	{
		str += _T("Alt+");
	}
	//
	if (nKey >= 'A' && nKey <= 'Z')
	{
		str += (TCHAR)nKey;
	}
	else if (nKey >= '0' && nKey <= '9')
	{
		str += (TCHAR)nKey;
	}
	else if (nKey >= VK_F1 && nKey <= VK_F19)
	{
		CString strText;
		strText.Format(_T("F%d"), nKey - VK_F1 + 1);
		str += strText;
	}
	else if (nKey == VK_ESCAPE)
	{
		str += _T("ESC");
	}
	else if (nKey == VK_RETURN)
	{
		str += _T("Enter");
	}
	else if (nKey == VK_INSERT)
	{
		str += _T("Insert");
	}
	else if (nKey == VK_DELETE)
	{
		str += _T("Delete");
	}
	else if (nKey == VK_HOME)
	{
		str += _T("Home");
	}
	else if (nKey == VK_END)
	{
		str += _T("End");
	}
	else if (nKey == VK_UP)
	{
		str += _T("PageUp");
	}
	else if (nKey == VK_DOWN)
	{
		str += _T("PageDown");
	}
	return str;
}

inline BOOL WizTextToAccel(LPCTSTR lpsz, BYTE& fVirt, UINT& nKey)
{
	fVirt = FVIRTKEY;
	//
	UINT nModifiers = 0;
	nKey = 0;
	if (!WizTextToHotKey(lpsz, nModifiers, nKey))
		return FALSE;
	//
	if (MOD_CONTROL & nModifiers)
	{
		fVirt |= FCONTROL;
	}
	if (MOD_SHIFT & nModifiers)
	{
		fVirt |= FSHIFT;
	}
	if (MOD_ALT & nModifiers)
	{
		fVirt |= FALT;
	}
	//
	return TRUE;
}



inline CString WizAccelToText(BYTE fVirt, UINT nKey)
{
	UINT nMod = 0;
	if (fVirt & FCONTROL)
	{
		nMod |= HOTKEYF_CONTROL;
	}
	if (fVirt & FALT)
	{
		nMod |= HOTKEYF_ALT;
	}
	if (fVirt & FSHIFT)
	{
		nMod |= HOTKEYF_SHIFT;
	}
	//
	WORD hotkey = MAKEWORD(nKey, nMod);
	//
	return WizHotKeyCtrlValueToText(hotkey);
}

struct WIZHOTKEYDATA
{
	CString strHotKey;
	UINT nCommand;
	//
	BOOL bRegistered;
	//
	WIZHOTKEYDATA()
		: nCommand(0)
		, bRegistered(FALSE)
	{
	}
	WIZHOTKEYDATA(LPCTSTR lpszHotKey, UINT command)
		: strHotKey(lpszHotKey)
		, nCommand(command)
		, bRegistered(FALSE)
	{
		if (0 == strHotKey.CompareNoCase(_T("None")))
		{
			strHotKey.Empty();
		}
	}
};
typedef std::vector<WIZHOTKEYDATA> CWizHotKeyDataArray;

class CWizHotKeyHelper
{
public:
	CWizHotKeyHelper()
		: m_hWnd(NULL)
		, m_bRegistered(FALSE)
	{
	}
private:
	BOOL m_bRegistered;
	HWND m_hWnd;
	CWizHotKeyDataArray m_arrayHotKey;
private:
	static BOOL GetError(LPCTSTR lpszHotKey, UINT nCommandID, CString& strError)
	{
		CString strDescription = WizFormatString0(nCommandID);
		if (strDescription.IsEmpty())
			return FALSE;
		//
		int nPos = strDescription.Find('\n');
		if (-1 != nPos)
		{
			strDescription = strDescription.Left(nPos);
		}
		//
		strError += CString(_T("\n")) + WizFormatString2(_T("%1 %2"), strDescription, lpszHotKey);
		//
		return TRUE;
	}
	//
	static BOOL Register(HWND hwnd, UINT nCommandID, LPCTSTR lpszHotKey, CString& strError)
	{
		if (!lpszHotKey)
			return TRUE;
		if (!*lpszHotKey)
			return TRUE;
		//
		UINT nKey = 0;
		UINT nMod = 0;
		if (!WizTextToHotKey(lpszHotKey, nMod, nKey))
		{
			strError = WizFormatString1(_T("Unknown Hot Key: %1"), lpszHotKey);
			return FALSE;
		}
		//
		BOOL bRet = RegisterHotKey(hwnd, nCommandID, nMod, nKey);
		if (!bRet)
		{
			GetError(lpszHotKey, nCommandID, strError);
		}
		//
		return bRet;
	}
public:
	BOOL IsRegistered() const
	{
		return m_bRegistered;
	}
	BOOL RegisterAll(HWND hwnd, const CWizHotKeyDataArray& arrayHotKey, CString& strAllErrors)
	{
		strAllErrors.Empty();
		//
		if (m_bRegistered)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		//
		if (m_hWnd)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		if (!hwnd)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		//
		m_hWnd = hwnd;
		m_arrayHotKey.assign(arrayHotKey.begin(), arrayHotKey.end());
		//
		for (CWizHotKeyDataArray::iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			CString strError;
			if (!Register(m_hWnd, it->nCommand, it->strHotKey, strError))
			{
				it->bRegistered = FALSE;
				strAllErrors += (strError + _T("\n"));
			}
			else
			{
				it->bRegistered = TRUE;
				m_bRegistered = TRUE;
			}
		}
		//
		return strAllErrors.IsEmpty();
	}
	//
	BOOL UnregisterAll()
	{
		if (!m_bRegistered)
		{
			return FALSE;
		}
		if (!m_hWnd)
		{
			ATLASSERT(FALSE);
			return FALSE;
		}
		//
		for (CWizHotKeyDataArray::iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			UnregisterHotKey(m_hWnd, it->nCommand);
			it->bRegistered = FALSE;
		}
		//
		m_arrayHotKey.clear();
		m_hWnd = NULL;
		m_bRegistered = FALSE;
		//
		return TRUE;
	}
	//
	CString GetHotKeyByCommand(UINT nCommand)
	{
		for (CWizHotKeyDataArray::const_iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			if (it->nCommand == nCommand)
				return it->strHotKey;
		}
		return CString();
	}
	CString GetRegisteredHotKeyByCommand(UINT nCommand)
	{
		for (CWizHotKeyDataArray::const_iterator it = m_arrayHotKey.begin();
			it != m_arrayHotKey.end();
			it++)
		{
			if (it->bRegistered
				&& it->nCommand == nCommand)
				return it->strHotKey;
		}
		return CString();
	}
#ifdef __ATLAPP_H__
	void UpdateHotKeyToMenu(HMENU hMenu)
	{
		CMenuHandle menu(hMenu);
		if (!menu.IsMenu())
			return;
		int nCount = menu.GetMenuItemCount();
		for (int i = 0; i < nCount; i++)
		{
			if (HMENU hSubMenu = GetSubMenu(hMenu, i))
			{
				UpdateHotKeyToMenu(hSubMenu);
			}
			else if (UINT nID = menu.GetMenuItemID(i))
			{
				CString strHotKey = GetRegisteredHotKeyByCommand(nID);
				if (!strHotKey.IsEmpty())
				{
					CString strText;
					menu.GetMenuString(i, strText, MF_BYPOSITION);
					//
					CString strOld = strText;
					int nPos = strText.Find('\t');
					if (nPos != -1)
						strText = strText.Left(nPos);
					//
					strText += CString(_T("\t")) + strHotKey;
					if (strOld != strText)
					{
						TCHAR szMenuItem[MAX_PATH];
						_tcscpy_s(szMenuItem, MAX_PATH, strText);
						//
						MENUITEMINFO mi;
						ZeroMemory(&mi, sizeof(MENUITEMINFO));
						//
						mi.cbSize = sizeof(MENUITEMINFO);
						mi.fMask = MIIM_TYPE;
						mi.fType = MFT_STRING;
						mi.dwTypeData = szMenuItem;
						mi.cch = MAX_PATH;
						//
						menu.SetMenuItemInfo(i, TRUE, &mi);
					}
				}
			}
		}
	}
#endif
};

#ifdef __ATLAPP_H__
inline void WizUpdateAccelToMenu(HACCEL hAccel, CMenuHandle menu)
{
	if (!hAccel)
		return;
	if (!menu.IsMenu())
		return;
	//
	const UINT ACCEL_COUNT = 40;
	ACCEL accel[ACCEL_COUNT];
	ZeroMemory(accel, sizeof(ACCEL) * ACCEL_COUNT);
	int nAccelCount = CopyAcceleratorTable(hAccel, accel, ACCEL_COUNT);
	//
	int nMenuCount = menu.GetMenuItemCount();
	for (int iMenu = 0; iMenu < nMenuCount; iMenu++)
	{
		if (HMENU hSubMenu = menu.GetSubMenu(iMenu))
		{
			WizUpdateAccelToMenu(hAccel, hSubMenu);
		}
		else if (UINT nID = menu.GetMenuItemID(iMenu))
		{
			CString strShortcut;
			for (int iAccel = 0; iAccel < nAccelCount; iAccel++)
			{
				if (nID == accel[iAccel].cmd)
				{
					strShortcut += (WizAccelToText(accel[iAccel].fVirt, accel[iAccel].key) + _T(" / "));
				}
			}
			if (strShortcut.IsEmpty())
				continue;
			strShortcut.Trim(_T("/ "));
			//
			CString strText;
			menu.GetMenuString(iMenu, strText, MF_BYPOSITION);
			//
			CString strOld = strText;
			int nPos = strText.Find('\t');
			if (nPos != -1)
				strText = strText.Left(nPos);
			//
			strText += CString(_T("\t")) + strShortcut;
			if (strOld != strText)
			{
				TCHAR szMenuItem[MAX_PATH];
				_tcscpy_s(szMenuItem, MAX_PATH, strText);
				//
				MENUITEMINFO mi;
				ZeroMemory(&mi, sizeof(MENUITEMINFO));
				//
				mi.cbSize = sizeof(MENUITEMINFO);
				mi.fMask = MIIM_TYPE;
				mi.fType = MFT_STRING;
				mi.dwTypeData = szMenuItem;
				mi.cch = MAX_PATH;
				//
				menu.SetMenuItemInfo(iMenu, TRUE, &mi);
			}
		}
	}
}
#endif



#endif //_WIZUISHARE_H_

