/**
* @file
* Axe 'errors' include header
*/

#pragma once

#ifndef __AXSI_ERRORS_H__
#define __AXSI_ERRORS_H__

AXSI_API int axsi_set_error_data(const int, char*, long);

#ifdef _DEBUG

  #define AXE_ASSERT(cond) _ASSERT(cond)

#else

  #define AXE_ASSERT ((void)0)
  
#endif

  #define AXSI_CHECK(cond, error)  if(cond == false) { \
                                    axsi_set_error(error); \
                                    return(AXE_FALSE); \
                                    }
#ifdef _DEBUG

#define AXSI_CHECK_DEBUG(cond, error) AXSI_CHECK(cond, error)

#else

#define AXSI_CHECK_DEBUG(cond, error) ((void)0)

#endif

#ifdef _DEBUG

#define axsi_set_error(error)	if((axsi_set_error_data(error, __FILE__, __LINE__)) ==  AXE_FALSE ) _CrtDbgBreak();								   

#else

#define axsi_set_error(error)	axsi_set_error_data(error, __FILE__, __LINE__)

#endif





#endif // __AXSI_ERRORS_H__
