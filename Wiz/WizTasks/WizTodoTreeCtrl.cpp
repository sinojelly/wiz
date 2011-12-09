#include "stdafx.h"
#include "resource.h"       // main symbols

#include <atlhost.h>

#include "../Globals/WizKMSmallDlgBase.h"

#include "../Globals/WizKMObjectMessage.h"

#include "WizTodoTreeCtrl.h"
#include "TodoDlg.h"

#include "MainDlg.h"

void CWizTodoTreeCtrl::UpdateMoveToMenu( WIZTODOSTATE state, CMenuHandle &menu ) 
{
	const int MOVE_TO_MENU_POS = 2;
	if (m_bMoveToMenuExist)
	{
		menu.RemoveMenu(MOVE_TO_MENU_POS, MF_BYPOSITION | MF_STRING);
	}
	m_bMoveToMenuExist = true;

	CMenuHandle moveToMenu; 
	moveToMenu.CreatePopupMenu(); 

	m_mapDocumentMenuID.clear();

	CString location = (state == todoState100) ? WizKMTodoGetCompletedLocation() : WizKMTodoGetInboxLocation();

	UINT flag = MF_BYPOSITION | MF_STRING;
	CWizDocumentArray arrayTodoList;
	WizKMGetTodo2Documents(m_pDatabase, location, arrayTodoList);
	if (!arrayTodoList.empty())
	{
		//
		CComPtr<IWizDocument> spDlgDocument = m_pTodoDlg->GetDocument();

		UINT index = 0;
		if (spDlgDocument != NULL)
		{
			for (CWizDocumentArray::const_iterator it = arrayTodoList.begin();
				it != arrayTodoList.end() && index < 20;
				it++)
			{
				CComPtr<IWizDocument> spDocument = *it;

				CString strGUID1 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDocument);
				CString strGUID2 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDlgDocument);

				if (strGUID1 == strGUID2)
				{
					continue;
				}

				CString strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
				UINT nID = ID_TODO_LIST_BEGIN + index;
				moveToMenu.InsertMenu(index, MF_BYPOSITION | MF_STRING, nID,  strTitle);
				//
				index++;
				//
				m_mapDocumentMenuID[nID] = spDocument;
			}
		}

		if (index <= 0)
		{
			flag |= MF_DISABLED | MF_GRAYED;
		}
	}
	
	menu.InsertMenu(MOVE_TO_MENU_POS, flag, (HMENU)moveToMenu,  WizFormatString0(IDS_MOVE_TO));
}

LRESULT CWizTodoTreeCtrl::OnMoveTodoItem(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CDocumentMenuIDMap::const_iterator it = m_mapDocumentMenuID.find(wID);
	if (it == m_mapDocumentMenuID.end())
		return 0;
	//
	CComPtr<IWizDocument> spDstDocument = it->second;
	if (!spDstDocument)
		return 0;

	CComPtr<IWizDocument> spSrcDocument = m_pTodoDlg->GetDocument();

	// 找到鼠标所指向的item
	HTREEITEM hSelectItem = GetFirstCommandItem();
	if (!hSelectItem)
		return 0;

	WIZTODODATAEX itemData;
	if (!ItemToData(hSelectItem, itemData))
	{
		return 0;
	}

	// 只更新Document即可，它会自动触发消息而使得界面更新
	WIZTODODATAEX::CWizTodoDataExArray arrayDst;
	WizDocumentGetTodoData(spDstDocument, arrayDst);
	arrayDst.push_back(itemData);  
	WizDocumentSetTodoData(spDstDocument, arrayDst);

	// 要删除的必然在界面上，从界面删除即可
	DeleteItem(hSelectItem);
	m_bModified = true;
	m_pTodoDlg->AutoSave();

	return 0;
}



void CWizTodoTreeCtrl::OnTodoLinkClicked(HTREEITEM hItem)
{
	if (!hItem)
		return;
	//
	if (!m_pDatabase)
		return;
	//
	WIZTODODATA* pData = GetItemTodo(hItem);
	if (!pData)
		return;
	//
	CString strDocumentGUID;
	//
	if (pData->arrayLinkedDocumentGUID.empty())
	{
		ATLASSERT(FALSE);
		return;
	}
	else if (pData->arrayLinkedDocumentGUID.size() == 1)
	{
		strDocumentGUID = pData->arrayLinkedDocumentGUID[0];
	}
	else
	{
		//
		CMenu menu;
		if (!menu.CreatePopupMenu())
			return;
		//
		for (CWizStdStringArray::const_iterator it = pData->arrayLinkedDocumentGUID.begin();
			it != pData->arrayLinkedDocumentGUID.end();
			it++)
		{
			CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(*it);
			if (!spDocument)
				continue;
			//
			CString strTitle = CWizKMDatabase::GetDocumentTitle(spDocument);
			if (strTitle.GetLength() > 50)
			{
				strTitle = strTitle.Left(50) + _T("...");
			}
			//
			menu.AppendMenu(MF_STRING, ID_TODO_LINK_BEGIN + int(it - pData->arrayLinkedDocumentGUID.begin()), strTitle);
		}
		//
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING, ID_TODOITEM_CREATELINK, WizFormatString0(IDS_EDIT_LINK));

		//
		CPoint pt;
		GetCursorPos(&pt);
		//
		UINT nID = menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD, pt.x, pt.y, m_hWnd, NULL);
		if (0 == nID)
			return;
		//
		int nIndex = nID - ID_TODO_LINK_BEGIN;
		//
		if (nIndex < 0 || nIndex >= int(pData->arrayLinkedDocumentGUID.size()))
		{
			PostMessage(WM_COMMAND, MAKEWPARAM(nID, 0), 0);
			return;
		}
		//
		strDocumentGUID = pData->arrayLinkedDocumentGUID[nIndex];
	}
	//
	CComPtr<IWizDocument> spDocument = m_pDatabase->GetDocumentByGUID(strDocumentGUID);
	if (!spDocument)
		return;
	//
	CString strType = CWizKMDatabase::GetDocumentType(spDocument);
	if (0 == strType.CompareNoCase(_T("event")))
	{
		CComPtr<IWizCommonUI> spCommonUI = ::WizKMCreateCommonUI();
		VARIANT_BOOL vbRet = VARIANT_FALSE;
		spCommonUI->EditCalendarEvent(spDocument, &vbRet);
	}
	else
	{
		WizGetMainDlg()->ViewDocument(spDocument);
	}
}