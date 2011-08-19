// TodoDlg.h : Declaration of the CTodoDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

#include "../Globals/WizKMSmallDlgBase.h"

#include "../Globals/WizKMObjectMessage.h"


#include "WizTodoTreeCtrl.h"



#define IDC_BUTTON_NEW				WIZ_ID_SMALL_DLG_BUTTON_BASE + 1
#define IDC_TREE_TODO				WIZ_ID_SMALL_DLG_BUTTON_BASE + 2


class CTodoDlg
	: public CWizKMSmallDlgBase<CTodoDlg>
	, public CWinDataExchange<CTodoDlg>
	, public CWizKMObjectMessageHandler<CTodoDlg>
{
public:
	CTodoDlg(CWizKMDatabase* pDatabase, LPCTSTR lpszInitTitle);
	~CTodoDlg();

private:
	CWizKMDatabase* m_pDatabase;
	//
	CWizVistaIconButton m_btnNew;
	CWizTodoTreeCtrl m_wndList;
	CString m_strInitTitle;
public:

BEGIN_MSG_MAP(CTodoDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	COMMAND_HANDLER(IDC_BUTTON_NEW, BN_CLICKED, OnBnClickedButtonNew)
	COMMAND_ID_HANDLER(ID_TODO_CHANGETITLE, OnTodoChangetitle)
	CHAIN_MSG_MAP(CWizKMSmallDlgBase<CTodoDlg>)
	CHAIN_MSG_MAP(CWizKMObjectMessageHandler<CTodoDlg>)
	REFLECT_NOTIFICATIONS()
END_MSG_MAP()
private:
	CComPtr<IWizDocument> m_spDocument;
	//
	BOOL CreateDocument();
	//
	CMenu m_menu;
	//
public:
	virtual CString GetTitle();
	virtual CRect GetTitleRect();
	//
	virtual void InitClient();
	virtual void UpdateLayout();
	virtual void UpdateLockButtonIcon();
	virtual void SetColor(COLORREF cr);
	virtual void Close();
	virtual BOOL AutoSave();
	virtual BOOL SavePos();
	virtual BOOL LoadPos();
public:
	//
	BOOL SaveData();
	BOOL SaveParam();
	//
	BOOL LoadData();
	BOOL LoadParam();
	//
	BOOL Load();
	//
	CComPtr<IWizDocument> GetDocument() const { return m_spDocument; }
	//
	void SetMinimize();
	//
	BOOL IsModified() const;
	//
	void Refresh();
	//
	BOOL SetDocument(IWizDocument* pDocument);
	//
	CComPtr<IWizEvent> GetTodoEvent(WIZTODODATA* pData);
	//
	BOOL OnModifyDocument(LPCTSTR lpszGUID);
	//
	void InitNewTodoList();
public:

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTodoChangetitle(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	void MoveCompletedTodoItems();
};


