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

			CString strGUID1 = CWizKMDatabase::GetObjectGUID<IWizDocument>(spDocument);

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

	// �ҵ������ָ���item
	HTREEITEM hSelectItem = GetFirstCommandItem();

	WIZTODODATAEX itemData;
	if (!ItemToData(hSelectItem, itemData))
	{
		return 0;
	}

	// ֻ����Document���ɣ������Զ�������Ϣ��ʹ�ý������
	WIZTODODATAEX::CWizTodoDataExArray arrayDst;
	WizDocumentGetTodoData(spDstDocument, arrayDst);
	arrayDst.push_back(itemData);  
	WizDocumentSetTodoData(spDstDocument, arrayDst);

	// Ҫɾ���ı�Ȼ�ڽ����ϣ��ӽ���ɾ������
	DeleteItem(hSelectItem);
	m_bModified = true;
	m_pTodoDlg->AutoSave();

	return 0;
}