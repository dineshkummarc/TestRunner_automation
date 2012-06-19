#pragma once

#include <atlbase.h>
#include <atlcom.h>

#include <winnt.h>
#include <wtypes.h>

template <class DestinationType, class SourceType = DestinationType>
class CCopyPolicy
{
public:
	static void init(DestinationType* p)
	{
		_Copy<DestinationType>::init(p);
	}

	static HRESULT copy(DestinationType* pTo, SourceType* pFrom)
	{
		return _Copy<DestinationType>::copy(pTo, pFrom);
	}

	static void destroy(DestinationType* p)
	{
		_Copy<DestinationType>::destroy(p);
	}
};

template <>
class CCopyPolicy<BSTR>
{
public:
	static void init(BSTR* pbstr)
	{
	}

	static HRESULT copy(BSTR* pbstrTo, BSTR* pbstrFrom)
	{
		HRESULT hr;

		if (*pbstrTo = SysAllocStringByteLen(reinterpret_cast<const char*>(*pbstrFrom), SysStringByteLen(*pbstrFrom)))
		{
			hr = S_OK;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		return hr;
	}

	static void destroy(BSTR* pbstr)
	{
		SysFreeString(*pbstr);
	}
};

template <>
class CCopyPolicy<VARIANT, BSTR>
{
public:
	static void init(VARIANT* pvar)
	{
		CCopyPolicy<VARIANT>::init(pvar);
	}

	static HRESULT copy(VARIANT* pvarTo, BSTR* pbstrFrom)
	{
		HRESULT hr;

		pvarTo->vt = VT_BSTR;
		
		if (pvarTo->bstrVal = SysAllocString(*pbstrFrom))
		{
			hr = S_OK;
		}
		else
		{
			hr = E_OUTOFMEMORY;
		}

		return hr;
	}

	static void destroy(VARIANT* pvar)
	{
		CCopyPolicy<VARIANT>::destroy(pvar);
	}
};

template <class Interface>
class CCopyInterfacePolicy
{
public:
	static void init(Interface** p)
	{
		_CopyInterface<Interface>::init(p);
	}

	static HRESULT copy(Interface** pTo, Interface** pFrom)
	{
		return _CopyInterface<Interface>::copy(pTo, pFrom);
	}

	static void destroy(Interface** p)
	{
		_CopyInterface<Interface>::destroy(p);
	}
};

template <class Interface>
class CCopyVariantFromInterfacePolicy
{
public:
	static void init(VARIANT* pvar)
	{
		VariantInit(pvar);
	}
	
	static HRESULT copy(VARIANT* pvarTo, Interface** pFrom)
	{
		HRESULT hr;
		
		hr = (*pFrom)->QueryInterface(IID_IDispatch, reinterpret_cast<void**>(&pvarTo->pdispVal));

		if (SUCCEEDED(hr))
		{
			pvarTo->vt = VT_DISPATCH;
		}
		else
		{
			hr = (*pFrom)->QueryInterface(IID_IUnknown, reinterpret_cast<void**>(&pvarTo->punkVal));

			if(SUCCEEDED(hr))
			{
				pvarTo->vt = VT_UNKNOWN;
			}
		}
		
		return hr;
	}
	
	static void destroy(VARIANT* pvar)
	{
		VariantClear(pvar);
	}
};

template <class DestinationType, class PairType>
class CCopyFromPairPolicy
{
public:
	static void init(DestinationType* p)
	{
		CCopyPolicy<DestinationType>::init(p);
	}

	static HRESULT copy(DestinationType* pTo, PairType* pFrom)
	{
		return CCopyPolicy<DestinationType, PairType::second_type>::copy(pTo, &pFrom->second);
	}

	static void destroy(DestinationType* p)
	{
		CCopyPolicy<DestinationType>::destroy(p);
	}
};

template <class SourceType, class PairType>
class CCopyToPairPolicy
{
public:
	static void init(PairType* p)
	{
		CCopyPolicy<PairType::second_type>::init(&p->second);
	}

	static HRESULT copy(PairType* pTo, SourceType* pFrom)
	{
		return CCopyPolicy<PairType::second_type, SourceType>::copy(&pTo->second, pFrom);
	}

	static void destroy(PairType* p)
	{
		CCopyPolicy<PairType::second_type>::destroy(&p->second);
	}
};

template <class Interface, class PairType>
class CCopyInterfaceFromPairPolicy
{
public:
	static void init(Interface** p)
	{
		CCopyInterfacePolicy<Interface>::init(p);
	}

	static HRESULT copy(Interface** pTo, PairType* pFrom)
	{
		return CCopyInterfacePolicy<Interface>::copy(pTo, &pFrom->second);
	}

	static void destroy(Interface** p)
	{
		CCopyInterfacePolicy<Interface>::destroy(p);
	}
};

template <class Interface, class PairType>
class CCopyInterfaceToPairPolicy
{
public:
	static void init(PairType* p)
	{
		CCopyInterfacePolicy<Interface>::init(&p->second);
	}

	static HRESULT copy(PairType* pTo, Interface** pFrom)
	{
		return CCopyInterfacePolicy<Interface>::copy(&pTo->second, pFrom);
	}

	static void destroy(PairType* p)
	{
		CCopyInterfacePolicy<Interface>::destroy(&p->second);
	}
};

template <class Interface, class PairType>
class CCopyVariantFromInterfaceInPairPolicy
{
public:
	static void init(VARIANT* pvar)
	{
		CCopyVariantFromInterfacePolicy<Interface>::init(pvar);
	}

	static HRESULT copy(VARIANT* pvarTo, PairType* pFrom)
	{
		return CCopyVariantFromInterfacePolicy<Interface>::copy(pvarTo, &pFrom->second);
	}

	static void destroy(VARIANT* pvar)
	{
		CCopyVariantFromInterfacePolicy<Interface>::destroy(pvar);
	}
};
