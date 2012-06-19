#if !defined(_CDURATIONCOUNTER_H_25B3D161_96D2_11d3_AC04_00508B0D0D6E)
#define _CDURATIONCOUNTER_H_25B3D161_96D2_11d3_AC04_00508B0D0D6E

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#if !defined(_TESTCOREXMLFORMATDEFS_H_B0D0CCC0_9313_11d3_AC03_00508B0D0D6E)
#error TestCoreXMLFormatDefs.h must be included first.
#endif
#include <stdio.h>

// Group = Helper Classes

// 
// Description:
//    Wraps up the QueryPerformance counter and provides the ability to 
//    format a time string.
// 
// Author:
//    Jerry Edens
//
// Include:
//    #include "CDurationCounter.h"
//
class CDurationCounter
{ 
public:

   // 'TORs 

   CDurationCounter()
   {
      m_lnStartCount.QuadPart = 0L;
      m_lnStopCount.QuadPart = 0L;
   }

   virtual ~CDurationCounter()
   {
   }
   
	
	// Group = Operations
   
   void start()
   {
      QueryPerformanceCounter(&m_lnStartCount);
   }

   void stop()
   {
      QueryPerformanceCounter(&m_lnStopCount);
   }

   // NOTE:
   // The desitnation buffer needs to be 255 bytes long
   // This requirement is so that there is less chance 
   // of buffer overruns.
   
   HRESULT toString(TCHAR szDurationString[MAX_TIME_STRING_SIZE])
   {
      HRESULT hr = S_OK;
      try
      {
         LARGE_INTEGER lnDuration_uSec = {0};
         LARGE_INTEGER lnFrequency;
         QueryPerformanceFrequency(&lnFrequency);

         lnDuration_uSec.QuadPart = 
               ((m_lnStopCount.QuadPart - m_lnStartCount.QuadPart) * 
                  ((LONGLONG)1E9/lnFrequency.QuadPart)) /  (LONGLONG)1E3; // could divide by 1E9 for Time in Sec

         _stprintf(szDurationString, gk_szDurationTimeFormatString, 
               lnDuration_uSec.LowPart/(LONG)1E6,           // Seconds
               (lnDuration_uSec.LowPart/(LONG)1E3)%(1000),  // miliSeconds
               (lnDuration_uSec.LowPart)%(1000));           // microSeconds
      }
      catch(HRESULT)
      {
      }
      catch(...)
      {
         hr = E_UNEXPECTED;
      }

      return(hr);
   }
	
private: 
	
   // {secret}	
   LARGE_INTEGER m_lnStartCount;
   // {secret}	
   LARGE_INTEGER m_lnStopCount;
}; 
	
#endif //	_CDURATIONCOUNTER_H_25B3D161_96D2_11d3_AC04_00508B0D0D6E
