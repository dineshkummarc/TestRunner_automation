#pragma once

#include <atlbase.h>
#include <atlcom.h>

#include <winnt.h>
#include <wtypes.h>

#include <vector>
#include <map>

#include "ComCopyPolicies.h"

template <class CollectionInterface, class ExposedItemType, class CustomEnumInterface, class ContainerType, 
	class OutgoingItemCopyPolicy, class IncomingItemCopyPolicy, class VariantCopyPolicy>
class CCollectionImpl :
	public ICollectionOnSTLImpl<CollectionInterface, ContainerType, ExposedItemType, OutgoingItemCopyPolicy,
			CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, VariantCopyPolicy, ContainerType> >
{
	typedef CComEnumOnSTL<CustomEnumInterface,
		&__uuidof(CustomEnumInterface),
		ExposedItemType,
		OutgoingItemCopyPolicy,
		ContainerType> CustomEnumImpl;

public:

// 
// Name: 
//	get_NewEnum
// 
// Description:
//	Get a new custom enumerator for this collection.
// 
// Arguments:
//	ppEnum - 
// 
// Remarks:
//	This property is analogous to the restricted _NewEnum property
//	used by Automation clients. Instead of returning an IEnumVARIANT
//	pointer, it returns a CustomEnumInterface pointer which is
//	correctly typed to return the appropriate object based on
//	the template parameters used when deriving from this class.
// 
	STDMETHOD(get_NewEnum)(CustomEnumInterface** ppEnum)
	{
		if (ppEnum == NULL)
		{
			return E_POINTER;
		}

		*ppEnum = NULL;
		
		HRESULT hr = S_OK;
		CComObject<CustomEnumImpl>* p;
		
		if (SUCCEEDED(hr = CComObject<CustomEnumImpl>::CreateInstance(&p)))
		{
			hr = p->Init(this, m_coll);
		
			if (hr == S_OK)
			{
				hr = p->QueryInterface(__uuidof(CustomEnumInterface), (void**)ppEnum);
			}
		}

		if (hr != S_OK)
		{
			delete p;
		}

		return hr;
	}

// 
// Name: 
//	Clear
// 
// Description:
//	Remove each item in the collection.
//
// Remarks:
//	Each item in the collection will be "destroyed" based on the copy
//	policy specified when deriving from this class. Objects will have
//	Release called on them, BSTRs will be SysStringFree'd, etc.
// 
	STDMETHOD(Clear)()
	{
		for (ContainerType::iterator it = m_coll.begin();
			it != m_coll.end();
			++it)
		{
				IncomingItemCopyPolicy::destroy(&*it);
		}

		m_coll.erase(m_coll.begin(), m_coll.end());

		return S_OK;
	}
};

template <class CollectionInterface, class ExposedItemType, class CustomEnumInterface,
	class ContainerType, class OutgoingItemCopyPolicy, class IncomingItemCopyPolicy, class VariantCopyPolicy>
class CIndexedCollectionImpl : 
	public CCollectionImpl<CollectionInterface, ExposedItemType, CustomEnumInterface,
		ContainerType, OutgoingItemCopyPolicy, IncomingItemCopyPolicy, VariantCopyPolicy>
{
public:
	STDMETHOD(Add)(ExposedItemType Item)
	{
		HRESULT hr;

		ContainerType::value_type InternalItem;
		IncomingItemCopyPolicy::init(&InternalItem);

		if (SUCCEEDED(hr = IncomingItemCopyPolicy::copy(&InternalItem, &Item)))
		{
			m_coll.insert(m_coll.end(), InternalItem);
		}

		return hr;
	}
	
	STDMETHOD(Insert)(long lIndex, ExposedItemType Item)
	{
		HRESULT hr;

		ContainerType::value_type InternalItem;
		IncomingItemCopyPolicy::init(&InternalItem);

		if (SUCCEEDED(hr = IncomingItemCopyPolicy::copy(&InternalItem, &Item)))
		{
			if (lIndex < 1 || lIndex > static_cast<long>(m_coll.size()))
			{
				hr = E_INVALIDARG;
			}
			else
			{
				ContainerType::iterator it = m_coll.begin();

				while (it != m_coll.end() && lIndex > 1)
				{
					++it;
					--lIndex;
				}
				
				m_coll.insert(it, InternalItem);
			}
		}

		return hr;
	}

	STDMETHOD(Remove)(long lIndex)
	{
		HRESULT hr = S_OK;

		if (lIndex < 1 || lIndex > static_cast<long>(m_coll.size()))
		{
			hr = E_INVALIDARG;
		}
		else
		{
			ContainerType::iterator it = m_coll.begin();

			while (it != m_coll.end() && lIndex > 1)
			{
				++it;
				--lIndex;
			}

			if (it != m_coll.end())
			{
				IncomingItemCopyPolicy::destroy(&*it);
				m_coll.erase(it);
			}
		}

		return hr;
	}
};

template <class CollectionInterface, class ExposedItemType, class CustomEnumInterface,
	class ContainerType, class OutgoingItemCopyPolicy, class IncomingItemCopyPolicy, class VariantCopyPolicy>
class CKeyedCollectionImpl : 
	public CCollectionImpl<CollectionInterface, ExposedItemType, CustomEnumInterface,
		ContainerType, OutgoingItemCopyPolicy, IncomingItemCopyPolicy, VariantCopyPolicy>
{
	typedef CCollectionImpl<CollectionInterface, ExposedItemType, CustomEnumInterface,
			ContainerType, OutgoingItemCopyPolicy, IncomingItemCopyPolicy, VariantCopyPolicy>
		CollectionImpl;

public:

	STDMETHOD(get_Item)(VARIANT varKey, ExposedItemType* pItem)
	{
		HRESULT hr;

		switch (varKey.vt)
		{
			case VT_BSTR:
				{
					CComBSTR bstrKey = varKey.bstrVal;

					ContainerType::iterator it = m_coll.find(bstrKey);

					if (it == m_coll.end())
					{
						hr = E_FAIL;
					}
					else
					{
						hr = OutgoingItemCopyPolicy::copy(pItem, &*it);
					}
				}
				break;
			case VT_I2:
				hr = CollectionImpl::get_Item(varKey.iVal, pItem);
				break;
			case VT_I4:
				hr = CollectionImpl::get_Item(varKey.lVal, pItem);
				break;
			case VT_UI1:
				hr = CollectionImpl::get_Item(varKey.bVal, pItem);
				break;
			case VT_UI2:
				hr = CollectionImpl::get_Item(varKey.uiVal, pItem);
				break;
			case VT_UI4:
				hr = CollectionImpl::get_Item(varKey.ulVal, pItem);
				break;
			default:
				hr = E_INVALIDARG;
		}

		return hr;
	}

	STDMETHOD(Insert)(BSTR bstrKey, ExposedItemType Item)
	{
		HRESULT hr;

		
		ContainerType::value_type InternalPair(CAdapt<CComBSTR>(bstrKey), ContainerType::referent_type());
		IncomingItemCopyPolicy::init(&InternalPair);

		if (SUCCEEDED(hr = IncomingItemCopyPolicy::copy(&InternalPair, &Item)))
		{
			std::pair<ContainerType::iterator, bool> p = m_coll.insert(InternalPair);

			hr = p.second ? S_OK : E_FAIL;
		}

		return hr;
	}

	STDMETHOD(Remove)(BSTR bstrKey)
	{
		HRESULT hr = S_OK;

		ContainerType::iterator it = m_coll.find(CComBSTR(bstrKey));

		if (it != m_coll.end())
		{
			hr = E_FAIL;
		}
		else
		{
			IncomingItemCopyPolicy::destroy(&*it);
			m_coll.erase(it);
		}

		return hr;
	}
};

template <class CollectionInterface, class ObjectInterface, class CustomEnumInterface, class ContainerType = std::vector<ObjectInterface*> >
class CIndexedObjectCollectionImpl :
	public CIndexedCollectionImpl<CollectionInterface, ObjectInterface*, CustomEnumInterface, ContainerType,
		CCopyInterfacePolicy<ObjectInterface>,
		CCopyInterfacePolicy<ObjectInterface>,
		CCopyVariantFromInterfacePolicy<ObjectInterface> >
{
};

template <class CollectionInterface, class ObjectInterface, class CustomEnumInterface, class ContainerType = std::map<CAdapt<CComBSTR>, ObjectInterface*> >
class CKeyedObjectCollectionImpl :
	public CKeyedCollectionImpl<CollectionInterface, ObjectInterface*, CustomEnumInterface, ContainerType,
		CCopyInterfaceFromPairPolicy<ObjectInterface, ContainerType::value_type>,
		CCopyInterfaceToPairPolicy<ObjectInterface, ContainerType::value_type>,
		CCopyVariantFromInterfaceInPairPolicy<ObjectInterface, ContainerType::value_type> >
{
};

template <class CollectionInterface, class CustomEnumInterface, class ContainerType = std::vector<BSTR> >
class CIndexedBstrCollectionImpl :
	public CIndexedCollectionImpl<CollectionInterface, BSTR, CustomEnumInterface, ContainerType,
		CCopyPolicy<BSTR>,
		CCopyPolicy<BSTR>,
		CCopyPolicy<VARIANT, BSTR> >
{
};

template <class CollectionInterface, class CustomEnumInterface, class ContainerType = std::map<CAdapt<CComBSTR>, BSTR> >
class CKeyedBstrCollectionImpl :
	public CKeyedCollectionImpl<CollectionInterface, BSTR, CustomEnumInterface, ContainerType,
		CCopyFromPairPolicy<BSTR, ContainerType::value_type>,
		CCopyToPairPolicy<BSTR, ContainerType::value_type>,
		CCopyFromPairPolicy<VARIANT, ContainerType::value_type> >
{
};
