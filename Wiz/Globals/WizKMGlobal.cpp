#include "stdafx.h"
#include "WizKMGlobal.h"


#include <shellapi.h>

CString WizKMGetTempPath()
{
	CString strPath = WizGetSystemTempPath() + WizGetProductName() + _T("\\");
	WizEnsurePathExists(strPath);
	return strPath;
}

CString WizKMGetEditorTempPath()
{
	CString strPath = WizGetSystemTempPath() + _T("WizHtmlEditor\\") + WizIntToStr(GetTickCount()) + _T("\\");
	WizEnsurePathExists(strPath);
	return strPath;
}


CString WizKMSelectDataStore(LPCTSTR lpszReg, LPCTSTR lpszApp)
{
	CString strRet(lpszApp);
	//
	typedef BOOL WINAPI Type_WizKMSelectDataStore(LPCWSTR lpszReg, LPCWSTR lpszApp, BSTR* pbstrRet);
	//
	HMODULE hModule = ::LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return strRet;
	//
	Type_WizKMSelectDataStore* fun = (Type_WizKMSelectDataStore *)::GetProcAddress(hModule, "WizKMSelectDataStore");
	if (!fun)
		return strRet;
	//
	CComBSTR bstrRet;
	fun(CStringW(lpszReg), CStringW(lpszApp), &bstrRet);
	//
	strRet = CString(bstrRet);
	//
	FreeLibrary(hModule);
	//
	return strRet;
}


CString WizKMGetDataStoreSubPath()
{
	CString strProductName = ::WizGetProductName();
	if (0 == strProductName.CompareNoCase(_T("AmazingNote")))
	{
		return CString(_T("AmazingNote Data\\"));
	}
	//
	return CString(_T("My Knowledge\\"));
}

CString WizKMGetDataStorePathFromReg()
{
	{
		CString strPathFromReg = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DataStore"), NULL);
		if (!strPathFromReg.IsEmpty())
			return strPathFromReg;
	}
	//
	{
		CString strPathFromRegOld = WizRegReadStringDef(HKEY_CURRENT_USER, _T("Software\\WizBrother\\Wiz"), _T("DataStore"), NULL);
		if (!strPathFromRegOld.IsEmpty())
		{
			WizRegWriteString(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DataStore"), strPathFromRegOld);
			return strPathFromRegOld;
		}
	}
	//strPathFromReg = WizGetMyDocumentsPath() + g_lpszDataStoreSubPath;
	//if (PathFileExists(strPathFromReg))
	//	return strPathFromReg;
	//
	return CString();
}

BOOL WizKMIsDev()
{
	static BOOL bDev = (WizGetSettings(_T("Common"), _T("DEV"), _T(""))  == _T("1"));
	return bDev;
}

BOOL WizKMIsPortable()
{
	static BOOL bPortable = (WizGetSettings(_T("Common"), _T("Portable"), _T(""))  == _T("1"));
	return bPortable;
}
CString WizKMGetDataStorePathFromApp()
{
	CString strRet;
	//
	BOOL bPortable = WizKMIsPortable();
	if (!bPortable)
		return strRet;
	//
	strRet = WizGetAppPath() + WizKMGetDataStoreSubPath();
	//
	return strRet;
}

CString WizKMGetDataStorePath()
{
	if (WizIsSystem())
	{
		return WizGetAppPath();
	}
	//
	CString strPathFromReg = WizKMGetDataStorePathFromReg();
	CString strPathFromApp = WizKMGetDataStorePathFromApp();
	//
	if (!strPathFromReg.IsEmpty() && !PathFileExists(strPathFromReg))
	{
		strPathFromReg.Empty();
	}
	if (!strPathFromApp.IsEmpty() && !PathFileExists(strPathFromApp))
	{
		strPathFromApp.Empty();
	}
	//
	CString strPath;
	//
	if (!strPathFromReg.IsEmpty()
		&& !strPathFromApp.IsEmpty())
	{
		strPath = WizKMSelectDataStore(strPathFromReg, strPathFromApp); 
	}
	else if (!strPathFromReg.IsEmpty())
	{
		strPath = strPathFromReg;
	}
	else if (!strPathFromApp.IsEmpty())
	{
		strPath = strPathFromApp;
	}
	else
	{
		strPath = WizGetMyDocumentsPath() + WizKMGetDataStoreSubPath();
	}
	//
	WizPathAddBackslash(strPath);
	WizEnsurePathExistsEx(strPath + _T("Data\\"));
	//
	return strPath;
}

BOOL WizKMSetDataStorePath(LPCTSTR lpszPath)
{
	CString strPath(lpszPath);
	//
	WizPathAddBackslash(strPath);
	//
	return WizRegWriteString(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("DataStore"), strPath);
}

CString WizKMGetBackupPath()
{
	CString strPath = WizRegReadStringDef(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("Backup"), NULL);
	if (strPath.IsEmpty())
	{
		strPath = WizKMGetDataStorePath() + _T("Backup\\");
		return strPath;
	}

	//
	WizPathAddBackslash(strPath);
	//
	WizEnsurePathExists(strPath);
	return strPath;
}

BOOL WizKMSetBackupPath(LPCTSTR lpszPath)
{
	CString strPath(lpszPath);
	//
	WizPathAddBackslash(strPath);
	//
	return WizRegWriteString(HKEY_CURRENT_USER, WIZKM_REG_KEY_ROOT, _T("Backup"), strPath);
}


CString WizKMGetSettingsPath()
{
	return WizKMGetDataStorePath();
}

CString WizKMGetSettingsFileTitle()
{
	return WizGetInnerProductName();
}
CString WizKMGetSettingsFileName()
{
	static CString strPath = WizKMGetSettingsPath() + WizKMGetSettingsFileTitle() + _T(".xml");
	return strPath;
}

CString WizKMGetLogFileName()
{
	static CString strFileName = WizKMGetSettingsPath() + WizKMGetSettingsFileTitle() + _T(".log");
	return strFileName;
}


#ifdef _WIZKMSETTINGS_H_

CString WizKMGetSkinPath(LPCTSTR lpszSkinName)
{
	CString strPath = WizGetAppPath() + _T("skins\\") + lpszSkinName + _T("\\");
	return strPath;
}

CString WizKMGetDefaultSkinPath()
{
	static CString strPath = WizKMGetSkinPath(_T("default"));
	return strPath;
}

CString& WizKMGetSkinName()
{
	static CString strSkinName;
	return strSkinName;
}

CString WizKMGetSkinPath()
{
	CString& strSkinName = WizKMGetSkinName();
	if (strSkinName.IsEmpty())
	{
		
		strSkinName = WizKMGetSettings().GetStr(_T("Common"), _T("Skin"));
		if (strSkinName.IsEmpty() 
			|| !PathFileExists(WizKMGetSkinPath(strSkinName)))
			strSkinName = _T("default");
	}
	//
	CString strPath = WizKMGetSkinPath(strSkinName);
	return strPath;
}
CString WizKMGetCurrentSkinName()
{
	CString& strSkinName = WizKMGetSkinName();
	if (strSkinName.IsEmpty())
	{
		
		strSkinName = WizKMGetSettings().GetStr(_T("Common"), _T("Skin"));
		//
		if (strSkinName.IsEmpty() 
			|| !PathFileExists(WizKMGetSkinPath(strSkinName)))
			strSkinName = _T("default");
	}
	//
	return strSkinName;
}

BOOL WizKMSetCurrentSkinName(LPCTSTR lpszSkinName)
{
	CString& strSkinName = WizKMGetSkinName();
	strSkinName = lpszSkinName;
	//
	
	WizKMGetSettings().SetStr(_T("Common"), _T("Skin"), strSkinName, 0);
	//
	return TRUE;
}

CString WizKMGetSkinIniFileName()
{
	return WizKMGetSkinPath() + _T("skin.ini");
}
CString WizKMGetFileNameInSkin(LPCTSTR lpszName)
{
	CString strFileName = WizKMGetSkinPath() + lpszName;
	if (PathFileExists(strFileName))
		return strFileName;
	//
	return WizKMGetDefaultSkinPath() + lpszName;
}
void WizKMGetAllSkins(CWizStdStringArray& arraySkinName)
{
	CWizStdStringArray arrayPath;
	WizEnumFolders( WizGetAppPath() + _T("skins\\"), arrayPath, 0);
	//
	for (CWizStdStringArray::const_iterator it = arrayPath.begin();
		it != arrayPath.end();
		it++)
	{
		CString strPath = *it;
		::WizPathAddBackslash(strPath);
		//
		CString strIniFileName = strPath + _T("skin.ini");
		//
		CWizIniFileEx ini;
		ini.LoadFromFile(strIniFileName);
		//
		CString strSkinName = ::WizExtractPathLastSubDir(strPath);
		CString strDisplayName = ini.GetLocalString(_T("Skin"), _T("Name"), strSkinName);
		if (strDisplayName.IsEmpty())
		{
			strDisplayName = strSkinName;
		}
		//
		//
		arraySkinName.push_back(strSkinName + _T("=") + strDisplayName);
	}
}


HICON WizKMLoadSkinsIcon(LPCTSTR lpszIconFileName, int nWidth /*= 16*/, int nHeight /*= 16*/)
{
	CString strFileName = WizKMGetFileNameInSkin(lpszIconFileName);
	if (!PathFileExists(strFileName))
		return NULL;
	//
	return (HICON)LoadImage(NULL, strFileName, IMAGE_ICON, nWidth, nHeight, LR_LOADFROMFILE);
}

#endif //ifdef _WIZKMSETTINGS_H_

CString WizKMGetShellFileName()
{
	return WizGetAppPath() + _T("Wiz.exe");
}

CString WizKMGetDefaultHtmlEditorFileName()
{
	return WizGetAppPath() + _T("WizHtmlEditor.exe");
}

BOOL WizKMNewDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, LPCTSTR lpszHtmlFileName, BOOL bInitEmptyTitle, LPCTSTR lpszDocumentType)
{
	CString strExeFileName = WizKMGetDefaultHtmlEditorFileName();
	CString strTempPath = WizExtractFilePath(lpszHtmlFileName);
	//
	CString strParams = WizFormatString6(_T("/WizCommandLine=1 /WizKMNewDocument=1 /SaveAsNoChangeFile=1 /NoFileNameInTitle=1 /NoEmptyTitle=1 /NoFileNew=1 /NoFileOpen=1 /DonotAddToRecentList=1 /WizKMDatabasePath=%1 /WizKMDocumentLocation=%2 /WizKMDocumentType=%3 /TempPath=%4 /LogFileName=%5 /FileName=%6"), 
		lpszDatabasePath,
		lpszLocation,
		lpszDocumentType,
		strTempPath, 
		WizKMGetLogFileName(), 
		lpszHtmlFileName);
	//
	if (bInitEmptyTitle)
	{
		strParams = CString(_T("/InitEmptyTitle=1 ")) + strParams;
	}
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	//
	ShellExecute(NULL, _T("open"), strExeFileName, strParams, NULL, SW_SHOW);
	//
	return TRUE;
}


#ifndef WIZKM_NO_DEFAULT_WIZGLOBAL

class CWizKMGlobal: public CWizGlobalDefault
{
public:
	CWizKMGlobal()
		: CWizGlobalDefault(FALSE)
	{
	}
public:
	virtual void WriteLog(LPCTSTR lpszMsg)
	{
		WizWriteLog(WizKMGetLogFileName(), lpszMsg);
	}
};



IWizGlobal* WizGlobal()
{
	static CWizKMGlobal global;
	return &global;
}

#endif


CString WizKMGetAccountsBasePath()
{
	CString strAccountPath = WizKMGetDataStorePath() + _T("Data\\");
	WizEnsurePathExistsEx(strAccountPath);
	return strAccountPath;
}

CWizKMToolsDll::CWizKMToolsDll()
	: CWizToolsDll(WizKMGetLogFileName(), WizKMGetSettingsFileName())
{
#ifdef _WIZKMSETTINGS_H_
	SetSkin(WizKMGetSkinIniFileName());
#endif //ifdef _WIZKMSETTINGS_H_
}

CWizKMToolsDll& WizKMGetToolsDll()
{
	static CWizKMToolsDll dll;
	return dll;
}

#ifdef _WIZUIBASE_H_

CWizSkin* WizGetSkin()
{
	static CWizSkin skin;
	//
	static bool first = true;
	if (first)
	{
		skin.Init(WizKMGetSkinIniFileName());
		first = false;
	}
	//
	return &skin;
}

#endif


#ifdef __WizKMCore_i_h__

CString WizKMServerGetToken(IWizDatabase* pDatabase)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return CString();
	//
	typedef HRESULT WINAPI Type_WizKMGetTokenFromServer(IWizDatabase* pDatabase, BSTR* pbstrToken, BSTR* pbstrErrorMessage);
	//
	HRESULT hr = E_FAIL;
	CString strToken;
	CString strError;
	//
	Type_WizKMGetTokenFromServer* fun = (Type_WizKMGetTokenFromServer *)GetProcAddress(hModule, "WizKMGetTokenFromServer");
	if (fun)
	{
		CComBSTR bstrToken;
		CComBSTR bstrError;
		hr = fun(pDatabase, &bstrToken, &bstrError);
		//
		strToken = CString(bstrToken);
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return CString();
	}
	//
	return strToken;
}



CString WizKMServerGetToken2(BOOL bUseWizServer, LPCWSTR lpszUserName, LPCWSTR lpszPassword)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return CString();
	//
	typedef HRESULT WINAPI Type_WizKMGetTokenFromServer2(BOOL bUseWizServer, LPCWSTR lpszUserName, LPCWSTR lpszPassword, BSTR* pbstrToken, BSTR* pbstrErrorMessage);
	//
	HRESULT hr = E_FAIL;
	CString strToken;
	CString strError;
	//
	Type_WizKMGetTokenFromServer2* fun = (Type_WizKMGetTokenFromServer2 *)GetProcAddress(hModule, "WizKMGetTokenFromServer2");
	if (fun)
	{
		CComBSTR bstrToken;
		CComBSTR bstrError;
		hr = fun(bUseWizServer, lpszUserName, lpszPassword, &bstrToken, &bstrError);
		//
		strToken = CString(bstrToken);
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return CString();
	}
	//
	return strToken;
}



BOOL WizKMServerGetCert(IWizDatabase* pDatabase, CString& strN, CString& stre, CString& strd, CString& strHint, CString& strError)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return FALSE;
	//
	typedef HRESULT WINAPI Type_WizKMGetCertFromServer(IWizDatabase* pDatabase, BSTR* pbstrN, BSTR* pbstre, BSTR* pbstrd, BSTR* pbstrHint, BSTR* pbstrError);
	//
	HRESULT hr = E_FAIL;
	//
	Type_WizKMGetCertFromServer* fun = (Type_WizKMGetCertFromServer *)GetProcAddress(hModule, "WizKMGetCertFromServer");
	if (fun)
	{
		CComBSTR bstrN;
		CComBSTR bstre;
		CComBSTR bstrd;
		CComBSTR bstrHint;
		CComBSTR bstrError;
		hr = fun(pDatabase, &bstrN, &bstre, &bstrd, &bstrHint, &bstrError);
		//
		strN = CString(bstrN);
		stre = CString(bstre);
		strd = CString(bstrd);
		strHint = CString(bstrHint);
		//
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return FALSE;
	}
	//
	return TRUE;
}


BOOL WizKMServerSetCert(IWizDatabase* pDatabase, LPCTSTR lpszN, LPCTSTR lpsze, LPCTSTR lpszd, LPCTSTR lpszHint, CString& strError)
{
	HMODULE hModule = LoadLibrary(WizGetAppPath() + _T("WizKMControls.dll"));
	if (!hModule)
		return FALSE;
	//
	typedef HRESULT WINAPI Type_WizKMSetCertToServer(IWizDatabase* pDatabase, BSTR bstrN, BSTR bstre, BSTR bstrd, BSTR bstrHint, BSTR* pbstrError);
	//
	HRESULT hr = E_FAIL;
	//
	Type_WizKMSetCertToServer* fun = (Type_WizKMSetCertToServer *)GetProcAddress(hModule, "WizKMSetCertToServer");
	if (fun)
	{
		CComBSTR bstrError;
		hr = fun(pDatabase, CComBSTR(lpszN), CComBSTR(lpsze), CComBSTR(lpszd), CComBSTR(lpszHint), &bstrError);
		//
		strError = CString(bstrError);
	}
	//
	FreeLibrary(hModule);
	//
	if (FAILED(hr))
	{
		return FALSE;
	}
	//
	return TRUE;
}



void WizKMWebSiteVisitWithToken(LPCTSTR lpszCommand, IWizDatabase* pDatabase)
{
	return WizKMWebSiteVisitWithToken(lpszCommand, WizKMServerGetToken(pDatabase));
}

CString WizKMWebSiteGetURLWithToken(LPCTSTR lpszCommand, IWizDatabase* pDatabase)
{
	CString strAtt = WizFormatString1(_T("token=%1"), WizKMServerGetToken(pDatabase));
	return WizKMWebSiteGetURL(lpszCommand, WizWebSiteEscapeAtt(strAtt));
}

CString WizKMWebSiteGetURLWithToken(LPCTSTR lpszCommand, LPCTSTR lpszAtt, IWizDatabase* pDatabase)
{
	CString strAtt = WizFormatString2(_T("token=%1&%2"), WizKMServerGetToken(pDatabase), lpszAtt);
	return WizKMWebSiteGetURL(lpszCommand, WizWebSiteEscapeAtt(strAtt));
}

CString WizKMStringToDocumentCustomID(LPCTSTR lpszIDString)
{
	CString str(lpszIDString);
	//
	return WizPasswordToMd5StringNoSpace(str);
}

BOOL WizKMSetDocumentCustomIDByString(IWizDocument* pDocument, LPCTSTR lpszIDString)
{
	return SUCCEEDED(pDocument->put_ParamValue(CComBSTR(g_lpszDocumentCustomIDParamName), CComBSTR(WizKMStringToDocumentCustomID(lpszIDString))));
}
BOOL WizKMSetDocumentCustomIDByID(IWizDocument* pDocument, LPCTSTR lpszCustomID)
{
	return SUCCEEDED(pDocument->put_ParamValue(CComBSTR(g_lpszDocumentCustomIDParamName), CComBSTR(lpszCustomID)));
}
#endif //#ifdef __WizKMCore_i_h__





CString WizKMGetImportFileParams(LPCTSTR lpszDocumentGUID, HWND hwnd, int nID, LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, LPCTSTR lpszTitle, BOOL bExecuteScript, BOOL bURLAsCustomID, UINT nUpdateDocumentFlags, LPCTSTR lpszURL)
{
	CString strParams;
	if (lpszDocumentGUID && *lpszDocumentGUID)
	{
		strParams = WizFormatString6(_T("/Window=%1 /ID=%2 /DatabasePath=%3 /OverwriteDocumentGUID=%4 /UpdateDocumentFlags=%5 /URL=%6 /ExecScript=1"),
			WizInt64ToStr(__int64(hwnd)),
			WizIntToStr(nID),
			lpszDatabasePath,
			lpszDocumentGUID,
			WizIntToStr(nUpdateDocumentFlags),
			lpszURL);
	}
	else
	{
		strParams = WizFormatString9(_T("/Window=%1 /ID=%2 /DatabasePath=%3 /Location=%4 /Title=%5 /ExecScript=%6 /URLAsCustomID=%7 /UpdateDocumentFlags=%8 /URL=%9"),
			WizInt64ToStr(__int64(hwnd)),
			WizIntToStr(nID),
			lpszDatabasePath,
			lpszLocation,
			lpszTitle,
			bExecuteScript ? _T("1") : _T("0"),
			bURLAsCustomID ? _T("1") : _T("0"),
			WizIntToStr(nUpdateDocumentFlags),
			lpszURL);
	}
	//
	return strParams;
}

CString WizKMGetOverwriteDocumentParams(LPCTSTR lpszDocumentGUID, HWND hwnd, int nID, LPCTSTR lpszDatabasePath, UINT nUpdateDocumentFlags, LPCTSTR lpszURL)
{
	return WizKMGetImportFileParams(lpszDocumentGUID, hwnd, nID, lpszDatabasePath, NULL, NULL, TRUE, FALSE, nUpdateDocumentFlags, lpszURL);
}

CString WizKMGetImportDocumentParams(HWND hwnd, int nID, LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, LPCTSTR lpszTitle, BOOL bExecuteScript, BOOL bURLAsCustomID, UINT nUpdateDocumentFlags, LPCTSTR lpszURL)
{
	return WizKMGetImportFileParams(NULL, hwnd, nID, lpszDatabasePath, lpszLocation, lpszTitle, bExecuteScript, bURLAsCustomID, nUpdateDocumentFlags, lpszURL);
}

CString WizKMGetShellImportFileParams(LPCTSTR lpszParams)
{
	CString strDllFileName = WizGetAppPath() + _T("WizKMControls.dll");
	CString strParams = WizFormatString2(_T("\"%1\", WizKMURLDownloadToDocument %2"),
			strDllFileName,
			lpszParams);
#ifdef _DEBUG
	TOLOG(strParams);
#endif
	return strParams;
}

HANDLE WizKMImportFileInShell(LPCTSTR lpszImportFileParams)
{
	CString strShellParams = WizKMGetShellImportFileParams(lpszImportFileParams);
	//
#ifdef _DEBUG
	TOLOG(strShellParams);
#endif
	//
	HANDLE hProcess = WizCreateProcess(WizKMGetShellFileName(), strShellParams);
	if (!hProcess)
	{
		CString strError = WizGetLastErrorMessage();
		TOLOG(strError);
#ifdef _DEBUG
		WizErrorMessageBox(strError);
		//
#endif
		//
		return NULL;
	}
	//
	return hProcess;
}


CString WIZKMCONTROLEVENTSDATA::GetCommandName() const
{
	ATLASSERT(vParam1.vt == VT_BSTR);
	return CString(vParam1.bstrVal);
}

HRESULT STDMETHODCALLTYPE CWizKMControlEventsListenerObject::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppv)
{
	*ppv = NULL;
	if (riid == IID_IUnknown)
		*ppv = (IUnknown *)this;
	else if (riid == IID_IDispatch)
		*ppv = (IDispatch *)this;
	if (*ppv)
	{
		((IUnknown*) *ppv)->AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}
HRESULT STDMETHODCALLTYPE CWizKMControlEventsListenerObject::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) 
{
	if (!m_hWnd)
		return S_OK;
	//
	if (0 == dispIdMember)
	{
		if (4 == pDispParams->cArgs)
		{
			WIZKMCONTROLEVENTSDATA data;
			data.vParam1 = pDispParams->rgvarg[0];
			data.vParam2 = pDispParams->rgvarg[1];
			data.vParam3 = pDispParams->rgvarg[2];
			data.vParam4 = pDispParams->rgvarg[3];
			//
			HRESULT hr = (HRESULT)::SendMessage(m_hWnd, WIZ_UM_CONTROLEVENTS, 0, (LPARAM)&data);
			//
			if (SUCCEEDED(hr) && pVarResult)
			{
				return VariantCopy(pVarResult, &data.vRet);
			}
			//
			return hr;
		}
		return E_INVALIDARG;
	}
	return E_NOTIMPL; 
}
