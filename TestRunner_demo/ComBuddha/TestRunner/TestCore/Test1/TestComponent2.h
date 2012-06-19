// TestComponent2.h : Declaration of the CTestComponent2

#ifndef __TESTCOMPONENT2_H_
#define __TESTCOMPONENT2_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestComponent2
class ATL_NO_VTABLE CTestComponent2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestComponent2, &CLSID_TestComponent2>,
	public ISupportErrorInfo,
	//public IDispatchImpl<ITest, &IID_ITest, &LIBID_TEST1Lib>,
	public IDispatchImpl<ITestComponent2, &IID_ITestComponent2, &LIBID_TEST1Lib>
{
public:
	CTestComponent2()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTCOMPONENT2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestComponent2)
	COM_INTERFACE_ENTRY(ITestComponent2)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ITest)
	COM_INTERFACE_ENTRY2(IDispatch, ITestComponent2)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITestComponent2
public:

// ITest
	STDMETHOD(Run)(ITestOutput* pTestOutput, VARIANT runParameter);
   STDMETHOD(StartUp)(ITestOutput* pTestOutput);
   STDMETHOD(ShutDown)(ITestOutput* pTestOutput);

};

#endif //__TESTCOMPONENT2_H_
