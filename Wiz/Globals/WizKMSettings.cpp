#include "stdafx.h"
#include "WizKMSettings.h"


CWizKMSettingsSection::CWizKMSettingsSection()
{
}
CWizKMSettingsSection::CWizKMSettingsSection(IWizSettingsSection* pSection)
{
	m_spSection = pSection;
}
CWizKMSettingsSection::CWizKMSettingsSection(IDispatch* pDisp)
{
	m_spSection = CComQIPtr<IWizSettingsSection>(pDisp);
}
BOOL CWizKMSettingsSection::Valid() const
{
	return m_spSection ? TRUE : FALSE;
}
//
CWizKMSettingsSection& CWizKMSettingsSection::operator = (const CWizKMSettingsSection& right)
{
	m_spSection = right.m_spSection;
	//
	return *this;
}
//
CString CWizKMSettingsSection::GetStr(LPCTSTR lpszKey, LPCTSTR lpszDefault /*= NULL*/)
{
	CString str(lpszDefault);
	//
	if (!m_spSection)
		return str;
	//
	CComBSTR bstrValue;
	HRESULT hr = m_spSection->get_StringValue(CComBSTR(lpszKey), &bstrValue);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to read string: %1!"), lpszKey);
		return str;
	}
	if (S_FALSE == hr)
		return str;
	//
	return CString(bstrValue);
}
int CWizKMSettingsSection::GetInt(LPCTSTR lpszKey, int nDefault /*= 0*/)
{
	if (!m_spSection)
		return nDefault;
	//
	long n = nDefault;
	HRESULT hr = m_spSection->get_IntValue(CComBSTR(lpszKey), &n);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to read string: %1!"), lpszKey);
		return nDefault;
	}
	if (S_FALSE == hr)
		return nDefault;
	//
	return n;
}
BOOL CWizKMSettingsSection::GetBool(LPCTSTR lpszKey, BOOL bDefault /*= FALSE*/)
{
	if (!m_spSection)
		return bDefault;
	//
	VARIANT_BOOL vb = bDefault ? VARIANT_TRUE : VARIANT_FALSE;
	HRESULT hr = m_spSection->get_BoolValue(CComBSTR(lpszKey), &vb);
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to read string: %1!"), lpszKey);
		return bDefault;
	}
	if (S_FALSE == hr)
		return bDefault;
	//
	return vb ? TRUE : FALSE;
}


CWizKMSettings::CWizKMSettings()
	:m_pSettings(NULL)
{
	
	////需要注意，在这里创建了IWizSettings，但是没有释放，////
	////因为静态变量会在com对象释放后被释放，导致出现错误，////
	////因此不再是放该对象，避免出现问题////
	
	CComPtr<IWizSettings> spSettings = WizKMCreateSettings();
	if (!spSettings)
	{
		TOLOG(_T("Failed to create IWizSettings"));
		return;
	}
	//
	m_pSettings = spSettings;
	m_pSettings->AddRef();
	//
	m_strSettingsFileName = WizKMGetSettingsFileName();
	//
	Reload();
}
CWizKMSettings::~CWizKMSettings(void)
{
}

BOOL CWizKMSettings::IsDirty()
{
	if (!m_pSettings)
		return FALSE;
	//
	VARIANT_BOOL vb = VARIANT_FALSE;
	m_pSettings->get_IsDirty(&vb);
	return vb ? TRUE : FALSE;
}

BOOL CWizKMSettings::Reload()
{
	if (!m_pSettings)
		return FALSE;
	//
	HRESULT hr = m_pSettings->Open(CComBSTR(m_strSettingsFileName));
	if (SUCCEEDED(hr))
	{
		m_tLast = ::WizGetFileModifiedTime(m_strSettingsFileName);
		return TRUE;
	}
	else
	{
		TOLOG1(_T("Failed to open settings file; %1"), m_strSettingsFileName);
		return FALSE;
	}
}

BOOL CWizKMSettings::Save()
{
	if (!m_pSettings)
		return FALSE;
	//
	HRESULT hr = m_pSettings->Save();
	m_tLast = ::WizGetFileModifiedTime(m_strSettingsFileName);
	//
	return SUCCEEDED(hr);
}
void CWizKMSettings::CheckOuterModified()
{
	ATLASSERT(m_pSettings);
	if (!m_pSettings)
		return;
	//
	if (::WizGetFileModifiedTime(m_strSettingsFileName) > m_tLast)
	{
		if (IsDirty())
		{
			TOLOG(_T("Settings is modified before reload!"));
			ATLVERIFY(FALSE);
		}
		//
		DEBUG_TOLOG(_T("Reload_Settings_Begin"));
		Reload();
		DEBUG_TOLOG(_T("Reload_Settings_End"));
	}
}

BOOL CWizKMSettings::GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue)
{
	if (!m_pSettings)
		return FALSE;
	//
	CheckOuterModified();
	//
	CComBSTR bstrValue;
	HRESULT hr = m_pSettings->get_StringValue(CComBSTR(lpszSection), CComBSTR(lpszKey), &bstrValue);
	if (FAILED(hr))
	{
		TOLOG2(_T("Failed to read string: %1.%2!"), lpszSection, lpszKey);
		return FALSE;
	}
	//
	strValue = CString(bstrValue);
	//
	return TRUE;
}
BOOL CWizKMSettings::SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue, UINT nFlags)
{
	if (!m_pSettings)
		return FALSE;
	//
	CheckOuterModified();
	//
	HRESULT hr = m_pSettings->put_StringValue(CComBSTR(lpszSection), CComBSTR(lpszKey), CComBSTR(lpszValue));
	if (FAILED(hr))
	{
		TOLOG3(_T("Failed to write string: %1.%2=%3!"), lpszSection, lpszKey, lpszValue);
		return FALSE;
	}
	//
	if (0 == (nFlags & WIZ_SETTINGS_MANUAL_SAVE))
	{
		Save();
	}
	//
	return TRUE;
}
BOOL CWizKMSettings::GetSection(LPCTSTR lpszSection, CWizKMSettingsSection& section)
{
	if (!m_pSettings)
		return FALSE;
	//
	CheckOuterModified();
	//
	CComPtr<IDispatch> spDisp;
	HRESULT hr = m_pSettings->get_Section(CComBSTR(lpszSection), &spDisp);
	if (S_FALSE == hr)
	{
		return FALSE;
	}
	//
	if (FAILED(hr))
	{
		//TOLOG1(_T("Failed to read section: %1!"), lpszSection);
		return FALSE;
	}
	//
	section = CWizKMSettingsSection(spDisp);
	//
	return section.Valid();
}
CWizKMSettingsSection CWizKMSettings::GetSection(LPCTSTR lpszSection)
{
	CWizKMSettingsSection section;
	GetSection(lpszSection, section);
	return section;
}
BOOL CWizKMSettings::ClearSection(LPCTSTR lpszSection)
{
	if (!m_pSettings)
		return FALSE;
	//
	CheckOuterModified();
	//
	HRESULT hr = m_pSettings->ClearSection(CComBSTR(lpszSection));
	if (FAILED(hr))
	{
		TOLOG1(_T("Failed to clear section: %1"), lpszSection);
		return FALSE;
	}
	//
	Save();
	//
	return TRUE;
}

CWizKMSettings& CWizKMSettings::GetSettings()
{
	static CWizKMSettings settings;
	return settings;
}

CWizKMSettings& WizKMGetSettings()
{
	return CWizKMSettings::GetSettings();
}


BOOL CWizKMSettingsEx::Save()
{
	return WizKMGetSettings().Save();
}

BOOL CWizKMSettingsEx::GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue)
{
	return WizKMGetSettings().GetValue(lpszSection, lpszKey, strValue);
}
BOOL CWizKMSettingsEx::SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue, UINT nFlags)
{
	return WizKMGetSettings().SetValue(lpszSection, lpszKey, lpszValue, nFlags);
}
BOOL CWizKMSettingsEx::ClearSection(LPCTSTR lpszSection)
{
	return WizKMGetSettings().ClearSection(lpszSection);
}
CWizKMSettingsSection CWizKMSettingsEx::GetSection(LPCTSTR lpszSection)
{
	return WizKMGetSettings().GetSection(lpszSection);
}
BOOL CWizKMSettingsEx::GetSection(LPCTSTR lpszSection, CWizKMSettingsSection& section)
{
	return WizKMGetSettings().GetSection(lpszSection, section);
}


//////////////////////////////////////////////////////////////

CString WizKMGetDefaultDisplayTemplate()
{
	CString strTemplateBasePath = WizGetAppPath() + _T("templates\\display\\");
	CString strDefaultTemplateFileName = strTemplateBasePath + _T("default.ziw");
	//
	
	return WizKMGetSettings().GetStr(_T("DisplayTemplate"), _T("DefaultTemplate"), strDefaultTemplateFileName);
}

BOOL WizKMSetDefaultDisplayTemplate(LPCTSTR lpszFileName)
{
	if (!PathFileExists(lpszFileName))
		return FALSE;
	//
	
	return WizKMGetSettings().SetStr(_T("DisplayTemplate"), _T("DefaultTemplate"), lpszFileName, 0);
}

BOOL WizKMGetUsingDisplayTemplate()
{
	return WizKMGetSettings().GetBool(_T("DisplayTemplate"), _T("UseTemplate"), TRUE);
}

BOOL WizKMSetUsingDisplayTemplate(BOOL b)
{
	
	return WizKMGetSettings().SetBool(_T("DisplayTemplate"), _T("UseTemplate"), b, 0);
}


#define CALENDAR_SECTION _T("Calendar")

BOOL WizCalendarIsShowWeekNumbers()
{
	
	return WizKMGetSettings().GetBool(CALENDAR_SECTION, _T("ShowWeekNumbers"), TRUE);
}

BOOL WizCalendarSetShowWeekNumbers(BOOL b)
{
	
	return WizKMGetSettings().SetBool(CALENDAR_SECTION, _T("ShowWeekNumbers"), b, 0);
}


COleDateTime WizCalendarGetFirstWeek()
{
	
	CString strFirstWeek = WizKMGetSettings().GetStr(CALENDAR_SECTION, _T("FirstWeek"), _T(""));
	if (strFirstWeek.IsEmpty())
		return COleDateTime((COleDateTime::GetCurrentTime()).GetYear(), 1, 1, 0, 0, 0);
	//
	COleDateTime t = WizStringToDateTime(strFirstWeek);
	if (t.GetMonth() == 2 && t.GetDay() == 29)
	{
		return COleDateTime((COleDateTime::GetCurrentTime()).GetYear(), 2, 28, 0, 0, 0);
	}
	//
	return COleDateTime((COleDateTime::GetCurrentTime()).GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
}

BOOL WizCalendarSetFirstWeek(const COleDateTime& t)
{
	COleDateTime t1 = COleDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
	//
	
	return WizKMGetSettings().SetStr(CALENDAR_SECTION, _T("FirstWeek"), ::WizDateTimeToString(t1), 0);
}


CString WizKMGetUserActions(LPCTSTR lpszActionsName, LPCTSTR lpszDefActionValue /*= NULL*/)
{
	
	return WizKMGetSettings().GetStr(_T("UserActions"), lpszActionsName, lpszDefActionValue ? lpszDefActionValue : WIZKM_ACTION_VALUE_NO_ACTION);
}

BOOL WizKMSetUserActions(LPCTSTR lpszActionsName, LPCTSTR lpszActionValue)
{
	return WizKMGetSettings().SetStr(_T("UserActions"), lpszActionsName, lpszActionValue, 0);
}


BOOL WizKMIsAutoShowAttach()
{
	return WizKMGetSettings().GetBool(_T("AttachmentsView"), _T("AutoShow"), TRUE);
}
//
void WizKMSetAutoShowAttach(BOOL b)
{
	WizKMGetSettings().SetBool(_T("AttachmentsView"), _T("AutoShow"), b, 0);
}


#ifdef _WIZKMDATABASE_H_

WizSearchFullText WizKMFullTextSearchTypeFromString(const CString& str)
{
	if (0 == str.CompareNoCase(_T("None")))
		return fulltextNone;
	else if (0 == str.CompareNoCase(_T("WindowsSearch")))
		return fulltextWindows;
	else if (0 == str.CompareNoCase(_T("GoogleDesktop")))
		return fulltextGoogle;
	return fulltextInner;
}
CString WizKMFullTextSearchTypeToString(WizSearchFullText eType)
{
	switch (eType)
	{
	case fulltextNone:
		return CString(_T("None"));
	case fulltextWindows:
		return CString(_T("WindowsSearch"));
	case fulltextGoogle:
		return CString(_T("GoogleDesktop"));
	default:
		return CString(_T("Wiz"));
	}
}

WizSearchFullText WizKMGetFullTextSearchType(CWizKMDatabase* pDatabase)
{
	if (!pDatabase)
		return fulltextNone;
	//
	ATLASSERT(pDatabase);
	//
	CString strType = pDatabase->GetMeta(_T("FullTextSearch"), _T("Type"));
	//
	return WizKMFullTextSearchTypeFromString(strType);
}

BOOL WizKMSetFullTextSearchType(CWizKMDatabase* pDatabase, WizSearchFullText eType)
{
	ATLASSERT(pDatabase);
	//
	return pDatabase->SetMeta(_T("FullTextSearch"), _T("Type"), WizKMFullTextSearchTypeToString(eType));
}

#endif //_WIZKMDATABASE_H_

int GetSyncMinutes()
{
	
	return WizKMGetSettings().GetInt(SECTION_SYNC, _T("SyncMinutes"), 15);
}

BOOL SetSyncMinutes(int nMinutes)
{
	
	return WizKMGetSettings().SetInt(SECTION_SYNC, _T("SyncMinutes"), nMinutes, 0);
}

BOOL GetSyncEnabled()
{
	
	return WizKMGetSettings().GetBool(SECTION_SYNC, _T("SyncEnabled"), TRUE);
}

BOOL SetSyncEnabled(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_SYNC, _T("SyncEnabled"), b, 0);
}

BOOL IsSyncShowResult()
{
	
	return WizKMGetSettings().GetBool(SECTION_SYNC, _T("ShowResult"), FALSE);
}

BOOL SetSyncShowResult(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_SYNC, _T("ShowResult"), b, 0);
}


BOOL GetSyncHttpsEnabled()
{
	
	return WizKMGetSettings().GetBool(SECTION_SYNC, _T("Https"), FALSE);
}

BOOL SetSyncHttpsEnabled(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_SYNC, _T("Https"), b, 0);
}

CString GetCachedSyncURL(LPCTSTR lpszCommand)
{
	
	return WizKMGetSettings().GetStr(SECTION_SYNC, lpszCommand, _T(""));
}

BOOL SetCachedSyncURL(LPCTSTR lpszCommand, LPCTSTR lpszURL)
{
	
	return WizKMGetSettings().SetStr(SECTION_SYNC, lpszCommand, lpszURL, 0);
}


#ifdef _WIZKMDATABASE_H_


CString WizKMGetLastTagsText(LPCTSTR lpszAttributeName)
{
	CString strAttributeName(lpszAttributeName);
	if (strAttributeName.IsEmpty())
	{
		strAttributeName = _T("Last");
	}
	
	//
	return WizKMGetSettings().GetStr(_T("UserTagsText"), strAttributeName);
}

void WizKMSetLastTagsText(LPCTSTR lpszAttributeName, LPCTSTR lpszTagsText)
{
	CString strAttributeName(lpszAttributeName);
	if (strAttributeName.IsEmpty())
	{
		strAttributeName = _T("Last");
	}
	
	//
	WizKMGetSettings().SetStr(_T("UserTagsText"), strAttributeName, lpszTagsText, 0);
}

BOOL WizKMGetTagsHistory(CWizStdStringArray& arrayTagsHistory)
{
	
	WizKMGetSettings().GetStringArray(_T("UserTagsText"), arrayTagsHistory);
	//
	return TRUE;
}

BOOL WizKMAddToTagsHistory(LPCTSTR lpszAttributeName, LPCTSTR lpszTagsText)
{
	CString strTagsText(lpszTagsText);
	//
	WizKMRegularTagsText(strTagsText);
	WizKMSetLastTagsText(lpszAttributeName, strTagsText);
	//
	if (-1 == strTagsText.Find(';'))
		return TRUE;
	//
	CWizStdStringArray arrayTag;
	WizSplitTextToArray(strTagsText, ';', arrayTag);
	for (CWizStdStringArray::iterator it = arrayTag.begin();
		it != arrayTag.end();
		it++)
	{
		it->Trim();
	}
	//
	WizStringArrayToText(arrayTag, strTagsText, _T("; "));
	//
	CWizStdStringArray arrayTagsHistory;
	//
	
	WizKMGetSettings().GetStringArray(_T("UserTagsText"), arrayTagsHistory);
	//
	if (-1 != WizFindInArrayNoCase(arrayTagsHistory, strTagsText))
		return TRUE;
	//
	arrayTagsHistory.push_back(strTagsText);
	//
	WizKMGetSettings().SetStringArray(_T("UserTagsText"), arrayTagsHistory);
	//
	return TRUE;
}

BOOL WizKMGetTagsHistoryWithTagsName(CWizKMDatabase* pDatabase, CWizStdStringArray& arrayTagsHistory)
{
	pDatabase->GetTagsName(arrayTagsHistory);
	//
	return WizKMGetTagsHistory(arrayTagsHistory);
}


BOOL WizKMGetRecentPicks(CWizStdStringArray& arrayLocation)
{
	
	//
	CWizKMSettingsSection section;
	if (!WizKMGetSettings().GetSection(_T("RecentPicks"), section))	//empty?
		return TRUE;
	//
	int nCount = section.GetInt(_T("Count"));
	for (int i = 0; i < nCount; i++)
	{
		CString strKey = CString(_T("Item_")) + WizIntToStr(i);
		CString strValue = section.GetStr(strKey);
		if (strValue.IsEmpty())
			continue;
		//
		arrayLocation.push_back(strValue);
	}
	//
	return TRUE;
}

BOOL WizKMGetRecentPicks(CWizKMDatabase* pDatabase, CWizFolderArray& arrayFolder)
{
	CWizStdStringArray arrayLocation;
	if (!WizKMGetRecentPicks(arrayLocation))
		return FALSE;
	//
	int nCount = int(arrayLocation.size());
	for (int i = 0; i < nCount; i++)
	{
		CString strLocation = arrayLocation[i];
		CComPtr<IWizFolder> spFolder = pDatabase->GetFolderByLocation(strLocation, FALSE);
		if (spFolder)
		{
			arrayFolder.push_back(spFolder);
		}
	}
	//
	return TRUE;
}

BOOL WizKMSetRecentPicks(const CWizStdStringArray& arrayLocation)
{
	CString strSection(_T("RecentPicks"));
	//
	CWizKMSettings& settings = WizKMGetSettings();
	//
	int nCount = int(arrayLocation.size());
	settings.ClearSection(strSection);
	settings.SetInt(strSection, _T("Count"), nCount, WIZ_SETTINGS_MANUAL_SAVE);
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strKey = CString(_T("Item_")) + WizIntToStr(i);
		CString strValue = arrayLocation[i];
		//
		settings.SetStr(strSection, strKey, strValue, WIZ_SETTINGS_MANUAL_SAVE);
	}
	//
	settings.Save();
	//
	return TRUE;
}
//
BOOL WizKMAppendRecentPicks(LPCTSTR lpszLocation)
{
	if (!lpszLocation)
		return FALSE;
	//
	if (!*lpszLocation)
		return FALSE;
	//
	if (0 == CString(lpszLocation).CompareNoCase(CString(_T("/")) + FOLDER_DELETED_ITEMS + _T("/")))
		return TRUE;
	//
	CWizStdStringArray arrayLocation;
	if (!WizKMGetRecentPicks(arrayLocation))
		return FALSE;
	//
	if (-1 != ::WizFindInArrayNoCase(arrayLocation, lpszLocation))
		return TRUE;
	//
	arrayLocation.insert(arrayLocation.begin(), lpszLocation);
	//
	if (arrayLocation.size() > 10)
	{
		arrayLocation.resize(10);
	}
	//
	return WizKMSetRecentPicks(arrayLocation);
}

BOOL WizKMAppendRecentPicks(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	return WizKMAppendRecentPicks(CWizKMDatabase::GetFolderLocation(pFolder));
}




BOOL WizKMGetFavoriteFolders(CWizStdStringArray& arrayLocation)
{
	CWizKMSettingsSection section;
	if (!WizKMGetSettings().GetSection(_T("FavoriteFolders"), section))	//empty?
		return TRUE;
	//
	int nCount = section.GetInt(_T("Count"));
	for (int i = 0; i < nCount; i++)
	{
		CString strKey = CString(_T("Item_")) + WizIntToStr(i);
		CString strValue = section.GetStr(strKey);
		if (strValue.IsEmpty())
			continue;
		//
		arrayLocation.push_back(strValue);
	}
	//
	return TRUE;
}

BOOL WizKMGetFavoriteFolders(CWizKMDatabase* pDatabase, CWizFolderArray& arrayFolder)
{
	CWizStdStringArray arrayLocation;
	if (!WizKMGetFavoriteFolders(arrayLocation))
		return FALSE;
	//
	int nCount = int(arrayLocation.size());
	for (int i = 0; i < nCount; i++)
	{
		CString strLocation = arrayLocation[i];
		CComPtr<IWizFolder> spFolder = pDatabase->GetFolderByLocation(strLocation, FALSE);
		if (spFolder)
		{
			arrayFolder.push_back(spFolder);
		}
	}
	//
	return TRUE;
}

BOOL WizKMSetFavoriteFolders(const CWizStdStringArray& arrayLocation)
{
	CString strSection(_T("FavoriteFolders"));
	//
	CWizKMSettings& settings = WizKMGetSettings();
	//
	int nCount = int(arrayLocation.size());
	settings.ClearSection(strSection);
	settings.SetInt(strSection, _T("Count"), nCount, WIZ_SETTINGS_MANUAL_SAVE);
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strKey = CString(_T("Item_")) + WizIntToStr(i);
		CString strValue = arrayLocation[i];
		//
		settings.SetStr(strSection, strKey, strValue, WIZ_SETTINGS_MANUAL_SAVE);
	}
	//
	settings.Save();
	//
	return TRUE;
}
//
BOOL WizKMAppendFavoriteFolders(LPCTSTR lpszLocation)
{
	if (!lpszLocation)
		return FALSE;
	//
	if (!*lpszLocation)
		return FALSE;
	//
	if (0 == CString(lpszLocation).CompareNoCase(CString(_T("/")) + FOLDER_DELETED_ITEMS + _T("/")))
		return TRUE;
	//
	CWizStdStringArray arrayLocation;
	if (!WizKMGetFavoriteFolders(arrayLocation))
		return FALSE;
	//
	if (-1 != ::WizFindInArrayNoCase(arrayLocation, lpszLocation))
		return TRUE;
	//
	arrayLocation.insert(arrayLocation.begin(), lpszLocation);
	//
	/*
	if (arrayLocation.size() > 10)
	{
		arrayLocation.resize(10);
	}
	*/
	//
	return WizKMSetFavoriteFolders(arrayLocation);
}

BOOL WizKMAppendFavoriteFolders(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	return WizKMAppendFavoriteFolders(CWizKMDatabase::GetFolderLocation(pFolder));
}

BOOL WizKMRemoveFavoriteFolders(LPCTSTR lpszLocation)
{
	if (!lpszLocation)
		return FALSE;
	//
	if (!*lpszLocation)
		return FALSE;
	//
	if (0 == CString(lpszLocation).CompareNoCase(CString(_T("/")) + FOLDER_DELETED_ITEMS + _T("/")))
		return TRUE;
	//
	CWizStdStringArray arrayLocation;
	if (!WizKMGetFavoriteFolders(arrayLocation))
		return FALSE;
	//
	int index = ::WizFindInArrayNoCase(arrayLocation, lpszLocation);
	if (-1 == index)
		return FALSE;
	//
	arrayLocation.erase(arrayLocation.begin() + index);
	//
	return WizKMSetFavoriteFolders(arrayLocation);
}

BOOL WizKMRemoveFavoriteFolders(IWizFolder* pFolder)
{
	if (!pFolder)
		return FALSE;
	//
	return WizKMRemoveFavoriteFolders(CWizKMDatabase::GetFolderLocation(pFolder));
}


CString WizKMGetRecentDocumentsSettingsSectionName(CWizKMDatabase* pDatabase)
{
	ATLASSERT(pDatabase);
	//
	CString strPath = pDatabase->GetDatabasePath();
	strPath = WizGetLongFileName(strPath);
	strPath.MakeLower();
	//
	return CString(_T("RecentDocuments_")) + WizMd5StringNoSpace(strPath);
}

void WizKMGetRecentDocuments(CWizKMDatabase* pDatabase, CWizKMDocumentGUIDAndTitleArray& arrayDocument)
{
	arrayDocument.clear();
	//
	CWizStdStringArray arrayText;
	//
	
	WizKMGetSettings().GetStringArray(WizKMGetRecentDocumentsSettingsSectionName(pDatabase), arrayText);
	//
	for (CWizStdStringArray::const_iterator it =  arrayText.begin();
		it != arrayText.end();
		it++)
	{
		CString strText = *it;
		//
		WIZKMDOCUMENTGUIDANDTITLE data;
		if (!WizStringSimpleSplit(strText, '|', data.strGUID, data.strTitle))
			continue;
		//
		if (data.strGUID.IsEmpty())
			continue;
		if (data.strTitle.IsEmpty())
			continue;
		//
		CComPtr<IWizDocument> spDocument = pDatabase->GetDocumentByGUID(data.strGUID);
		if (!spDocument)
			continue;
		//
		data.strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
		//
		arrayDocument.push_back(data);
	}
}

void WizKMSetRecentDocuments(CWizKMDatabase* pDatabase, const CWizKMDocumentGUIDAndTitleArray& arrayDocument)
{
	CWizStdStringArray arrayText;
	//
	int nIndex = 0;
	for (CWizKMDocumentGUIDAndTitleArray::const_iterator it = arrayDocument.begin();
		it != arrayDocument.end();
		it++)
	{
		arrayText.push_back(it->strGUID + _T("|") + it->strTitle);
		nIndex++;
		//
		if (nIndex >= 10)
			break;
	}
	//
	
	WizKMGetSettings().SetStringArray(WizKMGetRecentDocumentsSettingsSectionName(pDatabase), arrayText);
}
void WizKMAddRecentDocuments(CWizKMDatabase* pDatabase, LPCTSTR lszDocumentGUID, LPCTSTR lpszDocumentTitle)
{
	CWizKMDocumentGUIDAndTitleArray arrayDocument;
	WizKMGetRecentDocuments(pDatabase, arrayDocument);
	//
	WIZKMDOCUMENTGUIDANDTITLE data;
	data.strGUID = lszDocumentGUID;
	data.strTitle = lpszDocumentTitle;
	//
	arrayDocument.insert(arrayDocument.begin(), data);
	//
	WizKMSetRecentDocuments(pDatabase, arrayDocument);
}


#endif //_WIZKMDATABASE_H_


#ifdef _WIZ_USE_HTML

CString WizKMGetDefaultCSSFileName()
{
	CString strFileName(_T("files\\default.css"));
	//
	CString strUserFileName = ::WizKMGetSettingsPath() + strFileName;
	if (PathFileExists(strUserFileName))
		return strUserFileName;
	//
	CString strSystemFileName = WizGetAppPath() + strFileName;
	return strSystemFileName;
}
BOOL WizKMInsertDefaultCSSToHtml(CString& strHtml)
{
	
	CWizKMSettingsSection section;
	WizKMGetSettings().GetSection(_T("DocumentDefaults"), section);
	//
	BOOL bEnableDefaultCSS = section.GetBool(_T("EnableCSS"), FALSE);
	if (!bEnableDefaultCSS)
		return TRUE;
	//
	BOOL bEnableColor = section.GetBool(_T("EnableColor"), FALSE);
	//
	CString strFontName = section.GetStr(_T("FontName"), _T("Arial"));
	CString strFontSize = section.GetStr(_T("FontSize"), _T("10.5pt"));
	CString strLineHeight = section.GetStr(_T("LineHeight"), _T("1cm"));
	CString strFontColor = section.GetStr(_T("Color"), _T("black"));
	CString strBackgroundColor = section.GetStr(_T("BackgroundColor"), _T("white"));
	//
	if (!bEnableColor)
	{
		strFontColor = _T("inherit");
		strBackgroundColor = strFontColor;
	}
	//
	CString strCSSText;
	CString strDefaultCSSFileName = WizKMGetDefaultCSSFileName();
	if (!WizLoadUnicodeTextFromFile(strDefaultCSSFileName, strCSSText))
	{
		TOLOG1(_T("Failed to load default CSS file: %1"), strDefaultCSSFileName);
		return FALSE;
	}
	//
	strCSSText.Replace(_T("/*cssFontName*/"), strFontName);
	strCSSText.Replace(_T("/*cssFontSize*/"), strFontSize);
	strCSSText.Replace(_T("/*cssLineHeight*/"), strLineHeight);
	strCSSText.Replace(_T("/*cssColor*/"), strFontColor);
	strCSSText.Replace(_T("/*cssBackgroundColor*/"), strBackgroundColor);
	//
	strCSSText = CString(_T("\r\n<style type=\"text/css\" id=\"wiz_custom_css\">\r\n")) + strCSSText + _T("\r\n</style>\r\n");
	//
	::WizHTMLInsertTextInHead2(strCSSText, strHtml);
	//
	return TRUE;
}
BOOL WizKMInsertDefaultCSS(LPCTSTR lpszHtmlFileName)
{
	CString strHtml;
	if (!WizLoadUnicodeTextFromFile(lpszHtmlFileName, strHtml))
	{
		TOLOG1(_T("Failed to load template html file: %1"), lpszHtmlFileName);
		return FALSE;
	}
	//
	if (!::WizKMInsertDefaultCSSToHtml(strHtml))
	{
		TOLOG1(_T("Failed to insert default css to file: %1"), lpszHtmlFileName);
		return FALSE;
	}
	//
	if (!WizSaveUnicodeTextToUnicodeFile(lpszHtmlFileName, strHtml))
	{
		TOLOG1(_T("Failed to save template html file: %1"), lpszHtmlFileName);
		return FALSE;
	}
	//
	return TRUE;
}

#endif //#ifdef _WIZ_USE_HTML


CString ExplorerGetDoubleClickAction()
{
	
	return WizKMGetSettings().GetStr(SECTION_EXPLORER, _T("DoubleClickAction"), _T("NewNote"));
}

BOOL ExplorerSetDoubleClickAction(LPCTSTR lpszButtonName)
{
	
	return WizKMGetSettings().SetStr(SECTION_EXPLORER, _T("DoubleClickAction"), lpszButtonName, 0);
}


//
BOOL ExplorerIsEditDocumentAsDefault()
{
	
	return WizKMGetSettings().GetBool(SECTION_EXPLORER, _T("EditDocumentAsDefault"), FALSE);
}
BOOL ExplorerSetEditDocumentAsDefault(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_EXPLORER, _T("EditDocumentAsDefault"), b, 0);
}



//
BOOL ExplorerIsCloseToTray()
{
	
	return WizKMGetSettings().GetBool(SECTION_EXPLORER, _T("CloseToTray"), TRUE);
}
BOOL ExplorerSetCloseToTray(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_EXPLORER, _T("CloseToTray"), b, 0);
}

WizSaveDestination ExplorerGetSaveDestination()
{
	
	return (WizSaveDestination)WizKMGetSettings().GetInt(SECTION_EXPLORER, _T("SaveDestination"), wizPromptSelect);
}


BOOL ExplorerSetSaveDestination(WizSaveDestination dest)
{
	
	return WizKMGetSettings().SetInt(SECTION_EXPLORER, _T("SaveDestination"), dest, 0);
}


BOOL ExplorerIsEnableGlobalPlugins()
{
	
	return WizKMGetSettings().GetBool(SECTION_EXPLORER, _T("EnableGlobalPlugins"), TRUE);
}

BOOL ExplorerSetEnableGlobalPlugins(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_EXPLORER, _T("EnableGlobalPlugins"), b, 0);
}

CString ExplorerGetEditorSettings()
{
	
	//
	BOOL bTabAsSpace = WizKMGetSettings().GetBool(_T("Editor"), _T("TabAsSpace"), TRUE);
	int nTabSize = WizKMGetSettings().GetInt(_T("Editor"), _T("TabSize"), 4);
	CString strTabText = WizKMGetSettings().GetStr(_T("Editor"), _T("TabText"), _T(""));
	//
	BOOL bEnterInsertDiv = WizKMGetSettings().GetBool(_T("Editor"), _T("EnterInsertDiv"), TRUE);
	//
	return WizFormatString4(_T("/TabAsSpace=%1 /TabSize=%2 /TabText=%3 /EnterInsertDiv=%4"),
		bTabAsSpace ? _T("1") : _T("0"),
		WizIntToStr(nTabSize),
		strTabText,
		bEnterInsertDiv ? _T("1") : _T("0"));
}


BOOL IsCategoryTreeCtrlIncludeSubFolders()
{
	return WizKMGetSettings().GetBool(_T("CategoryTreeCtrl"), _T("IncludeSubFolders"), FALSE);
}
void SetCategoryTreeCtrlIncludeSubFolders(BOOL b)
{
	
	WizKMGetSettings().SetBool(_T("CategoryTreeCtrl"), _T("IncludeSubFolders"), b, 0);
}



//
BOOL ExplorerIsShowStatusBar(CWizKMSettings& settings)
{
	return WizKMGetSettings().GetBool(SECTION_EXPLORER, _T("StatusBarVisible"), TRUE);
}
BOOL ExplorerSetShowStatusBar(CWizKMSettings& settings, BOOL b)
{
	return WizKMGetSettings().SetBool(SECTION_EXPLORER, _T("StatusBarVisible"), b, 0);
}


BOOL ExplorerIsShowStatusBar()
{
	
	return ExplorerIsShowStatusBar(WizKMGetSettings());
}
BOOL ExplorerSetShowStatusBar(BOOL b)
{
	
	return ExplorerSetShowStatusBar(WizKMGetSettings(), b);
}

CString WizKMGetDestinationParam(LPCTSTR lpszSelectedLocation)
{
	CString strAppFileName = ::WizGetAppFileName();
	CString strAppName = WizExtractFileTitle(strAppFileName);

	CString strSelectedLocation(lpszSelectedLocation);
	//
	switch (ExplorerGetSaveDestination())
	{
	case wizSelectedFolder:
		if (strSelectedLocation.IsEmpty())
		{
			return WizFormatString1(_T("/Location=/%1/"), FOLDER_MY_DRAFTS);
		}
		else
		{
			return WizFormatString1(_T("/Location=%1"), strSelectedLocation);
		}
	case wizPromptSelect:
		return CString(_T("/PromptLocation=1"));
	default:
		return WizFormatString1(_T("/Location=/%1/"), FOLDER_MY_DRAFTS);
	}
}

int WizKMCopySelection(HWND hwndOwnerWindow, HWND hwndForegroundWindow, HWND hwndLastIEWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation)
{
	if (!hwndForegroundWindow)
		return 0;
	//
	CString strOwnerWindow = WizInt64ToStr(__int64(hwndOwnerWindow));
	CString strForegroundWindow = WizInt64ToStr(__int64(hwndForegroundWindow));
	CString strLastIEWindow = WizInt64ToStr(__int64(hwndLastIEWindow));
	//
	CString strDatabasePath(lpszDatabasePath);
	//
	CString strParams = ::WizFormatString5(_T("/OwnerWindow=%1 /ForegroundWindow=%2 /LastIEWindow=%3 /DatabasePath=%4 %5"),
		strOwnerWindow,
		strForegroundWindow,
		strLastIEWindow,
		strDatabasePath,
		WizKMGetDestinationParam(lpszSelectedLocation));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMCopySelection"), strParams, SW_SHOW);
	//
	return 0;
}


int WizKMClipScreenshot(HWND hwndOwnerWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation)
{
	Sleep(500);
	CString strOwnerWindow = WizInt64ToStr(__int64(hwndOwnerWindow));
	CString strDatabasePath(lpszDatabasePath);
	//
	CString strParams = ::WizFormatString3(_T("/OwnerWindow=%1 /DatabasePath=%2 %3"),
		strOwnerWindow, 
		strDatabasePath,
		WizKMGetDestinationParam(lpszSelectedLocation));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMClipScreenshot"), strParams, SW_SHOW);
	//
	return 0;
}


int WizKMPasteToWiz(HWND hwndOwnerWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation)
{
	// TODO: Add your command handler code here
	CString strOwnerWindow = WizInt64ToStr(__int64(hwndOwnerWindow));
	CString strDatabasePath(lpszDatabasePath);
	//
	CString strParams = ::WizFormatString3(_T("/OwnerWindow=%1 /DatabasePath=%2 %3"),
		strOwnerWindow,
		strDatabasePath,
		WizKMGetDestinationParam(lpszSelectedLocation));
	//
	::WizKMShellRunDll(WizGetAppPath() + _T("WizKMControls.dll"), _T("WizKMPasteToWiz"), strParams, SW_SHOW);
	//
	return 0;
}



BOOL WizKMImportFilesDataLoadFromFile(LPCTSTR lpszFileName, WIZKMIMPORTFILESDATA& data)
{
	CWizIniFileEx file;
	if (!file.LoadFromFile(lpszFileName))
		return FALSE;
	//
	CString strCommonSection(_T("Common"));
	//
	data.strDatabasePath = file.GetStringDef(strCommonSection, _T("Database"));
	if (data.strDatabasePath.IsEmpty())
		return FALSE;
	//
	data.strLocation = file.GetStringDef(strCommonSection, _T("Location"));
	if (data.strLocation.IsEmpty())
	{
		data.strLocation = CString(_T("/")) + FOLDER_MY_DRAFTS + _T("/");
	}
	//
	data.nUpdateDocumentFlags = file.GetIntDef(strCommonSection, _T("UpdateDocumentFlags"), 0);
	data.bDelete = file.GetBoolDef(strCommonSection, _T("Delete"), FALSE);
	//
	int nCount = file.GetIntDef(strCommonSection, _T("FileCount"), 0);
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strFileName = file.GetStringDef(_T("Files"), WizIntToStr(i));
		if (PathFileExists(strFileName))
		{
			data.arrayFile.push_back(strFileName);
		}
	}
	//
	if (data.bDelete)
	{
		DeleteFile(lpszFileName);
	}
	//
	//data.nUpdateDocumentFlags |= wizUpdateDocumentSaveContentOnly;
	//
	return TRUE;
}



BOOL WizKMImportFilesDataSaveToFile(LPCTSTR lpszFileName, const WIZKMIMPORTFILESDATA& data)
{
	CWizIniFileEx file;
	CString strCommonSection(_T("Common"));
	//
	file.SetString(strCommonSection, _T("Database"), data.strDatabasePath);
	file.SetString(strCommonSection, _T("Location"), data.strLocation);
	file.SetString(strCommonSection, _T("UpdateDocumentFlags"), WizIntToStr(data.nUpdateDocumentFlags));
	file.SetString(strCommonSection, _T("FileCount"), WizIntToStr((int)data.arrayFile.size()));
	file.SetString(strCommonSection, _T("Delete"), data.bDelete ? _T("1") : _T("0"));
	//
	int nCount = int(data.arrayFile.size());
	for (int i = 0; i < nCount; i++)
	{
		file.SetString(_T("Files"), WizIntToStr(i), data.arrayFile[i]);
	}
	//
	return file.SaveToUnicodeFile(lpszFileName);
}

BOOL WizKMImportFiles(LPCTSTR lpszFileName)
{
	CString strWizShellFileName = WizKMGetShellFileName();
	CString strParams = WizFormatString2(_T("\"%1\", WizKMImportFiles /CommandFileName=%2"),
		WizGetAppPath() + _T("WizKMControls.dll"),
		lpszFileName);
	//
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	//
	ShellExecute(NULL, _T("open"), strWizShellFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}

BOOL WizKMImportFiles(LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, UINT nUpdateDocumentFlags, const CWizStdStringArray& arrayFile)
{
	if (arrayFile.empty())
		return FALSE;
	//
	CString strLocation(lpszLocation);
	if (strLocation.IsEmpty())
	{
		strLocation = WizFormatString1(_T("/%1/"), FOLDER_MY_DRAFTS);
	}
	//
	WIZKMIMPORTFILESDATA data;
	data.arrayFile.assign(arrayFile.begin(), arrayFile.end());
	data.strDatabasePath = lpszDatabasePath;
	data.strLocation = strLocation;
	data.nUpdateDocumentFlags = nUpdateDocumentFlags;
	data.bDelete = TRUE;
	//
	CString strFileName = WizKMGetTempPath() + WizIntToStr(GetTickCount()) + _T(".ini");
	//
	if (!WizKMImportFilesDataSaveToFile(strFileName, data))
		return FALSE;
	//
	return WizKMImportFiles(strFileName);
}


CWizKMDatabaseWindow::CWizKMDatabaseWindow()
{
}
CWizKMDatabaseWindow::~ CWizKMDatabaseWindow()
{
	Unregister();
}
CString CWizKMDatabaseWindow::GetDatabasePath() const
{
	return m_strDatabasePath;
}
CString CWizKMDatabaseWindow::RegularDatabasePath(LPCTSTR lpszDatabasePath)
{
	CString strDatabasePath = WizGetLongFileName(lpszDatabasePath);
	strDatabasePath.Trim('"');
	strDatabasePath.MakeLower();
	WizPathAddBackslash(strDatabasePath);
	return strDatabasePath;
}
CString CWizKMDatabaseWindow::GetKeyPathOfDatabase(LPCTSTR lpszDatabasePath)
{
	CString strDatabasePath = RegularDatabasePath(lpszDatabasePath);
	return CString(WIZKM_REG_KEY_ROOT) + CString(_T("\\WizKMDatabase_")) + WizMd5StringNoSpace(strDatabasePath);
}
//
HWND CWizKMDatabaseWindow::GetWindowOfDatabase(LPCTSTR lpszDatabasePath, LPCTSTR lpszType)
{
	CString strKey(GetKeyPathOfDatabase(lpszDatabasePath));
	CString strVal = WizRegReadStringDef(HKEY_CURRENT_USER, strKey, lpszType, NULL);
	if (strVal.IsEmpty())
		return NULL;
	//
	__int64 nVal = _ttoi64(strVal);
	if (0 == nVal)
		return NULL;
	//
	HWND hWnd = (HWND)nVal;
	if (IsWindow(hWnd))
		return hWnd;
	//
	return NULL;
}
//
BOOL CWizKMDatabaseWindow::GetAllWindowsOfDatabase(LPCTSTR lpszDatabasePath, std::vector<HWND>& arrayHwnd)
{
	CString strKey = GetKeyPathOfDatabase(lpszDatabasePath);
	CWizStdStringArray arrayName;
	WizRegEnumValueName(HKEY_CURRENT_USER, strKey, arrayName);
	//
	for (CWizStdStringArray::const_iterator it = arrayName.begin();
		it != arrayName.end();
		it++)
	{
		if (0 == it->CompareNoCase(WIZKM_DATABASE_WINDOW_DATABASE_PARH))
			continue;
		if (0 == it->CompareNoCase(WIZKM_DATABASE_WINDOW_STOP_SYNC))
			continue;

		HWND hWnd = GetWindowOfDatabase(lpszDatabasePath, *it);
		if (hWnd)
		{
			arrayHwnd.push_back(hWnd);
		}
	}
	return TRUE;
}
//
BOOL CWizKMDatabaseWindow::QueryStopStatus(LPCTSTR lpszDatabasePath)
{
	CString strKey = GetKeyPathOfDatabase(lpszDatabasePath);
	return WizRegReadBoolDef(HKEY_CURRENT_USER, strKey, WIZKM_DATABASE_WINDOW_STOP_SYNC, FALSE);
}
BOOL CWizKMDatabaseWindow::SetStopStatus(LPCTSTR lpszDatabasePath, BOOL b)
{
	CString strKey = GetKeyPathOfDatabase(lpszDatabasePath);
	return WizRegWriteBool(HKEY_CURRENT_USER, strKey, WIZKM_DATABASE_WINDOW_STOP_SYNC, b);
}
//
BOOL CWizKMDatabaseWindow::Register(LPCTSTR lpszDatabasePath, HWND hWnd, LPCTSTR lpszType)
{
	m_strDatabasePath = lpszDatabasePath;
	m_hWnd = hWnd;
	m_strType = lpszType;
	//
	CString strKey(GetKeyPathOfDatabase(m_strDatabasePath));
	//
	return WizRegWriteString(HKEY_CURRENT_USER, strKey, WIZKM_DATABASE_WINDOW_DATABASE_PARH, m_strDatabasePath)
		&& WizRegWriteString(HKEY_CURRENT_USER, strKey, lpszType, WizInt64ToStr(__int64(hWnd)));
}
//
BOOL CWizKMDatabaseWindow::Unregister()
{
	CString strKey(GetKeyPathOfDatabase(m_strDatabasePath));
	return WizRegKeyExists(HKEY_CURRENT_USER, strKey)
		&& WizRegDeleteValue(HKEY_CURRENT_USER, strKey, m_strType);
}
//
void CWizKMDatabaseWindow::ShowSyncWindow()
{
	HWND hWnd = GetWindowOfDatabase(m_strDatabasePath, WIZKM_DATABASE_WINDOW_SYNC_DETAILS);
	if (IsWindow(hWnd))
	{
		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
	}
}
//
void CWizKMDatabaseWindow::StopSync()
{
	SetStopStatus(m_strDatabasePath, TRUE);
}


CString WizKMGetWizHtmlEditorName()
{
	return CString(WizGetProductName() + _T(" Html Editor"));
}



BOOL WizKMIsWizHtmlEditor(const WIZKMEDITORDATA& data)
{
	CString strFileName = WizGetLongFileName(data.strFileName);
	CString strName = WizExtractFileName(strFileName);
	return 0 == strName.CompareNoCase(_T("WizHtmlEditor.exe"));
}

WIZKMEDITORDATA WizKMGetWizHtmlEditor()
{
	WIZKMEDITORDATA data;
	data.strName = WizKMGetWizHtmlEditorName();
	data.strFileName = WizGetAppPath() + _T("WizHtmlEditor.exe");
	return data;
}
BOOL WizKMIsWizHtmlEditorInstalled()
{
	return PathFileExists(WizKMGetWizHtmlEditor().strFileName);
}

intptr_t WizKMEditorArrayIndexOfFileName(const CWizKMEditorDataArray& arrayEditor, LPCTSTR lpszFileName)
{
	CString strFileName = WizGetLongFileName(lpszFileName);
	//
	size_t nCount = arrayEditor.size();
	for (size_t i = 0; i < nCount; i++)
	{
		if (0 == WizGetLongFileName(arrayEditor[i].strFileName).CompareNoCase(strFileName))
		{
			return i;
		}
	}
	//
	return -1;
}
intptr_t WizKMEditorArrayIndexOfName(const CWizKMEditorDataArray& arrayEditor, LPCTSTR lpszName)
{
	size_t nCount = arrayEditor.size();
	for (size_t i = 0; i < nCount; i++)
	{
		if (0 == arrayEditor[i].strName.CompareNoCase(lpszName))
		{
			return i;
		}
	}
	//
	return -1;
}

BOOL WizKMGetEditor(CWizKMEditorDataArray& arrayEditor)
{
	if (WizKMIsWizHtmlEditorInstalled())
	{
		arrayEditor.push_back(WizKMGetWizHtmlEditor());
	}
	//
	
	int nCount = WizKMGetSettings().GetInt(SECTION_EDITOR, _T("Count"));
	//
	for (int i = 0; i < nCount; i++)
	{
		CString strSectionName = SECTION_EDITOR + CString(_T("_")) + WizIntToStr(i);
		//
		WIZKMEDITORDATA data;
		data.strName = WizKMGetSettings().GetStr(strSectionName, _T("Name"));
		data.strFileName = WizKMGetSettings().GetStr(strSectionName, _T("FileName"));
		data.strParams = WizKMGetSettings().GetStr(strSectionName, _T("CommandLine"));
		data.bTextEditor = WizKMGetSettings().GetBool(strSectionName, _T("TextEditor"));
		data.bUTF8Encoding = WizKMGetSettings().GetBool(strSectionName, _T("UTF8Encoding"));
		//
		if (0 == WizExtractFileName(data.strFileName).CompareNoCase(_T("WizHtmlEditor.exe")))
			continue;
		//
		if (data.strName.IsEmpty())
			continue;
		if (data.strFileName.IsEmpty())
			continue;
		if (!PathFileExists(data.strFileName))
			continue;
		//
		arrayEditor.push_back(data);
	}
	//
	return TRUE;
}

BOOL WizKMSetEditor(const CWizKMEditorDataArray& arrayEditor)
{
	CWizKMSettings& settings = WizKMGetSettings();
	//
	size_t nCount = arrayEditor.size();
	settings.SetInt(SECTION_EDITOR, _T("Count"), int(nCount), WIZ_SETTINGS_MANUAL_SAVE);
	//
	for (size_t i = 0; i < nCount; i++)
	{
		const WIZKMEDITORDATA& data = arrayEditor[i];
		CString strSectionName = SECTION_EDITOR + CString(_T("_")) + WizIntToStr(int(i));
		//
		settings.SetStr(strSectionName, _T("Name"), data.strName, WIZ_SETTINGS_MANUAL_SAVE);
		settings.SetStr(strSectionName, _T("FileName"), data.strFileName, WIZ_SETTINGS_MANUAL_SAVE);
		settings.SetStr(strSectionName, _T("CommandLine"), data.strParams, WIZ_SETTINGS_MANUAL_SAVE);
		settings.SetBool(strSectionName, _T("TextEditor"), data.bTextEditor, WIZ_SETTINGS_MANUAL_SAVE);
		settings.SetBool(strSectionName, _T("UTF8Encoding"), data.bUTF8Encoding, WIZ_SETTINGS_MANUAL_SAVE);
	}
	//
	settings.Save();
	//
	return TRUE;
}

WIZKMEDITORDATA WizKMGetDefaultEditor()
{
	CWizKMEditorDataArray arrayEditor;
	WizKMGetEditor(arrayEditor);
	//
	
	CString strName = WizKMGetSettings().GetStr(SECTION_EDITOR, _T("DefaultEditor2"));
	intptr_t nIndex = WizKMEditorArrayIndexOfName(arrayEditor, strName);
	if (-1 != nIndex)
		return arrayEditor[nIndex];
	//
	WIZKMEDITORDATA data;
	//
	return data;
}
CString WizKMGetDefaultEditorName()
{
	WIZKMEDITORDATA data = WizKMGetDefaultEditor();
	return data.strName;
}

BOOL WizKMSetDefaultEditorName(LPCTSTR lpszName)
{
	
	return WizKMGetSettings().SetStr(SECTION_EDITOR, _T("DefaultEditor2"), lpszName, 0);
}


BOOL WizKMIsPromptSave()
{
	
	return WizKMGetSettings().GetBool(SECTION_EDITOR, _T("PromptSave"), TRUE);
}

BOOL WizKMSetPromptSave(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_EDITOR, _T("PromptSave"), b, 0);
}


int WizKMGetAutoSaveMinutes()
{
	
	return WizKMGetSettings().GetInt(SECTION_EDITOR, _T("AutoSaveMinutes"), 3);
}


BOOL WizKMSetAutoSaveMinutes(int nMinutes)
{
	
	return WizKMGetSettings().SetInt(SECTION_EDITOR, _T("AutoSaveMinutes"), nMinutes, 0);
}



BOOL WizKMIsAutoSave()
{
	
	return WizKMGetSettings().GetBool(SECTION_EDITOR, _T("AutoSaveDocument"), TRUE);
}

BOOL WizKMSetAutoSave(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_EDITOR, _T("AutoSaveDocument"), b, 0);
}



#define WIZKM_FOLDER_SETTINGS_SECTION_SORT		_T("Sort")
#define WIZKM_FOLDER_SETTINGS_KEY_SORT_ORDER	_T("SortOrder")
#define WIZKM_FOLDER_SETTINGS_KEY_SORT_BY		_T("SortBy")




BOOL WizKMUsingOleDisplayDocument()
{
	LPCTSTR lpszSection = _T("Explorer");
	
	return WizKMGetSettings().GetBool(lpszSection, _T("UsingOle"), FALSE);
}

BOOL WizKMSetUsingOleDisplayDocument(BOOL b)
{
	LPCTSTR lpszSection = _T("Explorer");
	
	return WizKMGetSettings().SetBool(lpszSection, _T("UsingOle"), b, 0);
}

BOOL WizKMIsEditNoteWithHtmlEditor()
{
	
	return WizKMGetSettings().GetBool(_T("EditDocument"), _T("EditNoteWithHtmlEditor"), FALSE);
}

BOOL WizKMSetEditNoteWithHtmlEditor(BOOL b)
{
	
	return WizKMGetSettings().SetBool(_T("EditDocument"), _T("EditNoteWithHtmlEditor"), b, 0);
}



CString WizKMGetLastUserName()
{
	return WizKMGetSettings().GetStr(_T("Common"), _T("LastUserName"));
}
//
void WizKMSetLastUserName(LPCTSTR lpszUserName)
{
	WizKMGetSettings().SetStr(_T("Common"), _T("LastUserName"), lpszUserName, 0);
}




#ifdef __WizKMControls_i_h__
#ifdef _WIZKMDATABASE_H_


CString WizKMGetDocumentFileType(IWizDocument* pDocument)
{
	if (!pDocument)
		return CString();
	//
	CString strFileType = CWizKMDatabase::GetDocumentFileType(pDocument);
	strFileType.MakeLower();
	return strFileType;
}
CString WizKMGetAttachmentFileType(IWizDocumentAttachment* pAttachment)
{
	if (!pAttachment)
		return CString();
	//
	CString strAttachmentFileName = CWizKMDatabase::GetAttachmentFileName(pAttachment);
	CString strExt = WizExtractFileExt(strAttachmentFileName);
	strExt.MakeLower();
	return strExt;
}
//
CComPtr<IWizDocumentAttachment> WizKMGetAttachmentOfDocument(IWizDocument* pDocument)
{
	if (!pDocument)
		return NULL;
	//
	CWizDocumentAttachmentArray arrayAttachment;
	CWizKMDatabase::GetDocumentAttachments(pDocument, arrayAttachment);
	//
	if (arrayAttachment.size() != 1)
		return NULL;
	//
	return arrayAttachment[0];
}

//
BOOL WizKMDocumentSupportOle(LPCTSTR lpszDocumentFileType)
{
	if (!lpszDocumentFileType)
		return FALSE;
	//
	if (0 == _tcsicmp(lpszDocumentFileType, _T(".pdf"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".doc"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".docx"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".xls"))
		|| 0 == _tcsicmp(lpszDocumentFileType, _T(".xlsx"))
		)
		return TRUE;
	//
	return FALSE;
}
//
CComPtr<IWizDocumentAttachment> WizKMGetAttachmentOfDocumentForOleViewing(IWizDocument* pDocument, BOOL bCheckOleConfig /*= TRUE*/)
{
	if (!pDocument)
		return NULL;
	//
	if (bCheckOleConfig)
	{
		if (!WizKMUsingOleDisplayDocument())
			return NULL;
	}
	//
	CString strDocumentFileType = WizKMGetDocumentFileType(pDocument);
	if (strDocumentFileType.IsEmpty())
		return NULL;
	//
	CWizDocumentAttachmentArray arrayAttachment;
	CWizKMDatabase::GetDocumentAttachments(pDocument, arrayAttachment);
	//
	CComPtr<IWizDocumentAttachment>  spAttachment = WizKMGetAttachmentOfDocument(pDocument);
	if (!spAttachment)
		return NULL;
	//
	CString strAttachmentFileType = WizKMGetAttachmentFileType(spAttachment);
	if (strDocumentFileType != strAttachmentFileType)
		return NULL;
	//
	if (!WizKMDocumentSupportOle(strDocumentFileType))
		return NULL;
	//
	return spAttachment;
}


BOOL WizKMEditDocumentEx(CWizKMDatabase* pDatabase, IWizDocument* pDocument, BOOL bEditDocument)
{
	if (!pDocument)
		return FALSE;
	//
	CString strDatabasePath = pDatabase->GetDatabasePath();
	CString strDocumentGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	//
	CComBSTR bstrType;
	pDocument->get_Type(&bstrType);
	//
	CString strType(bstrType);
	strType.MakeLower();
	//
	if (WizKMIsEditNoteWithHtmlEditor())
	{
		strType.Empty();
	}
	//
	if (strType == _T("note"))
	{
		CString strNoteExeFileName = WizGetAppPath() + _T("WizNote.exe");
		//
		CString strParams = WizFormatString2(_T("/Command=edit_note /DocumentGUID=%1 /DatabasePath=%2"),
			strDocumentGUID,
			strDatabasePath);
		//
		ShellExecute(NULL, _T("open"), strNoteExeFileName, strParams, NULL, SW_SHOW);
		//
		return TRUE;
	}
	else if (strType == _T("todolist"))
	{
		CString strNoteExeFileName = WizGetAppPath() + _T("WizNote.exe");
		//
		CString strParams = WizFormatString2(_T("/Command=edit_todolist /DocumentGUID=%1 /DatabasePath=%2"),
			strDocumentGUID,
			strDatabasePath);
		//
		ShellExecute(NULL, _T("open"), strNoteExeFileName, strParams, NULL, SW_SHOW);
		//
		return TRUE;
	}
	else if (strType == _T("event"))
	{
		CComPtr<IWizCommonUI> spCommonUI = WizKMCreateCommonUI();
		if (!spCommonUI)
			return FALSE;
		//
		VARIANT_BOOL vbRet = VARIANT_FALSE;
		HRESULT hr = spCommonUI->EditCalendarEvent(pDocument, &vbRet);
		return SUCCEEDED(hr);
	}
	else
	{
		if (bEditDocument)
		{
			CString strEditorTempPath = WizKMGetEditorTempPath();
			CString strTempFileName = strEditorTempPath + WizIntToStr(GetTickCount()) + _T(".htm");
			if (FAILED(pDocument->SaveToHtml(CComBSTR(strTempFileName), 0)))
			{
				TOLOG2(_T("Failed to save %1 to file: %2"), CWizKMDatabase::GetDocumentTitle(pDocument), strTempFileName);
			}
			//
			return WizKMEditDocument(strDatabasePath, strTempFileName, strDocumentGUID);
		}
		else
		{
			CString strExeFileName = WizGetAppPath() + _T("WizViewer.exe");
			//
			CString strFileName = CWizKMDatabase::GetDocumentFileName(pDocument);
			//
			CString strParams = WizFormatString1(_T("\"%1\""), strFileName);
			//
			ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
			//
			return TRUE;
		}
	}
}


BOOL WizKMEditDocumentEx(IWizDocument* pDocument, BOOL bEditDocument)
{
	if (!pDocument)
		return FALSE;
	//
	CComPtr<IDispatch> spDisp;
	pDocument->get_Database(&spDisp);
	//
	CComQIPtr<IWizDatabase> spDatabase(spDisp);
	if (!spDatabase)
		return FALSE;
	//
	CWizKMDatabase db;
	db.SetDatabase(spDatabase);
	//
	return WizKMEditDocumentEx(&db, pDocument, bEditDocument);
}
BOOL WizKMEditDocumentEx(IWizDocument* pDocument)
{
	return WizKMEditDocumentEx(pDocument, TRUE);
}
BOOL WizKMViewDocumentEx(IWizDocument* pDocument)
{
	return WizKMEditDocumentEx(pDocument, FALSE);
}


BOOL WizKMTrackDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszDocumentGUID, LPCTSTR lpszDocumentHtmlFileName, HANDLE hProcess, BOOL bDeleteFiles, BOOL bTextFile, BOOL bUTF8)
{
	DWORD dwProcessID = GetProcessId(hProcess);
	//
	COleDateTime tFile = ::WizGetFileModifiedTime(lpszDocumentHtmlFileName);
	CString strFileTime = ::WizDateTimeToString(tFile);
	//
	CString strCommandLine = WizFormatString8(
		_T("/DatabasePath=%1 /DocumentGUID=%2 /DocumentHtmlFileName=%3 /ProcessID=%4 /FileModified=%5 /DeleteFiles=%6 /TextFile=%7 /UTF8=%8"),
		lpszDatabasePath,
		lpszDocumentGUID,
		lpszDocumentHtmlFileName,
		WizInt64ToStr(dwProcessID),
		strFileTime,
		bDeleteFiles ? _T("1") : _T("0"),
		bTextFile ? _T("1") : _T("0"),
		bUTF8 ? _T("1") : _T("0")
		);
	//
	CString strWizShellCommandLine = WizFormatString2(_T("\"%1\", WizKMTrackDocument %2"),
		WizGetAppPath() + _T("WizKMControls.dll"),
		strCommandLine);
	//
#ifdef _DEBUG
	TOLOG(strWizShellCommandLine);
#endif
	//
	return int(ShellExecute(NULL, _T("open"), WizKMGetShellFileName(),
		strWizShellCommandLine, NULL, SW_SHOW)) > 32;
}

BOOL WizKMExternalEditorEditDocument(const WIZKMEDITORDATA& data, IWizDocument* pDocument)
{
	CString strTempPath = WizGetSystemTempPath() + WizIntToStr(GetTickCount()) + _T("\\");
	WizEnsurePathExists(strTempPath);
	//
	CString strTempFileName;
	if (data.bTextEditor)
	{
		strTempFileName = strTempPath + WizIntToStr(GetTickCount()) + _T(".txt");
		CString strText = CWizKMDatabase::GetDocumentText(pDocument, 0);
		if (data.bUTF8Encoding)
		{
			if (!WizSaveAnsiTextToAnsiFile(strTempFileName, WizBSTR2STR(CP_UTF8, strText), TRUE, FALSE))
				return FALSE;
		}
		else
		{
			if (!WizSaveUnicodeTextToUnicodeFile(strTempFileName, strText))
				return FALSE;
		}
	}
	else
	{
		strTempFileName = strTempPath + WizIntToStr(GetTickCount()) + _T(".htm");
		//
		long nFlags = 0;
		if (data.bUTF8Encoding)
		{
			nFlags |= wizDocumentToHtmlUTF8;
		}
		//
		HRESULT hr = pDocument->SaveToHtml(CComBSTR(strTempFileName), nFlags);
		if (FAILED(hr))
			return FALSE;
	}
	//
	CString strParams = data.strParams;
	if (strParams.IsEmpty())
	{
		strParams = _T("%FileName%");
	}
	//
	strParams.Replace(_T("%FileName%"), WizFormatString1(_T("\"%1\""), strTempFileName));
	//
	HANDLE hProcess = WizCreateProcess(data.strFileName, strParams, TRUE);
	if (!hProcess)
	{
		return FALSE;
	}
	//
	CComPtr<IDispatch> spDatabaseDisp;
	pDocument->get_Database(&spDatabaseDisp);
	CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
	if (!spDatabase)
		return FALSE;
	//
	CComBSTR bstrDatabasePath;
	spDatabase->get_DatabasePath(&bstrDatabasePath);
	//
	CString strDocumentGUID = CWizKMDatabase::GetObjectGUID(pDocument);
	//
	return WizKMTrackDocument(CString(bstrDatabasePath), strDocumentGUID, strTempFileName, hProcess, TRUE, data.bTextEditor, data.bUTF8Encoding);
}


BOOL WizKMTrackAttachment(IWizDocumentAttachment* pAttachment, HANDLE hProcess)
{
	CComPtr<IWizDocument> spDocument = CWizKMDatabase::GetAttachmentDocument(pAttachment);
	if (!spDocument)
		return FALSE;
	//
	CComPtr<IDispatch> spDatabaseDisp;
	spDocument->get_Database(&spDatabaseDisp);
	CComQIPtr<IWizDatabase> spDatabase(spDatabaseDisp);
	if (!spDatabase)
		return FALSE;
	//
	CComBSTR bstrDatabasePath;
	spDatabase->get_DatabasePath(&bstrDatabasePath);
	//
	CString strAttachmentGUID = CWizKMDatabase::GetObjectGUID(pAttachment);
	CString strAttachmentFileName = CWizKMDatabase::GetAttachmentFileName(pAttachment);
	//
	return WizKMTrackAttachment(CString(bstrDatabasePath), strAttachmentGUID, strAttachmentFileName, hProcess);
}


#endif //_WIZKMDATABASE_H_
#endif //__WizKMControls_i_h__


BOOL WizKMIsSingleApp()
{
	
	return WizKMGetSettings().GetBool(_T("Common"), _T("SingleApp"), TRUE);
}

BOOL WizKMSetSingleApp(BOOL b)
{
	
	return WizKMGetSettings().SetBool(_T("Common"), _T("SingleApp"), b, 0);
}


BOOL IsUseGUIDAsDocumentFileName()
{
	
	return WizKMGetSettings().GetBool(SECTION_GLOBALS, _T("GUIDAsDocumentFileName"), FALSE);
}

BOOL SetUseGUIDAsDocumentFileName(BOOL b)
{
	
	return WizKMGetSettings().SetBool(SECTION_GLOBALS, _T("GUIDAsDocumentFileName"), b, 0);
}




BOOL WizKMConvertFileIsConvertToHtml()
{
	
	CString strSection(_T("Import"));
	return WizKMGetSettings().GetBool(strSection, _T("ConvertToHTML"), TRUE);
}

BOOL WizKMConvertFileIsUsingOffice()
{
	
	CString strSection(_T("Import"));
	return WizKMGetSettings().GetBool(strSection, _T("UseOffice"), TRUE);
}
BOOL WizKMConvertFileSetConvertToHtml(BOOL b)
{
	
	CString strSection(_T("Import"));
	return WizKMGetSettings().SetBool(strSection, _T("ConvertToHTML"), b, 0);
}

BOOL WizKMConvertFileSetUsingOffice(BOOL b)
{
	
	CString strSection(_T("Import"));
	return WizKMGetSettings().SetBool(strSection, _T("UseOffice"), b, 0);
}

BOOL WizKMConvertFileNeedToBeAddedToAttachment(LPCTSTR lpszExt)
{
	//
	//CString strAllExt = WizKMGetSettings().GetStr(_T("ImportFile"), _T("FileExt_AddToAttachment"), _T(".doc;.docx;.xls;.xlsx;.ppt;.pptx;.pdf;.wps"));
	CString strAllExt = _T(".doc;.docx;.xls;.xlsx;.ppt;.pptx;.pdf;.wps;.et;.pds;.tif;.tiff");
	//
	strAllExt.MakeLower();
	strAllExt = CString(_T(";")) + strAllExt + _T(";");
	//
	CString strExt(lpszExt);
	strExt.MakeLower();
	strExt = CString(_T(";")) + strExt + _T(";");
	//
	return -1 != strAllExt.Find(strExt);
}

BOOL WizKMConvertFileToHtml(CWizKMToolsDll& dll, LPCTSTR lpszSrcFileName, CString& strHtmlFileName)
{
	
	CString strSection(_T("Import"));
	BOOL bConvertToHTML = WizKMGetSettings().GetBool(strSection, _T("ConvertToHTML"), TRUE);
	BOOL bUseOffice = WizKMGetSettings().GetBool(strSection, _T("UseOffice"), TRUE);
	//
	if (!bConvertToHTML)
	{
		CString strExt = WizExtractFileExt(lpszSrcFileName);
		strExt.MakeLower();
		//
		if (WizKMConvertFileNeedToBeAddedToAttachment(strExt))
		{
			CString strHtml = WizFormatString1(_T("%1"), lpszSrcFileName);
			strHtmlFileName = WizKMGetTempPath() + WizIntToStr(GetTickCount()) + _T(".htm");
			if (!WizSaveUnicodeTextToUnicodeFile(strHtmlFileName, strHtml))
			{
				bConvertToHTML = TRUE;
			}
		}
		else
		{
			bConvertToHTML = TRUE;
		}
	}
	//
	if (bConvertToHTML)
	{
		long nFlags = 0;
		if (!bUseOffice)
		{
			nFlags |= WIZ_CONVERT_FILE_TO_HTML_USE_INNEL_ONVERTER;
		}
		if (!dll.ConvertToHtmlFile2(lpszSrcFileName, nFlags, strHtmlFileName))
		{
			TOLOG1(_T("Failed to convert %1 to html file"), lpszSrcFileName);
			return FALSE;
		}
	}
	if (!PathFileExists(strHtmlFileName))
		return FALSE;
	//
	return TRUE;
}
BOOL WizKMConvertFileToHtml(LPCTSTR lpszSrcFileName, CString& strHtmlFileName)
{
	CWizKMToolsDll dll;
	return WizKMConvertFileToHtml(dll, lpszSrcFileName, strHtmlFileName);
}




#ifdef __ATLCTRLX_H__
#ifdef _WIZ_USE_HTML
BOOL WizCombineHtmlText(CString& strTextTo, LPCTSTR lpszTextFrom)
{
	/*
	////强制获得正文////
	*/
	int nInsertPos = (int)WizStrRStrI_Pos(strTextTo, WizGetHtmlContentHiddenTagEnd());
	if (-1 == nInsertPos)
		nInsertPos = (int)WizStrRStrI_Pos(strTextTo, _T("</body"));
	if (-1 == nInsertPos)
		nInsertPos = (int)WizStrRStrI_Pos(strTextTo, _T("</html"));
	if (-1 == nInsertPos)
		nInsertPos = (int)strTextTo.GetLength();
	//
	CString strFrom;
	if (!WizHtmlGetContentByHiddenTag(lpszTextFrom, strFrom))
	{
		if (!WizHTMLGetBodyTextWithoutBodyTag(lpszTextFrom, strFrom))
			return FALSE;
	}
	//
	strTextTo.Insert(nInsertPos, strFrom);
	//
	return TRUE;
}

BOOL WizKMCombineDocumentsToHtmlFile(const CWizDocumentArray& arrayDocument, LPCTSTR lpszHtmlSplitter, CString& strHtmlFileName)
{
	CString strTempPath = WizKMGetTempPath();
	//
	CWizStdStringArray arrayFile;
	//
	size_t nCount = arrayDocument.size();
	for (size_t i = 0; i < nCount; i++)
	{
		CComPtr<IWizDocument> spDocument = arrayDocument[i];
		//
		CString strFileName = CWizKMDatabase::DocumentToTemp(spDocument);
		arrayFile.push_back(strFileName);
	}
	//
	ATLASSERT(nCount == arrayFile.size());
	//
	CString strHTML;
	//
	for (size_t i = 0; i < nCount; i++)
	{
		CString strFileName = arrayFile[i];
		//
		CString strText;
		if (!WizLoadUnicodeTextFromFile(strFileName, strText))
			return FALSE;
		//
		if (-1 != WizStrStrI_Pos(strText, CString(_T("<frameset"))))
		{
			TOLOG(_T("Cannot combine html because html contains frame set"));
			return FALSE;
		}
		//
		if (!WizCombineHtmlText(strHTML, strText))
			return FALSE;
		//
		if (i < nCount - 1)
		{
			if (lpszHtmlSplitter && *lpszHtmlSplitter)
			{
				WizCombineHtmlText(strHTML, lpszHtmlSplitter);
			}
		}
	}
	//
	strHtmlFileName = strTempPath + WizIntToStr(GetTickCount()) + _T("_combine.htm");
	return WizSaveUnicodeTextToUnicodeFile(strHtmlFileName, strHTML);
}

BOOL WizKMCombineDocuments(const CWizDocumentArray& arrayDocument, LPCTSTR lpszHtmlSplitter, LPCTSTR lpszTitle, BOOL bDelete)
{
	if (arrayDocument.size() <= 1)
		return FALSE;
	//
	CWaitCursor wait;
	//
	CString strHtmlFileName;
	if (!WizKMCombineDocumentsToHtmlFile(arrayDocument, lpszHtmlSplitter, strHtmlFileName))
	{
		TOLOG(_T("Failed to combine documents to html file!"));
		return FALSE;
	}
	//
	CComPtr<IWizDocument> spRetDocument = arrayDocument[0];
	HRESULT hr = spRetDocument->UpdateDocument(CComBSTR(strHtmlFileName), wizUpdateDocumentIncludeScript);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to update document!"));
		return FALSE;
	}
	//
	if (lpszTitle && *lpszTitle)
	{
		spRetDocument->ChangeTitleAndFileName(CComBSTR(lpszTitle));
	}
	//
	for (CWizDocumentArray::const_iterator it = arrayDocument.begin() + 1;
		it != arrayDocument.end();
		it++)
	{
		CWizStdStringArray arrayAttachment;
		::CWizKMDatabase::GetDocumentAttachments(*it, arrayAttachment);
		//
		for (CWizStdStringArray::const_iterator itAttachment = arrayAttachment.begin();
			itAttachment != arrayAttachment.end();
			itAttachment++)
		{
			if (PathFileExists(*itAttachment))
			{
				CComPtr<IDispatch> spAttachmentDisp;
				hr = spRetDocument->AddAttachment(CComBSTR(*itAttachment), &spAttachmentDisp);
				if (FAILED(hr))
				{
					TOLOG(_T("Failed to combine attachments!"));
					return FALSE;
				}
			}
		}
		if (bDelete)
		{
			hr = (*it)->Delete();
			if (FAILED(hr))
			{
				TOLOG1(_T("Failed to delete document: %1"), CWizKMDatabase::GetDocumentTitle(*it));
			}
		}
	}
	//
	return TRUE;
}

void WizKMGetCombineDocumentSettings(BOOL& bInsertSplitterHtml, CString& strSplitterHtml, BOOL& bDeleteDocuments)
{
	CWizKMSettings& settings = WizKMGetSettings();
	bInsertSplitterHtml = settings.GetBool(g_lpszCombineDocumentsSection, _T("InsertSpliterHtml"), bInsertSplitterHtml);
	strSplitterHtml = settings.GetStr(g_lpszCombineDocumentsSection, _T("SpliterHtml"), strSplitterHtml);
	bDeleteDocuments = settings.GetBool(g_lpszCombineDocumentsSection, _T("DeleteDocuments"), bDeleteDocuments);
}
void WizKMSetCombineDocumentSettings(BOOL bInsertSplitterHtml, LPCTSTR lpszSplitterHtml, BOOL bDeleteDocuments)
{
	CWizKMSettings& settings = WizKMGetSettings();	
	settings.SetBool(g_lpszCombineDocumentsSection, _T("InsertSpliterHtml"), bInsertSplitterHtml, WIZ_SETTINGS_MANUAL_SAVE);
	settings.SetStr(g_lpszCombineDocumentsSection, _T("SpliterHtml"), lpszSplitterHtml, WIZ_SETTINGS_MANUAL_SAVE);
	settings.SetBool(g_lpszCombineDocumentsSection, _T("DeleteDocuments"), bDeleteDocuments, WIZ_SETTINGS_MANUAL_SAVE);
	settings.Save();
}

BOOL WizKMCombineDocuments(IWizDocument* pDocOld, IWizDocument* pDocNew)
{
	BOOL bInsertSplitterHtml = TRUE;
	CString strSplitterHtml;
	BOOL bDeleteDocuments = TRUE;
	//
	WizKMGetCombineDocumentSettings(bInsertSplitterHtml, strSplitterHtml, bDeleteDocuments);
	//
	CString strTitle = CWizKMDatabase::GetDocumentTitle(pDocOld);
	//
	CWizDocumentArray arrayDocument;
	arrayDocument.push_back(pDocOld);
	arrayDocument.push_back(pDocNew);
	return WizKMCombineDocuments(arrayDocument, strSplitterHtml, strTitle, TRUE);
}

#endif //_WIZ_USE_HTML
#endif //__ATLCTRLX_H__


