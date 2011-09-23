

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Sep 21 12:38:43 2011
 */
/* Compiler settings for .\WizKMControls.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WizKMControls_i_h__
#define __WizKMControls_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWizDocumentListCtrl_FWD_DEFINED__
#define __IWizDocumentListCtrl_FWD_DEFINED__
typedef interface IWizDocumentListCtrl IWizDocumentListCtrl;
#endif 	/* __IWizDocumentListCtrl_FWD_DEFINED__ */


#ifndef __IWizDocumentAttachmentListCtrl_FWD_DEFINED__
#define __IWizDocumentAttachmentListCtrl_FWD_DEFINED__
typedef interface IWizDocumentAttachmentListCtrl IWizDocumentAttachmentListCtrl;
#endif 	/* __IWizDocumentAttachmentListCtrl_FWD_DEFINED__ */


#ifndef __IWizCommonUI_FWD_DEFINED__
#define __IWizCommonUI_FWD_DEFINED__
typedef interface IWizCommonUI IWizCommonUI;
#endif 	/* __IWizCommonUI_FWD_DEFINED__ */


#ifndef __IWizBatchDownloader_FWD_DEFINED__
#define __IWizBatchDownloader_FWD_DEFINED__
typedef interface IWizBatchDownloader IWizBatchDownloader;
#endif 	/* __IWizBatchDownloader_FWD_DEFINED__ */


#ifndef __IWizProgressWindow_FWD_DEFINED__
#define __IWizProgressWindow_FWD_DEFINED__
typedef interface IWizProgressWindow IWizProgressWindow;
#endif 	/* __IWizProgressWindow_FWD_DEFINED__ */


#ifndef __IWizSyncProgressDlg_FWD_DEFINED__
#define __IWizSyncProgressDlg_FWD_DEFINED__
typedef interface IWizSyncProgressDlg IWizSyncProgressDlg;
#endif 	/* __IWizSyncProgressDlg_FWD_DEFINED__ */


#ifndef __IWizHtmlDialogExternal_FWD_DEFINED__
#define __IWizHtmlDialogExternal_FWD_DEFINED__
typedef interface IWizHtmlDialogExternal IWizHtmlDialogExternal;
#endif 	/* __IWizHtmlDialogExternal_FWD_DEFINED__ */


#ifndef __IWizCategoryCtrl_FWD_DEFINED__
#define __IWizCategoryCtrl_FWD_DEFINED__
typedef interface IWizCategoryCtrl IWizCategoryCtrl;
#endif 	/* __IWizCategoryCtrl_FWD_DEFINED__ */


#ifndef __WizDocumentListCtrl_FWD_DEFINED__
#define __WizDocumentListCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentListCtrl WizDocumentListCtrl;
#else
typedef struct WizDocumentListCtrl WizDocumentListCtrl;
#endif /* __cplusplus */

#endif 	/* __WizDocumentListCtrl_FWD_DEFINED__ */


#ifndef __WizDocumentAttachmentListCtrl_FWD_DEFINED__
#define __WizDocumentAttachmentListCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentAttachmentListCtrl WizDocumentAttachmentListCtrl;
#else
typedef struct WizDocumentAttachmentListCtrl WizDocumentAttachmentListCtrl;
#endif /* __cplusplus */

#endif 	/* __WizDocumentAttachmentListCtrl_FWD_DEFINED__ */


#ifndef __WizCommonUI_FWD_DEFINED__
#define __WizCommonUI_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizCommonUI WizCommonUI;
#else
typedef struct WizCommonUI WizCommonUI;
#endif /* __cplusplus */

#endif 	/* __WizCommonUI_FWD_DEFINED__ */


#ifndef __WizBatchDownloader_FWD_DEFINED__
#define __WizBatchDownloader_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizBatchDownloader WizBatchDownloader;
#else
typedef struct WizBatchDownloader WizBatchDownloader;
#endif /* __cplusplus */

#endif 	/* __WizBatchDownloader_FWD_DEFINED__ */


#ifndef __WizProgressWindow_FWD_DEFINED__
#define __WizProgressWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizProgressWindow WizProgressWindow;
#else
typedef struct WizProgressWindow WizProgressWindow;
#endif /* __cplusplus */

#endif 	/* __WizProgressWindow_FWD_DEFINED__ */


#ifndef __WizSyncProgressDlg_FWD_DEFINED__
#define __WizSyncProgressDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizSyncProgressDlg WizSyncProgressDlg;
#else
typedef struct WizSyncProgressDlg WizSyncProgressDlg;
#endif /* __cplusplus */

#endif 	/* __WizSyncProgressDlg_FWD_DEFINED__ */


#ifndef __WizHtmlDialogExternal_FWD_DEFINED__
#define __WizHtmlDialogExternal_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizHtmlDialogExternal WizHtmlDialogExternal;
#else
typedef struct WizHtmlDialogExternal WizHtmlDialogExternal;
#endif /* __cplusplus */

#endif 	/* __WizHtmlDialogExternal_FWD_DEFINED__ */


#ifndef __WizCategoryCtrl_FWD_DEFINED__
#define __WizCategoryCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizCategoryCtrl WizCategoryCtrl;
#else
typedef struct WizCategoryCtrl WizCategoryCtrl;
#endif /* __cplusplus */

#endif 	/* __WizCategoryCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWizDocumentListCtrl_INTERFACE_DEFINED__
#define __IWizDocumentListCtrl_INTERFACE_DEFINED__

/* interface IWizDocumentListCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentListCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C128ECE0-A006-4E57-8054-4CBC49818231")
    IWizDocumentListCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventsListener( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EventsListener( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_App( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_App( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedDocuments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedDocuments( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StateSection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StateSection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisableContextMenu( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisableContextMenu( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SortBy( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SortBy( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SortOrder( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SortOrder( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParentFolder( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDocuments( 
            /* [in] */ IDispatch *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDocuments2( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ BSTR bstrSortBy,
            /* [in] */ BSTR bstrSortOrder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDocuments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Options( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Options( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecondLineType( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecondLineType( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentListCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentListCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentListCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentListCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentListCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentListCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventsListener )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EventsListener )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_App )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_App )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedDocuments )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedDocuments )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StateSection )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StateSection )( 
            IWizDocumentListCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisableContextMenu )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisableContextMenu )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SortBy )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SortBy )( 
            IWizDocumentListCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SortOrder )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SortOrder )( 
            IWizDocumentListCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParentFolder )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDocuments )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *pDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDocuments2 )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ BSTR bstrSortBy,
            /* [in] */ BSTR bstrSortOrder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWizDocumentListCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDocuments )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            IWizDocumentListCtrl * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecondLineType )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecondLineType )( 
            IWizDocumentListCtrl * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IWizDocumentListCtrlVtbl;

    interface IWizDocumentListCtrl
    {
        CONST_VTBL struct IWizDocumentListCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentListCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentListCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentListCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentListCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentListCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentListCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentListCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentListCtrl_get_EventsListener(This,pVal)	\
    ( (This)->lpVtbl -> get_EventsListener(This,pVal) ) 

#define IWizDocumentListCtrl_put_EventsListener(This,newVal)	\
    ( (This)->lpVtbl -> put_EventsListener(This,newVal) ) 

#define IWizDocumentListCtrl_get_App(This,pVal)	\
    ( (This)->lpVtbl -> get_App(This,pVal) ) 

#define IWizDocumentListCtrl_put_App(This,newVal)	\
    ( (This)->lpVtbl -> put_App(This,newVal) ) 

#define IWizDocumentListCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizDocumentListCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizDocumentListCtrl_get_SelectedDocuments(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedDocuments(This,pVal) ) 

#define IWizDocumentListCtrl_put_SelectedDocuments(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedDocuments(This,newVal) ) 

#define IWizDocumentListCtrl_get_StateSection(This,pVal)	\
    ( (This)->lpVtbl -> get_StateSection(This,pVal) ) 

#define IWizDocumentListCtrl_put_StateSection(This,newVal)	\
    ( (This)->lpVtbl -> put_StateSection(This,newVal) ) 

#define IWizDocumentListCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizDocumentListCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizDocumentListCtrl_get_DisableContextMenu(This,pVal)	\
    ( (This)->lpVtbl -> get_DisableContextMenu(This,pVal) ) 

#define IWizDocumentListCtrl_put_DisableContextMenu(This,newVal)	\
    ( (This)->lpVtbl -> put_DisableContextMenu(This,newVal) ) 

#define IWizDocumentListCtrl_get_SortBy(This,pVal)	\
    ( (This)->lpVtbl -> get_SortBy(This,pVal) ) 

#define IWizDocumentListCtrl_put_SortBy(This,newVal)	\
    ( (This)->lpVtbl -> put_SortBy(This,newVal) ) 

#define IWizDocumentListCtrl_get_SortOrder(This,pVal)	\
    ( (This)->lpVtbl -> get_SortOrder(This,pVal) ) 

#define IWizDocumentListCtrl_put_SortOrder(This,newVal)	\
    ( (This)->lpVtbl -> put_SortOrder(This,newVal) ) 

#define IWizDocumentListCtrl_get_ParentFolder(This,pVal)	\
    ( (This)->lpVtbl -> get_ParentFolder(This,pVal) ) 

#define IWizDocumentListCtrl_SetDocuments(This,pDisp)	\
    ( (This)->lpVtbl -> SetDocuments(This,pDisp) ) 

#define IWizDocumentListCtrl_SetDocuments2(This,pDisp,bstrSortBy,bstrSortOrder)	\
    ( (This)->lpVtbl -> SetDocuments2(This,pDisp,bstrSortBy,bstrSortOrder) ) 

#define IWizDocumentListCtrl_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IWizDocumentListCtrl_GetDocuments(This,pVal)	\
    ( (This)->lpVtbl -> GetDocuments(This,pVal) ) 

#define IWizDocumentListCtrl_get_Options(This,pVal)	\
    ( (This)->lpVtbl -> get_Options(This,pVal) ) 

#define IWizDocumentListCtrl_put_Options(This,newVal)	\
    ( (This)->lpVtbl -> put_Options(This,newVal) ) 

#define IWizDocumentListCtrl_get_SecondLineType(This,pVal)	\
    ( (This)->lpVtbl -> get_SecondLineType(This,pVal) ) 

#define IWizDocumentListCtrl_put_SecondLineType(This,newVal)	\
    ( (This)->lpVtbl -> put_SecondLineType(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentListCtrl_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentAttachmentListCtrl_INTERFACE_DEFINED__
#define __IWizDocumentAttachmentListCtrl_INTERFACE_DEFINED__

/* interface IWizDocumentAttachmentListCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentAttachmentListCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39B2717D-7FDA-4EDD-91A4-0173FD35B871")
    IWizDocumentAttachmentListCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventsListener( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EventsListener( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_App( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_App( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Document( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedAttachments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedAttachments( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAttachments( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAttachments2( 
            /* [in] */ VARIANT *pvFiles) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentAttachmentListCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentAttachmentListCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentAttachmentListCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventsListener )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EventsListener )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_App )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_App )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Document )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedAttachments )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedAttachments )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAttachments )( 
            IWizDocumentAttachmentListCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAttachments2 )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT *pvFiles);
        
        END_INTERFACE
    } IWizDocumentAttachmentListCtrlVtbl;

    interface IWizDocumentAttachmentListCtrl
    {
        CONST_VTBL struct IWizDocumentAttachmentListCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentAttachmentListCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentAttachmentListCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentAttachmentListCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentAttachmentListCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentAttachmentListCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentAttachmentListCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentAttachmentListCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentAttachmentListCtrl_get_EventsListener(This,pVal)	\
    ( (This)->lpVtbl -> get_EventsListener(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_EventsListener(This,newVal)	\
    ( (This)->lpVtbl -> put_EventsListener(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_App(This,pVal)	\
    ( (This)->lpVtbl -> get_App(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_App(This,newVal)	\
    ( (This)->lpVtbl -> put_App(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_Document(This,pVal)	\
    ( (This)->lpVtbl -> get_Document(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Document(This,newVal)	\
    ( (This)->lpVtbl -> put_Document(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_SelectedAttachments(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedAttachments(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_SelectedAttachments(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedAttachments(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_AddAttachments(This)	\
    ( (This)->lpVtbl -> AddAttachments(This) ) 

#define IWizDocumentAttachmentListCtrl_AddAttachments2(This,pvFiles)	\
    ( (This)->lpVtbl -> AddAttachments2(This,pvFiles) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentAttachmentListCtrl_INTERFACE_DEFINED__ */


#ifndef __IWizCommonUI_INTERFACE_DEFINED__
#define __IWizCommonUI_INTERFACE_DEFINED__

/* interface IWizCommonUI */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizCommonUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B671315F-B6FE-4799-AE50-AEA0848FBA05")
    IWizCommonUI : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryUserAccount( 
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddDocumentToCalendar( 
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateCalendarEvent( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ DATE dtEvent,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EditCalendarEvent( 
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AboutBox( 
            /* [in] */ BSTR bstrModuleName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OptionsDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BackupDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccountsManagerDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChooseAccount( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIntValue( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIntValue2( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [in] */ LONG nMin,
            /* [in] */ LONG nMax,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckNewVersion( 
            /* [in] */ VARIANT_BOOL vbPrompt,
            /* [in] */ VARIANT_BOOL vbSilent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InputBox( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InputMultiLineText( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWindowsFile( 
            /* [in] */ VARIANT_BOOL vbOpen,
            /* [in] */ BSTR bstrFilter,
            /* [retval][out] */ BSTR *pbstrResultFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWindowsFolder( 
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ BSTR *pbtrFolderPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWizFolder( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWizDocument( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadTextFromFile( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveTextToFile( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrText,
            /* [in] */ BSTR bstrCharset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetValueFromIni( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pbstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueToIni( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetATempFileName( 
            /* [in] */ BSTR bstrFileExt,
            /* [retval][out] */ BSTR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSpecialFolder( 
            /* [in] */ BSTR bstrFolderName,
            /* [retval][out] */ BSTR *pbstrPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunExe( 
            /* [in] */ BSTR bstrExeFileName,
            /* [in] */ BSTR bstrParams,
            /* [in] */ VARIANT_BOOL vbWait,
            /* [retval][out] */ long *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumFiles( 
            /* [in] */ BSTR bstrPath,
            /* [in] */ BSTR bstrFileExt,
            /* [in] */ VARIANT_BOOL vbIncludeSubFolders,
            /* [retval][out] */ VARIANT *pvFiles) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumFolders( 
            /* [in] */ BSTR bstrPath,
            /* [retval][out] */ VARIANT *pvFolders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateActiveXObject( 
            /* [in] */ BSTR bstrProgID,
            /* [retval][out] */ IDispatch **ppObjDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetValueFromReg( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [retval][out] */ BSTR *pbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueToReg( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [in] */ BSTR bstrData,
            /* [in] */ BSTR bstrDataType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumRegValues( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvValueNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumRegKeys( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvKeys) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectTemplate( 
            /* [in] */ BSTR bstrTemplateType,
            /* [retval][out] */ BSTR *pbstrResultTemplateFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlTagGetAttributeValue( 
            /* [in] */ BSTR bstrHtmlTag,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [retval][out] */ BSTR *pbstrAttributeValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlExtractTags( 
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [in] */ BSTR bstrTagAttributeValue,
            /* [retval][out] */ VARIANT *pvTags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlEnumLinks( 
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ VARIANT *pvLinks) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlGetContent( 
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrContent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlConvertFileToHtmlFile( 
            /* [in] */ BSTR bstrSrcFileName,
            /* [retval][out] */ BSTR *pbstrHtmlFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlConvertZipFileToHtmlFile( 
            /* [in] */ BSTR bstrSrcZipFileName,
            /* [in] */ BSTR bstrDestHtmlFileName,
            /* [in] */ BSTR bstrHtmlTitle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OptionsDlg2( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectDay( 
            /* [in] */ DATE dtDefault,
            /* [retval][out] */ DATE *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReportSyncResult( 
            /* [in] */ LONGLONG hWnd,
            /* [in] */ VARIANT vDownloaded,
            /* [in] */ VARIANT vUploaded,
            /* [in] */ VARIANT vSkipped,
            /* [in] */ VARIANT vFailed) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyTextToClipboard( 
            /* [in] */ BSTR bstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PromptTrafficLimit( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [in] */ LONGLONG nLimit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccountSecurityDlg( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitEncryptionDlg( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ImportCertDlg( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnterPasswordDlg( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrInfo,
            /* [in] */ VARIANT_BOOL vbShowRememberPasswordButton,
            /* [out] */ VARIANT_BOOL *pvbRememberPassword,
            /* [retval][out] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryUserAccount2( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardToImage( 
            /* [in] */ OLE_HANDLE hwnd,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureScreen( 
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpCHM( 
            /* [in] */ BSTR bstrCHMFileName,
            /* [in] */ BSTR bstrTempPath,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ VARIANT *pvRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HyperlinkDlg( 
            /* [in] */ IDispatch *pdispDatabase,
            /* [in] */ IDispatch *pdispDocument,
            /* [in] */ IDispatch *pdispHtmlDocument,
            /* [in] */ BSTR bstrInitURL,
            /* [retval][out] */ BSTR *pbstrResultURL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectColor( 
            /* [in] */ BSTR bstrInitColor,
            /* [retval][out] */ BSTR *pbstrRetColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFontNames( 
            /* [retval][out] */ VARIANT *pvNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFont( 
            /* [in] */ BSTR bstrInit,
            /* [retval][out] */ BSTR *pbstrRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateWizObject( 
            /* [in] */ BSTR bstrObjectName,
            /* [retval][out] */ IDispatch **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScriptParamValue( 
            /* [in] */ BSTR bstrParamName,
            /* [retval][out] */ BSTR *pbstrVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadStringFromFile( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrStringName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE URLDownloadToText( 
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWizTags( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ IDispatch **ppTagCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CalendarDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccountInfoDlg( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIniSections( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ VARIANT *pvValueNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadStringFromFile2( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSectionName,
            /* [in] */ BSTR bstrStringName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowHtmlDialog( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrURL,
            /* [in] */ LONG nWidth,
            /* [in] */ LONG nHeight,
            /* [in] */ BSTR bstrExtOptions,
            /* [in] */ VARIANT vParam,
            /* [retval][out] */ VARIANT *pvRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseHtmlDialog( 
            /* [in] */ IDispatch *pdispHtmlDialogDocument,
            /* [in] */ VARIANT vRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowMessage( 
            /* [in] */ BSTR bstrText,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nType,
            /* [retval][out] */ LONG *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CombineURL( 
            /* [in] */ BSTR bstrBase,
            /* [in] */ BSTR bstrPart,
            /* [retval][out] */ BSTR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE URLDownloadToTempFile( 
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrTempFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EditDocument( 
            /* [in] */ IDispatch *pApp,
            /* [in] */ IDispatch *pEvents,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONGLONG *pnWindowHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewDocument( 
            /* [in] */ IDispatch *pApp,
            /* [in] */ IDispatch *pEvents,
            /* [in] */ IDispatch *pFolderDisp,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONGLONG *pnWindowHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearDocumentWindow( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateAccountDlg( 
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrRetDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddExistingAccountDlg( 
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrRetDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePasswordDlg( 
            /* [in] */ IDispatch *pDatabaseDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ProtectAccountDlg( 
            /* [in] */ IDispatch *pDatabaseDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RefreshDatabaseIndex( 
            /* [in] */ LONGLONG nWindowHandle,
            /* [in] */ IDispatch *pDatabaseDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizCommonUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizCommonUI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizCommonUI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizCommonUI * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizCommonUI * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizCommonUI * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizCommonUI * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizCommonUI * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryUserAccount )( 
            IWizCommonUI * This,
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddDocumentToCalendar )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateCalendarEvent )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ DATE dtEvent,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EditCalendarEvent )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AboutBox )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrModuleName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OptionsDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackupDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccountsManagerDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChooseAccount )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIntValue )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIntValue2 )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [in] */ LONG nMin,
            /* [in] */ LONG nMax,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckNewVersion )( 
            IWizCommonUI * This,
            /* [in] */ VARIANT_BOOL vbPrompt,
            /* [in] */ VARIANT_BOOL vbSilent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InputBox )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InputMultiLineText )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWindowsFile )( 
            IWizCommonUI * This,
            /* [in] */ VARIANT_BOOL vbOpen,
            /* [in] */ BSTR bstrFilter,
            /* [retval][out] */ BSTR *pbstrResultFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWindowsFolder )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ BSTR *pbtrFolderPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWizFolder )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWizDocument )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadTextFromFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveTextToFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrText,
            /* [in] */ BSTR bstrCharset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetValueFromIni )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pbstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueToIni )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetATempFileName )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileExt,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSpecialFolder )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFolderName,
            /* [retval][out] */ BSTR *pbstrPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RunExe )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrExeFileName,
            /* [in] */ BSTR bstrParams,
            /* [in] */ VARIANT_BOOL vbWait,
            /* [retval][out] */ long *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumFiles )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrPath,
            /* [in] */ BSTR bstrFileExt,
            /* [in] */ VARIANT_BOOL vbIncludeSubFolders,
            /* [retval][out] */ VARIANT *pvFiles);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumFolders )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrPath,
            /* [retval][out] */ VARIANT *pvFolders);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateActiveXObject )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrProgID,
            /* [retval][out] */ IDispatch **ppObjDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetValueFromReg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [retval][out] */ BSTR *pbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueToReg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [in] */ BSTR bstrData,
            /* [in] */ BSTR bstrDataType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumRegValues )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvValueNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumRegKeys )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvKeys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectTemplate )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTemplateType,
            /* [retval][out] */ BSTR *pbstrResultTemplateFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlTagGetAttributeValue )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlTag,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [retval][out] */ BSTR *pbstrAttributeValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlExtractTags )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [in] */ BSTR bstrTagAttributeValue,
            /* [retval][out] */ VARIANT *pvTags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlEnumLinks )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ VARIANT *pvLinks);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlGetContent )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrContent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlConvertFileToHtmlFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrSrcFileName,
            /* [retval][out] */ BSTR *pbstrHtmlFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlConvertZipFileToHtmlFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrSrcZipFileName,
            /* [in] */ BSTR bstrDestHtmlFileName,
            /* [in] */ BSTR bstrHtmlTitle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OptionsDlg2 )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectDay )( 
            IWizCommonUI * This,
            /* [in] */ DATE dtDefault,
            /* [retval][out] */ DATE *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReportSyncResult )( 
            IWizCommonUI * This,
            /* [in] */ LONGLONG hWnd,
            /* [in] */ VARIANT vDownloaded,
            /* [in] */ VARIANT vUploaded,
            /* [in] */ VARIANT vSkipped,
            /* [in] */ VARIANT vFailed);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyTextToClipboard )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PromptTrafficLimit )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [in] */ LONGLONG nLimit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccountSecurityDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitEncryptionDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ImportCertDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnterPasswordDlg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrInfo,
            /* [in] */ VARIANT_BOOL vbShowRememberPasswordButton,
            /* [out] */ VARIANT_BOOL *pvbRememberPassword,
            /* [retval][out] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryUserAccount2 )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClipboardToImage )( 
            IWizCommonUI * This,
            /* [in] */ OLE_HANDLE hwnd,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureScreen )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpCHM )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrCHMFileName,
            /* [in] */ BSTR bstrTempPath,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ VARIANT *pvRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HyperlinkDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pdispDatabase,
            /* [in] */ IDispatch *pdispDocument,
            /* [in] */ IDispatch *pdispHtmlDocument,
            /* [in] */ BSTR bstrInitURL,
            /* [retval][out] */ BSTR *pbstrResultURL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectColor )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrInitColor,
            /* [retval][out] */ BSTR *pbstrRetColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFontNames )( 
            IWizCommonUI * This,
            /* [retval][out] */ VARIANT *pvNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFont )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrInit,
            /* [retval][out] */ BSTR *pbstrRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateWizObject )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrObjectName,
            /* [retval][out] */ IDispatch **ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScriptParamValue )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrParamName,
            /* [retval][out] */ BSTR *pbstrVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadStringFromFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrStringName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *URLDownloadToText )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWizTags )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ IDispatch **ppTagCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CalendarDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccountInfoDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIniSections )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ VARIANT *pvValueNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadStringFromFile2 )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSectionName,
            /* [in] */ BSTR bstrStringName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowHtmlDialog )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrURL,
            /* [in] */ LONG nWidth,
            /* [in] */ LONG nHeight,
            /* [in] */ BSTR bstrExtOptions,
            /* [in] */ VARIANT vParam,
            /* [retval][out] */ VARIANT *pvRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseHtmlDialog )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pdispHtmlDialogDocument,
            /* [in] */ VARIANT vRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowMessage )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrText,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nType,
            /* [retval][out] */ LONG *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CombineURL )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrBase,
            /* [in] */ BSTR bstrPart,
            /* [retval][out] */ BSTR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *URLDownloadToTempFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrTempFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EditDocument )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pApp,
            /* [in] */ IDispatch *pEvents,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONGLONG *pnWindowHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewDocument )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pApp,
            /* [in] */ IDispatch *pEvents,
            /* [in] */ IDispatch *pFolderDisp,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONGLONG *pnWindowHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearDocumentWindow )( 
            IWizCommonUI * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateAccountDlg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrRetDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddExistingAccountDlg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrRetDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangePasswordDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ProtectAccountDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RefreshDatabaseIndex )( 
            IWizCommonUI * This,
            /* [in] */ LONGLONG nWindowHandle,
            /* [in] */ IDispatch *pDatabaseDisp);
        
        END_INTERFACE
    } IWizCommonUIVtbl;

    interface IWizCommonUI
    {
        CONST_VTBL struct IWizCommonUIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizCommonUI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizCommonUI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizCommonUI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizCommonUI_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizCommonUI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizCommonUI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizCommonUI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizCommonUI_QueryUserAccount(This,hWnd,pbstrUserName,pbstrPassword)	\
    ( (This)->lpVtbl -> QueryUserAccount(This,hWnd,pbstrUserName,pbstrPassword) ) 

#define IWizCommonUI_AddDocumentToCalendar(This,pDocumentDisp,pbRet)	\
    ( (This)->lpVtbl -> AddDocumentToCalendar(This,pDocumentDisp,pbRet) ) 

#define IWizCommonUI_CreateCalendarEvent(This,pDatabaseDisp,dtEvent,ppDocumentDisp)	\
    ( (This)->lpVtbl -> CreateCalendarEvent(This,pDatabaseDisp,dtEvent,ppDocumentDisp) ) 

#define IWizCommonUI_EditCalendarEvent(This,pDocumentDisp,pbRet)	\
    ( (This)->lpVtbl -> EditCalendarEvent(This,pDocumentDisp,pbRet) ) 

#define IWizCommonUI_AboutBox(This,bstrModuleName)	\
    ( (This)->lpVtbl -> AboutBox(This,bstrModuleName) ) 

#define IWizCommonUI_OptionsDlg(This,nFlags)	\
    ( (This)->lpVtbl -> OptionsDlg(This,nFlags) ) 

#define IWizCommonUI_BackupDlg(This,nFlags)	\
    ( (This)->lpVtbl -> BackupDlg(This,nFlags) ) 

#define IWizCommonUI_AccountsManagerDlg(This,nFlags)	\
    ( (This)->lpVtbl -> AccountsManagerDlg(This,nFlags) ) 

#define IWizCommonUI_ChooseAccount(This,nFlags,pbstrDatabasePath)	\
    ( (This)->lpVtbl -> ChooseAccount(This,nFlags,pbstrDatabasePath) ) 

#define IWizCommonUI_GetIntValue(This,bstrTitle,bstrDescription,nInitValue,pvbOK,pnRet)	\
    ( (This)->lpVtbl -> GetIntValue(This,bstrTitle,bstrDescription,nInitValue,pvbOK,pnRet) ) 

#define IWizCommonUI_GetIntValue2(This,bstrTitle,bstrDescription,nInitValue,nMin,nMax,pvbOK,pnRet)	\
    ( (This)->lpVtbl -> GetIntValue2(This,bstrTitle,bstrDescription,nInitValue,nMin,nMax,pvbOK,pnRet) ) 

#define IWizCommonUI_CheckNewVersion(This,vbPrompt,vbSilent)	\
    ( (This)->lpVtbl -> CheckNewVersion(This,vbPrompt,vbSilent) ) 

#define IWizCommonUI_InputBox(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText)	\
    ( (This)->lpVtbl -> InputBox(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText) ) 

#define IWizCommonUI_InputMultiLineText(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText)	\
    ( (This)->lpVtbl -> InputMultiLineText(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText) ) 

#define IWizCommonUI_SelectWindowsFile(This,vbOpen,bstrFilter,pbstrResultFileName)	\
    ( (This)->lpVtbl -> SelectWindowsFile(This,vbOpen,bstrFilter,pbstrResultFileName) ) 

#define IWizCommonUI_SelectWindowsFolder(This,bstrDescription,pbtrFolderPath)	\
    ( (This)->lpVtbl -> SelectWindowsFolder(This,bstrDescription,pbtrFolderPath) ) 

#define IWizCommonUI_SelectWizFolder(This,bstrDatabasePath,bstrDescription,ppFolderDisp)	\
    ( (This)->lpVtbl -> SelectWizFolder(This,bstrDatabasePath,bstrDescription,ppFolderDisp) ) 

#define IWizCommonUI_SelectWizDocument(This,bstrDatabasePath,bstrDescription,ppDocumentDisp)	\
    ( (This)->lpVtbl -> SelectWizDocument(This,bstrDatabasePath,bstrDescription,ppDocumentDisp) ) 

#define IWizCommonUI_LoadTextFromFile(This,bstrFileName,pbstrText)	\
    ( (This)->lpVtbl -> LoadTextFromFile(This,bstrFileName,pbstrText) ) 

#define IWizCommonUI_SaveTextToFile(This,bstrFileName,bstrText,bstrCharset)	\
    ( (This)->lpVtbl -> SaveTextToFile(This,bstrFileName,bstrText,bstrCharset) ) 

#define IWizCommonUI_GetValueFromIni(This,bstrFileName,bstrSection,bstrKey,pbstrValue)	\
    ( (This)->lpVtbl -> GetValueFromIni(This,bstrFileName,bstrSection,bstrKey,pbstrValue) ) 

#define IWizCommonUI_SetValueToIni(This,bstrFileName,bstrSection,bstrKey,bstrValue)	\
    ( (This)->lpVtbl -> SetValueToIni(This,bstrFileName,bstrSection,bstrKey,bstrValue) ) 

#define IWizCommonUI_GetATempFileName(This,bstrFileExt,pbstrFileName)	\
    ( (This)->lpVtbl -> GetATempFileName(This,bstrFileExt,pbstrFileName) ) 

#define IWizCommonUI_GetSpecialFolder(This,bstrFolderName,pbstrPath)	\
    ( (This)->lpVtbl -> GetSpecialFolder(This,bstrFolderName,pbstrPath) ) 

#define IWizCommonUI_RunExe(This,bstrExeFileName,bstrParams,vbWait,pnRet)	\
    ( (This)->lpVtbl -> RunExe(This,bstrExeFileName,bstrParams,vbWait,pnRet) ) 

#define IWizCommonUI_EnumFiles(This,bstrPath,bstrFileExt,vbIncludeSubFolders,pvFiles)	\
    ( (This)->lpVtbl -> EnumFiles(This,bstrPath,bstrFileExt,vbIncludeSubFolders,pvFiles) ) 

#define IWizCommonUI_EnumFolders(This,bstrPath,pvFolders)	\
    ( (This)->lpVtbl -> EnumFolders(This,bstrPath,pvFolders) ) 

#define IWizCommonUI_CreateActiveXObject(This,bstrProgID,ppObjDisp)	\
    ( (This)->lpVtbl -> CreateActiveXObject(This,bstrProgID,ppObjDisp) ) 

#define IWizCommonUI_GetValueFromReg(This,bstrRoot,bstrKey,bstrValueName,pbstrData)	\
    ( (This)->lpVtbl -> GetValueFromReg(This,bstrRoot,bstrKey,bstrValueName,pbstrData) ) 

#define IWizCommonUI_SetValueToReg(This,bstrRoot,bstrKey,bstrValueName,bstrData,bstrDataType)	\
    ( (This)->lpVtbl -> SetValueToReg(This,bstrRoot,bstrKey,bstrValueName,bstrData,bstrDataType) ) 

#define IWizCommonUI_EnumRegValues(This,bstrRoot,bstrKey,pvValueNames)	\
    ( (This)->lpVtbl -> EnumRegValues(This,bstrRoot,bstrKey,pvValueNames) ) 

#define IWizCommonUI_EnumRegKeys(This,bstrRoot,bstrKey,pvKeys)	\
    ( (This)->lpVtbl -> EnumRegKeys(This,bstrRoot,bstrKey,pvKeys) ) 

#define IWizCommonUI_SelectTemplate(This,bstrTemplateType,pbstrResultTemplateFileName)	\
    ( (This)->lpVtbl -> SelectTemplate(This,bstrTemplateType,pbstrResultTemplateFileName) ) 

#define IWizCommonUI_HtmlTagGetAttributeValue(This,bstrHtmlTag,bstrTagAttributeName,pbstrAttributeValue)	\
    ( (This)->lpVtbl -> HtmlTagGetAttributeValue(This,bstrHtmlTag,bstrTagAttributeName,pbstrAttributeValue) ) 

#define IWizCommonUI_HtmlExtractTags(This,bstrHtmlText,bstrTagName,bstrTagAttributeName,bstrTagAttributeValue,pvTags)	\
    ( (This)->lpVtbl -> HtmlExtractTags(This,bstrHtmlText,bstrTagName,bstrTagAttributeName,bstrTagAttributeValue,pvTags) ) 

#define IWizCommonUI_HtmlEnumLinks(This,bstrHtmlText,bstrURL,pvLinks)	\
    ( (This)->lpVtbl -> HtmlEnumLinks(This,bstrHtmlText,bstrURL,pvLinks) ) 

#define IWizCommonUI_HtmlGetContent(This,bstrHtmlText,bstrURL,pbstrContent)	\
    ( (This)->lpVtbl -> HtmlGetContent(This,bstrHtmlText,bstrURL,pbstrContent) ) 

#define IWizCommonUI_HtmlConvertFileToHtmlFile(This,bstrSrcFileName,pbstrHtmlFileName)	\
    ( (This)->lpVtbl -> HtmlConvertFileToHtmlFile(This,bstrSrcFileName,pbstrHtmlFileName) ) 

#define IWizCommonUI_HtmlConvertZipFileToHtmlFile(This,bstrSrcZipFileName,bstrDestHtmlFileName,bstrHtmlTitle)	\
    ( (This)->lpVtbl -> HtmlConvertZipFileToHtmlFile(This,bstrSrcZipFileName,bstrDestHtmlFileName,bstrHtmlTitle) ) 

#define IWizCommonUI_OptionsDlg2(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> OptionsDlg2(This,pDisp,nFlags) ) 

#define IWizCommonUI_SelectDay(This,dtDefault,pRet)	\
    ( (This)->lpVtbl -> SelectDay(This,dtDefault,pRet) ) 

#define IWizCommonUI_ReportSyncResult(This,hWnd,vDownloaded,vUploaded,vSkipped,vFailed)	\
    ( (This)->lpVtbl -> ReportSyncResult(This,hWnd,vDownloaded,vUploaded,vSkipped,vFailed) ) 

#define IWizCommonUI_CopyTextToClipboard(This,bstrText)	\
    ( (This)->lpVtbl -> CopyTextToClipboard(This,bstrText) ) 

#define IWizCommonUI_PromptTrafficLimit(This,pDatabaseDisp,hWnd,nLimit)	\
    ( (This)->lpVtbl -> PromptTrafficLimit(This,pDatabaseDisp,hWnd,nLimit) ) 

#define IWizCommonUI_AccountSecurityDlg(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> AccountSecurityDlg(This,pDisp,nFlags) ) 

#define IWizCommonUI_InitEncryptionDlg(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> InitEncryptionDlg(This,pDisp,nFlags) ) 

#define IWizCommonUI_ImportCertDlg(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> ImportCertDlg(This,pDisp,nFlags) ) 

#define IWizCommonUI_EnterPasswordDlg(This,bstrTitle,bstrInfo,vbShowRememberPasswordButton,pvbRememberPassword,pbstrPassword)	\
    ( (This)->lpVtbl -> EnterPasswordDlg(This,bstrTitle,bstrInfo,vbShowRememberPasswordButton,pvbRememberPassword,pbstrPassword) ) 

#define IWizCommonUI_QueryUserAccount2(This,pDatabaseDisp,hWnd,pbstrUserName,pbstrPassword)	\
    ( (This)->lpVtbl -> QueryUserAccount2(This,pDatabaseDisp,hWnd,pbstrUserName,pbstrPassword) ) 

#define IWizCommonUI_ClipboardToImage(This,hwnd,bstrOptions,pbstrImageFileName)	\
    ( (This)->lpVtbl -> ClipboardToImage(This,hwnd,bstrOptions,pbstrImageFileName) ) 

#define IWizCommonUI_CaptureScreen(This,bstrOptions,pbstrImageFileName)	\
    ( (This)->lpVtbl -> CaptureScreen(This,bstrOptions,pbstrImageFileName) ) 

#define IWizCommonUI_DumpCHM(This,bstrCHMFileName,bstrTempPath,bstrOptions,pvRet)	\
    ( (This)->lpVtbl -> DumpCHM(This,bstrCHMFileName,bstrTempPath,bstrOptions,pvRet) ) 

#define IWizCommonUI_HyperlinkDlg(This,pdispDatabase,pdispDocument,pdispHtmlDocument,bstrInitURL,pbstrResultURL)	\
    ( (This)->lpVtbl -> HyperlinkDlg(This,pdispDatabase,pdispDocument,pdispHtmlDocument,bstrInitURL,pbstrResultURL) ) 

#define IWizCommonUI_SelectColor(This,bstrInitColor,pbstrRetColor)	\
    ( (This)->lpVtbl -> SelectColor(This,bstrInitColor,pbstrRetColor) ) 

#define IWizCommonUI_GetFontNames(This,pvNames)	\
    ( (This)->lpVtbl -> GetFontNames(This,pvNames) ) 

#define IWizCommonUI_SelectFont(This,bstrInit,pbstrRet)	\
    ( (This)->lpVtbl -> SelectFont(This,bstrInit,pbstrRet) ) 

#define IWizCommonUI_CreateWizObject(This,bstrObjectName,ppVal)	\
    ( (This)->lpVtbl -> CreateWizObject(This,bstrObjectName,ppVal) ) 

#define IWizCommonUI_GetScriptParamValue(This,bstrParamName,pbstrVal)	\
    ( (This)->lpVtbl -> GetScriptParamValue(This,bstrParamName,pbstrVal) ) 

#define IWizCommonUI_LoadStringFromFile(This,bstrFileName,bstrStringName,pVal)	\
    ( (This)->lpVtbl -> LoadStringFromFile(This,bstrFileName,bstrStringName,pVal) ) 

#define IWizCommonUI_URLDownloadToText(This,bstrURL,pbstrText)	\
    ( (This)->lpVtbl -> URLDownloadToText(This,bstrURL,pbstrText) ) 

#define IWizCommonUI_SelectWizTags(This,bstrDatabasePath,bstrTitle,nFlags,ppTagCollectionDisp)	\
    ( (This)->lpVtbl -> SelectWizTags(This,bstrDatabasePath,bstrTitle,nFlags,ppTagCollectionDisp) ) 

#define IWizCommonUI_CalendarDlg(This,nFlags)	\
    ( (This)->lpVtbl -> CalendarDlg(This,nFlags) ) 

#define IWizCommonUI_AccountInfoDlg(This,pDatabaseDisp,nFlags)	\
    ( (This)->lpVtbl -> AccountInfoDlg(This,pDatabaseDisp,nFlags) ) 

#define IWizCommonUI_GetIniSections(This,bstrFileName,pvValueNames)	\
    ( (This)->lpVtbl -> GetIniSections(This,bstrFileName,pvValueNames) ) 

#define IWizCommonUI_LoadStringFromFile2(This,bstrFileName,bstrSectionName,bstrStringName,pVal)	\
    ( (This)->lpVtbl -> LoadStringFromFile2(This,bstrFileName,bstrSectionName,bstrStringName,pVal) ) 

#define IWizCommonUI_ShowHtmlDialog(This,bstrTitle,bstrURL,nWidth,nHeight,bstrExtOptions,vParam,pvRet)	\
    ( (This)->lpVtbl -> ShowHtmlDialog(This,bstrTitle,bstrURL,nWidth,nHeight,bstrExtOptions,vParam,pvRet) ) 

#define IWizCommonUI_CloseHtmlDialog(This,pdispHtmlDialogDocument,vRet)	\
    ( (This)->lpVtbl -> CloseHtmlDialog(This,pdispHtmlDialogDocument,vRet) ) 

#define IWizCommonUI_ShowMessage(This,bstrText,bstrTitle,nType,pnRet)	\
    ( (This)->lpVtbl -> ShowMessage(This,bstrText,bstrTitle,nType,pnRet) ) 

#define IWizCommonUI_CombineURL(This,bstrBase,bstrPart,pbstrResult)	\
    ( (This)->lpVtbl -> CombineURL(This,bstrBase,bstrPart,pbstrResult) ) 

#define IWizCommonUI_URLDownloadToTempFile(This,bstrURL,pbstrTempFileName)	\
    ( (This)->lpVtbl -> URLDownloadToTempFile(This,bstrURL,pbstrTempFileName) ) 

#define IWizCommonUI_EditDocument(This,pApp,pEvents,pDocumentDisp,bstrOptions,pnWindowHandle)	\
    ( (This)->lpVtbl -> EditDocument(This,pApp,pEvents,pDocumentDisp,bstrOptions,pnWindowHandle) ) 

#define IWizCommonUI_NewDocument(This,pApp,pEvents,pFolderDisp,bstrOptions,pnWindowHandle)	\
    ( (This)->lpVtbl -> NewDocument(This,pApp,pEvents,pFolderDisp,bstrOptions,pnWindowHandle) ) 

#define IWizCommonUI_ClearDocumentWindow(This)	\
    ( (This)->lpVtbl -> ClearDocumentWindow(This) ) 

#define IWizCommonUI_CreateAccountDlg(This,bstrOptions,pbstrRetDatabasePath)	\
    ( (This)->lpVtbl -> CreateAccountDlg(This,bstrOptions,pbstrRetDatabasePath) ) 

#define IWizCommonUI_AddExistingAccountDlg(This,bstrOptions,pbstrRetDatabasePath)	\
    ( (This)->lpVtbl -> AddExistingAccountDlg(This,bstrOptions,pbstrRetDatabasePath) ) 

#define IWizCommonUI_ChangePasswordDlg(This,pDatabaseDisp)	\
    ( (This)->lpVtbl -> ChangePasswordDlg(This,pDatabaseDisp) ) 

#define IWizCommonUI_ProtectAccountDlg(This,pDatabaseDisp)	\
    ( (This)->lpVtbl -> ProtectAccountDlg(This,pDatabaseDisp) ) 

#define IWizCommonUI_RefreshDatabaseIndex(This,nWindowHandle,pDatabaseDisp)	\
    ( (This)->lpVtbl -> RefreshDatabaseIndex(This,nWindowHandle,pDatabaseDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizCommonUI_INTERFACE_DEFINED__ */


#ifndef __IWizBatchDownloader_INTERFACE_DEFINED__
#define __IWizBatchDownloader_INTERFACE_DEFINED__

/* interface IWizBatchDownloader */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizBatchDownloader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49C2236A-6DA1-4AA9-BAD7-BF0DA94535A4")
    IWizBatchDownloader : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJob( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbLinkTextAsTitle,
            /* [in] */ VARIANT_BOOL vbExecuteScript) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJobsFromTextFile( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrTextFileName,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbExecuteScript) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowWindow( 
            VARIANT_BOOL vbStartDownload) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CombineDocuments( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CombineDocuments( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJob2( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJob3( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrOverwriteDocumentGUID,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizBatchDownloaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizBatchDownloader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizBatchDownloader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizBatchDownloader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizBatchDownloader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizBatchDownloader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizBatchDownloader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizBatchDownloader * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJob )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbLinkTextAsTitle,
            /* [in] */ VARIANT_BOOL vbExecuteScript);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJobsFromTextFile )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrTextFileName,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbExecuteScript);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowWindow )( 
            IWizBatchDownloader * This,
            VARIANT_BOOL vbStartDownload);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CombineDocuments )( 
            IWizBatchDownloader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CombineDocuments )( 
            IWizBatchDownloader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJob2 )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJob3 )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrOverwriteDocumentGUID,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWizBatchDownloader * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IWizBatchDownloaderVtbl;

    interface IWizBatchDownloader
    {
        CONST_VTBL struct IWizBatchDownloaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizBatchDownloader_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizBatchDownloader_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizBatchDownloader_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizBatchDownloader_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizBatchDownloader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizBatchDownloader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizBatchDownloader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizBatchDownloader_AddJob(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,vbLinkTextAsTitle,vbExecuteScript)	\
    ( (This)->lpVtbl -> AddJob(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,vbLinkTextAsTitle,vbExecuteScript) ) 

#define IWizBatchDownloader_AddJobsFromTextFile(This,bstrDatabasePath,bstrLocation,bstrTextFileName,nUpdateDocumentFlags,vbExecuteScript)	\
    ( (This)->lpVtbl -> AddJobsFromTextFile(This,bstrDatabasePath,bstrLocation,bstrTextFileName,nUpdateDocumentFlags,vbExecuteScript) ) 

#define IWizBatchDownloader_ShowWindow(This,vbStartDownload)	\
    ( (This)->lpVtbl -> ShowWindow(This,vbStartDownload) ) 

#define IWizBatchDownloader_get_CombineDocuments(This,pVal)	\
    ( (This)->lpVtbl -> get_CombineDocuments(This,pVal) ) 

#define IWizBatchDownloader_put_CombineDocuments(This,newVal)	\
    ( (This)->lpVtbl -> put_CombineDocuments(This,newVal) ) 

#define IWizBatchDownloader_AddJob2(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,nJobFlags)	\
    ( (This)->lpVtbl -> AddJob2(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,nJobFlags) ) 

#define IWizBatchDownloader_AddJob3(This,bstrDatabasePath,bstrOverwriteDocumentGUID,bstrURL,bstrTitle,nUpdateDocumentFlags,nJobFlags)	\
    ( (This)->lpVtbl -> AddJob3(This,bstrDatabasePath,bstrOverwriteDocumentGUID,bstrURL,bstrTitle,nUpdateDocumentFlags,nJobFlags) ) 

#define IWizBatchDownloader_get_Title(This,pVal)	\
    ( (This)->lpVtbl -> get_Title(This,pVal) ) 

#define IWizBatchDownloader_put_Title(This,newVal)	\
    ( (This)->lpVtbl -> put_Title(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizBatchDownloader_INTERFACE_DEFINED__ */


#ifndef __IWizProgressWindow_INTERFACE_DEFINED__
#define __IWizProgressWindow_INTERFACE_DEFINED__

/* interface IWizProgressWindow */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizProgressWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF5BCE34-5FC1-4337-80D3-87747643CB15")
    IWizProgressWindow : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Max( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Pos( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Pos( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Destroy( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetParent( 
            /* [in] */ OLE_HANDLE hwnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizProgressWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizProgressWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizProgressWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizProgressWindow * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizProgressWindow * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizProgressWindow * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizProgressWindow * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizProgressWindow * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWizProgressWindow * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWizProgressWindow * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            IWizProgressWindow * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Max )( 
            IWizProgressWindow * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pos )( 
            IWizProgressWindow * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pos )( 
            IWizProgressWindow * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IWizProgressWindow * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IWizProgressWindow * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IWizProgressWindow * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hide )( 
            IWizProgressWindow * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Destroy )( 
            IWizProgressWindow * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetParent )( 
            IWizProgressWindow * This,
            /* [in] */ OLE_HANDLE hwnd);
        
        END_INTERFACE
    } IWizProgressWindowVtbl;

    interface IWizProgressWindow
    {
        CONST_VTBL struct IWizProgressWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizProgressWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizProgressWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizProgressWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizProgressWindow_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizProgressWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizProgressWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizProgressWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizProgressWindow_get_Title(This,pVal)	\
    ( (This)->lpVtbl -> get_Title(This,pVal) ) 

#define IWizProgressWindow_put_Title(This,newVal)	\
    ( (This)->lpVtbl -> put_Title(This,newVal) ) 

#define IWizProgressWindow_get_Max(This,pVal)	\
    ( (This)->lpVtbl -> get_Max(This,pVal) ) 

#define IWizProgressWindow_put_Max(This,newVal)	\
    ( (This)->lpVtbl -> put_Max(This,newVal) ) 

#define IWizProgressWindow_get_Pos(This,pVal)	\
    ( (This)->lpVtbl -> get_Pos(This,pVal) ) 

#define IWizProgressWindow_put_Pos(This,newVal)	\
    ( (This)->lpVtbl -> put_Pos(This,newVal) ) 

#define IWizProgressWindow_get_Text(This,pVal)	\
    ( (This)->lpVtbl -> get_Text(This,pVal) ) 

#define IWizProgressWindow_put_Text(This,newVal)	\
    ( (This)->lpVtbl -> put_Text(This,newVal) ) 

#define IWizProgressWindow_Show(This)	\
    ( (This)->lpVtbl -> Show(This) ) 

#define IWizProgressWindow_Hide(This)	\
    ( (This)->lpVtbl -> Hide(This) ) 

#define IWizProgressWindow_Destroy(This)	\
    ( (This)->lpVtbl -> Destroy(This) ) 

#define IWizProgressWindow_SetParent(This,hwnd)	\
    ( (This)->lpVtbl -> SetParent(This,hwnd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizProgressWindow_INTERFACE_DEFINED__ */


#ifndef __IWizSyncProgressDlg_INTERFACE_DEFINED__
#define __IWizSyncProgressDlg_INTERFACE_DEFINED__

/* interface IWizSyncProgressDlg */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizSyncProgressDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("476F255C-8032-42A4-AA36-4EBB25C36BAB")
    IWizSyncProgressDlg : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDatabasePath( 
            /* [in] */ BSTR bstrDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoShow( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Background( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Background( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizSyncProgressDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizSyncProgressDlg * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizSyncProgressDlg * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizSyncProgressDlg * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizSyncProgressDlg * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizSyncProgressDlg * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizSyncProgressDlg * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizSyncProgressDlg * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hide )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDatabasePath )( 
            IWizSyncProgressDlg * This,
            /* [in] */ BSTR bstrDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoShow )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Background )( 
            IWizSyncProgressDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Background )( 
            IWizSyncProgressDlg * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IWizSyncProgressDlgVtbl;

    interface IWizSyncProgressDlg
    {
        CONST_VTBL struct IWizSyncProgressDlgVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizSyncProgressDlg_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizSyncProgressDlg_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizSyncProgressDlg_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizSyncProgressDlg_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizSyncProgressDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizSyncProgressDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizSyncProgressDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizSyncProgressDlg_Show(This)	\
    ( (This)->lpVtbl -> Show(This) ) 

#define IWizSyncProgressDlg_Hide(This)	\
    ( (This)->lpVtbl -> Hide(This) ) 

#define IWizSyncProgressDlg_SetDatabasePath(This,bstrDatabasePath)	\
    ( (This)->lpVtbl -> SetDatabasePath(This,bstrDatabasePath) ) 

#define IWizSyncProgressDlg_AutoShow(This)	\
    ( (This)->lpVtbl -> AutoShow(This) ) 

#define IWizSyncProgressDlg_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IWizSyncProgressDlg_get_Background(This,pVal)	\
    ( (This)->lpVtbl -> get_Background(This,pVal) ) 

#define IWizSyncProgressDlg_put_Background(This,newVal)	\
    ( (This)->lpVtbl -> put_Background(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizSyncProgressDlg_INTERFACE_DEFINED__ */


#ifndef __IWizHtmlDialogExternal_INTERFACE_DEFINED__
#define __IWizHtmlDialogExternal_INTERFACE_DEFINED__

/* interface IWizHtmlDialogExternal */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizHtmlDialogExternal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A7BFBD0-65CE-4F73-A819-BAE5819C1127")
    IWizHtmlDialogExternal : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HtmlDialogParam( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CommonUIObject( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizHtmlDialogExternalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizHtmlDialogExternal * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizHtmlDialogExternal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizHtmlDialogExternal * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizHtmlDialogExternal * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizHtmlDialogExternal * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizHtmlDialogExternal * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizHtmlDialogExternal * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HtmlDialogParam )( 
            IWizHtmlDialogExternal * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CommonUIObject )( 
            IWizHtmlDialogExternal * This,
            /* [retval][out] */ IDispatch **pVal);
        
        END_INTERFACE
    } IWizHtmlDialogExternalVtbl;

    interface IWizHtmlDialogExternal
    {
        CONST_VTBL struct IWizHtmlDialogExternalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizHtmlDialogExternal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizHtmlDialogExternal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizHtmlDialogExternal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizHtmlDialogExternal_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizHtmlDialogExternal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizHtmlDialogExternal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizHtmlDialogExternal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizHtmlDialogExternal_get_HtmlDialogParam(This,pVal)	\
    ( (This)->lpVtbl -> get_HtmlDialogParam(This,pVal) ) 

#define IWizHtmlDialogExternal_get_CommonUIObject(This,pVal)	\
    ( (This)->lpVtbl -> get_CommonUIObject(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizHtmlDialogExternal_INTERFACE_DEFINED__ */


#ifndef __IWizCategoryCtrl_INTERFACE_DEFINED__
#define __IWizCategoryCtrl_INTERFACE_DEFINED__

/* interface IWizCategoryCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizCategoryCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C163AE7B-E5B1-4789-A61B-27AFC8C9E17D")
    IWizCategoryCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EventsListener( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EventsListener( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_App( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_App( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedType( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedFolder( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedFolder( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedTags( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedTags( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedStyle( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedStyle( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedDocument( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedDocument( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StateSection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StateSection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Options( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Options( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowDocuments( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowDocuments( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecuteCommand( 
            /* [in] */ BSTR bstrCommandName,
            /* [in] */ VARIANT *pvParam1,
            /* [in] */ VARIANT *pvParam2,
            /* [retval][out] */ VARIANT *pvRetValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelectedDocuments2( 
            /* [out] */ BSTR *pbstrSortBy,
            /* [out] */ BSTR *pbstrSortOrder,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizCategoryCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizCategoryCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizCategoryCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizCategoryCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizCategoryCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizCategoryCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizCategoryCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizCategoryCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventsListener )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EventsListener )( 
            IWizCategoryCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_App )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_App )( 
            IWizCategoryCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizCategoryCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedType )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedFolder )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedFolder )( 
            IWizCategoryCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedTags )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedTags )( 
            IWizCategoryCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedStyle )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedStyle )( 
            IWizCategoryCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedDocument )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedDocument )( 
            IWizCategoryCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StateSection )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StateSection )( 
            IWizCategoryCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            IWizCategoryCtrl * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShowDocuments )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ShowDocuments )( 
            IWizCategoryCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizCategoryCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizCategoryCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWizCategoryCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCommand )( 
            IWizCategoryCtrl * This,
            /* [in] */ BSTR bstrCommandName,
            /* [in] */ VARIANT *pvParam1,
            /* [in] */ VARIANT *pvParam2,
            /* [retval][out] */ VARIANT *pvRetValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedDocuments2 )( 
            IWizCategoryCtrl * This,
            /* [out] */ BSTR *pbstrSortBy,
            /* [out] */ BSTR *pbstrSortOrder,
            /* [retval][out] */ IDispatch **pVal);
        
        END_INTERFACE
    } IWizCategoryCtrlVtbl;

    interface IWizCategoryCtrl
    {
        CONST_VTBL struct IWizCategoryCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizCategoryCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizCategoryCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizCategoryCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizCategoryCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizCategoryCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizCategoryCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizCategoryCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizCategoryCtrl_get_EventsListener(This,pVal)	\
    ( (This)->lpVtbl -> get_EventsListener(This,pVal) ) 

#define IWizCategoryCtrl_put_EventsListener(This,newVal)	\
    ( (This)->lpVtbl -> put_EventsListener(This,newVal) ) 

#define IWizCategoryCtrl_get_App(This,pVal)	\
    ( (This)->lpVtbl -> get_App(This,pVal) ) 

#define IWizCategoryCtrl_put_App(This,newVal)	\
    ( (This)->lpVtbl -> put_App(This,newVal) ) 

#define IWizCategoryCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizCategoryCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizCategoryCtrl_get_SelectedType(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedType(This,pVal) ) 

#define IWizCategoryCtrl_get_SelectedFolder(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedFolder(This,pVal) ) 

#define IWizCategoryCtrl_put_SelectedFolder(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedFolder(This,newVal) ) 

#define IWizCategoryCtrl_get_SelectedTags(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedTags(This,pVal) ) 

#define IWizCategoryCtrl_put_SelectedTags(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedTags(This,newVal) ) 

#define IWizCategoryCtrl_get_SelectedStyle(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedStyle(This,pVal) ) 

#define IWizCategoryCtrl_put_SelectedStyle(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedStyle(This,newVal) ) 

#define IWizCategoryCtrl_get_SelectedDocument(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedDocument(This,pVal) ) 

#define IWizCategoryCtrl_put_SelectedDocument(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedDocument(This,newVal) ) 

#define IWizCategoryCtrl_get_StateSection(This,pVal)	\
    ( (This)->lpVtbl -> get_StateSection(This,pVal) ) 

#define IWizCategoryCtrl_put_StateSection(This,newVal)	\
    ( (This)->lpVtbl -> put_StateSection(This,newVal) ) 

#define IWizCategoryCtrl_get_Options(This,pVal)	\
    ( (This)->lpVtbl -> get_Options(This,pVal) ) 

#define IWizCategoryCtrl_put_Options(This,newVal)	\
    ( (This)->lpVtbl -> put_Options(This,newVal) ) 

#define IWizCategoryCtrl_get_ShowDocuments(This,pVal)	\
    ( (This)->lpVtbl -> get_ShowDocuments(This,pVal) ) 

#define IWizCategoryCtrl_put_ShowDocuments(This,newVal)	\
    ( (This)->lpVtbl -> put_ShowDocuments(This,newVal) ) 

#define IWizCategoryCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizCategoryCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizCategoryCtrl_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IWizCategoryCtrl_ExecuteCommand(This,bstrCommandName,pvParam1,pvParam2,pvRetValue)	\
    ( (This)->lpVtbl -> ExecuteCommand(This,bstrCommandName,pvParam1,pvParam2,pvRetValue) ) 

#define IWizCategoryCtrl_GetSelectedDocuments2(This,pbstrSortBy,pbstrSortOrder,pVal)	\
    ( (This)->lpVtbl -> GetSelectedDocuments2(This,pbstrSortBy,pbstrSortOrder,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizCategoryCtrl_INTERFACE_DEFINED__ */



#ifndef __WizKMControlsLib_LIBRARY_DEFINED__
#define __WizKMControlsLib_LIBRARY_DEFINED__

/* library WizKMControlsLib */
/* [helpstring][version][uuid] */ 


enum WizCategorySelectedType
    {	wizCategorySelectedTypeNone	= 0,
	wizCategorySelectedTypeFolder	= 1,
	wizCategorySelectedTypeDocument	= 2,
	wizCategorySelectedTypeTag	= 3,
	wizCategorySelectedTypeStyle	= 4,
	wizCategorySelectedTypeAllFolders	= 5,
	wizCategorySelectedTypeAllTags	= 6,
	wizCategorySelectedTypeAllStyles	= 7,
	wizCategorySelectedTypeAllQuickSearches	= 8,
	wizCategorySelectedTypeQuickSearchGroup	= 9,
	wizCategorySelectedTypeQuickSearch	= 10,
	wizCategorySelectedTypeFavoriteFolder	= 11,
	wizCategorySelectedTypeAllFavoriteFolders	= 12
    } ;

enum WizBatchDownloaderJobFlags
    {	wizWizBatchDownloaderJobLinkTextAsTitle	= 0x1,
	wizWizBatchDownloaderJobExecuteScript	= 0x2,
	wizWizBatchDownloaderJobURLAsCustomID	= 0x4
    } ;

enum WizCommandID
    {	wizCommandSelectPrevDocument	= 0x1,
	wizCommandSelectNextDocument	= 0x2
    } ;

enum WizCategoryCtrlOptions
    {	wizCategoryShowDocuments	= 0x1,
	wizCategoryDisplaySubFolderDocuments	= 0x2,
	wizCategoryDisplayChildTagDocuments	= 0x4,
	wizCategoryShowFolders	= 0x8,
	wizCategoryShowTags	= 0x10,
	wizCategoryShowStyles	= 0x20,
	wizCategoryShowQuickSearches	= 0x40,
	wizCategoryShowFavoriteFolders	= 0x80,
	wizCategoryNoSkin	= 0x100,
	wizCategoryNoMenu	= 0x200,
	wizCategoryForceBorder	= 0x400
    } ;

enum WizDocumentListCtrlOptions
    {	wizDocumentCtrlSingleLine	= 0x1
    } ;

enum WizDocumentListCtrlSecondLineType
    {	wizDocumentCtrlSecondLineAuto	= 0,
	wizDocumentCtrlSecondLineStar	= 0x1,
	wizDocumentCtrlSecondLineLocation	= 0x2,
	wizDocumentCtrlSecondLineDateCreated	= 0x3,
	wizDocumentCtrlSecondLineDateModified	= 0x4,
	wizDocumentCtrlSecondLineDateAccessed	= 0x5,
	wizDocumentCtrlSecondLineURL	= 0x6,
	wizDocumentCtrlSecondLineAuthor	= 0x7,
	wizDocumentCtrlSecondLineKeywords	= 0x8,
	wizDocumentCtrlSecondLineTags	= 0x9,
	wizDocumentCtrlSecondLineDataSize	= 0x10,
	wizDocumentCtrlSecondLineReadCount	= 0x11
    } ;

EXTERN_C const IID LIBID_WizKMControlsLib;

EXTERN_C const CLSID CLSID_WizDocumentListCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("D30F2928-D136-4F2D-98C4-080E3CB1C92C")
WizDocumentListCtrl;
#endif

EXTERN_C const CLSID CLSID_WizDocumentAttachmentListCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("A74098CA-0E98-40D6-92BF-06AAAE1B2EB8")
WizDocumentAttachmentListCtrl;
#endif

EXTERN_C const CLSID CLSID_WizCommonUI;

#ifdef __cplusplus

class DECLSPEC_UUID("5EABDAD8-A056-4445-AC98-E66885B0935F")
WizCommonUI;
#endif

EXTERN_C const CLSID CLSID_WizBatchDownloader;

#ifdef __cplusplus

class DECLSPEC_UUID("8C43A23A-11CD-4BFA-A3FA-CBC4A586F666")
WizBatchDownloader;
#endif

EXTERN_C const CLSID CLSID_WizProgressWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("E132C3B7-DA0C-4946-9332-D3D1822FC52C")
WizProgressWindow;
#endif

EXTERN_C const CLSID CLSID_WizSyncProgressDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("CDEF75C2-9494-4336-AF33-66980EB65E29")
WizSyncProgressDlg;
#endif

EXTERN_C const CLSID CLSID_WizHtmlDialogExternal;

#ifdef __cplusplus

class DECLSPEC_UUID("31B3C15F-0113-42A2-A652-93D299392ACF")
WizHtmlDialogExternal;
#endif

EXTERN_C const CLSID CLSID_WizCategoryCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("96D74A38-2385-41D0-A006-5D93BF796B61")
WizCategoryCtrl;
#endif
#endif /* __WizKMControlsLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


