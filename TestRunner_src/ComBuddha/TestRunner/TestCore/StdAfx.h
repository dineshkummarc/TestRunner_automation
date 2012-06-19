// 
//                Jerr Edens & Doug Eveland
//         Copyright(c) 1999 All Rights Reserved 
// 
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__74CDEBD7_818D_11D3_ABF5_00508B0D0D6E__INCLUDED_)
#define AFX_STDAFX_H__74CDEBD7_818D_11D3_ABF5_00508B0D0D6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>

#include <GeneralError.h>

// Simple macro to make null easier to type
#define null NULL


#ifndef CHECK_HR
// Checks the HRESULT for a failure code and 
// if found, throws the HRESULT
#define CHECK_HR(hr) \
   if(FAILED(hr)) \
   { \
      throw(hr); \
   } 
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__74CDEBD7_818D_11D3_ABF5_00508B0D0D6E__INCLUDED)
