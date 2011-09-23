#pragma once

class CWizKMHotKeyCtrl : public CWizHotKeyCtrlImpl<CWizKMHotKeyCtrl, CWizKMSettingsEx>
{
};


#ifdef _WIZUIBASE_H_

#ifdef __ATLSPLIT_H__
typedef CWizSplitterWindowT<true, CWizKMSettingsEx>    CWizKMSplitterWindow;
typedef CWizSplitterWindowT<false, CWizKMSettingsEx>   CWizKMHorSplitterWindow;
#endif //__ATLSPLIT_H__

#ifdef __ATLCTRLX_H__
class CWizKMADCtrl : public CWizADCtrl
{
public:
	CWizKMADCtrl()
		: CWizADCtrl(WizKMGetSettingsFileName(), WIZKM_SETTINGS_ROOT_NODE_NAME)
	{
	}
};
#endif //__ATLCTRLX_H__

#endif //_WIZUIBASE_H_


/*
class CWizKMToolBar 
	: public CWizVistaToolBarCtrl
{
public:
	CWizKMToolBar()
	{
	}
public:
	BOOL CreateEx(HWND hWndParent)
	{
		if (!Create(hWndParent, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN | TBSTYLE_TOOLTIPS | TBSTYLE_LIST | TBSTYLE_FLAT, 0))
			return FALSE;
		//
		ATLASSERT(IsWindow());
		//
		SetExtendedStyle(GetExtendedStyle()
			// | TBSTYLE_EX_MIXEDBUTTONS
			| TBSTYLE_EX_DRAWDDARROWS);
		SetButtonStructSize();
		AutoSetButtonSize();
		//
		CSize szPadding;
		GetPadding(&szPadding);
		SetPadding(20, szPadding.cy);
		//
		return TRUE;
	}
};

*/


template <class T, int SIZE>
class CWizKMSyncIconPlayer
{
public:
	CWizKMSyncIconPlayer()
		: m_nSyncIconIndex(0)
		, m_hIconDefault(NULL)
		, m_hIcon(NULL)
		, m_bPlaying(FALSE)
	{
		ZeroMemory(m_arraySyncIcon, sizeof(m_arraySyncIcon));
		m_hIconDefault = WizKMLoadSkinsIcon(_T("sync.ico"), SIZE, SIZE);
		m_hIcon = m_hIconDefault;
	}
	~CWizKMSyncIconPlayer()
	{
		m_hIconDefault = NULL;
		if (m_hIconDefault)
		{
			DestroyIcon(m_hIconDefault);
			m_hIconDefault = NULL;
		}
		//
		for (int i = 0; i < SYNC_ICON_COUNT; i++)
		{
			if (m_arraySyncIcon[i])
			{
				DestroyIcon(m_arraySyncIcon[i]);
				m_arraySyncIcon[i] = NULL;
			}
		}
	}
private:
	static const UINT ID_TIMER_SYNC_ICOM = 2000;
	int m_nSyncIconIndex;
	static const UINT SYNC_ICON_COUNT = 8;
	HICON m_arraySyncIcon[SYNC_ICON_COUNT];
	//
	HICON m_hIconDefault;
	//
	HICON m_hIcon;
	//
	BOOL m_bPlaying;
private:
	void InitSyncIcon()
	{
		for (int i = 0; i < SYNC_ICON_COUNT; i++)
		{
			if (!m_arraySyncIcon[i])
			{
				m_arraySyncIcon[i] = WizKMLoadSkinsIcon(WizFormatString1(_T("sync%1.ico"), WizIntToStr(i + 1)), SIZE, SIZE);
			}
		}
	}
public:
	BEGIN_MSG_MAP(CWizKMSyncIconPlayer)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()
	//
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		InitSyncIcon();
		//
		bHandled = FALSE;
		if (ID_TIMER_SYNC_ICOM == (UINT)wParam)
		{
			m_nSyncIconIndex++;
			m_nSyncIconIndex = m_nSyncIconIndex % SYNC_ICON_COUNT;
			//
			T* pT = static_cast<T*>(this);
			m_hIcon = m_arraySyncIcon[m_nSyncIconIndex];
			pT->UpdateSyncIcon();
			//
			bHandled = TRUE;
		}
		//
		return 0;
	}
public:
	void PlaySyncIcon()
	{
		m_bPlaying = TRUE;
		T* pT = static_cast<T*>(this);
		pT->SetTimer(ID_TIMER_SYNC_ICOM, 200, NULL);
		//
		BOOL bHandledTemp = FALSE;
		OnTimer(WM_TIMER, ID_TIMER_SYNC_ICOM, 0, bHandledTemp);
	}
	void StopSyncIcon()
	{
		m_bPlaying = FALSE;
		T* pT = static_cast<T*>(this);
		pT->KillTimer(ID_TIMER_SYNC_ICOM);
		m_hIcon = m_hIconDefault;
		pT->UpdateSyncIcon();
	}
	//
	void UpdateSyncIcon()
	{
		ATLASSERT(FALSE);
	}
	HICON GetSyncIcon()
	{
		return m_hIcon;
	}
	BOOL IsPlaying() const
	{
		return m_bPlaying;
	}
};



template <class T>
class CWizKMTreeCtrlState_Settings : 
	public std::map<CString, BOOL>,
	public CWizTreeCtrlStateBase<T>
{
public:
	CWizKMTreeCtrlState_Settings(LPCTSTR lpszSection, BOOL bLoad)
		: m_bLoad(bLoad)
	{
		m_strSection = lpszSection;
		//
		if (bLoad)
		{
			m_section = m_settings.GetSection(lpszSection);
			if (m_section.Valid())
			{
				m_strSelectedID = m_section.GetStr(_T("SelectedItem"));
			}
		}
		else
		{
			m_settings.ClearSection(lpszSection);
		}
	}
	~CWizKMTreeCtrlState_Settings()
	{
		if (!m_bLoad)
		{
			m_settings.Save();
		}
	}
protected:
	BOOL m_bLoad;
	CString m_strSection;
	CWizKMSettingsEx m_settings;
	CWizKMSettingsSection m_section;
	CString m_strSelectedID;
private:
	CString IDToKey(const CString& strID)
	{
		return CString(_T("_")) + WizMd5StringNoSpace(strID);
	}
public:
	virtual BOOL StateExists()
	{
		return m_section.Valid();
	}
	virtual void SaveScrollState(POINT pt)
	{
		m_settings.SetInt(m_strSection, _T("X"), pt.x, WIZ_SETTINGS_MANUAL_SAVE);
		m_settings.SetInt(m_strSection, _T("Y"), pt.y, WIZ_SETTINGS_MANUAL_SAVE);
	}
	virtual void SaveItemState(CWizTreeCtrlWithState<T>& tree, HTREEITEM hItem, BOOL bExpanded, BOOL bSelected)
	{
		int nState = 0;
		if (bExpanded)
		{
			nState |= TVIS_EXPANDED;
		}
		if (bSelected)
		{
			nState |= TVIS_SELECTED;
		}
		//
		CString strID = tree.GetItemStateID(hItem);
		//
		m_settings.SetInt(m_strSection, IDToKey(strID), nState, WIZ_SETTINGS_MANUAL_SAVE);
	}
	virtual POINT GetScrollState()
	{
		POINT pt = {0, 0};
		//
		if (!m_section.Valid())
			return pt;
		//
		pt.x = m_section.GetInt(_T("X"));
		pt.y = m_section.GetInt(_T("Y"));
		//
		return pt;
	}
	virtual void GetItemState(CWizTreeCtrlWithState<T>& tree, HTREEITEM hItem, BOOL& bExpanded, BOOL& bSelected)
	{
		if (!m_section.Valid())
			return;
		//
		CString strID = tree.GetItemStateID(hItem);
		//
		int nState = m_section.GetInt(IDToKey(strID));
		//
		bSelected = (TVIS_SELECTED == (nState & TVIS_SELECTED));
		bExpanded = (TVIS_EXPANDED == (nState & TVIS_EXPANDED));
	}
	//
	virtual BOOL ReadBool(LPCTSTR lpszKey, BOOL bDef)
	{
		if (!m_section.Valid())
			return bDef;
		//
		return m_section.GetBool(lpszKey, bDef);
	}
	virtual BOOL SetBool(LPCTSTR lpszKey, BOOL b)
	{
		return m_settings.SetBool(m_strSection, lpszKey, b, WIZ_SETTINGS_MANUAL_SAVE);
	}
	//
	virtual int ReadInt(LPCTSTR lpszKey, int nDef)
	{
		if (!m_section.Valid())
			return nDef;
		//
		return m_section.GetInt(lpszKey, nDef);
	}
	virtual BOOL SetInt(LPCTSTR lpszKey, int n)
	{
		return m_settings.SetInt(m_strSection, lpszKey, n, WIZ_SETTINGS_MANUAL_SAVE);
	}
};



#ifdef _WIZATLBROWSER_H_


#define WIZKM_AD_MIN_HEIGHT		100

class CWizKMADBrowser : public CWizSafeBrowser
{
public:
	CWizKMADBrowser()
	{
		m_bNoMenu = TRUE;
		m_bNo3DBorder = TRUE;
		m_bNoScroll = TRUE;
		m_bNoScript = TRUE;
		m_bDialog = FALSE;
		m_bNewWindow = FALSE;
		//
		m_strHiddenagID = _T("id_wiz_ad");
		m_strLocalURL = GetLocalFileName();
		//
		m_bSilent = TRUE;
	}

	BEGIN_MSG_MAP(CWizKMADBrowser)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		CHAIN_MSG_MAP(CWizSafeBrowser)
	END_MSG_MAP()
	//
private:
	static const UINT ID_START_AD = 100;
	static const UINT ID_CHECK_AD = 101;
	CString m_strUserType;
public:
	HWND CreateEx(HWND hWndParent, LPCTSTR lpszURL)
	{
		HWND hwnd = CWizSafeBrowser::CreateEx(hWndParent, lpszURL);
		//
		ShowWindow(SW_HIDE);
		SetTimer(ID_START_AD, 1000 * 10, NULL);
		//
		return hwnd;
	}
	CString GetLocalFileName()
	{
		CString strFileName = WizGetAppPath() + _T("Files\\AD\\") + WizIntToStr(WizTranslationsGetCurrentMappedLCID()) + _T("\\index.html");
		if (!PathFileExists(strFileName))
		{
			strFileName = WizGetAppPath() + _T("Files\\AD\\1033\\index.html");
		}
		//
		return strFileName;
	}
	//
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (ID_START_AD == wParam)
		{
			CString strAtt = WizFormatString3(_T("s=%1&m=%2&ut=%3"), WizIntToStr(GetSystemMetrics(SM_CXSCREEN)) + _T("X") + WizIntToStr(GetSystemMetrics(SM_CYSCREEN)), WizExtractFileTitle(WizGetAppFileName()), m_strUserType);
			CString strURL = ::WizKMWebSiteGetURL(_T("ad3"));
			strURL += _T("&");
			strURL += strAtt;
			//
			Navigate(strURL);
			KillTimer(ID_START_AD);
			//
			SetTimer(ID_CHECK_AD, 1000 * 5, NULL);
			//
			bHandled = TRUE;
			return 0;
		}
		else if (ID_CHECK_AD == wParam)
		{
 			if (IsSucceeded())
			{
				if (IsVIP())
				{
					if (WizKMGetSettings().GetBool(_T("Common"), _T("ShowAD"), TRUE)
						|| IsNotice())
					{
						ShowAD();
					}
				}
				else
				{
					ShowAD();
				}
			}
			//
			KillTimer(ID_CHECK_AD);
			//
			bHandled = TRUE;
			//
			return 0;
		}
		//
		bHandled = FALSE;
		return 0;
	}
	//
	void SetUserType(LPCTSTR lpszUserType)
	{
		m_strUserType = lpszUserType;
	}
	//
	CString GetUserType() const 
	{
		return m_strUserType;
	}
	void ChangeUserType(LPCTSTR lpszUserType)
	{
		m_strUserType = lpszUserType;
		//
		if (!IsVIP())
		{
			if (IsSucceeded())
			{
				if (0 == (GetStyle() & WS_VISIBLE))
				{
					ShowAD();
				}
			}
		}
	}
	//
	BOOL IsVIP()
	{
		return 0 == m_strUserType.CompareNoCase(_T("vip"));
	}
	//
	void ShowAD()
	{
		ShowWindow(SW_SHOW);
		KillTimer(ID_CHECK_AD);
		//
		GetParent().SendMessage(WM_SETTINGCHANGE, 0, 0);
	}
	
	BOOL IsNotice()
	{
		CComPtr<IHTMLDocument3> spDoc = GetDoc3();
		if (!spDoc)
			return FALSE;
		//
		CComPtr<IHTMLElement> spElem;
		spDoc->getElementById(CComBSTR(L"wiz_id_notice"), &spElem);
		//
		return spElem ? TRUE : FALSE;
	}
	BOOL IsCloseable()
	{
		CComPtr<IHTMLDocument3> spDoc = GetDoc3();
		if (!spDoc)
			return FALSE;
		//
		CComPtr<IHTMLElement> spElem;
		spDoc->getElementById(CComBSTR(L"wiz_id_closeable"), &spElem);
		//
		return spElem ? TRUE : FALSE;
	}
	CString GetCloseableURL()
	{
		CComPtr<IHTMLDocument3> spDoc = GetDoc3();
		if (!spDoc)
			return CString();
		//
		CComPtr<IHTMLElement> spElem;
		spDoc->getElementById(CComBSTR(L"wiz_id_closeable_url"), &spElem);
		//
		if (!spElem)
			return CString();
		//
		CComBSTR bstrText;
		//
		spElem->get_innerText(&bstrText);
		return CString(bstrText);
	}
	virtual BOOL OnBeforeNavigate2(IDispatch* pDisp, const CString& szURL, DWORD dwFlags, const CString& szTargetFrameName, CSimpleArray<BYTE>& pPostedData, const CString& szHeaders)
	{
		CWizSafeBrowser::OnBeforeNavigate2(pDisp, szURL, dwFlags, szTargetFrameName, pPostedData, szHeaders);
		//
		if (0 == szURL.CompareNoCase(_T("wiz:closead")))
		{
			if (IsVIP())
			{
				ShowWindow(SW_HIDE);
				GetParent().SendMessage(WM_SETTINGCHANGE, 0, 0);
				//
				WizKMGetSettings().SetBool(_T("Common"), _T("ShowAD"), FALSE, TRUE);
			}
			else if (IsCloseable())
			{
				ShowWindow(SW_HIDE);
				GetParent().SendMessage(WM_SETTINGCHANGE, 0, 0);
				//
				CString strURL = GetCloseableURL();
				if (!strURL.IsEmpty())
				{
					ShellExecute(NULL, _T("open"), strURL, NULL, NULL, SW_SHOW);
				}
			}
			else
			{
				::WizKMWebSiteVisit(_T("vip2"));
			}
			return TRUE;
		}
		//
		return FALSE;
	}
};




struct WIZKMSTYLEDATA
{
	COLORREF crText;
	COLORREF crBack;
	BOOL bBold;
	int nFlag;
	BOOL bDefault;
	//
	WIZKMSTYLEDATA()
		: bDefault(FALSE)
	{
		crText = RGB(0, 0, 0);
		crBack = RGB(255, 255, 255);
		bBold = FALSE;
		nFlag = -1;
	}
};

typedef std::map<CString, WIZKMSTYLEDATA> CWizKMStyleMap;

class CWizKMStyles : public CWizKMStyleMap
{
public:
	CWizKMStyles()
	{
		m_pDatabase = NULL;
		//
		m_dataDefault.crText = WizGetSkin()->GetItemTextColor(CWizSkin::wizisNormal);
		m_dataDefault.crBack = WizGetSkin()->GetItemColor(CWizSkin::wizisNormal);
		m_dataDefault.bDefault = TRUE;
	}
	~CWizKMStyles()
	{
	}
protected:
	CWizKMDatabase* m_pDatabase;
	//
	WIZKMSTYLEDATA m_dataDefault;
	//
	CWizStdStringArray m_arrayStyleName;
public:
	void SetDatabase(CWizKMDatabase* pDatabase)
	{
		ATLASSERT(pDatabase);
		m_pDatabase = pDatabase;
		//
		Reset();
	}
	//
	void Reset()
	{
		clear();
		m_arrayStyleName.clear();
		//
		InitStyles();
	}
	//
	const_iterator AddStyle(LPCTSTR lpszStyleGUID)
	{
		ATLASSERT(find(lpszStyleGUID) == end());
		//
		CComPtr<IWizStyle> spStyle = m_pDatabase->GetStyleByGUID(lpszStyleGUID);
		if (!spStyle)
		{
			AddEmptyStyle(lpszStyleGUID);
		}
		else
		{
			AddStyle(spStyle);
		}
		//
		return find(lpszStyleGUID);
	}
	//
	BOOL AddStyle(IWizStyle* pStyle)
	{
		CString strGUID = CWizKMDatabase::GetObjectGUID(pStyle);
		ATLASSERT(find(strGUID) == end());
		//
		WIZKMSTYLEDATA data;
		data.crText = CWizKMDatabase::GetStyleTextColor(pStyle);
		data.crBack = CWizKMDatabase::GetStyleBackgroundColor(pStyle);
		data.bBold = CWizKMDatabase::GetStyleTextBold(pStyle);
		data.nFlag = CWizKMDatabase::GetStyleFlagIndex(pStyle);
		//
		operator [] (strGUID) = data;
		//
		return TRUE;
	}
	BOOL AddEmptyStyle(LPCTSTR lpszStyleGUID)
	{
		CString strGUID = lpszStyleGUID;
		ATLASSERT(find(strGUID) == end());
		//
		WIZKMSTYLEDATA data;
		data.crText = ::GetSysColor(COLOR_WINDOWTEXT);
		data.crBack = ::GetSysColor(COLOR_WINDOW);
		data.bBold = FALSE;
		data.nFlag = -1;
		//
		operator [] (strGUID) = data;
		//
		return TRUE;
	}
	//
	const WIZKMSTYLEDATA& GetStyle(LPCTSTR lpszStyleGUID)
	{
		if (!lpszStyleGUID || !*lpszStyleGUID)
			return m_dataDefault;
		//
		const_iterator it = find(lpszStyleGUID);
		if (it != end())
			return it->second;
		//
		it = AddStyle(lpszStyleGUID);
		if (it != end())
			return it->second;
		//
		return m_dataDefault;
	}
	CComPtr<IWizStyle> GetStyleByName(LPCTSTR lpszStyleName)
	{
		CComPtr<IWizStyle> spStyle = m_pDatabase->GetStyleByName(lpszStyleName);
		return spStyle;
	}
	const WIZKMSTYLEDATA& GetDocumentStyle(IWizDocument* pDocument)
	{
		CString strStyleGUID = CWizKMDatabase::GetDocumentStyleGUID(pDocument);
		return GetStyle(strStyleGUID);
	}
	//
	BOOL InitStyles()
	{
		if (!m_pDatabase)
			return FALSE;
		//
		CWizStyleArray arrayStyle;
		m_pDatabase->GetStyles(arrayStyle);
		//
		for (CWizStyleArray::const_iterator it = arrayStyle.begin();
			it != arrayStyle.end();
			it++)
		{
			AddStyle(*it);
			m_arrayStyleName.push_back(CWizKMDatabase::GetObjectName(it->p));
		}
		//
		return TRUE;
	}
	//
	void GetAllStyleNames(CWizStdStringArray& arrayName)
	{
		arrayName.assign(m_arrayStyleName.begin(), m_arrayStyleName.end());
	}
};



#endif

