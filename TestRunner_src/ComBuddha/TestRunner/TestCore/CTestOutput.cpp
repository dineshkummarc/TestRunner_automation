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
// CTestOutput.cpp : Implementation of CTestOutput
#include "stdafx.h"
#include "TestCore.h"
#include "CTestOutput.h"

/////////////////////////////////////////////////////////////////////////////
// class CTestOutput
//

// {secret}
STDMETHODIMP CTestOutput::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestOutput
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// {secret}
// {group:Internal} 
// 
// Name: 
// 	CTestOutput
// 
// Description:
// 	Constructor
// 
// Arguments:
// 	m_StartTime(0L) - The start time for the test
//    m_EndTime(0L - The end time of the test
// 
CTestOutput::CTestOutput() : 
      m_StartTime(0L), m_EndTime(0L)
{
}

// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::openLogFile
// 
// Description:
// 	Opens the log file
// 
// Precondition:
//    The log file name property must have been set.
// 
// Postcondition:
//    The log file should be open.
//
// Results:
//    S_OK - All is well
//    TRE_GENERAL_PRECONDITION_FAILED - A precondition for this method has not been met.
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
HRESULT CTestOutput::openLogFile()
{
   HRESULT hr = S_OK;
   try
   {
      if (m_bstrLogFileName.Length() <= 0)
      {
         hr = TRE_GENERAL_PRECONDITION_FAILED;
         throw (hr);
      }

      buildStyleSheet();
      USES_CONVERSION;
      _stprintf(g_szXMLHeaderBuffer, gk_szXMLHeaderFormat, W2T(m_bstrStyleSheetName));
      
      m_file.open(W2A(m_bstrLogFileName), ios_base::out | ios_base::trunc);
      
      // Indicate to the world we are open and ready for business
      time_t t;
      time(&t);
      TCHAR szTimeString[MAX_TIME_STRING_SIZE];
      _tcsftime(szTimeString, MAX_TIME_STRING_SIZE, gk_szTimeFormatString, 
            localtime(&t));

      _bstr_t bstrMessage(g_szXMLHeaderBuffer);
      bstrMessage += gk_szXMLIndentLevel1;            // Indent
      bstrMessage += gk_szXMLStartTag;                // Start tag
      bstrMessage += gk_szXMLOpenTimeEntry;           // Open Time tag
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel2;            // Indent
      bstrMessage += szTimeString;                    // The time
      bstrMessage += gk_szXMLIndentLevel1;            // Indent
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLEndTag;                  // End tag   
      bstrMessage += gk_szXMLOpenTimeEntry;           // End time tag
      bstrMessage += "\n";                            // new line
      
      _bstr_t bstrInteranl(L"The log file opened on ");
      bstrInteranl += szTimeString;

      localLogResult(bstrInteranl, bstrMessage);

      m_totalDuration.start();
      
      ATLASSERT(m_file.is_open());
   }
   catch(HRESULT)
   {
   }
   catch(...)
   {
   }

   return (hr);
}


// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::buildStyleSheet
// 
// Description:
// 	Checks to see if a style sheet exists and if not creates it.
// 
// Side effects:
//    Uses the log file name to create a stylesheet name and 
//    stores it in m_bstrStyleSheetName.
//    
STDMETHODIMP CTestOutput::buildStyleSheet()
{
   if (m_bstrStyleSheetName.Length() <= 0)
   {
      buildStyleSheetName(m_bstrLogFileName);   
   }

   // The stream used to write out the style sheet.
   tfstream styleSheet;

   USES_CONVERSION;
   styleSheet.open(W2A(m_bstrStyleSheetName), ios_base::in);
   if (!styleSheet.is_open())
   {
      styleSheet.clear();
      styleSheet.open(W2A(m_bstrStyleSheetName), ios_base::out | ios_base::trunc);
      if (styleSheet.is_open())
      {
         styleSheet << gk_szXSLStyleSheet << endl;
      }
   }

   styleSheet.close();

   // if it fails it is not catastrophic the xml file will just view badly...
   return (S_OK);
}



// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::buildStyleSheetName
// 
// Description:
// 	Given the output file name, builds the style sheet name
// 
// Arguments:
// 	rOutputName - The output file name
// 
STDMETHODIMP CTestOutput::buildStyleSheetName(const CComBSTR& rOutputName)
{
   TCHAR drive[_MAX_DRIVE];
   TCHAR dir[_MAX_DIR];
   TCHAR fname[_MAX_FNAME];
   TCHAR ext[_MAX_EXT];
   
   TCHAR szStyleSheetName[_MAX_PATH + _MAX_DIR + _MAX_FNAME + _MAX_EXT + sizeof(TCHAR)];

   USES_CONVERSION;
   _tsplitpath(W2T(rOutputName), drive, dir, fname, ext);

   const TCHAR const szPathFormat[] = _T("%s%s%s.xsl");
   wsprintf(szStyleSheetName, szPathFormat, drive, dir, fname);

   // Save the name away
   m_bstrStyleSheetName = szStyleSheetName;

   return (S_OK);
}

// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::FinalRelease
// 
// Description:
// 	Called just before the object is destroyed.
// 
// Results:
//    S_OK - All is well
// 
HRESULT CTestOutput::FinalRelease()
{
   HRESULT hr = S_OK;
   try
   {
      if (m_file.is_open())
      {
         USES_CONVERSION;

         m_totalDuration.stop();

         // Indicate to the world that we are closed and no longer 
         // in business for now.
         time_t t;
         time(&t);
         TCHAR szTimeString[MAX_TIME_STRING_SIZE];
         _tcsftime(szTimeString, MAX_TIME_STRING_SIZE, gk_szTimeFormatString, 
               localtime(&t));

         TCHAR szDurationTimeString[MAX_TIME_STRING_SIZE];
         hr = m_totalDuration.toString(szDurationTimeString);
         CHECK_HR(hr);

         // Log time the log file is closed and total duration 
         // it was open..
         _bstr_t bstrMessage(gk_szXMLIndentLevel1);
         bstrMessage += gk_szXMLStartTag;
         bstrMessage += gk_szXMLCloseTimeEntry;
         bstrMessage += "\n";
         bstrMessage += gk_szXMLIndentLevel2; 
         bstrMessage += szTimeString; 
         bstrMessage += L", with a total duration of ";
         bstrMessage += szDurationTimeString;
         bstrMessage += gk_szXMLIndentLevel1; 
         bstrMessage += "\n"; 
         bstrMessage += gk_szXMLEndTag; 
         bstrMessage += gk_szXMLCloseTimeEntry; 
         bstrMessage += "\n";
         bstrMessage += gk_szXMLFooter; 
         bstrMessage += "\n";
         
         // Create an unformatted (non-XML) message for the listeners
         _bstr_t bstrInternal(L"The log file closed on ");
         bstrInternal += szTimeString;
         bstrInternal += L", with a total duration of ";
         bstrInternal += szDurationTimeString;

         // Send off the message to the listeners and log it...
         localLogResult(bstrInternal, bstrMessage);
         
         m_file.close();
     }
   }
   catch(HRESULT)
   {
   }
   catch(...)
   {
   }

   return (hr);
}

// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::rawlogToFile
// 
// Description:
// 	Logs the description to the test result file
// 
// Arguments:
// 	message - The message to place on the file.
// 
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
HRESULT CTestOutput::rawLogToFile(BSTR message)
{
   ATLASSERT(message != null);
   ATLASSERT(!::IsBadReadPtr(message, ::SysStringByteLen(message)));

   HRESULT hr = S_OK;
   try
   {
      if (message == null)
      {
         hr = E_INVALIDARG, throw hr;
      }

      if (m_file.is_open())
      {
         USES_CONVERSION;
         m_file << W2T(message) << endl;      
      }
   }
   catch(HRESULT /*hr*/)
   {
   }
   catch(_com_error& err)
   {
      hr = err.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

   return (hr);
}


// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::LogTestName
// 
// Description:
// 	Logs the test name to the log.
// 
STDMETHODIMP CTestOutput::logTestName()
{
   HRESULT hr = S_OK;

   try
   {
      // we can't log anything if the file is closed
      if (!m_file.is_open())
      {
         hr = openLogFile();
         // Allow the caller to log or not log the results.
         // So, having an empty file name, is not an error condition.
         CHECK_HR((TRE_GENERAL_PRECONDITION_FAILED == hr ? (hr = S_FALSE) : hr));
      }

      if (m_bstrTestName.Length() <= 0)
      {
         m_bstrTestName = L"Unknown";
      }
           
      _bstr_t bstrXMLMessage;
      bstrXMLMessage += gk_szXMLIndentLevel2;
      bstrXMLMessage += gk_szXMLStartTag;
      bstrXMLMessage += gk_szXMLTestNameEntry;
      bstrXMLMessage += "\n";
      bstrXMLMessage += gk_szXMLIndentLevel3;
      bstrXMLMessage += m_bstrTestName.m_str;
      bstrXMLMessage += "\n";
      bstrXMLMessage += gk_szXMLIndentLevel2;
      bstrXMLMessage += gk_szXMLEndTag;
      bstrXMLMessage += gk_szXMLTestNameEntry;
      bstrXMLMessage += "\n";                            // new line
      
      _bstr_t bstrInternal(L"Test Name = ");
      bstrInternal += m_bstrTestName.m_str;

      localLogResult(bstrInternal, bstrXMLMessage);
   }
   catch(...)
   {
   }

   return (hr);
}

// {secret}
// {group:Internal}
// 
// Name: 
// 	CTestOutput::localLogResult
// 
// Description:
// 	Used by methods which need to log the result in a differant format than what is passed 
//    back to the listener.
// 
// Arguments:
// 	bstrMessageInternal - The XML formatted string
// 
// 	bstrMessageExternal - The non-XML string
// 
STDMETHODIMP CTestOutput::localLogResult(BSTR bstrMessageInternal, BSTR bstrMessageExternal)
{
   ATLASSERT(bstrMessageInternal != null);
   ATLASSERT(!::IsBadReadPtr(bstrMessageInternal, ::SysStringByteLen(bstrMessageInternal)));
   ATLASSERT(bstrMessageExternal != null);
   ATLASSERT(!::IsBadReadPtr(bstrMessageExternal, ::SysStringByteLen(bstrMessageExternal)));

   HRESULT hr = S_OK;

   try
   {
	   if (bstrMessageInternal == null || bstrMessageExternal == null)
      {
		   return E_INVALIDARG;
      }

      // Perform the rquired actions to log the result
      if (m_spSupportTestOutput.p != null)
      {
         hr = m_spSupportTestOutput->LogResult(bstrMessageInternal);
      }
      
      // we can't log anything if the file is closed
      if (!m_file.is_open())
      {
         hr = openLogFile();
         // Allow the caller to log or not log the results.
         // So, having an empty file name, is not an error condition.
         CHECK_HR((TRE_GENERAL_PRECONDITION_FAILED == hr ? S_OK : hr));
      }

      rawLogToFile(bstrMessageExternal);
   }
   catch(HRESULT)
   {
   } 
   catch(_com_error& re)
   {
      hr = re.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

	return hr;
}



///////////////////////////////////////////////////////////////////////////////
// 
//                         ITestOutput 
// 
///////////////////////////////////////////////////////////////////////////////


// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::LogStartTime
// 
// Description:
// 	Initializes the timer which tracks the execution time of the test.
// 
// Precondition:
//    The log file name needs to be set
//    The log file needs to be open
// 
// Postcondition:
//    The start time will have been logged to the log file and 
//    sent to the listeners.
//
// Results:
// 
//    S_OK - All is well
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestOutput::LogStartTime()
{
   HRESULT hr = S_OK;

   try
   {
      // we can't log anything if the file is closed
      if (!m_file.is_open())
      {
         hr = openLogFile();
         // Allow the caller to log or not log the results.
         // So, having an empty file name, is not an error condition.
         CHECK_HR((TRE_GENERAL_PRECONDITION_FAILED == hr ? (hr = S_FALSE) : hr));
      }

      time(&m_StartTime);
      TCHAR szTimeString[MAX_TIME_STRING_SIZE];
      _tcsftime(szTimeString, MAX_TIME_STRING_SIZE, gk_szTimeFormatString, 
            localtime(&m_StartTime));

      // set up the xml text
      _bstr_t bstrMessage("\n");
      bstrMessage += gk_szXMLIndentLevel1;             // Indent
      bstrMessage += gk_szXMLStartTag;                // Start tag
      bstrMessage += gk_szXMLEntry;                   // Start Time tag
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel2;             // Indent
      bstrMessage += gk_szXMLStartTag;                // Start tag
      bstrMessage += gk_szXMLStartTimeEntry;          // Start Time tag
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel3;            // Indent
      bstrMessage += szTimeString;                    // The time
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel2;            // Indent
      bstrMessage += gk_szXMLEndTag;                  // End tag   
      bstrMessage += gk_szXMLStartTimeEntry;          // End time tag
      bstrMessage += "\n";                            // new line
      
      _bstr_t bstrInternal(L"Test started on ");
      bstrInternal += szTimeString;

      localLogResult(bstrInternal, bstrMessage);
      logTestName();
                  
      m_testDuaration.start();
   }
   catch(_com_error& re)
   {
      hr = re.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

	return hr;
}

// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::LogStopTime
// 
// Description:
// 	Stops the time accumulation.
// 
// Precondition:
//    LogStartTime() should have been called.  If LogStartTime has not 
//    been called the results are indeterminate.
//    
// Postcondition:
//    The stop time and the duration of the test will have been logged
//    to the log file and the sent to the listeners.
//
// Results:
// 
//    S_OK - All is well
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestOutput::LogStopTime()
{
   HRESULT hr = S_OK;

   try
   {
      // we can't log anything if the file is closed
      if (!m_file.is_open())
      {
         hr = openLogFile();
         // Allow the caller to log or not log the results.
         // So, having an empty file name, is not an error condition.
         CHECK_HR((TRE_GENERAL_PRECONDITION_FAILED == hr ? S_OK : hr));
      }

      // Stop the performance counter
      m_testDuaration.stop();

      // Get the date and time...
      time(&m_EndTime);

      TCHAR szTimeString[MAX_TIME_STRING_SIZE];
      _tcsftime(szTimeString, MAX_TIME_STRING_SIZE, gk_szTimeFormatString, 
            localtime(&m_EndTime));
      
      _bstr_t bstrMessage(gk_szXMLIndentLevel2);
      bstrMessage += gk_szXMLStartTag;                // Start tag
      bstrMessage += gk_szXMLEndTimeEntry;            // End Time tag
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel3;            // Indent
      bstrMessage += szTimeString;                    // The time
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel2;            // Indent
      bstrMessage += gk_szXMLEndTag;                  // End tag   
      bstrMessage += gk_szXMLEndTimeEntry;            // End Time tag
      bstrMessage += "\n";                            // new line

      _bstr_t bstrInternal(L"Test stopped on ");
      bstrInternal += szTimeString;

      hr = localLogResult(bstrInternal, bstrMessage);
      CHECK_HR(hr);

      TCHAR szDurationTimeString[MAX_TIME_STRING_SIZE];
      hr = m_testDuaration.toString(szDurationTimeString);
      CHECK_HR(hr);

      bstrMessage = "\n";                             // neww line
      bstrMessage = gk_szXMLIndentLevel2;             // Indent
      bstrMessage += gk_szXMLStartTag;                // Start tag
      bstrMessage += gk_szXMLDurationEntry;           // End Time tag
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel3;            // Indent
      bstrMessage += szDurationTimeString;                    // The time
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel2;            // Indent
      bstrMessage += gk_szXMLEndTag;                  // End tag   
      bstrMessage += gk_szXMLDurationEntry;           // End Time tag
      bstrMessage += "\n";                            // new line
      bstrMessage += "\n";                            // new line
      bstrMessage += gk_szXMLIndentLevel1;            // Indent
      bstrMessage += gk_szXMLEndTag;                  // Start tag
      bstrMessage += gk_szXMLEntry;                   // Start Time tag
      bstrMessage += "\n";                            // new line
      
      bstrInternal = L"Test duration was ";
      bstrInternal += szDurationTimeString;

      localLogResult(bstrInternal, bstrMessage);

   }
   catch(_com_error& re)
   {
      hr = re.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

	return hr;
}

// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::LogResult
// 
// Description:
// 	Logs the message.
// 
// Arguments:
// 	bstrMessage - The message which is to be logged.
//    hrError - Indicates if the message being posted is
//    a success for failure message.
// 
// Precondition:
//    The log file name property must have been set.
// 
// Postcondition:
//    The log file will have been opened.
//    The message will have logged to the log file and 
//    sent to the listeners.
//
// Results:
//    S_OK - All is well
//    TRE_GENERAL_PRECONDITION_FAILED - A precondition for this method has not been met.
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
// Remarks:
//    The state (SUCCESS/FAILURE) of the message is required so that the 
//    proper XML tag can be applied to the message.
//
STDMETHODIMP CTestOutput::LogResult(BSTR bstrMessage, HRESULT hrError)
{
   ATLASSERT(bstrMessage != null);
   ATLASSERT(!::IsBadReadPtr(bstrMessage, ::SysStringByteLen(bstrMessage)));

   HRESULT hr = S_OK;

   try
   {
      // Make sure we have a message to log.
	   if (bstrMessage == null)
      {
		   return E_INVALIDARG;
      }

      // Send the unformatted (non-XML) message off to the listeners.
      if (m_spSupportTestOutput.p != null)
      {
         hr = m_spSupportTestOutput->LogResult(bstrMessage);
      }
      
      // we can't log anything if the file is closed
      if (!m_file.is_open())
      {
         hr = openLogFile();
         // Allow the caller to log or not log the results.
         // So, having an empty file name, is not an error condition.
         CHECK_HR((TRE_GENERAL_PRECONDITION_FAILED == hr ? S_OK : hr));
      }

      _bstr_t bstrXMLMessage(gk_szXMLIndentLevel2);
      bstrXMLMessage += gk_szXMLStartTag;

      // Is this a success message or an error message?
      if (SUCCEEDED(hrError)) 
      {
         bstrXMLMessage += gk_szXMLMessageEntry;
      }
      else
      {
         bstrXMLMessage += gk_szXMLFaultEntry;
      }
      
      bstrXMLMessage += "\n";
      bstrXMLMessage += gk_szXMLIndentLevel3;            // Indent
      bstrXMLMessage += bstrMessage;
      bstrXMLMessage += "\n";
      bstrXMLMessage += gk_szXMLIndentLevel2;            // Indent
      bstrXMLMessage += gk_szXMLEndTag;
      
      if (SUCCEEDED(hrError)) 
      {
         bstrXMLMessage += gk_szXMLMessageEntry;
      }
      else
      {
         bstrXMLMessage += gk_szXMLFaultEntry;
      }
      
      bstrXMLMessage += "\n";

      rawLogToFile(bstrXMLMessage);
   }
   catch(_com_error& re)
   {
      hr = re.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

	return hr;
}

// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::AddListener
// 
// Description:
// 	Adds a listener for output
// 
// Arguments:
// 	pSupportTestOutput - Points to the component which is registering as a listener.
// 
// Precondition:
//    The pointer to the listener (ISupportTestOutput) must be a valid 
//    pointer.
//
// Postcondition:
//    The ISupportTestOutput pointer is registered as a listener.
// 
// Results:
// 
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
// Remarks:
//    If there is a need to have more than one listener this method can be
//    implemented with a std::vector< CAdapt< CComPtr< ISupportTestOutput > > >.
//    This extra suppport is not needed at this point.
//
STDMETHODIMP CTestOutput::AddListener(ISupportTestOutput* pSupportTestOutput)
{
   ATLASSERT(pSupportTestOutput != null);
   ATLASSERT(!::IsBadWritePtr(pSupportTestOutput, sizeof(ISupportTestOutput*)));

   HRESULT hr = S_OK;

   try
   {
	   if (pSupportTestOutput == null)
      {
		   return E_INVALIDARG;
      }

      m_spSupportTestOutput = pSupportTestOutput;

   }
   catch(_com_error& re)
   {
      hr = re.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

	return hr;
}

// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::get_LogFileName
// 
// Description:
// 	Returns the value of the LogFileName
// 
// Arguments:
// 	*pLogFileName - Holder fo the log file name
// 
// Precondition:
//    pLogFileName must be a valid BSTR*.
//
// Postcondition:
//    pLogFileName will point to a valid BSTR. The caller 
//    is responsible for releasing this memory.
//
// Results:
// 
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestOutput::get_LogFileName(BSTR* pLogFileName)
{
   return(setVal(static_cast<BSTR*>(pLogFileName), m_bstrLogFileName));
}


// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::put_LogFileName
// 
// Description:
// 	Sets the log file name
// 
// Arguments:
// 	newLogFileName - The new log file name
// 
// Precondition:
//    newLogFileName must be a valid BSTR.
//
// Postcondition:
//    m_bstrLogFileName will hold a copy of newLogFileName. 
//
// Results:
// 
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestOutput::put_LogFileName(BSTR newLogFileName)
{
   return(setVal(reinterpret_cast<CComBSTR*>(&m_bstrLogFileName), newLogFileName));
}

// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::get_TestName
// 
// Description:
// 	Gets the test name
// 
// Arguments:
// 	pTestName - Holder for the test name
// 
// Precondition:
//    pTestName must be a valid BSTR*.
//
// Postcondition:
//    pTestName will point to a valid BSTR. The caller 
//    is responsible for releasing this memory.
//
// Results:
// 
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestOutput::get_TestName(/*[out, retval]*/ BSTR* pTestName)
{
   return(setVal(static_cast<BSTR*>(pTestName), m_bstrTestName));
}

// {group:ITestOutput} 
// 
// Name: 
// 	CTestOutput::put_TestName
// 
// Description:
// 	Sets the test name
// 
// Arguments:
// 	newTestName - The new test name
// 
// Precondition:
//    newTestName must be a valid BSTR.
//
// Postcondition:
//    m_bstrTestName will hold a copy of newTestName. 
//
// Results:
// 
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestOutput::put_TestName(/*[in]*/ BSTR newTestName)
{
   return(setVal(reinterpret_cast<CComBSTR*>(&m_bstrTestName), newTestName));
}



