#ifndef GENERAL_ERROR_H
#define GENERAL_ERROR_H

#pragma once

#include "Error.h"

/*
   The values of the error/success codes.

   These values can be some flux during development so,
   by defining the value of each code the mc and this file 
   are less likely to get out of sync.
*/
enum
{
   // ERROR CODES
   INVALID_FIELD                    = 0x01,
   PRECONDITION_FAILED              = 0x02,

   // SUCCESS CODES
//   xxxx                    = 0x01,
};


/*
  NOTE:  If using the .mc file this enum is not needed.  However,
  if not using the .mc file the enum below will be needed to define
  the module specific messages.

*/

#define MAKE_TESTRUNNER_GENERAL_ERROR(num) \
      MAKE_TESTRUNNER_ERROR(TR_MODULE_GENERAL, num)

#define MAKE_TESTRUNNER_GENERAL_SUCCESS(num) \
      MAKE_TESTRUNNER_SUCCESS(TR_MODULE_GENERAL, num)

//  These are the generated HRESULT codes
enum
{
   // ERROR CODES
   TRE_GENERAL_INVALID_FIELD = MAKE_TESTRUNNER_GENERAL_ERROR(INVALID_FIELD),
   TRE_GENERAL_PRECONDITION_FAILED = MAKE_TESTRUNNER_GENERAL_ERROR(PRECONDITION_FAILED),

   // SUCCESS CODES
   //TRS_GENERAL_xxx = MAKE_TESTRUNNER_GENERAL_SUCCESS(xxx)
};

#endif
