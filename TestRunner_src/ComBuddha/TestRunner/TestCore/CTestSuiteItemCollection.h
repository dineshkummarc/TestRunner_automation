#if !defined(_TESTSUITEITEMCOLLECTION_H)
#define _TESTSUITEITEMCOLLECTION_H

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
// 	Holds a collection of ITestSuiteItems.
// 
// $Log: 
// $
// $Revision: $
// $Date: $
// Author: Jerry Edens
// 
// CTestSuiteItemCollection.h : Declaration of the CTestSuiteItemCollection

#include "resource.h"       // main symbols
#include "ComCollections.h"

// Group = Collections

/////////////////////////////////////////////////////////////////////////////
// Description:
//    Holds a collection of ITestSuiteItems
// 
// Remarks:
//    This collection uses the STL std::vector for implementation.
//
class ATL_NO_VTABLE CTestSuiteItemCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestSuiteItemCollection, &CLSID_CTestSuiteItemCollection>,
	public ISupportErrorInfo,
   public IDispatchImpl<CIndexedObjectCollectionImpl<ITestSuiteItemCollection, ITestSuiteItem,
         IEnumTestSuiteItems>, &__uuidof(ITestSuiteItemCollection)>
{
public:

	CTestSuiteItemCollection()
   {
   }
   
   // Group = Operations

   void FinalRelease()
   {
      Clear();
   }

DECLARE_REGISTRY_RESOURCEID(IDR_CTESTSUITEITEMCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestSuiteItemCollection)
	COM_INTERFACE_ENTRY(ITestSuiteItemCollection)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
// DEL	COM_INTERFACE_ENTRY(IDirectLoad)
END_COM_MAP()

// ISupportsErrorInfo
public:

   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestSuiteItemCollection
public:

   // Initializes the collection from infomation contained in the
   // registry.
   STDMETHOD(LoadFromRegistry)();

// CTestSuiteItemCollection
protected:

   // {secret}
   HRESULT getTestInformation(
      CLSID& clsid, CComBSTR& rbstrName, CComBSTR& rbstrDescription);

private:

};


#endif // _TESTSUITEITEMCOLLECTION_H

