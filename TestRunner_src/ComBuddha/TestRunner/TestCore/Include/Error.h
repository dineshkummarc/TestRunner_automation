#ifndef TRERROR_H_43E4EEC0_1B65_11d3_A8EE_00104BCD4C49
#define TRERROR_H_43E4EEC0_1B65_11d3_A8EE_00104BCD4C49

#if _MSC_VER > 100
#pragma once
#endif // _MSC_VER > 100

// This file holds the macros for creating Test Runner specific
// error messages.  This file also holds the Test Runner Module numbers.

///////////////////////////////
// Please refer to <winerror.h>
//
// The upper 16 bits of HRESULT are predetermined;
//    Severity    == SEVERITY_SUCCESS || SEVERITY_ERROR
//    Facility    == FACILITY_ITF (4)
// and other bits are reserved.  This leaves the lower 16 bits for general use, 
// Test Runner Module numbers use (8 bits) and then the Module Error (8 bits).  

#define MAKE_TESTRUNNER_HRESULT_(mod, num)  (((unsigned short)(mod) << 8) | ((unsigned short)(num) & 0x00ff))

#define MAKE_TESTRUNNER_SUCCESS(mod, num)   (MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, MAKE_TESTRUNNER_HRESULT_(mod, num)))

#define MAKE_TESTRUNNER_ERROR(mod, num)     (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, MAKE_TESTRUNNER_HRESULT_(mod, num)))

#define GET_TESTRUNNER_HRESULT_(hr)         (HRESULT_FACILITY(hr) == FACILITY_ITF ? ((unsigned)((hr) & 0x0000FFFFL)) : 0)

#define GET_TESTRUNNER_MODULE(hr)           (HRESULT_FACILITY(hr) == FACILITY_ITF ? ((unsigned short)(((hr) & 0x0000FF00L) >> 8)) : 0 ) 

#define GET_TESTRUNNER_ERRNUM(hr)           (HRESULT_FACILITY(hr) == FACILITY_ITF ? ((unsigned short)((hr) & 0x000000FFL)) : 0 )



#define TR_MODULE_FIRST             (CV_MODULE_GENERAL)
#define TR_MODULE_GENERAL           (0x04)
#define TR_MODULE_CORE              (0x05)
#define TR_MODULE_GUI               (0x06)

#define TR_MOD_LAST_AVAILABLE        (0xFF) // Can't exceed this module number


#endif   // #define CVERROR_H_43E4EEC0_1B65_11d3_A8EE_00104BCD4C49
