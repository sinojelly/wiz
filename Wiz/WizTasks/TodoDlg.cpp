#include "StdAfx.h"
#include "TodoDlg.h"
#include "MainDlg.h"

#include "TodoSettings.h"

#include "../Globals/WizKMCalendarEvents.h"

#define TIMER_ID_SAVE		101

CTodoDlg::CTodoDlg(CWizKMDatabase* pDatabase, LPCTSTR lpszInitTitle)
	: m_pDatabase(pDatabase)
	, m_wndList(pDatabase)
	, m_strInitTitle(lpszInitTitle)
{
	ATLASSERT(m_pDatabase);
	//
	m_crBackground = RGB(0xCB, 0xFE, 0xC5);
	m_crBackground = WizHTMLStringColorToColor(WizKMGetPrivateString(_T("Todo"), _T("DefaultBackgroundColor"), WizHTMLColorToStringColor(m_crBackground)));
	//
	m_nMenuID = IDR_MENU_TODO;
}

CTodoDlg::~CTodoDlg()
{
}

LRESULT CTodoDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	//
	m_btnNew.Create(m_hWnd, NULL, NULL, 0, 0, IDC_BUTTON_NEW);
	m_wndList.Create(m_hWnd, NULL, NULL, 0, 0, IDC_TREE_TODO);
	m_wndList.SetTodoDlg(this);

	WizTranslationsTranslateWindow(m_hWnd);
	//
	InitClient();
	//
	m_btnNew.SetIcon(IDI_ICON_NEW_BUTTON);
	m_btnMenu.SetIcon(IDI_ICON_MENU_BUTTON);
	m_btnClose.SetIcon(IDI_ICON_CLOSE_BUTTON);
	//
	//ModifyStyleEx(0, WS_EX_LAYERED, 0);
	//
	SetTimer(TIMER_ID_SAVE, 1000 * 10, NULL);
	//
	RandomPosition();
	//
	WizKMObjectMessageRegisterReceiver(objecttypeDocument, m_hWnd);
	//
	SetColor(m_crBackground);
	UpdateLayout();
	UpdateLockButtonIcon();
	//
	m_bInfoModified = FALSE;
	//
	return 1;  // Let the system set the focus
}

LRESULT CTodoDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WizKMObjectMessageUnregisterReceiver(objecttypeDocument, m_hWnd);

	return 0;
}

CRect CTodoDlg::GetTitleRect()
{
	CRect rcNew;
	if (m_btnNew.IsWindow())
	{
		m_btnNew.GetWindowRect(&rcNew);
		ScreenToClient(&rcNew);
	}
	CRect rcMenu;
	if (m_btnMenu.IsWindow())
	{
		m_btnMenu.GetWindowRect(&rcMenu);
		ScreenToClient(&rcMenu);
	}
	//
	CRect rcTitle(rcNew.right + 8, rcNew.top, rcMenu.left - 8, rcMenu.bottom);
	return rcTitle;
}

CString CTodoDlg::GetTitle()
{
	if (m_spDocument)
	{
		CString title = CWizKMDatabase::GetDocumentTitle(m_spDocument);
		bool isDefault = CWizKMDatabase::GetDocumentParam(m_spDocument, _T("DefaultTodoList")) == _T("1") ? true : false;
		if (isDefault)
		{
			title += WizFormatString0(IDS_DEFAULT_TODOLIST);
		}

		return title;
	}
	else
	{
		if (m_strInitTitle.IsEmpty())
		{
			m_strInitTitle = WizFormatString0(IDS_NEW_TODOLIST_TITLE);
		}
		return m_strInitTitle;
	}
}

void CTodoDlg::SetColor(COLORREF cr)
{
	CWizKMSmallDlgBase::SetColor(cr);
	//
	COLORREF crTitle = GetTitleBackgroundColor();
	//
	m_btnNew.SetBackgroundColor(crTitle);
	//
	m_wndList.SetBackgroundColor(m_crBackground);
}


LRESULT CTodoDlg::OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	switch ((UINT)wParam)
	{
	case TIMER_ID_SAVE:
		AutoSave();
		break;
	}
	//
	return 0;
}

BOOL CTodoDlg::OnModifyDocument(LPCTSTR lpszGUID)
{
	if (!m_spDocument)
		return FALSE;
	//
	if (0 != CWizKMDatabase::GetObjectGUID(m_spDocument.p).CompareNoCase(lpszGUID))
		return FALSE;
	//
	////避免保存的时候，消息重入，导致死循环////
	if (IsModified())
		return FALSE;
	//
	Refresh();
	//
	return TRUE;
}

void CTodoDlg::InitClient()
{
	CWizKMSmallDlgBase::InitClient();
	//
	m_wndContainer.SetClient(m_wndList);
	//
	UpdateLayout();
}

void CTodoDlg::UpdateLayout()
{
	CWizKMSmallDlgBase::UpdateLayout();
	//
	CRect rc;
	GetClientRect(&rc);
	//
	CRect rcNew = CRect(8, 5, 26, 23);
	//
	if (m_btnNew.IsWindow())
	{
		m_btnNew.SetWindowPos(NULL, rcNew, SWP_NOZORDER | SWP_NOACTIVATE);
	}
}


void CTodoDlg::Close()
{
	CWizKMSmallDlgBase<CTodoDlg>::Close();
	//
	WizGetMainDlg()->PostMessage(UM_SAVE_TODOLISTS_STATUS, 0, 0);
}


BOOL CTodoDlg::SavePos()
{
	if (!m_spDocument)
		return FALSE;
	if (!IsWindow())
		return FALSE;
	if (!m_pDatabase)
		return FALSE;
	//
	CRect rc;
	GetWindowRect(&rc);
	//
	CWizKMDocumentParamLine line;
	line.AddInt(_T("l"), rc.left);
	line.AddInt(_T("t"), rc.top);
	line.AddInt(_T("r"), rc.right);
	line.AddInt(_T("b"), rc.bottom);
	//
	return m_pDatabase->SetMeta(_T("TodoPos"), CWizKMDatabase::GetObjectGUID(m_spDocument.p), line.GetLine());
}

BOOL CTodoDlg::SaveParam()
{
	if (!m_spDocument)
		return FALSE;
	//
	CWaitCursor wait;
	//
	CWizKMDocumentParamLine line;
	line.AddColor(_T("c"), m_crBackground);
	line.AddInt(_T("ts"), m_nTransparentPercent);
	line.AddInt(_T("lk"), GetDlgState());
	line.AddInt(_T("mh"), m_nNormalHeight);
	//
	CWizKMDatabase::SetDocumentParam(m_spDocument, _T("Todo"), line.GetLine());
	//
	m_bInfoModified = FALSE;
	//
	return TRUE;
}


BOOL CTodoDlg::LoadPos()
{
	if (!IsWindow())
		return FALSE;
	//
	if (!m_spDocument)
		return FALSE;
	//
	if (!m_pDatabase)
		return FALSE;
	//
	CWizKMDocumentParamLine line(m_pDatabase->GetMeta(_T("TodoPos"), CWizKMDatabase::GetObjectGUID(m_spDocument.p)));
	//
	CRect rc;
	GetWindowRect(&rc);
	//
	rc.left = line.GetInt(_T("l"), rc.left);
	rc.top = line.GetInt(_T("t"), rc.top);
	rc.right = line.GetInt(_T("r"), rc.right);
	rc.bottom = line.GetInt(_T("b"), rc.bottom);
	//
	if (rc.right < 0
		|| rc.bottom < 0
		|| rc.left >= ::GetSystemMetrics(SM_CXSCREEN)
		|| rc.top >= ::GetSystemMetrics(SM_CYSCREEN)
		|| rc.Width() < 5
		|| rc.Height() < 5)
	{
		RandomPosition();
		return TRUE;
	}
	//
	SetWindowPos(NULL, rc, SWP_NOZORDER | SWP_NOACTIVATE);
	//
	return TRUE;
}
//
BOOL CTodoDlg::LoadParam()
{
	if (!IsWindow())
		return FALSE;
	//
	if (!m_spDocument)
		return FALSE;
	//
	//
	LoadPos();
	//
	CWizKMDocumentParamLine line;
	CWizKMDatabase::GetDocumentParamLine(m_spDocument, _T("Todo"), line);
	//
	COLORREF cr = line.GetColor(_T("c"), m_crBackground);
	int nTransparent = line.GetInt(_T("ts"), m_nTransparentPercent);
	m_nNormalHeight = line.GetInt(_T("mh"), m_nNormalHeight);
	int nState = line.GetInt(_T("lk"), FALSE);
	//
	SetDlgState((WIZSMALLDLGSTATE)nState);
	SetColor(cr);
	SetTransparentPercent(nTransparent);
	//
	m_bInfoModified = FALSE;
	//
	UpdateUpDownButtons();
	//
	Invalidate();
	//
	return TRUE;
}

BOOL CTodoDlg::Load()
{
	return LoadData() && LoadParam();
}


BOOL CTodoDlg::SaveData()
{
	CWaitCursor wait;
	//
	if (!m_spDocument)
	{
		if (!CreateDocument() || !m_spDocument)
		{
			TOLOG(_T("Failed to create todolist2 document!"));
			return FALSE;
		}
	}
	//
	CComPtr<IWizTodoItemCollection> spColl = m_wndList.GetAllData();
	if (!spColl)
	{
		TOLOG(_T("Failed to get todo item data!"));
		return FALSE;
	}
	//
	HRESULT hr = m_spDocument->put_TodoItems(spColl);
	if (FAILED(hr))
	{
		TOLOG(_T("Failed to update document!"));
		return FALSE;
	}
	//
	m_wndList.SetModified(FALSE);
	//
	return TRUE;
}

BOOL CTodoDlg::AutoSave()
{
	if (m_wndList.GetModify())
	{
		if (!SaveData())
			return FALSE;
	}
	//
	if (m_bInfoModified)
	{
		if (!SaveParam())
			return FALSE;
	}
	//
	Invalidate();
	//
	return TRUE;
}

void CTodoDlg::UpdateLockButtonIcon()
{
	UINT nIcon = IDI_ICON_UNLOCK_BUTTON;
	switch (GetDlgState())
	{
	case stateTopMost:
		nIcon = IDI_ICON_LOCK_BUTTON;
		break;
	case statePinDesk:
		nIcon = IDI_ICON_PIN_DESK_BUTTON;
		break;
	};
	//
	m_btnLock.SetIcon(nIcon);
}


BOOL CTodoDlg::CreateDocument()
{
	if (m_spDocument)
		return TRUE;
	//
	m_spDocument = WizKMCreateTodo2Document(m_pDatabase, WizKMTodoGetInboxLocation(), GetTitle());
	if (!m_spDocument)
	{
		TOLOG(_T("Failed to create todolist2 document!"));
		return FALSE;
	}
	//
	SavePos();
	WizGetMainDlg()->PostMessage(UM_SAVE_TODOLISTS_STATUS, 0, 0);
	//
	return TRUE;
}

BOOL CTodoDlg::SetDocument(IWizDocument* pDocument)
{
	ATLASSERT(!m_spDocument);
	//
	m_spDocument = pDocument;
	//
	////SetDocument只会调用一次，Load回调用多次（例如刷新），因此收集操作放在这里，每次启动程序的时候收集////
	MoveCompletedTodoItems();
    //  
	BOOL bRet = Load();
	//
	m_bIniting = FALSE;
	//
	return bRet;
}


LRESULT CTodoDlg::OnBnClickedButtonNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	//
	WizGetMainDlg()->PostMessage(WM_COMMAND, MAKEWPARAM(ID_TRAY_NEW_TODOLIST, 0), 0);
	//
	return 0;
}

BOOL CTodoDlg::IsModified() const 
{
	if (!m_wndList.IsWindow())
		return FALSE; 
	//
	return m_wndList.GetModify() || m_bInfoModified;
}
//

void CTodoDlg::Refresh()
{
	AutoSave();
	//
	Load();
}

bool hasCompletedItem(IWizDocument *document)
{
	WIZTODODATAEX::CWizTodoDataExArray items;
	WizDocumentGetTodoData(document, items);

	std::vector<WIZTODODATAEX>::iterator it = items.begin();
	for (; it != items.end(); ++it)
	{
		if ((*it).eState == todoState100)
			return true;
	}

	return false;
}

void CTodoDlg::MoveCompletedTodoItems()
{
	////不要收集已完成的任务列表////
	if (WizKMIsCompletedTodoList(m_spDocument))
		return;
	//
	if (!hasCompletedItem(m_spDocument))
	{
		return;
	}

    CComQIPtr<IWizDocument> spCompleted;
    CWizDocumentArray arrayDocument;

    CString title; 
    COleDateTime tNow = COleDateTime::GetCurrentTime();
	CString monthString;
	monthString.Format(_T("%4d%02d"), tNow.GetYear(), tNow.GetMonth());
    title.Format(_T("%s%s"), WizFormatString0(IDS_TASKS), monthString);

    CString sql;
    sql.Format(_T("DOCUMENT_TITLE='%s'"), title);
    
    HRESULT hr = m_pDatabase->GetDocumentsBySQL(CComBSTR(sql), arrayDocument);
    if (FAILED(hr) || arrayDocument.empty())
    {
        spCompleted = WizKMCreateTodo2Document(m_pDatabase, WizKMTodoGetCompletedLocation(), CComBSTR(title));
		ATLASSERT(spCompleted);
		if (!spCompleted)
			return;
		//
		
		////需要设置为已完成的任务列表////
		//
		WizKMSetCompletedTodoList(spCompleted, TRUE);
		//
		//CWizKMDatabase::SetDocumentParam(pCompleted, "TasksCompleted", monthString);  
		// jelly: 先不用这种方案。用户如果改名，估计希望后续任务不再存储到该列表。
		// DOCUMENT_GUID in (select DOCUMENT_GUID from WIZ_DOCUMENT_PARAM where PARAM_NAME='TASKSCOMPLETED' and PARAM_VALUE='201108')
    }
    else
    {
        spCompleted = arrayDocument[0];
    }
	//
    m_pDatabase->GetDatabase()->MoveCompletedTodoItems(m_spDocument, spCompleted);
}

BOOL CTodoDlg::LoadData()
{
	if (!IsWindow())
		return FALSE;
	//
	{
		CWizTreeCtrlStateLocker<CWizTodoTreeCtrl> locker(m_wndList);
		//
		m_wndList.DeleteAllItems();

		//
		SetWindowText(GetTitle());
		
		//
		WIZTODODATAEX::CWizTodoDataExArray arrayData;
		//
		if (m_spDocument)
		{
			WizDocumentGetTodoData(m_spDocument, arrayData);
		}

		bool isDefault = CWizKMDatabase::GetDocumentParam(m_spDocument, _T("DefaultTodoList")) == _T("1") ? true : false;
		if (isDefault)
		{
			COleDateTime tNow = COleDateTime::GetCurrentTime();
			WizKMCalendarEventsAddToTodoData(m_pDatabase, tNow, arrayData);
		}

		//
		m_wndList.SetAllData(arrayData);
		//
		Invalidate();
		//
		m_wndList.GetBlankTodoItem(NULL, TRUE);
		m_wndList.SetModified(FALSE);
	}
	//
	m_wndList.ExpandAllItemsWithChildren(NULL, TVE_EXPAND);
	//
	UpdateUpDownButtons();
	//
	return TRUE;
}


LRESULT CTodoDlg::OnTodoChangetitle(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	CString strTitle;
	if (!WizKMInputBox(IDS_CHANGE_TODOLIST_TITLE, IDS_TODOLIST_TITLE_DESCRIPTION, CWizKMDatabase::GetDocumentTitle(m_spDocument), strTitle))
		return 0;
	//
	m_strInitTitle = strTitle;
	//
	if (m_spDocument)
	{
		m_spDocument->ChangeTitleAndFileName(CComBSTR(strTitle));
	}
	//
	Invalidate();

	return 0;
}

LRESULT CTodoDlg::OnTodoSetDefault(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	const CComBSTR defaultParamName = _T("DefaultTodoList");

	if (!m_spDocument)
	{
		SaveData();
	}

	CWizDocumentArray arrayTodoList;
	WizKMGetTodo2Documents(m_pDatabase, WizKMTodoGetInboxLocation(), arrayTodoList);

	for (CWizDocumentArray::const_iterator it = arrayTodoList.begin();
		it != arrayTodoList.end() ;
		it++)
	{
		CComPtr<IWizDocument> spDocument = *it;

		CComBSTR defaultValue;
		defaultValue = CWizKMDatabase::GetDocumentParam(*it, defaultParamName);

		if (defaultValue == _T("1"))
		{
			CWizKMDatabase::SetDocumentParam(*it, defaultParamName, _T("0"));
			// TODO: 1. 如何删除Param?  2. 如何更新它对应的窗口标题？
		}
	}

	CWizKMDatabase::SetDocumentParam(m_spDocument, defaultParamName, _T("1"));

	return 0;
}

void CTodoDlg::InitNewTodoList()
{
	m_wndList.GetBlankTodoItem(NULL, TRUE);
	m_wndList.SetModified(FALSE);
}



LRESULT CTodoDlg::OnNotifyParentCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LPCTSTR lpszCommand = (LPCTSTR)wParam;
	try
	{
		if (lpszCommand)
		{
			if (0 == _tcsicmp(lpszCommand, _T("OnItemCheckStateChanged")))
			{
				WIZTODODATA* pData = (WIZTODODATA *)lParam;
				if (pData
					&& pData->eState == todoState100)
				{
					CComPtr<IWizEvent> spEvent = GetTodoEvent(pData);
					if (spEvent)
					{
						if (WizKMGetPrivateBool(_T("Event"), _T("CompleteEventWhileTodoCompleted"), TRUE))
						{
							WizKMEventSetCompleted(spEvent);
							//
							//WizGetMainDlg()->PostMessage(UM_REFRESH_TODO_LIST, 0, 0);
						}
					}
				}
			}
		}
	}
	catch (...)
	{
	}
	return 0;
}


CComPtr<IWizEvent> CTodoDlg::GetTodoEvent(WIZTODODATA* pData)
{
	if (!pData)
		return NULL;
	//
	if (pData->arrayLinkedDocumentGUID.size() != 1)
		return NULL;
	//
	CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(pData->arrayLinkedDocumentGUID[0]);
	if (!spDocument)
		return NULL;
	CString strType = CWizKMDatabase::GetDocumentType(spDocument);
	if (0 != strType.CompareNoCase(_T("event")))
		return NULL;
	CComPtr<IDispatch> spEventDisp;
	spDocument->get_Event(&spEventDisp);
	CComQIPtr<IWizEvent> spEvent(spEventDisp);
	if (!spEvent)
		return NULL;
	//
	CComBSTR bstrRecurrence;
	spEvent->get_Recurrence(&bstrRecurrence);
	CString strRecurrence(bstrRecurrence);
	if (!strRecurrence.IsEmpty())
	{
		COleDateTime tDate = WizGetCurrentTime();

		CString strRecurrenceIndex;
		strRecurrenceIndex.Format(_T("%04d%02d%02d"),
			tDate.GetYear(),
			tDate.GetMonth(),
			tDate.GetDay());

		spEvent->put_RecurrenceIndex(CComBSTR(strRecurrenceIndex));
	}
	//
	return spEvent;
}
//