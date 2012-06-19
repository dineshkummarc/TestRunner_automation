#if !defined(CPROPERTYTESTER_H_A2EFEBC1_921D_11d3_AC01_00508B0D0D6E)
#define CPROPERTYTESTER_H_A2EFEBC1_921D_11d3_AC01_00508B0D0D6E

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
// 	 Tests a set of properties associated with the interface.
// 
// $Log: 
// $
// $Revision: $
// $Date: $
// Author: Jerry Edens
// 
// CPropertyTester.h : Definition of CPropertyTester

#if !defined(__ATLBASE_H__)
#error "The AtlBase.h file must be included first."
#endif
#if !defined(CHECK_HR)
#error "CHECK_HR must be defined!"
#endif
#if !defined(RESERVED)
//#error "RESERVED must be defined, normally as 0"
#define RESERVED 0
#endif

#include <map>

// Group = Helper Classes

// 
// Description:
// 	Test the properties of the object.
//
// Author:
// 	Jerry Edens
//
// Include: 
//    #include "CPropertyTester.h"
//
class CPropertyTester
{ 
   // {secret} 
   struct InvokeInfo
   {
      CComPtr<IDispatch> pDispatch; 
      UINT uInvKind;
      CComPtr<ITypeInfo> pITypeInfo; 
      FUNCDESC funcDesc;
      CComPtr<ITestOutput> pTestOutput;
   };

   // These maps hold the put and get information about the properties
   // They are held in seperate maps for the following reasons:
   // 1. The order of the get and puts can not be know before hand.
   //    To propertly test the get and puts the put must be done first
   //    then a get.
   // 2. The properties have the same name so keep them in seperate maps.
   // {secret} 
   typedef std::map< CAdapt< CComBSTR >, InvokeInfo> GetPropertyInfoMap;
   // {secret} 
   typedef std::map< CAdapt< CComBSTR >, InvokeInfo> PutPropertyInfoMap;

public: 

	// Group = Constructors
   
   CPropertyTester()
   {
      bVerbose = false;
   }

   virtual ~CPropertyTester()
   {
      m_getPropertyInfoMap.clear();
      m_putPropertyInfoMap.clear();
   }
	
	// Group = Operations

   // 
   // Name: 
   // 	TestProperties
   // 
   // Description:
   // 	Tests the properties of the interface using IDispatch::Invoke.
   // 
   // Arguments:
   // 	ISupportOutput* pOutput - Used to ouput result messages.
   // 
   // 	IDispatch* - The interface whose properties are to be tested.
   // 
   // Returns:
   //    S_OK - All is well
   //    E_INVALIDARG - The argument is NULL or out of range.
   //    E_UNEXPECTED - An unexpected error has occured.
   //
   virtual HRESULT TestProperties(ITestOutput* pTestOutput, 
         IDispatch* pDispatch)
   {
      ATLASSERT(pTestOutput != NULL);
      ATLASSERT(!::IsBadReadPtr(pTestOutput, sizeof(pTestOutput)));
      ATLASSERT(pDispatch != NULL);
      ATLASSERT(!::IsBadReadPtr(pDispatch, sizeof(pDispatch)));

      HRESULT hr = S_OK;

      try
      {
         processMessage(pTestOutput, _bstr_t(L"Entering CPropertyTester::TestProperties()"));

         if (pTestOutput == NULL || pDispatch == NULL)
         {
            hr = E_INVALIDARG;
            processMessage(pTestOutput, _bstr_t(L"Invalid argument. Either pTestOutput or pDispatch is null!"));
            throw hr;
         }

         // find all the properties in the component

         // determine if the object exposes type information
         UINT cntTypeInfo;
         hr = pDispatch->GetTypeInfoCount(&cntTypeInfo);
         CHECK_HR(hr);

         // The the type information  ITypeInfo
         CComPtr<ITypeInfo> pITypeInfo;
         hr = pDispatch->GetTypeInfo(RESERVED, 0, &pITypeInfo);
         CHECK_HR(hr);

         //ATLTRACE("Retrieving the type info succeeded\n");
         
         TYPEATTR* pTypeAttr = NULL;
         hr = pITypeInfo->GetTypeAttr(&pTypeAttr);
         CHECK_HR(hr);

         // copy the contents locally 
         TYPEATTR typeAttr = *pTypeAttr;
         // release the TYPEATTR resource
         pITypeInfo->ReleaseTypeAttr(pTypeAttr);

         // loop through and look at each interface
         UINT cntFuncNames = typeAttr.cFuncs;
         for (UINT i = 0; i < cntFuncNames; i++)
         {
            FUNCDESC* pFuncDesc = NULL;
            hr = pITypeInfo->GetFuncDesc(i, &pFuncDesc);
            CHECK_HR(hr);

            // Only test properties
            if (pFuncDesc->invkind == INVOKE_PROPERTYGET ||
               pFuncDesc->invkind == INVOKE_PROPERTYPUT ||
               pFuncDesc->invkind == INVOKE_PROPERTYPUTREF)
            {
		        
               CComBSTR bstrPropertyName;
               pITypeInfo->GetDocumentation(pFuncDesc->memid, &bstrPropertyName, null, null, null);

#if defined (_DEBUG) && defined (_SHOW_PROPERY_NAME)
               CComBSTR bstrExplanation(bstrPropertyName);
               bstrExplanation.Append(L" is a ");
               bstrExplanation.Append((pFuncDesc->invkind == INVOKE_PROPERTYGET ? L"get" : L"put"));
               bstrExplanation.Append(L" property... ");
               processMessage(pTestOutput, _bstr_t(bstrExplanation));
#endif

               UINT uInvKind = (pFuncDesc->invkind == INVOKE_PROPERTYGET ? DISPATCH_PROPERTYGET :
                     (pFuncDesc->invkind == INVOKE_PROPERTYPUT ? 
                        DISPATCH_PROPERTYPUT : DISPATCH_PROPERTYPUTREF));

               InvokeInfo invokeInfo;
               invokeInfo.funcDesc = *pFuncDesc;
               invokeInfo.pDispatch = pDispatch; 
               invokeInfo.pITypeInfo = pITypeInfo;
               invokeInfo.pTestOutput = pTestOutput; 
               invokeInfo.uInvKind = uInvKind;

               if (uInvKind == DISPATCH_PROPERTYGET)
               {
                  m_getPropertyInfoMap[bstrPropertyName] = invokeInfo;
               }
               else
               {
                  m_putPropertyInfoMap[bstrPropertyName] = invokeInfo;
               }
                
            }                       
         
            pITypeInfo->ReleaseFuncDesc(pFuncDesc);
           // find the min max values for each property
         }

         PutPropertyInfoMap::iterator putIterBegin;
         PutPropertyInfoMap::iterator putIterEnd;
         putIterBegin = m_putPropertyInfoMap.begin();
         putIterEnd = m_putPropertyInfoMap.end();
         while (putIterBegin != putIterEnd)
         {
            InvokeInfo invokeInfo = (*putIterBegin).second;
            hr = handleInvoke(invokeInfo.pDispatch, invokeInfo.uInvKind, 
                  invokeInfo.pITypeInfo, &invokeInfo.funcDesc, invokeInfo.pTestOutput);
            if (FAILED(hr))
            {
               _bstr_t bstrMessage(L"Invoking ");
               bstrMessage += (invokeInfo.funcDesc.invkind == INVOKE_PROPERTYGET ? L"get_" : L"put_");
               //bstrMessage += bstrPropertyName.m_str;
               bstrMessage += static_cast<BSTR>((*putIterBegin).first.m_T);
               bstrMessage += L" failed.";
               processError(invokeInfo.pTestOutput, hr, bstrMessage);
            }

            putIterBegin++;
         }  // while (iterBegin != iterEnd)

         GetPropertyInfoMap::iterator getIterBegin;
         GetPropertyInfoMap::iterator getIterEnd;
         getIterBegin = m_getPropertyInfoMap.begin();
         getIterEnd = m_getPropertyInfoMap.end();
         while (getIterBegin != getIterEnd)
         {
            InvokeInfo invokeInfo = (*getIterBegin).second;
            hr = handleInvoke(invokeInfo.pDispatch, invokeInfo.uInvKind, 
                  invokeInfo.pITypeInfo, &invokeInfo.funcDesc, invokeInfo.pTestOutput);
            if (FAILED(hr))
            {
               _bstr_t bstrMessage(L"Invoking ");
               bstrMessage += (invokeInfo.funcDesc.invkind == INVOKE_PROPERTYGET ? L"get_" : L"put_");
               //bstrMessage += bstrPropertyName.m_str;
               bstrMessage += static_cast<BSTR>((*getIterBegin).first.m_T);
               bstrMessage += L" failed.";
               processError(invokeInfo.pTestOutput, hr, bstrMessage);
            }

            getIterBegin++;
         }  // while (getIterBegin != getIterEnd)
      }
      catch(HRESULT hr)
      {
         processError(pTestOutput, hr, _bstr_t(L"Caught thrown HRESULT. "));
      }
      catch(_com_error& re)
      {
         hr = re.Error();
         processError(pTestOutput, hr, _bstr_t(L"Caught thrown _com_error. "));
      }
      catch(...)
      {
         hr = E_UNEXPECTED;
         processError(pTestOutput, hr, _bstr_t(L"Caught thrown exception. "));
      }
      
      processMessage(pTestOutput, _bstr_t(L"Exiting CPropertyTester::TestProperties()"));

      return(hr);
   }

   // Group=Virtual Data Members

   // 
   // Name:
   //    bVerbose
   // 
   // Description:
   //    bVerbose is used to determine how much information to 
   //    put out to the log file.  When it is true, more information 
   //    is placed out onto the file.
   // 
   // Remarks:
   //    The default value is false.
   //
   __declspec( property( get=GetbVerbose, put=PutbVerbose ) ) VARIANT_BOOL bVerbose;

   // {secret} 
   VARIANT_BOOL GetbVerbose(){VARIANT_BOOL b; get_bVerbose(&b); return b;}
   // {secret} 
   void PutbVerbose(VARIANT_BOOL newB){put_bVerbose(newB);}

   // {secret} 
   // 
   // Name: 
   // 	get_bVerbose
   // 
   // Description:
   // 	Implementation for the bVerbose property.
   // 
   // Arguments:
   // 	pBool - Holder for the result.
   // 
   void get_bVerbose(VARIANT_BOOL* pBool){ATLASSERT(pBool != NULL); *pBool = m_bVerbose;}

   // {secret} 
   // 
   // Name: 
   //    put_bVerbose 
   // 
   // Description:
   // 	Implementation for the bVerbose property.
   // 
   // Arguments:
   //    newBool - The new value to set.
   // 
   void put_bVerbose(VARIANT_BOOL newBool){m_bVerbose = newBool;}
	

	protected: 
	
   // {secret} 
   // 
   // Name: 
   // 	processMessage
   // 
   // Description:
   // 	Puts the text out to the log. Dependent on the verbose flag.
   // 
   // Arguments:
   // 	pTestOutput - The pointer to the log.
   // 
   // 	bstrMessage - The message to be logged.
   // 
   virtual void processMessage(ITestOutput* pTestOutput, _bstr_t bstrMessage)
   {
      ATLASSERT(pTestOutput != NULL);
      ATLASSERT(!::IsBadReadPtr(pTestOutput, sizeof(ITestOutput*)));

      if (bVerbose && pTestOutput)
      {
         pTestOutput->LogResult(bstrMessage, VARIANT_FALSE);
      }
   }

   // {secret} 
   // 
   // Name: 
   // 	processError
   // 
   // Description:
   // 	Puts the error message onto the log file dependent on the HRESULT passed in.
   // 
   // Arguments:
   // 	pTestOutput - The log onto which to put the message.
   // 
   // 	hr - The error value to base the message on.
   // 
   // 	bstrPrefixInfo - Additional text which gets prefixed onto the message.
   // 
   virtual void processError(ITestOutput* pTestOutput, HRESULT hr, _bstr_t bstrPrefixInfo)
   {
      ATLASSERT(pTestOutput != NULL);
      ATLASSERT(!::IsBadReadPtr(pTestOutput, sizeof(ITestOutput*)));

      LPTSTR sztMessage = NULL;

      try
      {
         if (pTestOutput)
         {
            DWORD dwFlags = 
               FORMAT_MESSAGE_IGNORE_INSERTS | 
               FORMAT_MESSAGE_ALLOCATE_BUFFER |
               FORMAT_MESSAGE_FROM_SYSTEM; 

            // Tells the os to allocate the string buffer
            // so it must be freed.
            FormatMessage(
                  dwFlags, 
                  0,
                  hr, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), 
                  reinterpret_cast<LPTSTR>(&sztMessage), 
                  0, 
                  NULL); 
   
            // clean off any cr-lf's
            if ((sztMessage != NULL && sztMessage[0] != '\0') && 
                  sztMessage[_tcslen(sztMessage) - 1] == '\n')
            {
               sztMessage[_tcslen(sztMessage) - 1] = '\0';
            }
      
            // Prepend the text with any extra info supplied.
            _bstr_t bstrMessage;
            if (bstrPrefixInfo.length() > 0)
            {
               bstrMessage += bstrPrefixInfo;
               bstrMessage += L"  ";
            }

            // Now add the error info to the message.
            bstrMessage += L"Exception: hr = ";
            TCHAR szHR[100];
            wsprintf(szHR, _T("0x%8x, "), hr);
            bstrMessage += szHR;
            bstrMessage += sztMessage;
         
            processMessage(pTestOutput, bstrMessage);
         
            ATLTRACE(static_cast<char*>(bstrMessage));
         }
      }
      catch(...)
      {
      }
      
      LocalFree(sztMessage);
   }

private: 
	
   // {secret}
   #define CASE_STRING( x ) \
      case x: \
         s = _T(#x); \
         break; 

   // {secret}
   // 
   // Name: 
   // 	GetTypeKindName
   // 
   // Description:
   // 	Retrieves the type kind name as a string.
   // 
   // Arguments:
   // 	typekind - The type kind
   // 
   // Results:
   // 	The type kind in the form of a string
   // 
   LPCTSTR GetTypeKindName( TYPEKIND typekind )
   {
      LPTSTR s = _T("<unknown>");
      switch ( typekind )
      {
         CASE_STRING ( TKIND_ENUM )
         CASE_STRING ( TKIND_RECORD )
         CASE_STRING ( TKIND_MODULE )
         CASE_STRING ( TKIND_INTERFACE )
         CASE_STRING ( TKIND_DISPATCH )
         CASE_STRING ( TKIND_COCLASS )
         CASE_STRING ( TKIND_ALIAS )
         CASE_STRING ( TKIND_UNION )
      }
      return s;
   }

   // {secret}
   // 
   // Name: 
   // 	GetInvokeKindName
   // 
   // Description:
   // 	Returns the type of function or property.
   // 
   // Arguments:
   // 	invkind - The invoke kind of the function
   // 
   // Results:
   // 	The invoke kind in the form of a string.
   // 
   LPCTSTR GetInvokeKindName( INVOKEKIND invkind )
   {
      LPTSTR s = _T("<unknown>");
      switch ( invkind )
      {       
         CASE_STRING ( INVOKE_FUNC )
         CASE_STRING ( INVOKE_PROPERTYGET )
         CASE_STRING ( INVOKE_PROPERTYPUT )
         CASE_STRING ( INVOKE_PROPERTYPUTREF )
      }    
      return s;
   }

   // {secret}
   // 
   // Name: 
   // 	GetCallingConventionAsText
   // 
   // Description:
   // 	Retrieves the Calling convention as text
   // 
   // Arguments:
   // 	callConv - The calling convention type
   // 
   // Results:
   // 	The calling type as a string
   // 
   LPCTSTR GetCallingConventionAsText(CALLCONV callConv)
   {
      LPTSTR s = _T("<unknown>");
      switch ( callConv )
      {
         case CC_FASTCALL:
            s = _T("__fastcall");
            break;
         case CC_CDECL:
            s = _T("__cdecl");
            break;
         //case CC_MSCPASCAL:
         case CC_PASCAL:
            s = _T("__pascal");
            break;
         case CC_MACPASCAL:
            s = _T("__macpascal");
            break;
         case CC_STDCALL:
            s = _T("__stdcall");
            break;
         case CC_FPFASTCALL:
            s = _T("__fpfastcall");
            break;
         case CC_SYSCALL:
            s = _T("__syscall");
            break;
         case CC_MPWCDECL:
            s = _T("__mpwcdecl");
            break;
         case CC_MPWPASCAL:
            s = _T("_mpwpascal");
            break;
      }
      return s;
   }

   // {secret}
   // 
   // Name: 
   // 	GetFunctionTypeAsStirng
   // 
   // Description:
   // 	Returns the funtion type as a string.
   // 
   // Arguments:
   // 	funcKind - The function kind
   // 
   // Results:
   // 	The function type as a string
   // 
   LPCTSTR GetFunctionTypeAsStirng(FUNCKIND funcKind)
   {
      LPTSTR s = _T("<unknown>");
      switch ( funcKind )
      {
         case FUNC_VIRTUAL:
            s = _T("virtual");
            break;
         case FUNC_PUREVIRTUAL:
            s = _T("pure virtual");
            break;
         case FUNC_NONVIRTUAL:
            s = _T("non virtual");
            break;
         case FUNC_STATIC:
            s = _T("static");
            break;
         case FUNC_DISPATCH:
            s = _T("dispatch");
            break;
      }
      return s;
   }

   
   // {secret}
   // 
   // Name: 
   // 	handleInvoke
   // 
   // Description:
   // 	Performs needs steps to call invoke on the property
   // 
   // Arguments:
   // 	pDispatch - The IDispatch pointer which is to be tested.
   // 
   // 	uInvKind - The type of property
   // 
   // 	ITypeInfo* pITypeInfo - Points to the typeInfo for this function.  
   //    Currently not used.
   // 
   // 	pFuncDesc - The function description 
   // 
   // 	pTestOutput - Points to the output hook
   // 
   HRESULT handleInvoke(IDispatch* pDispatch, UINT uInvKind, 
         ITypeInfo* pITypeInfo, FUNCDESC* pFuncDesc, 
         ITestOutput* pTestOutput)
   {
      ATLASSERT(pDispatch != NULL);
      ATLASSERT(!::IsBadReadPtr(pDispatch, sizeof(IDispatch*)));
      ATLASSERT(pITypeInfo != NULL);
      ATLASSERT(!::IsBadReadPtr(pITypeInfo, sizeof(ITypeInfo*)));
      ATLASSERT(pFuncDesc != NULL);
      ATLASSERT(!::IsBadReadPtr(pFuncDesc, sizeof(FUNCDESC*)));
      ATLASSERT(pTestOutput != NULL);
      ATLASSERT(!::IsBadReadPtr(pTestOutput, sizeof(ITestOutput)));

      EXCEPINFO excepInfo = {0};
      WORD wFlags = 0;
      UINT uArgErr = 0;
      DISPID dispId[1] = {0};
      CComVariant vars[1];
      CComVariant varResult;
      DISPPARAMS dispParams[1] = {0};
      
      HRESULT hr = E_FAIL; 

      try
      {
         if (pDispatch == NULL || pITypeInfo == NULL || pFuncDesc == NULL || pTestOutput == NULL)
         {
            hr = E_INVALIDARG;
            CHECK_HR(hr);
         }

         switch (uInvKind)
         {
            case INVOKE_PROPERTYGET: 
            {
               wFlags = DISPATCH_PROPERTYGET;
            
               dispParams[0].rgvarg = NULL;
               dispParams[0].cArgs = 0;
               dispParams[0].rgdispidNamedArgs = NULL;
               dispParams[0].cNamedArgs = 0;
               break;
            }
            case INVOKE_PROPERTYPUT:
            {
               wFlags = DISPATCH_PROPERTYPUT;
               dispId[0] = DISPID_PROPERTYPUT;
            
               fillVariant(vars[0], pFuncDesc, pITypeInfo, pTestOutput);
	   	      
               dispParams[0].rgvarg = vars;
               dispParams[0].cArgs = 1;
               dispParams[0].rgdispidNamedArgs = dispId;
               dispParams[0].cNamedArgs = 1;
               break;
            }
            case INVOKE_PROPERTYPUTREF:
            {
               wFlags = DISPATCH_PROPERTYPUTREF;
               dispId[0] = DISPID_PROPERTYPUT;
            
               fillVariant(vars[0], pFuncDesc, pITypeInfo, pTestOutput);
            
               dispParams[0].rgvarg = vars;
               dispParams[0].cArgs = 1;
               dispParams[0].rgdispidNamedArgs = dispId;
               dispParams[0].cNamedArgs = 1;
               break;
            }
            default:
               ATLASSERT(FALSE);
         }

         hr = pDispatch->Invoke(pFuncDesc->memid, IID_NULL, LOCALE_USER_DEFAULT,
               wFlags, dispParams, &varResult, &excepInfo, &uArgErr);

         CComBSTR bstrPropertyName;
         pITypeInfo->GetDocumentation(pFuncDesc->memid, &bstrPropertyName, null, null, null);

         _bstr_t bstrMessage = L"The test of ";
         bstrMessage += (wFlags == DISPATCH_PROPERTYGET ? L"get_" : L"put_");
         bstrMessage += bstrPropertyName.m_str;
      
         // Did the invoke succeeded ?
         if (SUCCEEDED(hr))
         {
            bstrMessage += L", succeeded";
         }
         else
         {
            wchar_t szErrorCode[50];
            swprintf(szErrorCode, L"0x%08x", hr);
            bstrMessage += L", failed with hr = ";
            bstrMessage += szErrorCode;
         }

         pTestOutput->LogResult(bstrMessage, VARIANT_FALSE);

         if (uInvKind == INVOKE_PROPERTYGET)
         {
            logVar(varResult, pTestOutput);
         }
         else
         {
            logVar(vars[0], pTestOutput);
         }
      }
      catch(...)
      {
         hr = E_UNEXPECTED;
      }
            
      return(hr);
   }

   // {secret}
   // 
   // Name: 
   // 	fillVariant
   // 
   // Description:
   // 	Fills the variant with some sample data
   // 
   // Arguments:
   // 	var - The variant which is to be set.
   // 
   // 	pFuncDesc - The function description
   // 
   // 	pITypeInfo - The type information
   // 
   // 	pTestOutput - The log output hook
   // 
   // Remarks:
   //    This method will fill the data with some more reasonable
   //    data once the persistence layer has been implemented.
   // 
   void fillVariant(CComVariant& var, FUNCDESC* pFuncDesc, ITypeInfo* pITypeInfo, 
         ITestOutput* pTestOutput)
   {
      // 
      // Fix Me!
      // 	This needs to be re-done after the persistence layer is complete.
      // 
      // Jerry Edens, 11/1/99 4:13:17 PM
      // 
      var = 123;
   }

   // {secret}
   // 
   // Name: 
   // 	logVar
   // 
   // Description:
   // 	Logs the variant to the test output.
   // 
   // Arguments:
   // 	rVarResult - The variant to log.
   // 
   // 	pTestOutput - The output hook to log to.
   // 
   void logVar(CComVariant& rVarResult, ITestOutput* pTestOutput)
   {
      // 
      // Fix Me!
      // 	This is an arbitrary value.  
      // 
      // Jerry Edens, 11/1/99 4:13:17 PM
      // 
      USES_CONVERSION;
      TCHAR szMessage[1024] = {0};
            
      switch (rVarResult.vt)
      {
         case VT_UI1:                              //    Byte                bVal;               
         {
            _stprintf(szMessage, _T("The varResult is a Byte, = %c"), rVarResult.bVal);
            break; 
         }

         case VT_I2:                               //    Short               iVal;               
         {
            _stprintf(szMessage, _T("The varResult is a Short, = %d"), rVarResult.iVal);
            break; 
         }

         case VT_I4:                               //    long                lVal;               
         {
            _stprintf(szMessage, _T("The varResult is a long, = %d"), rVarResult.lVal);
            break; 
         }

         case VT_R4:                               //    float               fltVal;             
         {
            _stprintf(szMessage, _T("The varResult is a float, = %g"), rVarResult.fltVal);
            break; 
         }

         case VT_R8:                               //    double              dblVal;             
         {
            _stprintf(szMessage, _T("The varResult is a double, = %g"), rVarResult.dblVal);
            break; 
         }

         case VT_BOOL:                             //    VARIANT_BOOL        boolVal;            
         {
            _stprintf(szMessage, _T("The varResult is a VARIANT_BOOL, = %c"), rVarResult.boolVal);
            break; 
         }

         case VT_ERROR:                            //    SCODE               scode;              
         {
            _stprintf(szMessage, _T("The varResult is a SCODE, = 0x%08x"), rVarResult.scode);
            break; 
         }

         case VT_CY:                               //    CY                  cyVal;              
         {
            _stprintf(szMessage, _T("The varResult is a CURRENCY, = %d"), rVarResult.cyVal.int64);
            break; 
         }

         case VT_DATE:                             //    DATE                date;               
         {
            _stprintf(szMessage, _T("The varResult is a DATE, = %d"), rVarResult.date);
            break; 
         }

         case VT_BSTR:                             //    BSTR                bstrVal;            
         {
            _stprintf(szMessage, _T("The varResult is a BSTR, = %s"), W2T(rVarResult.bstrVal));
            break; 
         }

         case VT_BYREF|VT_DECIMAL:                 //    DECIMAL             FAR* pdeal        
         {
            _stprintf(szMessage, _T("The varResult is a DECIMAL, = %d"), (*rVarResult.pdecVal).Hi32);
            break; 
         }

         case VT_UNKNOWN:                          //    IUnknown            FAR* punkVal;       
         {
            _stprintf(szMessage, _T("The varResult is a IUnknown pointer, = %p"), rVarResult.punkVal);
            break; 
         }

         case VT_DISPATCH:                         //    IDispatch           FAR* pdispVal;      
         {
            _stprintf(szMessage, _T("The varResult is a IDispatch pointer, = %p"), rVarResult.pdispVal);
            break; 
         }

         case VT_ARRAY:                             //    SAFEARRAY           FAR* parray;        
         {
            _stprintf(szMessage, _T("The varResult is a SAFEARRAY"));
            break; 
         }

         case VT_BYREF|VT_UI1:                     //    Byte                FAR* pbVal;         
         {
            _stprintf(szMessage, _T("The varResult is a byte by reference, = %c"), *(rVarResult.pbVal));
            break; 
         }

         case VT_BYREF|VT_I2:                      //    short               FAR* piVal;         
         {
            _stprintf(szMessage, _T("The varResult is a short by reference, = %d"), *(rVarResult.piVal));
            break; 
         }

         case VT_BYREF|VT_I4:                      //    long                FAR* plVal;         
         {
            _stprintf(szMessage, _T("The varResult is a long by reference, = %d"), *(rVarResult.plVal));
            break; 
         }

         case VT_BYREF|VT_R4:                      //    float               FAR* pfltVal;       
         {
            _stprintf(szMessage, _T("The varResult is a float by reference, = %g"), *(rVarResult.pfltVal));
            break; 
         }

         case VT_BYREF|VT_R8:                      //    double              FAR* pdblVal;       
         {
            _stprintf(szMessage, _T("The varResult is a double by reference, = %g"), *(rVarResult.pdblVal));
            break; 
         }

         case VT_BYREF|VT_BOOL:                    //    VARIANT_BOOL        FAR* pboolVal;      
         {
            _stprintf(szMessage, _T("The varResult is a VARIANT_BOOL by reference, = %c"), *(rVarResult.pboolVal));
            break; 
         }

         case VT_BYREF|VT_ERROR:                   //    SCODE               FAR* pscode;        
         {
            _stprintf(szMessage, _T("The varResult is a SCODE by reference, = 0x%08x"), *(rVarResult.pscode));
            break; 
         }

         case VT_BYREF|VT_CY:                      //    CY                  FAR* pcyVal;        
         {
            _stprintf(szMessage, _T("The varResult is a CURRENCY by reference, = %d"), (*(rVarResult.pcyVal)).int64);
            break; 
         }

         case VT_BYREF|VT_DATE:                    //    DATE                FAR* pdate;         
         {
            //_stprintf(szMessage, _T("The varResult is a DATE by reference = %d"), (*(rVarResult.pdate)));
            break; 
         }

         case VT_BYREF|VT_BSTR:                    //    BSTR                FAR* pbstrVal;      
         {
            _stprintf(szMessage, _T("The varResult is a BSTR by reference, = %s"), W2T(*(rVarResult.pbstrVal)));
            break; 
         }

         case VT_BYREF|VT_UNKNOWN:                 //    IUnknown            FAR* FAR* ppunkVal; 
         {
            _stprintf(szMessage, _T("The varResult is a IUnknown* by reference, = %p"), (*(rVarResult.ppunkVal)));
            break; 
         }

         case VT_BYREF|VT_DISPATCH:                //    IDispatch           FAR* FAR* ppdispVal;
         {
            _stprintf(szMessage, _T("The varResult is a IDispatch* by reference, = %p"), (*(rVarResult.ppdispVal)));
            break; 
         }

         //case VT_ARRAY|:                          //    SAFEARRAY           FAR* FAR* pparray;  
         //   //_stprintf(szMessage, _T("The varResult = %d"), rVarResult.);
         //  break; 

         case VT_BYREF|VT_VARIANT:                 //    VARIANT             FAR* pvarVal;       
         {
            logVar(CComVariant(*(rVarResult.pvarVal)), pTestOutput);
            break; 
         }

         // Generic ByRef.                         //    void                FAR* byref;         
         case VT_I1:                               //    char                cVal;               
         {
            _stprintf(szMessage, _T("The varResult is a char, = %c"), rVarResult.cVal);
            break; 
         }

         case VT_UI2:                              //    unsigned short      uiVal;              
         {
            _stprintf(szMessage, _T("The varResult is a unsigned short, = %u"), rVarResult.uiVal);
            break; 
         }

         case VT_UI4:                              //    unsigned long       ulVal;              
         {
            _stprintf(szMessage, _T("The varResult is a unsigned long, = %u"), rVarResult.ulVal);
            break; 
         }

         case VT_INT:                              //    int                 intVal;             
         {
            _stprintf(szMessage, _T("The varResult is a int, = %d"), rVarResult.intVal);
            break; 
         }

         case VT_UINT:                             //    unsigned int        uintVal;            
         {
            _stprintf(szMessage, _T("The varResult unsigned int, = %u"), rVarResult.uintVal);
            break; 
         }

         case VT_BYREF|VT_I1:                      //    char FAR *          pal;              
         {
            _stprintf(szMessage, _T("The varResult is a char*, = %s"), (*(rVarResult.pcVal)));
            break; 
         }

         case VT_BYREF|VT_UI2:                     //    unsigned short FAR* puiVal;             
         {
            _stprintf(szMessage, _T("The varResult is a unsigned short*, = %u"), (*(rVarResult.puintVal)));
            break; 
         }

         case VT_BYREF|VT_UI4:                     //    unsigned long FAR * pulVal;             
         {
            _stprintf(szMessage, _T("The varResult is a unsigned long*, = %u"), (*(rVarResult.pulVal)));
            break; 
         }

         case VT_BYREF|VT_INT:                     //    int FAR *           pintVal;            
         {
            _stprintf(szMessage, _T("The varResult is a int*, = %d"), (*(rVarResult.pintVal)));
            break; 
         }

         case VT_BYREF|VT_UINT:                    //    unsigned int FAR *  puintVal;           
         {
            _stprintf(szMessage, _T("The varResult is a unsigned int*, = %u"), (*(rVarResult.puintVal)));
            break; 
         }

         case VT_EMPTY:
         {
            break;
         }
         
         default:                                         
            ATLASSERT(false);
      }
 
      if (szMessage[0] != '\0')
      {
         pTestOutput->LogResult(_bstr_t(szMessage), VARIANT_FALSE);
      }
   }
   
   // {secret} 
   // Don't allow any copies to be made
	CPropertyTester(const CPropertyTester&);
   // {secret} 
   // Don't allow the assigment operator
	CPropertyTester& operator=(const CPropertyTester& rCPropertyTester);
   // {secret} 
   // Don't allow the equality operator
	bool operator==(const CPropertyTester& rCPropertyTester);

   // {secret}
   VARIANT_BOOL m_bVerbose;

   // {secret}
   GetPropertyInfoMap m_getPropertyInfoMap;
   // {secret}
   PutPropertyInfoMap m_putPropertyInfoMap;
}; 
	
#endif      // #define CPROPERTYTESTER_H_A2EFEBC1_921D_11d3_AC01_00508B0D0D6E
