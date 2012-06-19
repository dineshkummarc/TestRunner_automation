#if !defined(_TESTSUITECOLLECTION_H)
#define _TESTSUITECOLLECTION_H

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
// CTestSuiteCollection.h : Declaration of the CTestSuiteCollection

#include "resource.h"       // main symbols
#include "ComCollections.h"

// Group = Collections

/////////////////////////////////////////////////////////////////////////////
// Description:
//    Holds a collection of ITestSuites
// 
// Remarks:
//    This collection uses the STL std::vector for implementation.
//
class ATL_NO_VTABLE CTestSuiteCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestSuiteCollection, &CLSID_CTestSuiteCollection>,
	public ISupportErrorInfo,
   public IDispatchImpl<CIndexedObjectCollectionImpl<ITestSuiteCollection, ITestSuite, 
         IEnumTestSuites>, &__uuidof(ITestSuiteCollection)>
{
public:

   CTestSuiteCollection()
	{
      m_lRunCount = 0L;
	}

   // Group = Operations

   void FinalRelease()
   {
      Clear();
   }

DECLARE_REGISTRY_RESOURCEID(IDR_CTESTSUITECOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestSuiteCollection)
	COM_INTERFACE_ENTRY(ITestSuiteCollection)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
public:
	
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestSuiteCollection
public:

   // {group:properties}
   STDMETHOD(get_RunCount)(/*[out, retval]*/ long *pVal);
   // {group:properties}
	STDMETHOD(put_RunCount)(/*[in]*/ long newVal);


// CTestSuiteCollection
private:

   // {secret}
   // Holds the run count for this test
   long m_lRunCount;

   // {secret}
   template<typename type> 
   HRESULT setVal(type* pDestination, type theSource)
   {
      ATLASSERT(pDestination != NULL);
      ATLASSERT(!::IsBadWritePtr(pDestination, sizeof(type*)));

      HRESULT hr = S_OK;

      try
      {
         if(pDestination)
         {
            *pDestination = theSource;
         }
         else
         {
            hr = E_INVALIDARG;
         }
      }
      catch(_com_error& re)
      {
         hr = re.Error();
      }
      catch(...)
      {
         hr = E_UNEXPECTED;
      }

      return(hr);
   }

   // End of the templates
   /////////////////////////////////////////////////////////////////

};

#endif // _TESTSUITECOLLECTION_H
