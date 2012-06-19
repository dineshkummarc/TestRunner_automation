#if !defined(_TESTSUITE_H)
#define _TESTSUITE_H

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
// CTestSuite.h : Declaration of the CTestSuite

// Group = Core Classes

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Description:
//    Holds a set of ITestSuiteItems which compose a Test Suite
//
// Remarks:
//    Uses a ITestSuiteItemCollection for implementation of the collectin.
//
// Author:
// 	Jerry Edens
//
// Include:
//    #include "CTestSuite.h" 
// 
class ATL_NO_VTABLE CTestSuite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestSuite, &CLSID_CTestSuite>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITestSuite, &IID_ITestSuite, &LIBID_TESTCORELib>
{
public:
   
   // Group = TORS

	CTestSuite()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CTESTSUITE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestSuite)
	COM_INTERFACE_ENTRY(ITestSuite)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ITestSuite
public:

   STDMETHOD(put_TestSuiteItems)(/*[in]*/ 
         ITestSuiteItemCollection* pITestSuiteItemCollection);

   STDMETHOD(get_TestSuiteItems)(/*[out, retval]*/ 
         ITestSuiteItemCollection** ppITestSuiteItemCollection);

// ISupportsErrorInfo
public:
	
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// CTestSuite
protected:

   CComPtr<ITestSuiteItemCollection> m_pTestSuiteItemCollection;
};




#endif // _TESTSUITE_H
