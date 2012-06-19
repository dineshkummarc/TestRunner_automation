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
// $Log: 
// $
// $Revision: $
// $Date: $
// Author: Jerry Edens
//
// CTestSuiteCollection.cpp : Implementation of CTestSuiteCollection

#include "stdafx.h"
#include "TestCore.h"
#include "CTestSuiteCollection.h"

/////////////////////////////////////////////////////////////////////////////
// CTestSuiteCollection

STDMETHODIMP CTestSuiteCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestSuiteCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
//                            ITestSuiteCollection
//


// Group = ITestSuiteCollection

// 
// Name: 
// 	CTestSuiteCollection::get_RunCount
// 
// Description:
// 	Retrieves the number of times this test is to be executed.
// 
// Arguments:
// 	pRunCount - Holder for the number of tests to run.
// 
// Returns
//    S_OK - All is well 
//    E_INVALIDARG - One of the parameters is invalid.
//    E_UNEXPECTED - An unknown and unexpected exception has occured.
//    
STDMETHODIMP CTestSuiteCollection::get_RunCount(long *pRunCount)
{
   return(setVal(pRunCount, m_lRunCount));
}

// 
// Name: 
// 	CTestSuiteCollection::put_RunCount
// 
// Description:
// 	Sets the number of times this test is to be executed.
// 
// Arguments:
// 	newRunCount - The number of times to run the test
// 
// Returns
//    S_OK - All is well 
//    E_INVALIDARG - One of the parameters is invalid.
//    E_UNEXPECTED - An unknown and unexpected exception has occured.
//    
STDMETHODIMP CTestSuiteCollection::put_RunCount(long newRunCount)
{
   return(setVal(&m_lRunCount, newRunCount));
}         

