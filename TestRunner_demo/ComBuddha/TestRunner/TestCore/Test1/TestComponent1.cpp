// TestComponent1.cpp : Implementation of CTestComponent1
#include "stdafx.h"
#include "Test1.h"
#include "TestComponent1.h"
#include "..\CPropertyTester.h"

#include <iostream>
using namespace std;
   
class TestOutput : public ITestOutput
{
    HRESULT __stdcall LogResult (
         BSTR bstrMessage )
    {
      USES_CONVERSION;
      cout << W2A(bstrMessage) << endl;
    }
};

class Cfoo
{
public:
   Cfoo(){}
   virtual ~Cfoo(){}
   HRESULT CheckValue(int nValue){return ((nValue>0) ? S_OK:E_FAIL);}
};

/////////////////////////////////////////////////////////////////////////////
// CTestComponent1

STDMETHODIMP CTestComponent1::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestComponent1
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


///////////////////////////////////////////////////////////////////////////////
//                         ITest

STDMETHODIMP CTestComponent1::Run(ITestOutput* pTestOutput, VARIANT runParameter)
{
   ATLASSERT(pTestOutput != NULL);
   ATLASSERT(!::IsBadReadPtr(pTestOutput, sizeof(ITestOutput*)));

   HRESULT hr = S_OK;

   //MessageBox(NULL, _T("CTestComponent1::Run()"), _T("Test App"), MB_OK|MB_TOPMOST);
   if(pTestOutput)
   {  
      //
      // Test a non-COM object, in this case we use a c++ class.
      //

      // Create a c++ object to be tested.
      Cfoo foo;
      pTestOutput->LogStartTime();
      //
      pTestOutput->LogResult(CComBSTR(L"Tesing CFoo"), S_OK);
      hr = foo.CheckValue(5);
      // The actions taken here is the responsibility of the 
      // test component writer.
      if(FAILED(hr))
      {
         // The hr indicates that an error occured.
         //	Passing in S_OK indicates success.
         pTestOutput->LogResult(_bstr_t(L"Checking the value failed."), hr);
      }
      // Stop the test time clock   
      pTestOutput->LogStopTime();

      
      //
      // Test a COM object, in this case we use ITestSuiteItem
      //

      // Start a second test  ...       

      CComPtr<ITestSuiteItem> pItem;
      hr = pItem.CoCreateInstance(L"TestCore.CTestSuiteItem.1");
      if(FAILED(hr))
      {
         pTestOutput->LogResult(L"Creating the ITestSuiteItem failed", hr);
         return hr;
      }

      pTestOutput->LogStartTime();
      pTestOutput->LogResult(CComBSTR(L"Tesing ITestSuiteItem"), S_OK);
      pTestOutput->LogResult(CComBSTR(L"Testing the properties of ITestSuiteItem"), S_OK);

      CPropertyTester ta;
      ta.TestProperties(pTestOutput, static_cast<IDispatch*>(pItem));

      pTestOutput->LogStopTime();
         
      // When the test is in a tight loop, be friendly to scripting and sleep once in awhile.
      //::Sleep(1);      
   }

   return(S_OK);
}

STDMETHODIMP CTestComponent1::StartUp(ITestOutput* pTestOutput)
{
   return(S_OK);
}

STDMETHODIMP CTestComponent1::ShutDown(ITestOutput* pTestOutput)
{
   return(S_OK);
}

STDMETHODIMP CTestComponent1::get_bstrPropName(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTestComponent1::put_bstrPropName(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTestComponent1::get_Count(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTestComponent1::put_Count(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
