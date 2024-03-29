

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IWizDocumentListCtrl,0xC128ECE0,0xA006,0x4E57,0x80,0x54,0x4C,0xBC,0x49,0x81,0x82,0x31);


MIDL_DEFINE_GUID(IID, IID_IWizDocumentAttachmentListCtrl,0x39B2717D,0x7FDA,0x4EDD,0x91,0xA4,0x01,0x73,0xFD,0x35,0xB8,0x71);


MIDL_DEFINE_GUID(IID, IID_IWizCommonUI,0xB671315F,0xB6FE,0x4799,0xAE,0x50,0xAE,0xA0,0x84,0x8F,0xBA,0x05);


MIDL_DEFINE_GUID(IID, IID_IWizBatchDownloader,0x49C2236A,0x6DA1,0x4AA9,0xBA,0xD7,0xBF,0x0D,0xA9,0x45,0x35,0xA4);


MIDL_DEFINE_GUID(IID, IID_IWizProgressWindow,0xFF5BCE34,0x5FC1,0x4337,0x80,0xD3,0x87,0x74,0x76,0x43,0xCB,0x15);


MIDL_DEFINE_GUID(IID, IID_IWizSyncProgressDlg,0x476F255C,0x8032,0x42A4,0xAA,0x36,0x4E,0xBB,0x25,0xC3,0x6B,0xAB);


MIDL_DEFINE_GUID(IID, IID_IWizHtmlDialogExternal,0x9A7BFBD0,0x65CE,0x4F73,0xA8,0x19,0xBA,0xE5,0x81,0x9C,0x11,0x27);


MIDL_DEFINE_GUID(IID, IID_IWizCategoryCtrl,0xC163AE7B,0xE5B1,0x4789,0xA6,0x1B,0x27,0xAF,0xC8,0xC9,0xE1,0x7D);


MIDL_DEFINE_GUID(IID, LIBID_WizKMControlsLib,0x89FE0B90,0xC336,0x4BDF,0xA9,0x31,0x7C,0xA8,0xDC,0xD7,0xE0,0x02);


MIDL_DEFINE_GUID(CLSID, CLSID_WizDocumentListCtrl,0xD30F2928,0xD136,0x4F2D,0x98,0xC4,0x08,0x0E,0x3C,0xB1,0xC9,0x2C);


MIDL_DEFINE_GUID(CLSID, CLSID_WizDocumentAttachmentListCtrl,0xA74098CA,0x0E98,0x40D6,0x92,0xBF,0x06,0xAA,0xAE,0x1B,0x2E,0xB8);


MIDL_DEFINE_GUID(CLSID, CLSID_WizCommonUI,0x5EABDAD8,0xA056,0x4445,0xAC,0x98,0xE6,0x68,0x85,0xB0,0x93,0x5F);


MIDL_DEFINE_GUID(CLSID, CLSID_WizBatchDownloader,0x8C43A23A,0x11CD,0x4BFA,0xA3,0xFA,0xCB,0xC4,0xA5,0x86,0xF6,0x66);


MIDL_DEFINE_GUID(CLSID, CLSID_WizProgressWindow,0xE132C3B7,0xDA0C,0x4946,0x93,0x32,0xD3,0xD1,0x82,0x2F,0xC5,0x2C);


MIDL_DEFINE_GUID(CLSID, CLSID_WizSyncProgressDlg,0xCDEF75C2,0x9494,0x4336,0xAF,0x33,0x66,0x98,0x0E,0xB6,0x5E,0x29);


MIDL_DEFINE_GUID(CLSID, CLSID_WizHtmlDialogExternal,0x31B3C15F,0x0113,0x42A2,0xA6,0x52,0x93,0xD2,0x99,0x39,0x2A,0xCF);


MIDL_DEFINE_GUID(CLSID, CLSID_WizCategoryCtrl,0x96D74A38,0x2385,0x41D0,0xA0,0x06,0x5D,0x93,0xBF,0x79,0x6B,0x61);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



