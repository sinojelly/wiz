#include "stdafx.h"
#include "resource.h"       // main symbols

#include <atlhost.h>

#include "../Globals/WizKMSmallDlgBase.h"

#include "../Globals/WizKMObjectMessage.h"

#include "WizTodoTreeCtrl.h"
#include "TodoDlg.h"


void CWizTodoTreeCtrl::UpdateMoveToMenu( CMenuHandle &menu ) 
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

	CWizDocumentArray arrayTodoList;
	WizKMGetTodo2Documents(m_pDatabase, WizKMTodoGetInboxLocation(), arrayTodoList);
	if (!arrayTodoList.empty())
	{
		//
		CComPtr<IWizDocument> spDlgDocument = m_pTodoDlg->GetDocument();

		UINT index = 0;
		for (CWizDocumentArray::const_iterator it = arrayTodoList.begin();
			it != arrayTodoList.end() && index < 20;
			it++)
		{
			CComPtr<IWizDocument> spDocument = *it;

			CString strGUID1 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDocument);			CString strGUID2 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDlgDocument);

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

	menu.InsertMenu(MOVE_TO_MENU_POS, MF_BYPOSITION | MF_STRING, (HMENU)moveToMenu,  CString("Move To"));
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
	WIZTODODATA* pItemData = GetItemTodo(hSelectItem);
	if (!pItemData)
		return 0;

	// 只更新Document即可，它会自动触发消息而使得界面更新
	WIZTODODATAEX::CWizTodoDataExArray arrayDst;
	WizDocumentGetTodoData(spDstDocument, arrayDst);
	arrayDst.push_back(*pItemData);  
	WizDocumentSetTodoData(spDstDocument, arrayDst);

	// 要删除的必然在界面上，从界面删除即可
	DeleteItem(hSelectItem);
	m_bModified = true;
	m_pTodoDlg->AutoSave();

	return 0;
}
