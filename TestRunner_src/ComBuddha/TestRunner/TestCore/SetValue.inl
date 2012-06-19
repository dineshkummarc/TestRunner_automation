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
   ////////////////////////////////////////////////////////////////////////////
   //
   //                          Templated functions
   //
   ////////////////////////////////////////////////////////////////////////////
   
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

   template<typename BSTR> 
   HRESULT setVal(BSTR* pDestination, CComBSTR theSource)
   {
      ATLASSERT(pDestination != NULL);
      ATLASSERT(!::IsBadWritePtr(pDestination, sizeof(BSTR*)));

      HRESULT hr = S_OK;

      try
      {
         if(pDestination)
         {
            theSource.CopyTo(pDestination);
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

   template<class CComBSTR> 
   HRESULT setVal(CComBSTR* pDestination, BSTR theSource)
   {
      ATLASSERT(pDestination != NULL);
      ATLASSERT(!::IsBadWritePtr(pDestination, sizeof(CComBSTR*)));

      HRESULT hr = S_OK;

      try
      {
         if(pDestination)
         {
            (*pDestination) = theSource;
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

