#include "stdafx.h"
#include "WizUIBase.h"


#include <math.h>


CWizSkinBase::CWizSkinBase()
{
	
}
//
BOOL CWizSkinBase::Init(LPCTSTR lpszFileName)
{
	m_map.clear();
	//
	CWizStdStringArray arrayText;
	if (!WizStringArrayLoadFromFile(lpszFileName, arrayText))
		return FALSE;
	//
	for (CWizStdStringArray::const_iterator it = arrayText.begin();
		it != arrayText.end();
		it++)
	{
		const CString& strLine = *it;
		CString strLeft;
		CString strRight;
		if (WizStringSimpleSplit(strLine, '=', strLeft, strRight))
		{
			m_map[strLeft] = strRight;
		}
	}
	//
	return TRUE;
}

CString CWizSkinBase::GetValue(const CString& strKey)
{
	CString strEmpty;
	std::map<CString, CString>::const_iterator it = m_map.find(strKey);
	if (it == m_map.end())
		return strEmpty;
	//
	return it->second;
}

COLORREF CWizSkinBase::GetColor(const CString& strKey, COLORREF crDefault)
{
	CString str = GetValue(strKey);
	if (str.IsEmpty())
		return crDefault;
	//
	return ::WizStringToColor(str);
}
BOOL CWizSkinBase::GetBool(const CString& strKey, BOOL bDef)
{
	CString str = GetValue(strKey);
	if (str.IsEmpty())
		return bDef;
	str.MakeLower();
	return str == _T("true") || str == _T("1");
}
int CWizSkinBase::GetInt(const CString& strKey, int nDef)
{
	CString str = GetValue(strKey);
	if (str.IsEmpty())
		return nDef;
	return _ttoi(str);
}


static LPCTSTR g_arraySkinColorTypeName [CWizSkin::WIZCOLORTYPE_END - CWizSkin::WIZCOLORTYPE_BEGIN + 1] = 
{
	_T("Window"),
	_T("WindowText"),
	_T("Control"),
	_T("ControlText"),
	
	_T("MenuBar"),
	_T("MenuBarHot"),
	_T("MenuBarText"),
	_T("MenuBarTextHot"),
	
	_T("ToolBar"),
	
	_T("ToolBarButtonNormal"),
	_T("ToolBarButtonHot"),
	_T("ToolBarButtonDown"),
	_T("ToolBarButtonDisabled"),
	
	_T("ToolBarButtonBorderNormal"),
	_T("ToolBarButtonBorderHot"),
	_T("ToolBarButtonBorderDown"),
	_T("ToolBarButtonBorderDisabled"),
	
	_T("ToolBarButtonTextNormal"),
	_T("ToolBarButtonTextHot"),
	_T("ToolBarButtonTextDown"),
	_T("ToolBarButtonTextDisabled"),
	
	_T("Item"),
	_T("ItemHot"),
	_T("ItemSelected"),
	_T("ItemSelectedNoFocus"),

	_T("ItemText"),
	_T("ItemTextHot"),
	_T("ItemTextSelected"),
	_T("ItemTextSelectedNoFocus"),

	_T("ToolBarEdit"),
	_T("ToolBarEditText"),
	_T("ToolBarEditBorderHot"),

	_T("SecondLineText"),

	_T("ToolBarShadow"),
	_T("ToolBarBorder"),

	_T("Splitter"),

	_T("ControlBorder"),
};

CWizSkin::CWizSkin()
{
	//InitDefault();
}
void CWizSkin::InitDefault()
{
	m_arrayColor[crWindow] = ::GetSysColor(COLOR_WINDOW);
	m_arrayColor[crWindowText] = ::GetSysColor(COLOR_WINDOWTEXT);
	m_arrayColor[crControl] = ::GetSysColor(COLOR_BTNFACE);
	m_arrayColor[crControlText] = ::GetSysColor(COLOR_BTNTEXT);
	
	m_arrayColor[crMenuBar] = m_arrayColor[crControl];
	m_arrayColor[crMenuBarHot] = ::GetSysColor(COLOR_HIGHLIGHT);
	m_arrayColor[crMenuBarText] = ::GetSysColor(COLOR_MENUTEXT);
	m_arrayColor[crMenuBarTextHot] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	
	m_arrayColor[crToolBar] = m_arrayColor[crControl];
	
	m_arrayColor[crToolBarButtonNormal] = ::GetSysColor(COLOR_WINDOW);
	m_arrayColor[crToolBarButtonHot] = ::GetSysColor(COLOR_BTNFACE);
	m_arrayColor[crToolBarButtonDown] = ::GetSysColor(COLOR_BTNSHADOW);
	m_arrayColor[crToolBarButtonDisabled] = ::GetSysColor(COLOR_BTNFACE);
	
	m_arrayColor[crToolBarButtonBorderNormal] = ::GetSysColor(COLOR_BTNSHADOW);
	m_arrayColor[crToolBarButtonBorderHot] = ::GetSysColor(COLOR_BTNSHADOW);
	m_arrayColor[crToolBarButtonBorderDown] = ::GetSysColor(COLOR_BTNSHADOW);
	m_arrayColor[crToolBarButtonBorderDisabled] = ::GetSysColor(COLOR_BTNSHADOW);
	
	m_arrayColor[crToolBarButtonTextNormal] = ::GetSysColor(COLOR_BTNTEXT);
	m_arrayColor[crToolBarButtonTextHot] = ::GetSysColor(COLOR_BTNTEXT);
	m_arrayColor[crToolBarButtonTextDown] = ::GetSysColor(COLOR_BTNTEXT);
	m_arrayColor[crToolBarButtonTextDisabled] = ::GetSysColor(COLOR_BTNSHADOW);
	
	m_arrayColor[crItem] = ::GetSysColor(COLOR_WINDOW);
	m_arrayColor[crItemHot] = ::GetSysColor(COLOR_HIGHLIGHT);
	m_arrayColor[crItemSelected] = ::GetSysColor(COLOR_HIGHLIGHT);
	m_arrayColor[crItemSelectedNoFocus] = ::GetSysColor(COLOR_BTNSHADOW);
	
	m_arrayColor[crItemText] = ::GetSysColor(COLOR_WINDOWTEXT);
	m_arrayColor[crItemTextHot] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_arrayColor[crItemTextSelected] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_arrayColor[crItemTextSelectedNoFocus] = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	//
	m_arrayColor[crToolBarEdit] = m_arrayColor[crWindow];
	m_arrayColor[crToolBarEditText] = m_arrayColor[crWindowText];
	m_arrayColor[crToolBarEditBorderHot] = m_arrayColor[crToolBarButtonBorderHot];
	//
	m_arrayColor[crSecondLineText] = ::GetSysColor(COLOR_BTNSHADOW);
	//
	m_arrayColor[crToolBarShadow] = ::GetSysColor(COLOR_BTNSHADOW);
	m_arrayColor[crToolBarBorder] = ::GetSysColor(COLOR_BTNSHADOW);
	//
	m_arrayColor[crSplitter] = m_arrayColor[crControl];
	//
	m_arrayColor[crControlBorder] = ::GetSysColor(COLOR_BTNSHADOW);
}

CString CWizSkin::ColorTypeToName(WizSkinColorType type)
{
	return CString(g_arraySkinColorTypeName[type]);
}
CWizSkin::WizItemState CWizSkin::CalItemState(HWND hwnd, BOOL bSelected, BOOL bHot)
{
	WizItemState state = wizisNormal;
	//
	if (bSelected)
	{
		//
		if (::GetFocus() == hwnd)
		{
			state = CWizSkin::wizisSelected;
		}
		else
		{
			state = CWizSkin::wizisSelectedNoFocus;
		}
	}
	else if (bHot)
	{
		return wizisHot;
	}
	//
	return state;
}


BOOL CWizSkin::Init(LPCTSTR lpszFileName)
{
	InitDefault();
	//
	if (!CWizSkinBase::Init(lpszFileName))
		return FALSE;
	//
	for (int i = 0; i <= WIZCOLORTYPE_END - WIZCOLORTYPE_BEGIN; i++)
	{
		m_arrayColor[i] = GetColor(g_arraySkinColorTypeName[i], m_arrayColor[i]);
	}
	//
	return TRUE;
}
//

COLORREF CWizSkin::GetMenuBarColor(BOOL bHot)
{
	return m_arrayColor[ bHot ? crMenuBarHot : crMenuBar];
}
COLORREF CWizSkin::GetMenuBarTextColor(BOOL bHot)
{
	return m_arrayColor[ bHot ? crMenuBarTextHot : crMenuBarText];
}
COLORREF CWizSkin::GetToolBarColor()
{
	return m_arrayColor[ crToolBar ];
}
//
COLORREF CWizSkin::GetToolBarButtonColor(WizButtonState state)
{
	return m_arrayColor[crToolBarButtonNormal + state];
}
COLORREF CWizSkin::GetToolBarButtonBorderColor(WizButtonState state)
{
	return m_arrayColor[crToolBarButtonBorderNormal + state];
}
COLORREF CWizSkin::GetToolBarButtonTextColor(WizButtonState state)
{
	return m_arrayColor[crToolBarButtonTextNormal + state];
}
//
COLORREF CWizSkin::GetItemColor(WizItemState state)
{
	return m_arrayColor[crItem + state];
}
COLORREF CWizSkin::GetItemTextColor(WizItemState state)
{
	return m_arrayColor[crItemText + state];
}

COLORREF CWizSkin::GetWindowColor()
{
	return m_arrayColor[crWindow];
}
COLORREF CWizSkin::GetWindowTextColor()
{
	return m_arrayColor[crWindowText];
}
//
COLORREF CWizSkin::GetControlColor()
{
	return m_arrayColor[crControl];
}
COLORREF CWizSkin::GetControlTextColor()
{
	return m_arrayColor[crControlText];
}

COLORREF CWizSkin::GetToolBarEditColor()
{
	return m_arrayColor[crToolBarEdit];
}

COLORREF CWizSkin::GetToolBarEditTextColor()
{
	return m_arrayColor[crToolBarEditText];
}

COLORREF CWizSkin::GetToolBarEditBorderHotColor()
{
	return m_arrayColor[crToolBarEditBorderHot];
}

COLORREF CWizSkin::GetSecondLineTextColor()
{
	return m_arrayColor[crSecondLineText];
}


COLORREF CWizSkin::GetToolBarShadowColor()
{
	return m_arrayColor[crToolBarShadow];
}
COLORREF CWizSkin::GetToolBarBorderColor()
{
	return m_arrayColor[crToolBarBorder];
}

COLORREF CWizSkin::GetSplitterColor()
{
	return m_arrayColor[crSplitter];
}

COLORREF CWizSkin::GetControlBorderColor()
{
	return m_arrayColor[crControlBorder];
}


CString CWizSkin::GetCustomKey(LPCTSTR lpszName, WizSkinColorType type)
{
	CString strKey = CString(lpszName) + _T("_") + ColorTypeToName(type);
	return strKey;
}

COLORREF CWizSkin::GetCustomColor(LPCTSTR lpszName, WizSkinColorType type, COLORREF crDefault)
{
	if (!lpszName || !*lpszName)
		return crDefault;
	//
	CString strKey = GetCustomKey(lpszName, type);
	return GetColor(strKey, crDefault);
}

void CWizSkin::DrawItemBackground(CDCHandle dc, const RECT& rcItem, CWizSkin::WizItemState state, BOOL bFocus, COLORREF crDefault)
{
	if (wizisHot == state
		|| wizisSelected == state
		|| wizisSelectedNoFocus == state)
	{
		COLORREF cr = GetItemColor(state);
		dc.FillSolidRect(&rcItem, cr);
	}
	else
	{
		if ((COLORREF)-1 != crDefault)
		{
			dc.FillSolidRect(&rcItem, crDefault);
		}
	}
}
void CWizSkin::DrawButtonBackground(CDCHandle dc, const RECT& rcButton, CWizSkin::WizButtonState state)
{
	DrawButtonBackgroundEx(dc, rcButton, state, TRUE, FALSE);
}
void CWizSkin::DrawButtonBackgroundEx(CDCHandle dc, const RECT& rcButton, WizButtonState state, BOOL bLeft, BOOL bRight)
{
	COLORREF crBackground = GetToolBarButtonColor(state);
	COLORREF crBorder = GetToolBarButtonBorderColor(state);
	DrawRoundRect(dc, rcButton, crBorder, crBackground, bLeft, bRight);
}

//
int CWizSkin::GetDropDownArrowWidth()
{
	return 8;
}
void CWizSkin::DrawDropDownArrow(CDCHandle dc, const CRect& rc, COLORREF cr)
{
	CWizDCSaver saver(dc);
	//
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, cr);
	dc.SelectPen(pen);
	//
	CBrush brush;
	brush.CreateSolidBrush(cr);
	dc.SelectBrush(brush);
	//
	CPoint ptCenter = rc.CenterPoint();
	//
	POINT arrayPt[3] = 
	{
		{ptCenter.x - 2, ptCenter.y -1},
		{ptCenter.x + 2, ptCenter.y - 1},
		{ptCenter.x, ptCenter.y + 1}
	};
	//
	dc.Polygon(arrayPt, 3);
}
void CWizSkin::DrawDropDownArrow2(CDCHandle dc, const CRect& rc, COLORREF cr)
{
	CWizDCSaver saver(dc);
	//
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, cr);
	dc.SelectPen(pen);
	//
	CBrush brush;
	brush.CreateSolidBrush(cr);
	dc.SelectBrush(brush);
	//
	CPoint ptCenter = rc.CenterPoint();
	//
	POINT arrayPt[3] = 
	{
		{ptCenter.x - 2, ptCenter.y +1},
		{ptCenter.x + 2, ptCenter.y + 1},
		{ptCenter.x, ptCenter.y - 1}
	};
	//
	dc.Polygon(arrayPt, 3);
}

//
void CWizSkin::DrawToolButtonBackground(CDCHandle dc, const RECT& rcButton, LPCTSTR lpszText, UINT nFlags, CWizSkin::WizButtonState state, CWizSkin::WizToolButtonDropDownState stateDropDown)
{
	DrawToolButtonBackgroundEx(dc, rcButton, lpszText, nFlags, state, stateDropDown, TRUE, TRUE);
}

void CWizSkin::DrawToolButtonBackgroundEx(CDCHandle dc, const RECT& rcButton, LPCTSTR lpszText, UINT nFlags, CWizSkin::WizButtonState state, CWizSkin::WizToolButtonDropDownState stateDropDown, BOOL bLeft, BOOL bRight)
{
	COLORREF crBorder = GetToolBarButtonBorderColor(state);
	COLORREF crFill = GetToolBarButtonColor(state);
	COLORREF crText = GetToolBarButtonTextColor(state);
	//
	DrawToolButtonBackgroundCustomColor(dc, rcButton, lpszText, nFlags, crBorder, crFill, crText, state, stateDropDown, bLeft, bRight);
}

void CWizSkin::DrawToolButtonBackgroundCustomColor(CDCHandle dc, const RECT& rcButton, LPCTSTR lpszText, UINT nFlags, COLORREF crBorder, COLORREF crFill, COLORREF crText, CWizSkin::WizButtonState state, WizToolButtonDropDownState stateDropDown, BOOL bLeft, BOOL bRight)
{
	BOOL bBorder = (nFlags & wizbbBorder) ? TRUE : FALSE;
	BOOL bText = (nFlags & wizbbText) ? TRUE : FALSE;
	BOOL bImage = (nFlags & wizbbImage) ? TRUE : FALSE;
	//
	bBorder = (bBorder || state == wizbsDown || state == wizbsHot);
	//
	if (bBorder)
	{
		DrawRoundRect(dc, rcButton, crBorder, crFill, bLeft, bRight);
		//
		if (stateDropDown == wizddsDropDown)
		{
			CRect rcDropDown = rcButton;
			rcDropDown.left = rcDropDown.right - 16;
			rcDropDown.right -= 2;
			//
			rcDropDown.right = rcDropDown.left + 1;
			//
			dc.FillSolidRect(&rcDropDown, crBorder);
		}
	}
	//
	if (stateDropDown == wizddsDropDown)
	{
		CRect rcDropDown = rcButton;
		rcDropDown.left = rcDropDown.right - 16;
		rcDropDown.right -= 2;
		DrawDropDownArrow(dc, rcDropDown, crText);
	}
	else if (stateDropDown == wizddsWholeDropDown)
	{
		int nTextWidth = 0;
		if (bText && lpszText && *lpszText)
		{
			CSize szText;
			dc.GetTextExtent(lpszText, -1, &szText);
			nTextWidth = szText.cx + 4;
		}
		//
		int nImageWidth = 0;
		if (bImage)
		{
			nImageWidth = 16 + 4;
		}
		//
		int nDropDownWodth = GetDropDownArrowWidth();
		//
		int nAllWidth = nTextWidth + nImageWidth + nDropDownWodth;
		//
		CRect rcDropDown = rcButton;
		int nLeft = rcDropDown.CenterPoint().x + nAllWidth / 2 - nDropDownWodth;
		rcDropDown.left = nLeft;
		rcDropDown.right = rcDropDown.left + nDropDownWodth;
		//
		DrawDropDownArrow(dc, rcDropDown, crText);
	}
}


//
void CWizSkin::DrawRoundRect(CDCHandle dc, const CRect& rc, COLORREF crColor, COLORREF crFill, BOOL bLeft, BOOL bRight)
{
	if (crFill != (COLORREF)-1)
	{
		CRect rcFill = rc;
		rcFill.DeflateRect(1, 1);
		dc.FillSolidRect(&rcFill, crFill);
	}
	//
	dc.FillSolidRect(CRect(rc.left + 1, rc.top, rc.right - 1, rc.top + 1), crColor);
	dc.FillSolidRect(CRect(rc.left, rc.top + 1, rc.left + 1, rc.bottom - 1), crColor);
	dc.FillSolidRect(CRect(rc.right - 1, rc.top + 1, rc.right, rc.bottom - 1), crColor);
	dc.FillSolidRect(CRect(rc.left + 1, rc.bottom - 1, rc.right - 1, rc.bottom), crColor);

	if (!bLeft)
	{
		dc.SetPixelV(rc.left, rc.top, crColor);
		dc.SetPixelV(rc.left, rc.bottom - 1, crColor);
	}
	else if (!bRight)
	{
		dc.SetPixelV(rc.right - 1, rc.top, crColor);
		dc.SetPixelV(rc.right - 1, rc.bottom - 1, crColor);
	}
}

BOOL CWizSkin::GetDrawToolBarTopBorder()
{
	BOOL b = GetBool(_T("DrawToolBarBorderTop"), FALSE);
	return b;
}
BOOL CWizSkin::GetDrawControlBorder()
{
	BOOL b = GetBool(_T("DrawControlBorder"), FALSE);
	return b;
}


BOOL WizCreateUIFont(CFont& font, UINT nFlags, LPCTSTR lpszFontName, int nFontHeight)
{
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
#if (WINVER >= 0x0600)
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(ncm.iPaddedBorderWidth);
#else
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
#endif
	//
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	//
	BOOL bBold = (nFlags & WIZUIFONT_BOLD) ? TRUE : FALSE;
	BOOL bItalic = (nFlags & WIZUIFONT_ITALIC) ? TRUE : FALSE;
	BOOL bUnderline = (nFlags & WIZUIFONT_UNDERLINE) ? TRUE : FALSE;
	BOOL bStrikeOut = (nFlags & WIZUIFONT_STRIKEOUT) ? TRUE : FALSE;
	//
	ncm.lfMenuFont.lfWeight = FW_NORMAL;
	//
	LOGFONT lf = ncm.lfMenuFont;
	lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = bItalic;
	lf.lfUnderline = bUnderline;
	lf.lfStrikeOut = bStrikeOut;
	//
	if (lpszFontName && *lpszFontName)
	{
		_tcscpy_s(lf.lfFaceName, LF_FACESIZE, lpszFontName);
	}
	//
	if (nFontHeight != 0)
	{
		lf.lfHeight = nFontHeight;
	}
	else if (nFlags & WIZUIFONT_SMALL)
	{
		if (lf.lfHeight < 0)
		{
			lf.lfHeight += 2;
		}
		else
		{
			lf.lfHeight--;
		}
	}
	else if (nFlags & WIZUIFONT_LARGE)
	{
		if (lf.lfHeight < 0)
		{
			lf.lfHeight -= 2;
		}
		else
		{
			lf.lfHeight++;
		}
	}
	//
	return NULL != font.CreateFontIndirect(&lf);
}


int WizGetFontHeight(HWND hWnd, HFONT hFont)
{
	HDC hDC = GetDC(hWnd);
	//
	int nDC = SaveDC(hDC);
	//
	int nHeight = 0;
	//
	try
	{
		if (hFont)
		{
			SelectObject(hDC, hFont);
		}
		//
		LPCTSTR lpszString = _T("kg中国");
		//
		CSize sz;
		GetTextExtentPoint32(hDC, lpszString, (int)_tcslen(lpszString), &sz);
		//
		nHeight = sz.cy;
	}
	catch (...)
	{
	}
	//
	RestoreDC(hDC, nDC);
	//
	ReleaseDC(hWnd, hDC);
	//
	return nHeight;
}

int WizGetFontHeight(HWND hWnd)
{
	if (!hWnd)
		return 0;
	//
	CClientDC dc(hWnd);
	//
	LPCTSTR lpszString = _T("kg中国");
	//
	CSize sz;
	dc.GetTextExtent(lpszString, -1, &sz);
	//
	return sz.cy;
}

int WizGetTextWidth(HWND hWnd, LPCTSTR lpszText, HFONT hFont)
{
	if (!hWnd)
		return 0;
	//
	CClientDC dc(hWnd);
	//
	HFONT hOldFont = NULL;
	if (hFont)
	{
		hOldFont = dc.SelectFont(hFont);
	}
	//
	CSize sz;
	dc.GetTextExtent(lpszText, -1, &sz);
	//
	if (hFont)
	{
		dc.SelectFont(hOldFont);
	}
	//
	return sz.cx;
}

CWizDCSaver::CWizDCSaver(HDC hDC)
	: m_nSavedDC(0)
	, m_hDC(hDC)
{
	if (m_hDC)
	{
		m_nSavedDC = ::SaveDC(hDC);
	}
}
CWizDCSaver::~CWizDCSaver()
{
	if (m_nSavedDC && m_hDC)
	{
		RestoreDC(m_hDC, m_nSavedDC);
	}
}





CWizToolBarEdit::CWizToolBarEdit()
	: m_fMouseOver(0)
{
}
LRESULT CWizToolBarEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
	//
	if(m_fMouseOver == 0)
	{
		m_fMouseOver = 1;
		Invalidate();
		GetParent().Invalidate();
		GetParent().UpdateWindow();
		StartTrackMouseLeave();
	}
	//
	return lRet;
}

LRESULT CWizToolBarEdit::OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_fMouseOver == 1)
	{
		m_fMouseOver = 0;
		Invalidate();
		GetParent().Invalidate();
		GetParent().UpdateWindow();
	}
	return 0;
}

BOOL CWizToolBarEdit::StartTrackMouseLeave()
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	return _TrackMouseEvent(&tme);
}
BOOL CWizToolBarEdit::IsMouseHover() const
{
	if (m_fMouseOver)
		return TRUE;
	//
	return FALSE;
}


CWizLinkToolBarEdit::CWizLinkToolBarEdit()
{
	m_hCursor = NULL;
}
CWizLinkToolBarEdit::~CWizLinkToolBarEdit()
{
	if (m_hCursor)
	{
		DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	}
}
//
LRESULT CWizLinkToolBarEdit::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_tip.Create(m_hWnd);
	//
	CString strTooltip = WizTranslationsTranslateString(_T("Ctrl+Click to edit hyperlink"));
	m_tip.AddTool(m_hWnd, (LPCTSTR)strTooltip);
	//
	bHandled = FALSE;
	//
	return 0;
}
LRESULT CWizLinkToolBarEdit::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CWizLinkToolBarEdit::OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_brush.IsNull())
	{
		m_brush.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
	}
	if (m_font.IsNull())
	{
		::WizCreateUIFont(m_font, WIZUIFONT_UNDERLINE);
	}
	//
	HDC hDC = (HDC)wParam;
	CDCHandle dc(hDC);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	dc.SetTextColor(RGB(0, 0, 255));
	dc.SelectFont(m_font);
	//
	return (LRESULT)m_brush.m_hBrush;
}
//
LRESULT CWizLinkToolBarEdit::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_hCursor)
	{
		m_hCursor = LoadCursor(NULL, IDC_HAND);
	}
	//
	SetCursor(m_hCursor);
	return TRUE;
}
//
LRESULT CWizLinkToolBarEdit::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ToolTipRelayEvent();
	//
	if (GetKeyState(VK_CONTROL) < 0)
	{
	}
	else
	{
		CString strText;
		GetWindowText(strText);
		if (!strText.IsEmpty())
		{
			ShellExecute(NULL, _T("open"), strText, NULL, NULL, SW_SHOW);
		}
	}
	//
	bHandled = FALSE;
	//
	return 0;
}
//

LRESULT CWizLinkToolBarEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ToolTipRelayEvent();
	return CWizToolBarEdit::OnMouseMove(uMsg, wParam, lParam, bHandled);
}

//
LRESULT CWizLinkToolBarEdit::OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ToolTipRelayEvent();
	//
	bHandled = FALSE;
	//
	return 0;
}
//
void CWizLinkToolBarEdit::ToolTipRelayEvent()
{
	const MSG* pMsg = GetCurrentMessage();
	if (pMsg)
	{
		MSG msg = *pMsg;
		m_tip.RelayEvent(&msg);
	}
}


HWND CWizSimpleToolBar::CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, HICON* parrayIcon, UINT nIconCount, UINT nToolBarID)
{
	HWND hwnd = Create(hWndParent, lprc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_LIST, nToolBarID);
	if (!hwnd)
		return NULL;
	SetExtendedStyle(TBSTYLE_EX_MIXEDBUTTONS);
	//
	SetButtonSize(22, 22);
	//
	m_il.Create(16, 16, ILC_COLOR32 | ILC_MASK, nIconCount, 0);
	if (parrayIcon)
	{
		for (int i = 0; i < int(nIconCount); i++)
		{
			m_il.AddIcon(parrayIcon[i]);
		}
	}
	//
	SetImageList(m_il);
	//
	CMenu menu;
	if (!menu.LoadMenu(nMenuResourceID))
		return hwnd;
	//
	CMenu menuSub = menu.GetSubMenu(0);
	if (!menuSub.IsMenu())
		return hwnd;
	//
	TCHAR szText[MAX_PATH] = {0};
	//
	int nImageIndex = 0;
	//
	for (int i = 0; i < menuSub.GetMenuItemCount(); i++)
	{
		ZeroMemory(szText, sizeof(TCHAR) * MAX_PATH);
		//
		MENUITEMINFO mii;
		//
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_ID | MIIM_TYPE;
		mii.dwTypeData = szText;
		mii.cch = MAX_PATH;
		//
		menuSub.GetMenuItemInfo(i, TRUE, &mii);
		if (0 == mii.wID)
			continue;
		//
		AddToolButtonNoTextWithToolTip(mii.wID, szText, nImageIndex);
	}
	//
	return hwnd;
}
HWND CWizSimpleToolBar::CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, HICON hIcon, UINT nToolBarID)
{
	return CreateEx(hWndParent, lprc, nMenuResourceID, &hIcon, 1, nToolBarID);
}
HWND CWizSimpleToolBar::CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, LPCTSTR lpszIconFileName, UINT nToolBarID)
{
	HICON hIcon = (HICON)LoadImage(NULL, lpszIconFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	if (!hIcon)
		return NULL;
	//
	HWND hWnd = CreateEx(hWndParent, lprc, nMenuResourceID, hIcon, nToolBarID);
	//
	DestroyIcon(hIcon);
	//
	return hWnd;
}


HWND CWizSimpleToggleButton::CreateToggleButton(HWND hwndParent, LPRECT lprc, UINT nMenuResourceID, LPCTSTR lpszNormalIconFileName, LPCTSTR lpszDownIconFileName, UINT nToolBarID)
{
	HWND hwnd = CreateEx(hwndParent, lprc, nMenuResourceID, lpszNormalIconFileName, nToolBarID);
	if (!hwnd)
		return NULL;
	//
	HICON hIconDown = (HICON)LoadImage(NULL, lpszDownIconFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	if (!hIconDown)
		return hwnd;
	//
	m_il.AddIcon(hIconDown);
	//
	DestroyIcon(hIconDown);
	//
	return hwnd;
}
//
LRESULT CWizSimpleToggleButton::OnNMClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	bHandled = TRUE;
	//
	SetCheck(!GetCheck());
	UpdateStatus();
	//
	return 0;
}
//
UINT CWizSimpleToggleButton::GetButtonID()
{
	if (!IsToggleButton())
		return 0;
	//
	TBBUTTON tb;
	GetButton(0, &tb);
	return tb.idCommand;
}
//
BOOL CWizSimpleToggleButton::IsToggleButton()
{
	if (!IsWindow())
		return FALSE;
	//
	if (1 != GetButtonCount())
		return FALSE;
	//
	return TRUE;
}
BOOL CWizSimpleToggleButton::GetCheck()
{
	if (!IsToggleButton())
		return FALSE;
	//
	return IsButtonChecked(GetButtonID());
}
void CWizSimpleToggleButton::SetCheck(BOOL b)
{
	if (!IsToggleButton())
		return;
	//
	CheckButton(GetButtonID(), b);
	//
	UpdateStatus();
}
//
void CWizSimpleToggleButton::UpdateStatus()
{
	if (!IsToggleButton())
		return;
	//
	int nImage = 0;
	if (GetCheck())
	{
		nImage = 1;
	}
	//
	SetButtonInfo(GetButtonID(), TBIF_IMAGE, 0, 0, NULL, nImage, 0, 0, NULL);
}



CWizFlatToolBarCtrl::CWizFlatToolBarCtrl()
	: m_bDrawShadow(FALSE)
{
	m_crShadow = WizGetSkin()->GetToolBarShadowColor();
}

int CWizFlatToolBarCtrl::GetMinHeight()
{
	int nMinHeight = CWizCustomCommandToolBar::GetMinHeight();
	if (m_bDrawShadow)
		nMinHeight += 3;
	//
	return nMinHeight;
}

void CWizFlatToolBarCtrl::SetSkinName(LPCTSTR lpszSkinName)
{
	CWizCustomCommandToolBar::SetSkinName(lpszSkinName);
	//
	m_crShadow = WizGetSkin()->GetCustomColor(lpszSkinName, CWizSkin::crToolBarShadow, m_crShadow);
}

void CWizFlatToolBarCtrl::DrawBackground(CDCHandle dc, const CRect& rc)
{
	if (m_bDrawShadow)
	{
		CRect rcBackground = rc;
		rcBackground.bottom -= 1;
		//
		dc.FillSolidRect(&rcBackground, GetBackgroundColor());
		//
		dc.FillSolidRect(rc.left, rc.bottom - 1, rc.right, rc.bottom - 0, m_crShadow);
	}
	else
	{
		dc.FillSolidRect(&rc, GetBackgroundColor());
	}
	//
	if (IsDrawTopBorder())
	{
		CRect rcBorder = rc;
		rcBorder.bottom = rcBorder.top + 1;
		dc.FillSolidRect(&rcBorder, GetBorderColor());
	}
}
//
void CWizFlatToolBarCtrl::SetDrawShadow(BOOL b)
{
	m_bDrawShadow = b;
	//
	if (IsWindow())
	{
		Invalidate();
	}
}


int WizGetTaskBarHeight(int& nAlign)
{
	const LPCTSTR lpszClassName = _T("Shell_TrayWnd");
	HWND hWndTaskBar = ::FindWindow(lpszClassName, NULL);
	if (hWndTaskBar)
	{
		RECT rc;
		::GetWindowRect(hWndTaskBar, &rc);
		if (rc.top < 10 && rc.left < 10)
		{
			nAlign = rc.right > 400 ? WIZ_ALIGN_TOP : WIZ_ALIGN_LEFT;
		}
		else
		{
			nAlign =  rc.left < 10 ? WIZ_ALIGN_BOTTOM : WIZ_ALIGN_RIGHT;
		}
		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
		switch (nAlign)
		{
		case WIZ_ALIGN_TOP:
			return rc.bottom;
		case WIZ_ALIGN_LEFT:
			return rc.right;
		case WIZ_ALIGN_BOTTOM:
			return nScreenHeight - rc.top;
		case WIZ_ALIGN_RIGHT:
			return nScreenWidth - rc.left;
		}
		return min(rc.bottom - rc.top, rc.right - rc.left);
	}
	return 30;
}

void WizSetInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex, HWND hWnd)
{
	WizRegWriteInt64(HKEY_CURRENT_USER, lpszRegKey, WizIntToStr(nInfoWndIndex), __int64(hWnd));
}

BOOL WizIsInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex)
{
	__int64 nVal = WizRegReadInt64Def(HKEY_CURRENT_USER, lpszRegKey, WizIntToStr(nInfoWndIndex), 0);
	if (!nVal)
		return FALSE;
	//
	return ::IsWindow((HWND)nVal);
}

RECT WizGetInfoWindowRect(HWND hwnd, LPCTSTR lpszRegKey, int& nInfoWndIndex)
{
	nInfoWndIndex = 0;
	while (1)
	{
		if (!WizIsInfoWindowIndexVisible(lpszRegKey, nInfoWndIndex))
			break;
		//
		nInfoWndIndex++;
	}
	//
	int nAlign = WIZ_ALIGN_BOTTOM;
	int nTaskBarHeight = WizGetTaskBarHeight(nAlign) + 4;
	//
	RECT rc;
	GetWindowRect(hwnd, &rc);
	int nWidth = rc.right - rc.left;
	int nHeight = rc.bottom - rc.top;
	//
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//
	int nScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL) + 4;
	//
	int nX = 0;
	int nY = 0;
	//
	if (nAlign == WIZ_ALIGN_BOTTOM)
	{
		nX = nScreenWidth - nWidth - nScrollBarWidth;
		nY = nScreenHeight - nHeight - nTaskBarHeight;
		nY -= (nInfoWndIndex * nHeight);
	}
	else if (nAlign == WIZ_ALIGN_TOP)
	{
		nX = nScreenWidth - nWidth - nScrollBarWidth;
		nY = nTaskBarHeight;
		nY += (nInfoWndIndex * nHeight);
	}
	else if (nAlign == WIZ_ALIGN_LEFT)
	{
		nX = nTaskBarHeight;
		nY = nScreenHeight - nHeight;
		nY -= (nInfoWndIndex * nHeight);
	}
	else if (nAlign == WIZ_ALIGN_RIGHT)
	{
		nX = nScreenWidth - nWidth - nTaskBarHeight;
		nY = nScreenHeight - nHeight;
		nY -= (nInfoWndIndex * nHeight);
	}
	//
	rc.left = nX;
	rc.top = nY;
	rc.right = rc.left + nWidth;
	rc.bottom = rc.top + nHeight;
	//
	return rc;
}





CWizSkinHeaderCtrl::CWizSkinHeaderCtrl()
{
	::WizCreateUIFont(m_font);
	m_crBackground = ::WizGetSkin()->GetItemColor(CWizSkin::wizisNormal);
	m_crBackgroundHot = ::WizGetSkin()->GetItemColor(CWizSkin::wizisSelectedNoFocus);
	m_bMouseOver = FALSE;
	m_bAsc = TRUE;
}
LRESULT CWizSkinHeaderCtrl::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	if (!m_bMouseOver)
	{
		m_bMouseOver = TRUE;
		Invalidate();
		StartTrackMouseLeave();
	}
	//
	//
	bHandled = FALSE;
	return 1;
}

LRESULT CWizSkinHeaderCtrl::OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_bMouseOver)
	{
		m_bMouseOver = FALSE;
		Invalidate();
	}
	return 0;
}

//
LRESULT CWizSkinHeaderCtrl::OnSkinChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetSkinName(m_strSkinName);
	return 0;
}

BOOL CWizSkinHeaderCtrl::StartTrackMouseLeave()
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	return _TrackMouseEvent(&tme);
}
BOOL CWizSkinHeaderCtrl::IsMouseHover() const
{
	if (m_bMouseOver)
		return TRUE;
	//
	return FALSE;
}
//
void CWizSkinHeaderCtrl::DoPaint( CDCHandle dcPaint )
{
	CRect rc;
	GetClientRect(&rc);
	dcPaint.FillSolidRect(&rc, IsMouseHover() ? m_crBackgroundHot : m_crBackground);
	//
	if (0 == GetItemCount())
		return;
	//
	dcPaint.SelectFont(m_font);
	//
	TCHAR szText[1024] = {0};
	HDITEM item;
	ZeroMemory(&item, sizeof(HDITEM));
	item.mask = HDI_TEXT;
	item.pszText = szText;
	item.cchTextMax = 1024;
	GetItem(0, &item);
	//
	CSize sizeText;
	dcPaint.GetTextExtent(szText, -1, &sizeText);
	//
	CRect rcButton(rc.left + 4, rc.top + 1, rc.right - 4, rc.bottom - 1);
	//
	CRect rcText = rcButton;
	rcText.right -= 16;
	rcText.left += 4;
	//
	if (rcText.Width() > sizeText.cx)
	{
		rcText.right = rcText.left + sizeText.cx + 2;
	}
	//
	CRect rcDropdown = rcButton;
	rcDropdown.left = rcText.right;
	rcDropdown.right = rcDropdown.left + 16;
	//
	//
	if (m_bAsc)
	{
		WizGetSkin()->DrawDropDownArrow2(dcPaint, rcDropdown, WizGetSkin()->GetWindowTextColor());
	}
	else
	{
		WizGetSkin()->DrawDropDownArrow(dcPaint, rcDropdown, WizGetSkin()->GetWindowTextColor());
	}
	//
	dcPaint.SetBkMode(TRANSPARENT);
	dcPaint.DrawText(szText, -1, &rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	//
}
void CWizSkinHeaderCtrl::SetSkinName(LPCTSTR lpszSkinName)
{
	m_strSkinName = lpszSkinName;
	//
	CWizSkin* pSkin = WizGetSkin();
	COLORREF crDefault = pSkin->GetWindowColor();
	COLORREF crDefaultHot = pSkin->GetItemColor(CWizSkin::wizisSelectedNoFocus);
	//
	crDefault = pSkin->GetColor(m_strSkinName + _T("_WindowBackground"), crDefault);
	crDefaultHot = pSkin->GetCustomColor(lpszSkinName, CWizSkin::crItemSelectedNoFocus, crDefaultHot);
	//
	m_crBackground = pSkin->GetColor(m_strSkinName + _T("_HeaderBackground"), crDefault);;	
	m_crBackgroundHot = pSkin->GetColor(m_strSkinName + _T("_HeaderBackgroundHot"), crDefaultHot);;	
}
void CWizSkinHeaderCtrl::SetAsc(BOOL b)
{
	m_bAsc = b;
	if (IsWindow())
	{
		Invalidate();
	}
}
//
void CWizSkinHeaderCtrl::SetText(LPCTSTR lpszText)
{
	HDITEM item;
	ZeroMemory(&item, sizeof(HDITEM));
	item.mask = HDI_TEXT;
	item.pszText = (LPTSTR)lpszText;
	item.cchTextMax = (int)_tcslen(lpszText);
	SetItem(0, &item);
}
