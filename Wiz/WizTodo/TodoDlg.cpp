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
		return CWizKMDatabase::GetDocumentTitle(m_spDocument);
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
	/*
	case statePinDesk:
		nIcon = IDI_ICON_PIN_DESK_BUTTON;
		break;
		*/
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
	if (!hasCompletedItem(m_spDocument))
	{
		return;
	}

    CComQIPtr<IWizDocument> pCompleted;
    CWizDocumentArray arrayDocument;

    CString title; 
    COleDateTime tNow = COleDateTime::GetCurrentTime();
    title.Format(L"Tasks%4d%02d", tNow.GetYear(), tNow.GetMonth());

    CString sql;
    sql.Format(L"DOCUMENT_TITLE='%s'", title);
    
    HRESULT hr = m_pDatabase->GetDocumentsBySQL(CComBSTR(sql), arrayDocument);
    if (FAILED(hr) || arrayDocument.empty())
    {
        pCompleted = WizKMCreateTodo2Document(m_pDatabase, WizKMTodoGetCompletedLocation(), CComBSTR(title));
    }
    else
    {
        pCompleted = arrayDocument[0];
    }
    m_pDatabase->GetDatabase()->MoveCompletedTodoItems(m_spDocument, pCompleted);
}

BOOL CTodoDlg::LoadData()
{
	if (!IsWindow())
		return FALSE;
	//
	{
		CWizTreeCtrlStateLocker<CWizTodoTreeCtrl> locker(m_wndList);

        //        
		MoveCompletedTodoItems();
        
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
	if (!WizKMInputBox(IDS_CHANGE_TODOLIST_TITLE, IDS_TODOLIST_TITLE_DESCRIPTION, GetTitle(), strTitle))
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

void CTodoDlg::InitNewTodoList()
{
	m_wndList.GetBlankTodoItem(NULL, TRUE);
	m_wndList.SetModified(FALSE);
}
