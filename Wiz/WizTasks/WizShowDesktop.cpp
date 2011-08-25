#include "stdafx.h"
#include "WizShowDesktop.h"



typedef CWinTraits<WS_EX_TOOLWINDOW> CWizShowDesktopTraits;


class CWizShowDesktop
	: public CWindowImpl<CWizShowDesktop, CWindow, CWizShowDesktopTraits>
{
public:
	CWizShowDesktop()
		: m_showDesktop(false)
		, m_hwndEvents(NULL)
	{
		m_strWindowCaption = CString(_T("WizShowDesktop_")) + ::WizGenGUID();
	}
private:
	CString m_strWindowCaption;
    bool m_showDesktop;
	HWND m_hwndEvents;
public:
	BOOL Init()
	{
		HWND hwnd = Create(NULL, CRect(0, 0, 0, 0));
		if (!hwnd)
			return FALSE;
		SetWindowText(m_strWindowCaption);
		//
		SetWindowPos(HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
		//
		SetTimer(100, 200, NULL);
		return TRUE;
	}

	BEGIN_MSG_MAP(CWizShowDesktop)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()



	// the desktop worker window (if available) can hide the reference window
private:
	HWND GetDesktopWorkerWindow() 
	{
		HWND hwndShellWindow = ::GetShellWindow();
		if (!hwndShellWindow)
			return NULL;
		//
		DWORD nShellId = 0;
		::GetWindowThreadProcessId(hwndShellWindow, &nShellId);
		//
		HWND hwndWorkerWindow = NULL;
		while ((hwndWorkerWindow = ::FindWindowEx(NULL, hwndWorkerWindow, _T("WorkerW"), NULL)) 
			!= NULL)
		{
			DWORD nWorkerId = 0;
			::GetWindowThreadProcessId(hwndWorkerWindow, &nWorkerId);
			//
			if (nWorkerId == nShellId) 
			{
				HWND hwnd = ::FindWindowEx(hwndWorkerWindow, NULL, _T("SHELLDLL_DefView"), NULL);
				if (hwnd) 
				{
					HWND hwndDesktopWindow = ::FindWindowEx(hwnd, NULL, _T("SysListView32"), NULL);
					if (hwndDesktopWindow)
					{
						return hwndWorkerWindow;
					}
				}
			}
		}
		return NULL;
	}

public:
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if ((UINT)wParam != 100)
		{
			bHandled = FALSE;
			return 0;
		}
		//
		bool showDesktopDetected = false;

		HWND hwndWorkerWindow = GetDesktopWorkerWindow();
		if (hwndWorkerWindow) 
		{
			// search if the reference window is behind the worker window
			HWND hwndSelf = ::FindWindowEx(NULL, hwndWorkerWindow, NULL, m_strWindowCaption);
			showDesktopDetected = (hwndSelf != NULL);
		} 
		else 
		{
			// if there is no worker window, then nothing can hide the reference
			showDesktopDetected = false;
		}

		if (m_showDesktop != showDesktopDetected) 
		{
			m_showDesktop = showDesktopDetected;
			if (m_hwndEvents) 
			{
				::SendMessage(m_hwndEvents, WIZ_UM_SHOW_DESKTOP_EVENTS, (WPARAM)showDesktopDetected, 0);
			}
		}
		//
		return 0;
	}
	//
private:
	static CWizShowDesktop& Instance()
	{
		static CWizShowDesktop sd;
		static bool first = true;
		if (first)
		{
			first = false;
			sd.Init();
		}
		//
		return sd;
	}

public:
	static void RegisterShowDesktopEvents(HWND hwndEvents)
	{
		CWizShowDesktop& sd = Instance();
		if (sd.m_hWnd)
		{
			sd.m_hwndEvents = hwndEvents;
		}
	}

	static void DestroyShowDesktopEventsWindow()
	{
		CWizShowDesktop& sd = Instance();
		if (sd.m_hWnd)
		{
			sd.DestroyWindow();
		}
	}
};





void WizRegisterShowDesktopEvents(HWND hwndEvents)
{
	CWizShowDesktop::RegisterShowDesktopEvents(hwndEvents);
}

void WizDestroyShowDesktopEventsWindow()
{
	CWizShowDesktop::DestroyShowDesktopEventsWindow();
}

