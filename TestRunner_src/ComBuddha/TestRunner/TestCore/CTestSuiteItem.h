#if !defined(_CTESTSUITEITEM_H)
#define _CTESTSUITEITEM_H

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
// CTestSuiteItem.h : Declaration of the CTestSuiteItem

#include "resource.h"       // main symbols

// Group = Core Classes

/////////////////////////////////////////////////////////////////////////////
// Description:
//    Used to represent an individual component to be tested.
//
// Author:
// 	Jerry Edens
// 
// Include: 
//    #include "CTestSuiteItem.h"
// 
class ATL_NO_VTABLE CTestSuiteItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestSuiteItem, &CLSID_CTestSuiteItem>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITestSuiteItem, &IID_ITestSuiteItem, &LIBID_TESTCORELib>,
	public ICustomTestSuiteItem
{
public:

   CTestSuiteItem()
	{
      m_lRunCount = 0l;
      m_Clsid = IID_NULL;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_CTESTSUITEITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestSuiteItem)
	COM_INTERFACE_ENTRY(ITestSuiteItem)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ICustomTestSuiteItem)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


// ITestSuiteItem
public:
   
   STDMETHOD(get_ProgId)(/*[out, retval]*/ BSTR *pbstrCLSID);
	STDMETHOD(put_ProgId)(/*[in]*/ BSTR bstrCLSID);
	
   STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pbstrDescription);
	STDMETHOD(put_Description)(/*[in]*/ BSTR bstrDescription);

   STDMETHOD(get_RunCount)(/*[out, retval]*/ long *pRunCount);
	STDMETHOD(put_RunCount)(/*[in]*/ long newRunCount);

   STDMETHOD(get_TestName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TestName)(/*[in]*/ BSTR newVal);


// ICustomTestSuiteItem
private:
   
   STDMETHOD(get_Clsid)(/*[out, retval]*/ CLSID* pCLSID);
	STDMETHOD(put_Clsid)(/*[in]*/ CLSID aCLSID);


// CTestSuiteItem
private:

	CLSID m_Clsid;
   CComBSTR m_bstrProgId;
   CComBSTR m_bstrDescription;
   CComBSTR m_bstrTestName;
   long m_lRunCount;

#include "SetValue.inl"

};

#endif // _CTESTSUITEITEM_H
