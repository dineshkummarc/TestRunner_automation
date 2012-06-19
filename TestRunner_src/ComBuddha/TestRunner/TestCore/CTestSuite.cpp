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
// CTestSuite.cpp : Implementation of CTestSuite
#include "stdafx.h"
#include "TestCore.h"
#include "CTestSuite.h"

/////////////////////////////////////////////////////////////////////////////
// CTestSuite

// {secret}
STDMETHODIMP CTestSuite::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestSuite
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}




///////////////////////////////////////////////////////////////////////////////
// 
//                   ITestSuite
// 
///////////////////////////////////////////////////////////////////////////////



// {group:ITestSuite} 
// 
// Name: 
// 	CTestSuite::put_TestSuiteItems
// 
// Description:
// 	Sets the test suite item collection.
// 
// Arguments:
// 	pITestSuiteItemCollection - Holds a pointer to the test suite item collection
// 
// Precondition:
//    pITestSuiteItemCollection must point to a valid ITestSuiteItemCollection.
//
// Postcondition:
//    m_pTestSuiteItemCollection now points to pITestSuiteItemCollection.
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuite::put_TestSuiteItems(
      ITestSuiteItemCollection* pITestSuiteItemCollection)
{
   ATLASSERT(pITestSuiteItemCollection != null);
   ATLASSERT(!::IsBadWritePtr(pITestSuiteItemCollection, sizeof(ITestSuiteItemCollection*)));

   HRESULT hr = S_OK;

   try
   {
      if (pITestSuiteItemCollection == null)
      {
         hr = E_INVALIDARG, throw hr;
      }
      m_pTestSuiteItemCollection = pITestSuiteItemCollection ;
   }
   catch(HRESULT)
   {
   }
   catch(_com_error& er)
   {
      hr = er.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }
   
   return(hr);
}

// {group:ITestSuite} 
// 
// Name: 
// 	CTestSuite::get_TestSuiteItems
// 
// Description:
// 	Retrieves a pointer to the test suite item collection.
// 
// Arguments:
// 	ppITestSuiteItemCollection - Holder for the ITestSuiteItemCollection pointer.
// 
// Precondition:
//    ppITestSuiteItemCollection must point to a valid ITestSuiteItemCollection*.
//
// Postcondition:
//    (*ppTestSuiteItemCollection) now points to the same collection as m_pTestSuiteItemCollection.
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuite::get_TestSuiteItems(
      ITestSuiteItemCollection** ppITestSuiteItemCollection)
{
   ATLASSERT(ppITestSuiteItemCollection != null);
   ATLASSERT(!::IsBadWritePtr(ppITestSuiteItemCollection, sizeof(ITestSuiteItemCollection*)));

   HRESULT hr = S_OK;

   try
   {
      if (ppITestSuiteItemCollection == null)
      {
         hr = E_INVALIDARG, throw hr;
      }
      m_pTestSuiteItemCollection.CopyTo(ppITestSuiteItemCollection);
   }
   catch(HRESULT)
   {
   }
   catch(_com_error& er)
   {
      hr = er.Error();
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }
   
   return(hr);
}

