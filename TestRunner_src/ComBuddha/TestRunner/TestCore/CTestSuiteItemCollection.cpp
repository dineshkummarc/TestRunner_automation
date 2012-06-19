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
// CTestSuiteItemCollection.cpp : Implementation of CTestSuiteItemCollection

#include "stdafx.h"

#include "TestCore.h"
#include "CTestSuiteItemCollection.h"

#include "ComCat.h"

#include "INITGUID.H"

// {50105161-8295-11d3-ABF6-00508B0D0D6E}
DEFINE_GUID(CATID_Test, 
   0x50105161, 0x8295, 0x11d3, 0xab, 0xf6, 0x0, 0x50, 0x8b, 0xd, 0xd, 0x6e);

// This is an arbitray value that has no real reason.
const int MAX_REG_VALUE_LENGTH = 512;

/////////////////////////////////////////////////////////////////////////////
// CTestSuiteItemCollection

STDMETHODIMP CTestSuiteItemCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestSuiteItemCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


// {secret}
// 
// Name: 
// 	CTestSuiteItemCollection::getTestInformation
// 
// Description:
// 	Retrieves the test name and description for the provided CLSID.
// 
// Arguments:
// 	clsid - The class is for which the name and description are being requested.
// 
// 	rbstrName - Holder for the test name.
// 
// 	rbstrDescription - Holder for the description.
// 
// Results:
// 
//    S_OK - All is well
//    REGDB_E_KEYMISSING - Could not open the registry key.
//    E_UNEXPECTED - An unknown exception has been caught.
// 
HRESULT CTestSuiteItemCollection::getTestInformation(
      CLSID& clsid, CComBSTR& rbstrName, CComBSTR& rbstrDescription)
{
   HRESULT hr = S_OK;

   TCHAR* sztSubKey = NULL;

   try
   {
      CRegKey keyTestInfo;
      
      LPOLESTR szClsId;
      ::StringFromCLSID(clsid, &szClsId);
      
      USES_CONVERSION;
      CComBSTR bstrSubKey(L"CLSID\\");
      
      bstrSubKey.Append(szClsId);
      ::CoTaskMemFree(szClsId);

      bstrSubKey.Append(L"\\Test Information");

      long lResult = keyTestInfo.Open(HKEY_CLASSES_ROOT, W2T(bstrSubKey));
      if(lResult == ERROR_SUCCESS)
      {

         TCHAR sztName[MAX_REG_VALUE_LENGTH];
         TCHAR sztDescription[MAX_REG_VALUE_LENGTH];

         DWORD count = MAX_REG_VALUE_LENGTH;
         lResult = keyTestInfo.QueryValue(sztName, _T("TestName"), &count);
         
         count = MAX_REG_VALUE_LENGTH;
         lResult = keyTestInfo.QueryValue(sztDescription, _T("Description"), &count);

         rbstrName = sztName;
         rbstrDescription = sztDescription;
      }
      else
      {
         hr = REGDB_E_KEYMISSING;
      }                     
   }
   catch(HRESULT hr)
   {
      ATLTRACE("Error 0x%8x\n", hr);
   }
   catch(_com_error& rerr)
   {
      ATLTRACE("Error 0x%8x\n", rerr.Error());
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

   return(hr);
}

///////////////////////////////////////////////////////////////////
//                  ITestSuiteItemCollection
//

// Group = ITestSuiteItemCollection

// 
// Name: 
// 	CTestSuiteItemCollection::LoadFromRegistry
// 
// Description:
// 	Loads the category information from the registry. Used to initialize 
//    the list of categories.
// 
// Results:
// 
//    S_OK - All is well
//    REGDB_E_KEYMISSING - Could not open the registry key.
//    E_UNEXPECTED - An unknown exception has been caught.
// 
STDMETHODIMP CTestSuiteItemCollection::LoadFromRegistry()
{
   HRESULT hr = S_OK;

   try
   {
      CComPtr<ICatInformation> pCatInfo;
      hr = pCatInfo.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
      CHECK_HR(hr);
      
      CComPtr<IEnumCLSID> pEnumClsId;
      CATID rgcid[1];
      rgcid[0] = CATID_Test;

      // Find all the clsids for the CATID_Test category
      hr = pCatInfo->EnumClassesOfCategories(1, rgcid, -1, 0, &pEnumClsId);
      CHECK_HR(hr);
      
      enum{MAX_CNT = 64};
      CLSID rgClsId[MAX_CNT];

      do
      {
         // For each item in the collection create a ITestSuiteItem and place it into 
         // the collection
         ULONG cActual = 0L;
         hr = pEnumClsId->Next(MAX_CNT, rgClsId, &cActual);
         if(SUCCEEDED(hr))
         {
            for(ULONG l = 0; l < cActual; l++)
            {
               CComPtr<ICustomTestSuiteItem> pCustomItem;
               hr = pCustomItem.CoCreateInstance(__uuidof(CTestSuiteItem));
               CHECK_HR(hr);

               // Get the clsid 
               pCustomItem->put_Clsid(rgClsId[l]);
               
               CComPtr<ITestSuiteItem> pItem;
               pCustomItem.QueryInterface(&pItem);

               // Get the description
               CComBSTR bstrName;
               CComBSTR bstrDescription;

               getTestInformation(rgClsId[l], bstrName, bstrDescription);
               LPOLESTR szProgId;
               ::ProgIDFromCLSID(rgClsId[l], &szProgId);
               pItem->put_ProgId(szProgId);
               ::CoTaskMemFree(szProgId);
               pItem->put_TestName(bstrName);
               pItem->put_Description(bstrDescription);

               // add it to the collection
               Add(pItem);
            }
         }
      }while(hr == S_OK);
      

   }
   catch(HRESULT hr)
   {
      // 
      // Fix Me!
      // 	Make this a more meningful message
      // 
      // Jerry Edens, 10/22/99 1:52:59 PM
      // 
      ATLTRACE("Error 0x%8x\n", hr);
   }
   catch(_com_error& rerr)
   {
      ATLTRACE("Error 0x%8x\n", rerr.Error());
   }
   catch(...)
   {
      hr = E_UNEXPECTED;
   }

	return hr;
}

