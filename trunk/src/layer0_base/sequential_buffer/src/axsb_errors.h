#pragma once

/**
* @file
* 
* @author    Carlos Fuentes
* @date      23 Aug 2004
*/
#ifndef __AXSB_ERRORS_H__
  #define __AXSB_ERRORS_H__

  #define AXSB_NUM_ERROR_MSG  2

/**
* error messages ids
*/
enum AXE_SEQUENTIAL_BUFFER_ERROR_MSG
{
  AXE_ERROR_MSG_BUFFER_INCORRECT= AXE_BASIC_ERROR_MSG_COUNT,
  AXE_ERROR_MSG_NO_CHUNCKS,
};

/**
* error messages
*/
extern const char*   axsb_error_messages[AXSB_NUM_ERROR_MSG]; 

#endif // __AXSB_ERRORS_H__

/* $Id: axsb_errors.h,v 1.2 2004/08/25 06:16:23 ilgenio Exp $ */
