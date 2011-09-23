#ifndef _WIZKMSETTINGS_H_
#define _WIZKMSETTINGS_H_

#pragma once

class CWizKMSettingsSection
{
public:
	CWizKMSettingsSection();
	CWizKMSettingsSection(IWizSettingsSection* pSection);
	CWizKMSettingsSection(IDispatch* pDisp);
protected:
	CComPtr<IWizSettingsSection> m_spSection;
public:
	BOOL Valid() const;
	CWizKMSettingsSection& operator = (const CWizKMSettingsSection& right);
	CString GetStr(LPCTSTR lpszKey, LPCTSTR lpszDefault = NULL);
	int GetInt(LPCTSTR lpszKey, int nDefault = 0);
	BOOL GetBool(LPCTSTR lpszKey, BOOL bDefault = FALSE);
};


class CWizKMSettings : public IWizSettingsBase
{
private:
	CWizKMSettings();
public:
	virtual ~CWizKMSettings(void);
protected:
	IWizSettings* m_pSettings;
	//
	CString m_strSettingsFileName;
	COleDateTime m_tLast;
protected:
	BOOL Reload();
	BOOL IsDirty();
	void CheckOuterModified();
public:
	//
	virtual BOOL Save();
	virtual BOOL GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue);
	virtual BOOL SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue, UINT nFlags);
	virtual BOOL ClearSection(LPCTSTR lpszSection);
	//
	CWizKMSettingsSection GetSection(LPCTSTR lpszSection);
	BOOL GetSection(LPCTSTR lpszSection, CWizKMSettingsSection& section);
public:
	static CWizKMSettings& GetSettings();
};

class CWizKMSettingsEx : public IWizSettingsBase
{
public:
	virtual BOOL Save();
	//
	virtual BOOL GetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, CString& strValue);
	virtual BOOL SetValue(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpszValue, UINT nFlags);
	virtual BOOL ClearSection(LPCTSTR lpszSection);
	CWizKMSettingsSection GetSection(LPCTSTR lpszSection);
	BOOL GetSection(LPCTSTR lpszSection, CWizKMSettingsSection& section);
};


CWizKMSettings& WizKMGetSettings();



CString WizKMGetDefaultDisplayTemplate();
BOOL WizKMSetDefaultDisplayTemplate(LPCTSTR lpszFileName);
BOOL WizKMGetUsingDisplayTemplate();
BOOL WizKMSetUsingDisplayTemplate(BOOL b);


const LPCTSTR CALENDAR_SECTION = _T("Calendar");

BOOL WizCalendarIsShowWeekNumbers();
BOOL WizCalendarSetShowWeekNumbers(BOOL b);
COleDateTime WizCalendarGetFirstWeek();
BOOL WizCalendarSetFirstWeek(const COleDateTime& t);


const LPCTSTR WIZKM_ACTION_NAME_DOC_DBLCLICKNAME		=	_T("DocumentListCtrl_DblClickItem");
const LPCTSTR WIZKM_ACTION_NAME_DOC_DBLCLICKBLANK		=	_T("DocumentListCtrl_DblClickBlank");
const LPCTSTR WIZKM_ACTION_NAME_DOCVIEW_DBLCLICK		=	_T("DocView_DblClick");

const LPCTSTR WIZKM_ACTION_VALUE_NO_ACTION				=	_T("NoAction");
const LPCTSTR WIZKM_ACTION_VALUE_NEW_DOCUMENT			=	_T("NewDocument");
const LPCTSTR WIZKM_ACTION_VALUE_EDIT_DOCUMENT			=	_T("EditDocument");
const LPCTSTR WIZKM_ACTION_VALUE_FULLSCREEN				=	_T("FullScreen");

CString WizKMGetUserActions(LPCTSTR lpszActionsName, LPCTSTR lpszDefActionValue = NULL);
BOOL WizKMSetUserActions(LPCTSTR lpszActionsName, LPCTSTR lpszActionValue);

BOOL WizKMIsAutoShowAttach();
void WizKMSetAutoShowAttach(BOOL b);


#ifdef _WIZKMDATABASE_H_
enum WizSearchFullText { fulltextNone, fulltextWindows, fulltextGoogle, fulltextInner};

WizSearchFullText WizKMFullTextSearchTypeFromString(const CString& str);
CString WizKMFullTextSearchTypeToString(WizSearchFullText eType);
WizSearchFullText WizKMGetFullTextSearchType(CWizKMDatabase* pDatabase);
BOOL WizKMSetFullTextSearchType(CWizKMDatabase* pDatabase, WizSearchFullText eType);
#endif //_WIZKMDATABASE_H_

const LPCTSTR SECTION_SYNC = _T("Sync");


int GetSyncMinutes();
BOOL SetSyncMinutes(int nMinutes);
BOOL GetSyncEnabled();
BOOL SetSyncEnabled(BOOL b);
BOOL IsSyncShowResult();
BOOL SetSyncShowResult(BOOL b);

BOOL GetSyncHttpsEnabled();
BOOL SetSyncHttpsEnabled(BOOL b);
CString GetCachedSyncURL(LPCTSTR lpszCommand);
BOOL SetCachedSyncURL(LPCTSTR lpszCommand, LPCTSTR lpszURL);


CString WizKMGetLastTagsText(LPCTSTR lpszAttributeName);
void WizKMSetLastTagsText(LPCTSTR lpszAttributeName, LPCTSTR lpszTagsText);
BOOL WizKMGetTagsHistory(CWizStdStringArray& arrayTagsHistory);

BOOL WizKMAddToTagsHistory(LPCTSTR lpszAttributeName, LPCTSTR lpszTagsText);

#ifdef _WIZKMDATABASE_H_
BOOL WizKMGetTagsHistoryWithTagsName(CWizKMDatabase* pDatabase, CWizStdStringArray& arrayTagsHistory);
BOOL WizKMGetRecentPicks(CWizKMDatabase* pDatabase, CWizFolderArray& arrayFolder);
BOOL WizKMGetRecentPicks(CWizStdStringArray& arrayLocation);
BOOL WizKMSetRecentPicks(const CWizStdStringArray& arrayLocation);
BOOL WizKMAppendRecentPicks(LPCTSTR lpszLocation);
BOOL WizKMAppendRecentPicks(IWizFolder* pFolder);

BOOL WizKMGetFavoriteFolders(CWizKMDatabase* pDatabase, CWizFolderArray& arrayFolder);
BOOL WizKMGetFavoriteFolders(CWizStdStringArray& arrayLocation);
BOOL WizKMSetFavoriteFolders(const CWizStdStringArray& arrayLocation);
BOOL WizKMAppendFavoriteFolders(LPCTSTR lpszLocation);
BOOL WizKMAppendFavoriteFolders(IWizFolder* pFolder);
BOOL WizKMRemoveFavoriteFolders(LPCTSTR lpszLocation);
BOOL WizKMRemoveFavoriteFolders(IWizFolder* pFolder);



#endif //_WIZKMDATABASE_H_





struct WIZKMDOCUMENTGUIDANDTITLE
{
	CString strGUID;
	CString strTitle;
};

typedef std::vector<WIZKMDOCUMENTGUIDANDTITLE>	CWizKMDocumentGUIDAndTitleArray;


#ifdef _WIZKMDATABASE_H_

CString WizKMGetRecentDocumentsSettingsSectionName(CWizKMDatabase* pDatabase);
void WizKMGetRecentDocuments(CWizKMDatabase* pDatabase, CWizKMDocumentGUIDAndTitleArray& arrayDocument);
void WizKMSetRecentDocuments(CWizKMDatabase* pDatabase, const CWizKMDocumentGUIDAndTitleArray& arrayDocument);
void WizKMAddRecentDocuments(CWizKMDatabase* pDatabase, LPCTSTR lszDocumentGUID, LPCTSTR lpszDocumentTitle);

#endif //_WIZKMDATABASE_H_

#ifdef _WIZ_USE_HTML
CString WizKMGetDefaultCSSFileName();
BOOL WizKMInsertDefaultCSSToHtml(CString& strHtml);
BOOL WizKMInsertDefaultCSS(LPCTSTR lpszHtmlFileName);
#endif //#ifdef _WIZ_USE_HTML

const LPCTSTR SECTION_EXPLORER = _T("WizExplorer");


CString ExplorerGetDoubleClickAction();
BOOL ExplorerSetDoubleClickAction(LPCTSTR lpszButtonName);
//
BOOL ExplorerIsEditDocumentAsDefault();
BOOL ExplorerSetEditDocumentAsDefault(BOOL b);
//
BOOL ExplorerIsCloseToTray();
BOOL ExplorerSetCloseToTray(BOOL b);

enum WizSaveDestination
{
	wizDestinationMyDrafts,
	wizSelectedFolder,
	wizPromptSelect
};

WizSaveDestination ExplorerGetSaveDestination();
BOOL ExplorerSetSaveDestination(WizSaveDestination dest);


BOOL ExplorerIsEnableGlobalPlugins();
BOOL ExplorerSetEnableGlobalPlugins(BOOL b);
CString ExplorerGetEditorSettings();

const LPCTSTR SECTION_HOTKEY = _T("HotKey2");

const LPCTSTR HOTKEY_NAME_NEWNOTE = _T("NewNote");
const LPCTSTR HOTKEY_NAME_NEWSTICKYNOTE = _T("NewStickyNote");
const LPCTSTR HOTKEY_NAME_CLIPSCREEN = _T("ClipScreen");
const LPCTSTR HOTKEY_NAME_COPYCLIPBOARD = _T("CopySelection");
const LPCTSTR HOTKEY_NAME_PASTECLIPBOARD = _T("PasteClipboard");
const LPCTSTR HOTKEY_NAME_TRAY= _T("Tray");
const LPCTSTR HOTKEY_NAME_DISPLAY_NOTES = _T("DisplayNotes");


const LPCTSTR HOTKEY_DEFAULT_NEWNOTE = _T("Ctrl+Alt+N");
const LPCTSTR HOTKEY_DEFAULT_NEWSTICKYNOTE = _T("Ctrl+Alt+D");
const LPCTSTR HOTKEY_DEFAULT_CLIPSCREEN = _T("Win+PrintScreen");
const LPCTSTR HOTKEY_DEFAULT_COPYSELECTION = _T("Win+S");
const LPCTSTR HOTKEY_DEFAULT_PASTECLIPBOARD = _T("Ctrl+Alt+V");
const LPCTSTR HOTKEY_DEFAULT_TRAY= _T("Ctrl+Alt+M");
const LPCTSTR HOTKEY_DEFAULT_DISPLAY_NOTE = _T("Ctrl+F2");

BOOL IsCategoryTreeCtrlIncludeSubFolders();
void SetCategoryTreeCtrlIncludeSubFolders(BOOL b);
//
BOOL ExplorerIsShowStatusBar(CWizKMSettings& settings);
BOOL ExplorerSetShowStatusBar(CWizKMSettings& settings, BOOL b);

BOOL ExplorerIsShowVirtualFolder();
BOOL ExplorerSetShowVirtualFolder(BOOL b);
BOOL ExplorerIsShowStatusBar();
BOOL ExplorerSetShowStatusBar(BOOL b);
CString WizKMGetDestinationParam(LPCTSTR lpszSelectedLocation);

int WizKMCopySelection(HWND hwndOwnerWindow, HWND hwndForegroundWindow, HWND hwndLastIEWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation);
int WizKMClipScreenshot(HWND hwndOwnerWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation);
int WizKMPasteToWiz(HWND hwndOwnerWindow, LPCTSTR lpszDatabasePath, LPCTSTR lpszSelectedLocation);


struct WIZKMIMPORTFILESDATA
{
	CString strDatabasePath;
	CString strLocation;
	CWizStdStringArray arrayFile;
	UINT nUpdateDocumentFlags;
	BOOL bDelete;
	//
	WIZKMIMPORTFILESDATA()
	{
		bDelete = FALSE;
		nUpdateDocumentFlags = 0;
	}
};


BOOL WizKMImportFilesDataLoadFromFile(LPCTSTR lpszFileName, WIZKMIMPORTFILESDATA& data);
BOOL WizKMImportFilesDataSaveToFile(LPCTSTR lpszFileName, const WIZKMIMPORTFILESDATA& data);

BOOL WizKMImportFiles(LPCTSTR lpszFileName);
BOOL WizKMImportFiles(LPCTSTR lpszDatabasePath, LPCTSTR lpszLocation, UINT nUpdateDocumentFlags, const CWizStdStringArray& arrayFile);

const LPCTSTR WIZKM_DATABASE_WINDOW_EXPLORER = _T("Explorer");
const LPCTSTR WIZKM_DATABASE_WINDOW_SYNC_DETAILS = _T("SyncDetails");
const LPCTSTR WIZKM_DATABASE_WINDOW_NOTE = _T("Note");
const LPCTSTR WIZKM_DATABASE_WINDOW_TODO = _T("Todo");

const LPCTSTR WIZKM_DATABASE_WINDOW_DATABASE_PARH = _T("DatabasePath");
const LPCTSTR WIZKM_DATABASE_WINDOW_STOP_SYNC = _T("StopSync");


class CWizKMDatabaseWindow
{
public:
	CWizKMDatabaseWindow();
	~ CWizKMDatabaseWindow();
private:
	HWND m_hWnd;
	CString m_strDatabasePath;
	CString m_strType;
public:
	CString GetDatabasePath() const;
	static CString RegularDatabasePath(LPCTSTR lpszDatabasePath);
	static CString GetKeyPathOfDatabase(LPCTSTR lpszDatabasePath);
	static HWND GetWindowOfDatabase(LPCTSTR lpszDatabasePath, LPCTSTR lpszType);
	static BOOL GetAllWindowsOfDatabase(LPCTSTR lpszDatabasePath, std::vector<HWND>& arrayHwnd);
	static BOOL QueryStopStatus(LPCTSTR lpszDatabasePath);
	static BOOL SetStopStatus(LPCTSTR lpszDatabasePath, BOOL b);
public:
	BOOL Register(LPCTSTR lpszDatabasePath, HWND hWnd, LPCTSTR lpszType);
	BOOL Unregister();
	void ShowSyncWindow();
	void StopSync();
};


struct WIZKMEDITORDATA
{
	CString strName;
	CString strFileName;
	CString strParams;
	BOOL bTextEditor;
	BOOL bUTF8Encoding;
	//
	WIZKMEDITORDATA()
		: bTextEditor(FALSE)
		, bUTF8Encoding(FALSE)
	{
	}
};

typedef std::vector<WIZKMEDITORDATA> CWizKMEditorDataArray;

const LPCTSTR SECTION_EDITOR = _T("Editor");

CString WizKMGetWizHtmlEditorName();

BOOL WizKMIsWizHtmlEditor(const WIZKMEDITORDATA& data);
WIZKMEDITORDATA WizKMGetWizHtmlEditor();
BOOL WizKMIsWizHtmlEditorInstalled();

intptr_t WizKMEditorArrayIndexOfFileName(const CWizKMEditorDataArray& arrayEditor, LPCTSTR lpszFileName);
intptr_t WizKMEditorArrayIndexOfName(const CWizKMEditorDataArray& arrayEditor, LPCTSTR lpszName);
BOOL WizKMGetEditor(CWizKMEditorDataArray& arrayEditor);
BOOL WizKMSetEditor(const CWizKMEditorDataArray& arrayEditor);
WIZKMEDITORDATA WizKMGetDefaultEditor();
CString WizKMGetDefaultEditorName();
BOOL WizKMSetDefaultEditorName(LPCTSTR lpszName);

BOOL WizKMIsPromptSave();
BOOL WizKMSetPromptSave(BOOL b);

int WizKMGetAutoSaveMinutes();
BOOL WizKMSetAutoSaveMinutes(int nMinutes);



BOOL WizKMIsAutoSave();
BOOL WizKMSetAutoSave(BOOL b);

const LPCTSTR WIZKM_FOLDER_SETTINGS_SECTION_SORT	=	_T("Sort");
const LPCTSTR WIZKM_FOLDER_SETTINGS_KEY_SORT_ORDER	=	_T("SortOrder");
const LPCTSTR WIZKM_FOLDER_SETTINGS_KEY_SORT_BY		=	_T("SortBy");




BOOL WizKMUsingOleDisplayDocument();
BOOL WizKMSetUsingOleDisplayDocument(BOOL b);

BOOL WizKMIsEditNoteWithHtmlEditor();
BOOL WizKMSetEditNoteWithHtmlEditor(BOOL b);


CString WizKMGetLastUserName();
void WizKMSetLastUserName(LPCTSTR lpszUserName);


#ifdef __WizKMControls_i_h__
#ifdef _WIZKMDATABASE_H_

CString WizKMGetDocumentFileType(IWizDocument* pDocument);
CString WizKMGetAttachmentFileType(IWizDocumentAttachment* pAttachment);
CComPtr<IWizDocumentAttachment> WizKMGetAttachmentOfDocument(IWizDocument* pDocument);
//
BOOL WizKMDocumentSupportOle(LPCTSTR lpszDocumentFileType);
CComPtr<IWizDocumentAttachment> WizKMGetAttachmentOfDocumentForOleViewing(IWizDocument* pDocument, BOOL bCheckOleConfig = TRUE);



BOOL WizKMEditDocumentEx(CWizKMDatabase* pDatabase, IWizDocument* pDocument, BOOL bEditDocument);
BOOL WizKMEditDocumentEx(IWizDocument* pDocument, BOOL bEditDocument);
BOOL WizKMEditDocumentEx(IWizDocument* pDocument);
BOOL WizKMViewDocumentEx(IWizDocument* pDocument);
BOOL WizKMTrackDocument(LPCTSTR lpszDatabasePath, LPCTSTR lpszDocumentGUID, LPCTSTR lpszDocumentHtmlFileName, HANDLE hProcess, BOOL bDeleteFiles, BOOL bTextFile, BOOL bUTF8);
BOOL WizKMExternalEditorEditDocument(const WIZKMEDITORDATA& data, IWizDocument* pDocument);
#endif //_WIZKMDATABASE_H_
#endif	//__WizKMControls_i_h__


BOOL WizKMIsSingleApp();
BOOL WizKMSetSingleApp(BOOL b);




const LPCTSTR SECTION_GLOBALS = _T("Globals");

BOOL IsUseGUIDAsDocumentFileName();
BOOL SetUseGUIDAsDocumentFileName(BOOL b);



BOOL WizKMConvertFileIsConvertToHtml();

BOOL WizKMConvertFileIsUsingOffice();
BOOL WizKMConvertFileSetConvertToHtml(BOOL b);
BOOL WizKMConvertFileSetUsingOffice(BOOL b);

BOOL WizKMConvertFileNeedToBeAddedToAttachment(LPCTSTR lpszExt);
BOOL WizKMConvertFileToHtml(CWizKMToolsDll& dll, LPCTSTR lpszSrcFileName, CString& strHtmlFileName);
BOOL WizKMConvertFileToHtml(LPCTSTR lpszSrcFileName, CString& strHtmlFileName);
BOOL WizKMTrackAttachment(IWizDocumentAttachment* pAttachment, HANDLE hProcess);


#ifdef __ATLCTRLX_H__
#ifdef _WIZ_USE_HTML
const LPCTSTR g_lpszCombineDocumentsSection = _T("CombineDocuments");

BOOL WizCombineHtmlText(CString& strTextTo, LPCTSTR lpszTextFrom);
BOOL WizKMCombineDocumentsToHtmlFile(const CWizDocumentArray& arrayDocument, LPCTSTR lpszHtmlSplitter, CString& strHtmlFileName);
BOOL WizKMCombineDocuments(const CWizDocumentArray& arrayDocument, LPCTSTR lpszHtmlSplitter, LPCTSTR lpszTitle, BOOL bDelete);

void WizKMGetCombineDocumentSettings(BOOL& bInsertSplitterHtml, CString& strSplitterHtml, BOOL& bDeleteDocuments);
void WizKMSetCombineDocumentSettings(BOOL bInsertSplitterHtml, LPCTSTR lpszSplitterHtml, BOOL bDeleteDocuments);
BOOL WizKMCombineDocuments(IWizDocument* pDocOld, IWizDocument* pDocNew);
#endif //#ifdef _WIZ_USE_HTML
#endif	//__ATLCTRLX_H__

#endif //_WIZKMSETTINGS_H_

