/**
* @file
* Detect behaviors to make them transparent to the register methos function
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      28 May 2004
*/
#include "axsc_stdafx.h"

/**
* check return value
*/
void check_return_value( int return_value )
{
  switch( return_value )
  {
    case asSUCCESS:
      return;

    case asERROR:
      AXE_ASSERT_MSG( false, "An error occured" );
      break;

    case asCONTEXT_ACTIVE:
      AXE_ASSERT_MSG( false, "A script context is currently active" );
      break;

    case asCONTEXT_NOT_FINISHED:
      AXE_ASSERT_MSG( false, "A script context hasn't finished the execution" );
      break;

    case asCONTEXT_NOT_PREPARED:
      AXE_ASSERT_MSG( false, "The context hasn't been prepared yet and cannot be executed" );
      break;

    case asINVALID_ARG:
      AXE_ASSERT_MSG( false, "One or more arguments are invalid" );
      break;

    case asNO_FUNCTION:
      AXE_ASSERT_MSG( false, "No function could be found" );
      break;

    case asNOT_SUPPORTED:
      AXE_ASSERT_MSG( false, "The feature you are trying to use is not yet supported" );
      break;

    case asINVALID_NAME:
      AXE_ASSERT_MSG( false, "The name is invalid" );
      break;

    case asNAME_TAKEN:
      AXE_ASSERT_MSG( false, "The name is taken" );
      break;

    case asINVALID_DECLARATION:
      AXE_ASSERT_MSG( false, "The declaration is invalid" );
      break;

    case asINVALID_OBJECT:
      AXE_ASSERT_MSG( false, "The object is invalid" );
      break;

    case asINVALID_TYPE:
      AXE_ASSERT_MSG( false, "The type is invalid" );
      break;

    case asALREADY_REGISTERED:
      AXE_ASSERT_MSG( false, "The function, property, or object is already registered" );
      break;

    case asMULTIPLE_FUNCTIONS:
      AXE_ASSERT_MSG( false, "Multiple functions were found that matches the search" );
      break;

    case asNO_MODULE:
      AXE_ASSERT_MSG( false, "No module with the specified name could be found" );
      break;

    case asNO_GLOBAL_VAR:
      AXE_ASSERT_MSG( false, "No global variable with the specified name could be found" );
      break;

    case asINVALID_CONFIGURATION:
      AXE_ASSERT_MSG( false, "At least one of the registration methods failed" );
      break;

    case asINVALID_INTERFACE:
      AXE_ASSERT_MSG( false, "The function cannot be bound because the interface is not correct" );
      break;

    case asCANT_BIND_ALL_FUNCTIONS:
      AXE_ASSERT_MSG( false, "Not all of the functions could be bound" );
      break;

    default:
      AXE_ASSERT_MSG( false, "Unknown error" );
      break;
  }
}

/* $Id: axsc_check_errors.cpp,v 1.1 2004/09/26 21:55:59 doneval Exp $ */
