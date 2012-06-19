#if !defined(_TESTOUTPUT_H)
#define _TESTOUTPUT_H

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
// CTestOutput.h : Declaration of the CTestOutput

#include "resource.h"       // main symbols
#include "TestCoreXMLFormatDefs.h"
#include "CDurationCounter.h"
#include "Time.h"
#include <fstream>
using namespace std;

// Group = Core Classes

/////////////////////////////////////////////////////////////////////////////
// Description:
//    Used to log test results to a file and send notifications to a listener
// 
// Remarks:
//    The current design only allows for one listener.  If at some point
//    this seems wrong it can be updated (without effecting the interface)
//    to support multiple listeners.
//
// Author:
// 	Jerry Edens
//
// Include: 
//    #include "CTestOutput.h"
//
class ATL_NO_VTABLE CTestOutput : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestOutput, &CLSID_CTestOutput>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITestOutput, &IID_ITestOutput, &LIBID_TESTCORELib>
{
public:

   CTestOutput();

DECLARE_REGISTRY_RESOURCEID(IDR_CTESTOUTPUT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestOutput)
	COM_INTERFACE_ENTRY(ITestOutput)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
public:
	
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestOutput
public:

   // 'TORs

   HRESULT FinalRelease();

   // Logging methods
	STDMETHOD(LogStartTime)();
   STDMETHOD(LogStopTime)();
   STDMETHOD(LogResult)(/*[in]*/ BSTR bstrMessage, 
         /*[in, optional, defaultvalue(VARIANT_FALSE)]*/ HRESULT hrError = S_OK);
	
   // Listener support methods 
   STDMETHOD(AddListener)(/*[in]*/ ISupportTestOutput* pSupportTestOutput);

   // Properties
   STDMETHOD(get_LogFileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LogFileName)(/*[in]*/ BSTR newVal);

	STDMETHOD(get_TestName)(/*[out, retval]*/ BSTR *pTestName);
	STDMETHOD(put_TestName)(/*[in]*/ BSTR newTestName);

// CTestOutput
protected:

   virtual HRESULT openLogFile();
   virtual HRESULT rawLogToFile(BSTR message);
   STDMETHOD(buildStyleSheet)();
   STDMETHOD(buildStyleSheetName)(const CComBSTR& rOutputName);
   STDMETHOD(localLogResult)(BSTR bstrMessageInternal, BSTR bstrMessageExternal);
   STDMETHOD(logTestName)();

private:

   // {secret}
   typedef basic_fstream<TCHAR, char_traits<TCHAR> > tfstream;
   // {secret}
   // File for writing log on
   tfstream m_file;

   // {secret}
   // Start and stop times
   time_t m_StartTime;
   // {secret}
   time_t m_EndTime;
   
   // {secret}
   CDurationCounter m_testDuaration;
   // {secret}
   CDurationCounter m_totalDuration;

   // The name of the test being logged.
   CComBSTR m_bstrTestName;
   // The name of the file to put the log information onto.
   CComBSTR m_bstrLogFileName;
   // {secret}
   CComBSTR m_bstrStyleSheetName;

   // Pointer to the listener
   // NOTE:  This could just as well be a vector of listeners
   // {secret}
   CComPtr<ISupportTestOutput> m_spSupportTestOutput;

   // include the code to set values.
   // {secret}
#include "SetValue.inl"
};


#endif // _TESTSUITE_H
