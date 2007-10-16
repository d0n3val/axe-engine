/**
* @file
* Axe 'system_info' library PRIVATE include header
*/
#ifndef __AXSI_SYSTEM_INFO_H__
  #define __AXSI_SYSTEM_INFO_H__

  #include <windows.h>
  #include <comutil.h>
  #include <dxdiag.h>

// axsi_system_info.cpp ----------------------------------------------------------
int                 display_output( const int, const char* , const char*  );

int                 start_dxdiag();
int                 get_variant_dxdiag( VARIANT* value, char* section, const char* property );
int                 get_bool_dxdiag( char* section, const char* property );
int                 get_int_dxdiag( char* section, const char* property );
int                 get_str_dxdiag( char* to_copy, char* section, const char* property );
int                 stop_dxdiag();

IDxDiagContainer*   get_dxdiag_section( char* section );

void                str_to_wstr( const char* string, wchar_t* wide_string );
void                wstr_to_str( const wchar_t* wide_string, char* string );

int                 get_list_num( const int pos, const char* separator, char* list );

time_t              get_date( const char* str );
#endif /*__AXSI_SYSTEM_INFO_H__*/

/* $Id: axsi_system_info.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
