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
// CTestSuiteItem.cpp : Implementation of CTestSuiteItem

#include "stdafx.h"
#include "TestCore.h"
#include "CTestSuiteItem.h"

const int MAX_GUID_LENGTH = 40;

/////////////////////////////////////////////////////////////////////////////
// CTestSuiteItem

// {secret}
STDMETHODIMP CTestSuiteItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestSuiteItem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


////////////////////////////////////////////////////////////////////////////
//
//                   ITestSuiteItem 
//
////////////////////////////////////////////////////////////////////////////



// {group:ITestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::get_Description
// 
// Description:
// 	Retrieves the description for the component
// 
// Arguments:
// 	pbstrDescription - Holder for the description
// 
// Precondition:
//    pbstrDescription must be a valid BSTR*.
//
// Postcondition:
//    pbstrDescription will point to a valid BSTR. The caller 
//    is responsible for releasing this memory.
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::get_Description(BSTR* pbstrDescription)
{
   return(setVal(static_cast<BSTR*>(pbstrDescription), m_bstrDescription));
}

// {group:ITestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::pet_Description
// 
// Description:
// 	Sets the description for the component
// 
// Arguments:
// 	bstrDescription - The new description
// 
// Precondition:
//    bstrDescription must be a valid BSTR.
//
// Postcondition:
//    m_bstrDescription will hold a copy of bstrDescription. 
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::put_Description(BSTR bstrDescription)
{
   return(setVal(reinterpret_cast<CComBSTR*>(&m_bstrDescription), bstrDescription));
}

// {group:ITestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::get_RunCount
// 
// Description:
// 	Retrieves the number of times this test is to be executed.
// 
// Precondition:
//    pRunCount must be a valid long*.
//
// Postcondition:
//    pRunCount holds the same value as m_lRunCount.
//
// Arguments:
// 	pRunCount - Holder for the number of tests to run.
// 
// Returns
//    S_OK - All is well 
//    E_INVALIDARG - One of the parameters is invalid.
//    E_UNEXPECTED - An unknown and unexpected exception has occured.
//    
STDMETHODIMP CTestSuiteItem::get_RunCount(long* pRunCount)
{
   return(setVal(pRunCount, m_lRunCount));
}

// {group:ITestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::put_RunCount
// 
// Description:
// 	Sets the number of times this test is to be executed.
// 
// Arguments:
// 	newRunCount - The number of times to run the test
// 
// Postcondition:      
//    m_lRunCount will hold a copy of newRunCount. 
//
// Returns
//    S_OK - All is well 
//    E_INVALIDARG - One of the parameters is invalid.
//    E_UNEXPECTED - An unknown and unexpected exception has occured.
//    
STDMETHODIMP CTestSuiteItem::put_RunCount(long newRunCount)
{
   return(setVal(&m_lRunCount, newRunCount));
}

// {group:ITestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::get_ProgId
// 
// Description:
// 	Retrieves the class id for the component to test.
// 
// Arguments:
// 	pbstrCLSID - Holder for the clsid
// 
// Precondition:
//    pbstrProgId must be a valid BSTR*.
//
// Postcondition:
//    pbstrProgId will point to a copy of m_bstrProgId. The caller 
//    is responsible for releasing this memory.
//
// Results:
//    S_OK - All is well
//    REGDB_E_CLASSNOTREG  - Class not registered in the registry. 
//    REGDB_E_READREGDB - Error reading registry
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::get_ProgId(BSTR* pbstrProgId)
{
   return(setVal(static_cast<BSTR*>(pbstrProgId), m_bstrProgId));
}

// {group:ITestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::put_ProgId
// 
// Description:
// 	Sets the class id for the component to test.from the ProgId
// 
// Arguments:
// 	bstrCLSID - The progId
// 
// Precondition:
//    bstrProgId must be a valid BSTR.
//
// Postcondition:
//    m_bstrProgId will hold a copy of bstrProgId. 
//
// Results:
//    S_OK - All is well
//    CO_E_CLASSSTRING - The registered CLSID for the ProgID is invalid. 
//    REGDB_E_WRITEREGDB - An error occurred writing the CLSID to the registry.
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::put_ProgId(BSTR bstrProgId)
{
   return(setVal(reinterpret_cast<CComBSTR*>(&m_bstrProgId), bstrProgId));
}



////////////////////////////////////////////////////////////////////////////
//
//                   ICustomTestSuiteItem 
//
////////////////////////////////////////////////////////////////////////////

// {group:ICustomTestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::get_Clsid
// 
// Description:
// 	Returns the CLSID for the class to be tested.
// 
// Arguments:
// 	pCLSID - Holder for the CLSID
// 
// Precondition:
//    pCLSID must be a valid CLSID*.
//
// Postcondition:
//    pCLSID will hold a copy of m_Clsid. 
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::get_Clsid(CLSID* pCLSID)
{
   return(setVal(pCLSID, m_Clsid));
}


// {group:ICustomTestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::put_Clsid
// 
// Description:
// 	Sets the CLSID for the class to be tested.
// 
// Arguments:
// 	newCLSID - The CLSID
// 
// Precondition:
//    newCLSID must be a valid CLSID.
//
// Postcondition:
//    m_Clsid will hold a copy of newCLSID. 
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::put_Clsid(CLSID newCLSID)
{
   return(setVal(&m_Clsid, newCLSID));
}


// {group:ICustomTestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::get_TestName
// 
// Description:
// 	Retrieves the name associated with this test
// 
// Arguments:
// 	pbstrTestName -  Holder for the test name
// 
// Precondition:
//    pbstrTestName must be a valid BSTR*.
//
// Postcondition:
//    pbstrTestName will point to a valid BSTR. The caller 
//    is responsible for releasing this memory.
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::get_TestName(BSTR *pbstrTestName)
{
   return(setVal(static_cast<BSTR*>(pbstrTestName), m_bstrTestName));
}


// {group:ICustomTestSuiteItem}
// 
// Name: 
// 	CTestSuiteItem::put_TestName
// 
// Description:
// 	Sets the test name for the class 
// 
// Arguments:
// 	newTestName - The newTestName
// 
// Precondition:
//    newTestName must be a valid BSTR.
//
// Postcondition:
//    m_bstrTestName will hold a copy of newTestName. 
//
// Results:
//    S_OK - All is well
//    E_INVALIDARG - The argument being passed in is invalid (ex. null)
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItem::put_TestName(BSTR newTestName)
{
   return(setVal(reinterpret_cast<CComBSTR*>(&m_bstrTestName), newTestName));
}



