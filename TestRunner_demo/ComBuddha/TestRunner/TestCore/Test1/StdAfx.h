// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__EC864253_8321_11D3_ABF8_00508B0D0D6E__INCLUDED_)
#define AFX_STDAFX_H__EC864253_8321_11D3_ABF8_00508B0D0D6E__INCLUDED_

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

#import "..\TestCore.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#define null NULL

#if !defined(CHECK_HR)

#define CHECK_HR(hr) \
   if(FAILED(hr)) \
   { \
      throw(hr); \
   } 

#endif

#if !defined(RESERVED)
#define RESERVED 0
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__EC864253_8321_11D3_ABF8_00508B0D0D6E__INCLUDED)
