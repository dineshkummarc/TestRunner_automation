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
#include "stdafx.h"
#include "TestCoreXMLFormatDefs.h"

// The size of the buffer for the time date string
//const int MAX_TIME_STRING_SIZE = 255;

// The date time format is as follows:
// <Start|End> on Day, Month date, year at hh:mm::ss
const TCHAR const gk_szTimeFormatString[] = 
      _T("%a, %b %d, %Y at %H:%M::%S");
// Duration is Seconds, miliSeconds, microSeconds
const TCHAR const gk_szDurationTimeFormatString[] = 
      _T("%3d Sec, %03d mSec, %03d uSec");

// XML formats
const TCHAR const gk_szXMLHeaderFormat[] = 
      _T("<?xml version=\"1.0\"?>\n<?xml:stylesheet type=\"text/xsl\" href=\"%s\"?>\n\n<TESTRESULTS>\n");
TCHAR g_szXMLHeaderBuffer[sizeof(gk_szXMLHeaderFormat) + MAX_PATH] = {0};
const TCHAR const gk_szXMLFooter[] = _T("</TESTRESULTS>");

const TCHAR const gk_szXMLIndentLevel1[] = _T("   ");
const TCHAR const gk_szXMLIndentLevel2[] = _T("      ");
const TCHAR const gk_szXMLIndentLevel3[] = _T("         ");

const TCHAR const gk_szXMLStartTag[] = _T("<");
const TCHAR const gk_szXMLEndTag[] = _T("</");
const TCHAR const gk_szXMLTestNameEntry[] = _T("TESTNAME>");
const TCHAR const gk_szXMLEntry[] = _T("RESULTENTRY>");
const TCHAR const gk_szXMLOpenTimeEntry[] = _T("OPENTIME>");
const TCHAR const gk_szXMLCloseTimeEntry[] = _T("CLOSETIME>");
const TCHAR const gk_szXMLStartTimeEntry[] = _T("STARTTIME>");
const TCHAR const gk_szXMLEndTimeEntry[] = _T("ENDTIME>");
const TCHAR const gk_szXMLDurationEntry[] = _T("DURATION>");
const TCHAR const gk_szXMLMessageEntry[] = _T("MESSAGE>");
const TCHAR const gk_szXMLFaultEntry[] = _T("FAULT>");

const TCHAR const gk_szXSLStyleSheet[] = 
      _T("<?xml version=\"1.0\" ?> \n") 
      _T("<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/TR/WD-xsl\">\n\n") 
         
	   _T("   <xsl:template match=\"//\">\n") 
		_T("      <xsl:define-template-set>\n\n")
         
		_T("         <xsl:template match=\"RESULTENTRY\">\n")
		_T("            <table bgcolor='f0 f0 f0' bordercolor='b0 b0 b0' border='1' width='100%'>\n")
		_T("               <th bgcolor='d0 d0 d0'>Test Name</th>\n")
		_T("               <th bgcolor='d0 d0 d0'>Test Start Time</th>\n")
		_T("               <th bgcolor='d0 d0 d0'>Test End Time</th>\n")
		_T("               <th bgcolor='d0 d0 d0'>Test Duration</th>\n")
		_T("            <tr><xsl:apply-templates select=\"TESTNAME\" />\n")
		_T("                <xsl:apply-templates select=\"STARTTIME\" />\n")
		_T("                <xsl:apply-templates select=\"ENDTIME\" />\n")
		_T("                <xsl:apply-templates select=\"DURATION\" /> </tr>\n")
		_T("            <tr><xsl:apply-templates select=\"MESSAGE\" /> </tr>\n")
		_T("            <tr><xsl:apply-templates select=\"FAULT\" /> </tr>\n")
		_T("            </table>\n")
		_T("            <br />\n")
		_T("         </xsl:template>\n\n")
         
		_T("         <xsl:template match=\"OPENTIME\">	\n")
		_T("	          <DIV STYLE=\"font-family:arial;font-size:10pt;color:blue;margin-left:.33cm\"> \n")
		_T("		          <h2><center>Log file open for business on <xsl:value-of/></center></h2> <br /> <br />\n")
		_T("	          </DIV>\n")
		_T("         </xsl:template>\n\n")
         
		_T("         <xsl:template match=\"CLOSETIME\">	\n")
   	_T("	          <SPAN STYLE=\"font-family:arial;font-size:10pt;color:blue\"> \n")
		_T("		          <br /><h2><center>Log file closed for business on <xsl:value-of/></center></h2> <br /> <br /> \n")
		_T("	          </SPAN> \n")
		_T("         </xsl:template> \n\n")
         
		_T("      </xsl:define-template-set> \n")
		_T("      <xsl:apply-templates /> \n")
	   _T("   </xsl:template> \n\n")
         
		_T("   <xsl:template match=\"TESTNAME\">	\n")
      _T("      <td bgcolor='ef ef ff'>\n")
		_T("		    <xsl:value-of />\n")
      _T("      </td>\n")
		_T("   </xsl:template>\n\n")
         
	   _T("   <xsl:template match=\"MESSAGE\"> \n")
      _T("      <tr><td bordercolor='ff ff ff' cellspacing='0' bgcolor='ff ff ff' colspan='4'>\n")
		_T("         <xsl:value-of />\n")
      _T("      </td></tr>\n")
	   _T("   </xsl:template> \n\n")
         
	   _T("   <xsl:template match=\"FAULT\"> \n")
      _T("      <tr><td bordercolor='ff 00 00' cellspacing='0' bgcolor='df 00 00' colspan='4'> <font color='white'>\n")
		_T("         <xsl:value-of />\n")
      _T("      </font></td></tr>\n")
	   _T("   </xsl:template> \n\n")
         
	   _T("   <xsl:template match=\"STARTTIME\">	\n")
      _T("      <td bgcolor='ef ef ff'>\n")
		_T("         <xsl:value-of />\n")
      _T("      </td>\n")
	   _T("   </xsl:template> \n\n")
         
	   _T("   <xsl:template match=\"ENDTIME\"> \n")
      _T("      <td bgcolor='ef ef ff'>\n")
		_T("         <xsl:value-of />\n")
      _T("      </td>\n")
	   _T("   </xsl:template> \n\n")
         
	   _T("   <xsl:template match=\"DURATION\"> \n")
      _T("      <td bgcolor='ef ef ff'>\n")
		_T("         <xsl:value-of />\n")
      _T("      </td>\n")
	   _T("   </xsl:template> \n\n")
      _T("</xsl:stylesheet>\n"); 

