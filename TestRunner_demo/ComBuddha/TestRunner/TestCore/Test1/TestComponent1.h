// TestComponent1.h : Declaration of the CTestComponent1

#ifndef __TESTCOMPONENT1_H_
#define __TESTCOMPONENT1_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CTestComponent1
class ATL_NO_VTABLE CTestComponent1 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestComponent1, &CLSID_TestComponent1>,
	public ISupportErrorInfo,
	//public IDispatchImpl<ITest, &IID_ITest, &LIBID_TEST1Lib>,
	public IDispatchImpl<ITestComponent1, &IID_ITestComponent1, &LIBID_TEST1Lib>
{
public:
	CTestComponent1()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTCOMPONENT1)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestComponent1)
	COM_INTERFACE_ENTRY(ITestComponent1)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ITest)
	COM_INTERFACE_ENTRY2(IDispatch, ITestComponent1)
END_COM_MAP()

// ISupportsErrorInfo
public:
	
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestComponent1
public:

// ITest
public:
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Count)(/*[in]*/ long newVal);
	STDMETHOD(get_bstrPropName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_bstrPropName)(/*[in]*/ BSTR newVal);
   
   STDMETHOD(Run)(ITestOutput* pTestOutput, VARIANT runParameter);
   STDMETHOD(StartUp)(ITestOutput* pTestOutput);
   STDMETHOD(ShutDown)(ITestOutput* pTestOutput);

};

#endif //__TESTCOMPONENT1_H_
