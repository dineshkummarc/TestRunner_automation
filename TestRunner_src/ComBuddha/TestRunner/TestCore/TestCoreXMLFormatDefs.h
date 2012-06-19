#ifndef _TESTCOREXMLFORMATDEFS_H_B0D0CCC0_9313_11d3_AC03_00508B0D0D6E
#define _TESTCOREXMLFORMATDEFS_H_B0D0CCC0_9313_11d3_AC03_00508B0D0D6E

#if _MSC_VER > 100
#pragma once
#endif // _MSC_VER > 100

// 
//                Jerry Edens & Doug Eveland
//         Copyright(c) 1999 All Rights Reserved 
// 
// This code may be used in compiled form for non-profit
// purposes and the source code may be redistributed 
// unmodified by any means providing it is not sold for 
// profit, unless written consent is granted by the 
// authors, and providing that this notice and the 
// authors names are included.
//
// If you find any bugs or make any modifications please
// send them to me for incorporation into the code.
//
// This file is provided "as is" with out expressed or 
// implied warranty.
//
// Contact me if you have any questions, comments, or 
// bug reports at jerrye@home.com
//
// Description:
// 	
// 
// $Log: 
// $
// $Revision: $
// $Date: $
// Author: Jerry Edens
// 

#pragma warning(push)
#pragma warning(disable:4114)

///////////////////////////////////////////////////////////////////////////////
// Format strings

// The size of the buffer for the time date string
const int MAX_TIME_STRING_SIZE = 255;

// The date time format is as follows:
// <Start|End> on Day, Month date, year at hh:mm::ss
extern const TCHAR const gk_szTimeFormatString[];  

// Duration is Seconds, miliSeconds, microSeconds
extern const TCHAR const gk_szDurationTimeFormatString[]; 

///////////////////////////////////////////////////////////////////////////////
// XML formats

extern const TCHAR const gk_szXMLHeaderFormat[]; /*= 
      _T("<?xml version=\"1.0\"?>\n<?xml:stylesheet type=\"text/xsl\" href=\"%s\"?>\n\n<TESTRESULTS>\n"); */

extern TCHAR g_szXMLHeaderBuffer[]; 
extern const TCHAR const gk_szXMLFooter[]; 

extern const TCHAR const gk_szXMLIndentLevel1[]; 
extern const TCHAR const gk_szXMLIndentLevel2[]; 
extern const TCHAR const gk_szXMLIndentLevel3[]; 

extern const TCHAR const gk_szXMLStartTag[]; 
extern const TCHAR const gk_szXMLEndTag[]; 
extern const TCHAR const gk_szXMLTestNameEntry[]; 
extern const TCHAR const gk_szXMLEntry[]; 
extern const TCHAR const gk_szXMLOpenTimeEntry[]; 
extern const TCHAR const gk_szXMLCloseTimeEntry[]; 
extern const TCHAR const gk_szXMLStartTimeEntry[]; 
extern const TCHAR const gk_szXMLEndTimeEntry[]; 
extern const TCHAR const gk_szXMLDurationEntry[]; 
extern const TCHAR const gk_szXMLMessageEntry[]; 
extern const TCHAR const gk_szXMLFaultEntry[]; 

extern const TCHAR const gk_szXSLStyleSheet[]; 

#endif 