#ifndef _WIZHTMLBASE_H_
#define _WIZHTMLBASE_H_

#pragma once

#define wizHTMLTagStyleEnd		0x01

#define WizHTMLIsQuot(x)   ((x) == _T('\'') || (x) == _T('"'))


UINT WizHTMLGetTagStyle(LPCTSTR lpszTag);
BOOL WizHTMLGetTagName(LPCTSTR lpszTag, LPTSTR lpszName, size_t nSize);
BOOL WizHTMLGetTagValue(LPCTSTR lpszTag, LPCTSTR lpszValueName, LPTSTR pszValue, size_t nSize);
BOOL WizHTMLSetTagValue(LPTSTR pszTag, size_t nSize, LPCTSTR lpszValueName, LPCTSTR lpszValue);
BOOL WizHTMLDeleteTagValue(LPTSTR pszTag, LPCTSTR lpszValueName);
BOOL WizHTMLGetTagEvent(LPCTSTR lpszTag, LPTSTR lpszEvent, size_t nBufferSize);
LPCTSTR WizHTMLFindEndOfQuotInBlockScriptSource(LPCTSTR p, TCHAR chQuot);


#ifdef __CSTRINGT_H__
BOOL WizHTMLGetTagValue(LPCTSTR lpszTag, LPCTSTR lpszValueName, CString& strValue);
void WizHTMLDecodeInplace(CString& strText);

//
#define wizHTMLTagStyleExEnd		0x01
#define wizHTMLTagStyleExBegin		0x02

UINT WizHTMLGetTagStyleEx(LPCTSTR lpszTag);
//
#endif



BOOL WizHTMLGetBodyTextWithoutBodyTag(LPCTSTR lpszText, CString& strRet);
LPCTSTR WizGetHtmlContentHiddenTagBegin();
LPCTSTR WizGetHtmlContentHiddenTagEnd();
BOOL WizHtmlGetContentByHiddenTag(const CString& strHtmlText, CString& strContent);
BOOL WizHtmlContentAppendHiddenTag(CString& strContent);
BOOL WizHtmlGetContentByHiddenTagWithHiddenTag(const CString& strHtmlText, CString& strContent);
BOOL WizHtmlContentInsertIntoContent(CString& strContent, LPCTSTR lpszHtml);
BOOL WizHTMLGetHeadText(LPCTSTR lpszText, CString& strRet);
CString WizHTMLGetTitleFromText(LPCTSTR lpszText);
BOOL WizHTMLSetTitleToText(CString& strText, LPCTSTR lpszTitle);
CString WizHTMLGetTitleFromFile(LPCTSTR lpszFileName);
BOOL WizHTMLSetTitleToFile(LPCTSTR lpszFileName, LPCTSTR lpszTitle);
void WizHTMLInsertTextInHead(LPCTSTR lpszText, CString& strHTML);
void WizHTMLInsertTextInHead2(LPCTSTR lpszText, CString& strHTML);

struct WIZHTMLIMAGEDATA
{
	CString strURL;
	CString strText;
	CString strFileName;
};

typedef std::vector<WIZHTMLIMAGEDATA> CWizHTMLImageDataArray;

BOOL WizHTMLImageInArray(const WIZHTMLIMAGEDATA& data, const CWizHTMLImageDataArray& arrayImages);

void WizHTMLInsertTextAfterBodyA(LPCSTR lpszText, CStringA& strHTML);
void WizHTMLInsertTextAfterBodyW(LPCWSTR lpszText, CStringW& strHTML);

#ifdef _UNICODE
#define WizHTMLInsertTextAfterBody WizHTMLInsertTextAfterBodyW
#else
#define WizHTMLInsertTextAfterBody WizHTMLInsertTextAfterBodyA
#endif



BOOL WizHTMLLinkInArray(const WIZHTMLLINKDATA& data, const CWizHTMLLinkDataArray& arrayLinks);
void WizHTMLLinkRemoveMultiLinks(CWizHTMLLinkDataArray& arrayLinks);



struct WIZHTMLRESOURCEFILEDATA
{
	CString strURL;
	CString strFileName;
	CComPtr<IStream> spStream;
};

typedef std::vector<WIZHTMLRESOURCEFILEDATA> CWizHTMLResourceFileDataArray;


struct WIZHTMLURLANDFILEDATA
{
	CString strURL;
	CString strFileName;
	//
	WIZHTMLURLANDFILEDATA()
	{
	}
	//
	WIZHTMLURLANDFILEDATA(LPCTSTR lpszURL, LPCTSTR lpszFileName)
	{
		strURL = lpszURL;
		strFileName = lpszFileName;
	}
};

class CWizHTMLURLAndFileDataArray : public std::vector<WIZHTMLURLANDFILEDATA>
{
public:
	BOOL LoadFromIni(LPCTSTR lpszText);
	BOOL SaveToIni(CString& strText) const;
};

intptr_t WizHTMLURLAndFileIndexOfURL(const CWizHTMLURLAndFileDataArray& arrayFiles, LPCTSTR lpszURL);
CString WizURLAndFileGetFileNameByURL(const CWizHTMLURLAndFileDataArray& arrayFiles, LPCTSTR lpszURL);

#define WIZHTMLFLASHDATA			WIZHTMLURLANDFILEDATA
#define CWizHTMLFlashDataArray		CWizHTMLURLAndFileDataArray

BOOL WizHTMLFlashInArray(const WIZHTMLFLASHDATA& data, const CWizHTMLFlashDataArray& arrayLinks);




struct WIZHTMLFRAMEDATA
{
	CString strURL;
	CString strName;
	CString strID;
	CString strExtName;
	CString strFileName;
	CString strIncludeScriptFileName;
	CString strNoScriptFileName;
	//
	CString strResultText;
	//
	int nDepth;
	//
	WIZHTMLFRAMEDATA()
	{
		nDepth = 0;
	}
};


class CWizFrameArray 
	: public std::vector<WIZHTMLFRAMEDATA>
{
public:
	intptr_t IndexOfURL(LPCTSTR lpszURL) const
	{
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strURL == lpszURL)
				return it - begin();
		}
		return -1;
	}
	intptr_t FindByName(LPCTSTR lpszName) const
	{
		if (!lpszName)
			return -1;
		//
		if (_tcslen(lpszName) == 0)
			return -1;
		//
		//注意：必须检查同样的name，在浏览器内有几个。
		//如果多于1个，则会有同名的frame，但是url不同（可能参数不同）
		//无法判断究竟属于哪一个。因此返回-1
		//
		if (GetCountOfName(lpszName) != 1)
			return -1;
		//
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strName == lpszName)
				return it - begin();
		}
		return -1;
	}
	intptr_t FindByExtName(LPCTSTR lpszExtName) const
	{
		if (!lpszExtName)
			return -1;
		//
		if (_tcslen(lpszExtName) == 0)
			return -1;
		//
		//注意：必须检查同样的name，在浏览器内有几个。
		//如果多于1个，则会有同名的frame，但是url不同（可能参数不同）
		//无法判断究竟属于哪一个。因此返回-1
		//
		if (GetCountOfExtName(lpszExtName) != 1)
			return -1;
		//
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strExtName == lpszExtName)
				return it - begin();
		}
		return -1;
	}
	intptr_t FindByID(LPCTSTR lpszID) const
	{
		if (!lpszID)
			return -1;
		//
		if (_tcslen(lpszID) == 0)
			return -1;
		//
		//注意：必须检查同样的name，在浏览器内有几个。
		//如果多于1个，则会有同名的frame，但是url不同（可能参数不同）
		//无法判断究竟属于哪一个。因此返回-1
		//
		if (GetCountOfID(lpszID) != 1)
			return -1;
		//
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strID == lpszID)
				return it - begin();
		}
		return -1;
	}
	intptr_t FindByFileName(LPCTSTR lpszFileName) const
	{
		if (_tcslen(lpszFileName) == 0)
			return -1;
		CString strFileName = WizExtractFileName(lpszFileName);
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (WizExtractFileName(it->strFileName).CompareNoCase(strFileName) == 0)
				return it - begin();
		}
		return -1;
	}
protected:
	CString GetNameOfURL(LPCTSTR lpszURL)
	{
		CString strName;
		//
		CWizURL url(lpszURL);
		if (url.GetNameOfURL(strName))
		{
			strName = WizExtractFileTitle(strName) + _T(".htm");
			//
			if (FindByFileName(strName) == -1)
				return strName;
		}
		//
		static bool bFirst = true;
		if (bFirst)
		{
			srand(GetTickCount());
			bFirst = false;
		}
		//
		return WizIntToStr(GetTickCount()) + _T("_") + WizIntToStr(rand()) + _T(".htm");
	}
	size_t GetCountOfName(LPCTSTR lpszName) const
	{
		if (!lpszName)
			return 0;
		//
		size_t nCount = 0;
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strName == lpszName)
				nCount++;
		}
		return nCount;
	}
	size_t GetCountOfExtName(LPCTSTR lpszExtName) const
	{
		if (!lpszExtName)
			return 0;
		//
		size_t nCount = 0;
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strExtName == lpszExtName)
				nCount++;
		}
		return nCount;
	}
	size_t GetCountOfID(LPCTSTR lpszID) const
	{
		if (!lpszID)
			return 0;
		//
		size_t nCount = 0;
		for (const_iterator it = begin(); it < end(); it++)
		{
			if (it->strID == lpszID)
				nCount++;
		}
		return nCount;
	}
public:
	BOOL SaveToFile(LPCTSTR lpszFileName)
	{
		CWizXMLDocument doc;
		//
		CWizXMLNode nodeRoot;
		if (!doc.AppendChild(_T("WizFrameArray"), nodeRoot))
			return FALSE;
		//
		for (const_iterator it = begin();it != end(); it++)
		{
			const WIZHTMLFRAMEDATA& data = *it;
			//
			CWizXMLNode nodeFrame;
			if (!nodeRoot.AppendChild(_T("Frame"), nodeFrame))
				return FALSE;
			//
			nodeFrame.SetAttributeText(_T("URL"), data.strURL);
			nodeFrame.SetAttributeText(_T("Name"), data.strName);
			nodeFrame.SetAttributeText(_T("ID"), data.strID);
			nodeFrame.SetAttributeText(_T("ExtName"), data.strExtName);
			nodeFrame.SetAttributeText(_T("FileName"), data.strFileName);
			nodeFrame.SetAttributeText(_T("IncludeScriptFileName"), data.strIncludeScriptFileName);
			nodeFrame.SetAttributeText(_T("NoScriptFileName"), data.strNoScriptFileName);
			nodeFrame.SetAttributeInt(_T("Depth"), data.nDepth);
		}
		//
		return doc.ToUnicodeFile(lpszFileName);
	}
	BOOL LoadFromFile(LPCTSTR lpszFileName)
	{
		CWizXMLDocument doc;
		if (!doc.LoadFromFile(lpszFileName))
			return FALSE;
		//
		//
		CWizXMLNode nodeRoot;
		if (!doc.FindChildNode(_T("WizFrameArray"), nodeRoot))
			return FALSE;
		//
		std::vector<CWizXMLNode> arrayFrames;
		if (!nodeRoot.GetAllChildNodes(arrayFrames))
			return FALSE;
		//
		for (std::vector<CWizXMLNode>::iterator it = arrayFrames.begin();it != arrayFrames.end(); it++)
		{
			CWizXMLNode& nodeFrame = *it;
			//
			WIZHTMLFRAMEDATA data;
			//
			nodeFrame.GetAttributeText(_T("URL"), data.strURL);
			nodeFrame.GetAttributeText(_T("Name"), data.strName);
			nodeFrame.GetAttributeText(_T("ID"), data.strID);
			nodeFrame.GetAttributeText(_T("ExtName"), data.strExtName);
			nodeFrame.GetAttributeText(_T("FileName"), data.strFileName);
			nodeFrame.GetAttributeText(_T("IncludeScriptFileName"), data.strIncludeScriptFileName);
			nodeFrame.GetAttributeText(_T("NoScriptFileName"), data.strNoScriptFileName);
			nodeFrame.GetAttributeInt(_T("Depth"), data.nDepth);
			//
			push_back(data);
		}
		//
		return !empty();
	}
	//
public:
	BOOL LoadFromIni(LPCTSTR lpszText);
	BOOL SaveToIni(CString& strText) const;
};



#define WIZ_URL_SERIAL_WILDCARD  _T("(*)")


BOOL WizHTMLRemoveDocType(CStringW& strHtml);
BOOL WizHTMLRemoveBodyInnerText(CString& strHtml);


void WizHTMLInsertTextBeforeBody(LPCTSTR lpszText, CString& strHTML);
CString WizHTMLGetFilesTextToInsert(LPCTSTR lpszHtmlFilePath, LPCTSTR lpszFilesTitle, const CWizStdStringArray& arrayFiles);




BOOL WizHtmlUnicodeToAnsi(const wchar_t* lpszText, CStringA& strText, CString* pstrCharset = NULL, BOOL bForceNotUseUnicode = FALSE);
BOOL WizTextUnicodeToAnsi(const wchar_t* lpszText, CStringA& strText, CString* pstrCharset = NULL, BOOL bForceNotUseUnicode = FALSE);


BOOL WizHtmlUnicodeToUtf8(const wchar_t* lpszText, CStringA& strText);
BOOL WizTextUnicodeToUtf8(const wchar_t* lpszText, CStringA& strText);

BOOL WizHtmlReplaceCharset(CStringA& strText, LPCTSTR lpszCharset);


BOOL WizConvertFlashToHTML(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL WizConvertFlashToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertFlashToHTMLFile_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
CString CyberArticleGetConvertFlashToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath);
BOOL CyberArticleConvertFlashToHTML(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL CyberArticleConvertFlashToHTMLFile(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHTMLFileName);
BOOL WizConvertImageToHTML(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
CString CyberArticleGetConvertImageToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath);
BOOL CyberArticleConvertImageToHTML(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL CyberArticleConvertImageToHTMLFile(LPCTSTR lpszCyberArticleAppPath, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHTMLFileName);
BOOL WizConvertImageToHtmlFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertImageToHtmlFile_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertImageToHTML_DefaultTemplate(LPCTSTR lpszFileName, LPCTSTR lpszTitle, CStringW& strHTML);
BOOL WizConvertTextToHTML_ForPaste_ProcessSpaceBeginEnd(int nBegin, CStringW& strLine, const CStringW& strTab);
BOOL WizConvertTextToHTML_ForPaste_ProcessBeginSpace(CStringW& strLine, const CStringW& strTab);
BOOL WizConvertTextToHTML_ForPaste_ProcessEndSpace(CStringW& strLine, const CStringW& strTab);
BOOL WizConvertTextToHTML_ForPaste_Line(CStringW& strLine, const CStringW& strTab, const CStringW& strMidTab);
BOOL WizConvertTextToHTML_ForPaste(CStringW& strText, int nTabSize);
CString CyberArticleGetConvertTextToHTMLTemplateFileName(LPCTSTR lpszCyberArticleAppPath);
BOOL WizConvertTextToHTML_Template(LPCWSTR lpszTemplateText, LPCWSTR lpszTitle, CStringW& strText);
BOOL WizConvertTextToHTML(LPCTSTR lpszTemplateFileName, LPCWSTR lpszTitle, CStringW& strText);
BOOL WizConvertTextToHTML_DefaultTemplate(LPCWSTR lpszTitle, CStringW& strText);
BOOL WizConvertTextFileToHTMLFile(LPCTSTR lpszTemplateFileName, LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName);
BOOL WizConvertTextFileToHTMLFile_DefaultTemplate(LPCTSTR lpszTextFileName, LPCWSTR lpszTitle, LPCTSTR lpszHtmlFileName);




#endif