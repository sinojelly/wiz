#include "stdafx.h"
#include "resource.h"       // main symbols

#include <atlhost.h>

#include "../Globals/WizKMSmallDlgBase.h"

#include "../Globals/WizKMObjectMessage.h"

#include "WizTodoTreeCtrl.h"
#include "TodoDlg.h"


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

				CString strGUID1 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDocument);				CString strGUID2 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDlgDocument);

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
	HTREEITEM hSelectItem = GetFirstCommandItem();	if (!hSelectItem)		return 0;

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
