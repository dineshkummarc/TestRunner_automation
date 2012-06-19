#pragma once

// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
// 	StdAfx.h 
// 
// Description:
// 	Main header used for preprocessing
// 
// $Log: 
//  4    CliniVision1.3         11/9/99 12:21:53 PM  Doug C. Eveland Added file
//       header documentation
//  3    CliniVision1.2         11/4/99 6:02:32 PM   Doug C. Eveland Added msmxl
//       import statement
//  2    CliniVision1.1         10/19/99 2:53:32 PM  Doug C. Eveland Added
//       cvDragDropItem.h
// 
//  1    CliniVision1.0         10/15/99 2:08:49 PM  Doug C. Eveland 
// $
// $Revision: 4$
// $Date: 11/9/99 12:21:53 PM$
// $Author: Doug C. Eveland$
// 
#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxole.h>         // MFC OLE classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <memory>			// STL memory (including auto_ptr)

#include <atlbase.h>
#include <comdef.h>
CComModule _module;

//#import "msxml.dll" named_guids no_namespace
#import "c:\winnt\system32\msxml.dll" named_guids rename_namespace("XML")


#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "cvCDragDropItem.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



