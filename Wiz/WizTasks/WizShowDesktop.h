#pragma once

const UINT WIZ_UM_SHOW_DESKTOP_EVENTS = ::RegisterWindowMessage(_T("OnShowDesktop"));

void WizRegisterShowDesktopEvents(HWND hwndEvents);
void WizDestroyShowDesktopEventsWindow();



/*
		MESSAGE_HANDLER(WIZ_UM_SHOW_DESKTOP_EVENTS, OnShowDesltop)


			
	LRESULT OnShowDesltop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	*/

