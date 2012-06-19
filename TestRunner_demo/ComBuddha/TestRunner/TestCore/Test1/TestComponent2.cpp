// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// Description:
// 	
// 
// $Log: 
//  11   CliniVision1.10        11/18/99 Jerry Edens     General update to match
//       changes made to ITestOutput
//  10   CliniVision1.9         11/08/99 Jerry Edens     Updated to support better
//       property testing
//       Updated the xml and xsl output.
//  9    CliniVision1.8         11/05/99 Jerry Edens     Updated to support
//       differant manner of logging the test name.
//  8    CliniVision1.7         11/02/99 Jerry Edens     Added functionality for
//       automating property testing
//  7    CliniVision1.6         10/21/99 Jerry Edens     Updated run method to call
//       start and stop timer
//  6    CliniVision1.5         10/21/99 Jerry Edens     Updated the signature of
//       ITest::Run
//  5    CliniVision1.4         10/21/99 Jerry Edens     Removed Message Boxes
//  4    CliniVision1.3         10/19/99 Jerry Edens     Removed dependency on
//       ITest.idl
//  3    CliniVision1.2         10/19/99 Jerry Edens     Updated the
//       ISupportTestOutput interface and implementing classes
//  2    CliniVision1.1         10/18/99 Jerry Edens     General clean up.
//       Add copy right notices to idl
//       Update vbscript test
//       Updated functionality
//  1    CliniVision1.0         10/15/99 Jerry Edens     
// $
// $Revision: 11$
// $Date: 11/18/99 2:29:32 PM$
// $Author: Jerry Edens$
// 
// TestComponent2.cpp : Implementation of CTestComponent2
#include "stdafx.h"
#include "Test1.h"
#include "TestComponent2.h"

/////////////////////////////////////////////////////////////////////////////
// CTestComponent2

STDMETHODIMP CTestComponent2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestComponent2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//                               ITest

STDMETHODIMP CTestComponent2::Run(ITestOutput* pTestOutput, VARIANT runParameter)
{
   ATLASSERT(pTestOutput != NULL);
   ATLASSERT(!::IsBadReadPtr(pTestOutput, sizeof(ITestOutput*)));

   //MessageBox(NULL, _T("CTestComponent2::Run()"), _T("Test App"), MB_OK|MB_TOPMOST);
   if(pTestOutput)
   {
      pTestOutput->LogStartTime();
      pTestOutput->LogResult(CComBSTR(L"CTestComponent2::Run()"), S_OK);
      pTestOutput->LogStopTime();
   }

   return(S_OK);
}

STDMETHODIMP CTestComponent2::StartUp(ITestOutput* pTestOutput)
{
   return(S_OK);
}

STDMETHODIMP CTestComponent2::ShutDown(ITestOutput* pTestOutput)
{
   return(S_OK);
}


