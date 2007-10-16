/**
* @file
* Axe 'system_info' utilities code
*/
#include "axsi_stdafx.h"
#include <dxdiag.h>

#define SAFE_RELEASE( p ) { \
    if( p ) {               \
      ( p )->Release();     \
      ( p ) = NULL;         \
    }                       \
  }

extern _state state;

/// Global state of the library
int start_dxdiag() {
  HRESULT hr;

  hr = CoInitialize( NULL );
  if( hr < 0 ) {
    axsi_set_error( 5 );
    return( AXE_FALSE );
  }

  // CoCreate a IDxDiagProvider*
  hr = CoCreateInstance(
      CLSID_DxDiagProvider,
      NULL,
      CLSCTX_INPROC_SERVER,
      IID_IDxDiagProvider,
      (LPVOID*) &state.dxdiag_provider );

  if( hr < 0 ) {
    stop_dxdiag();
    return( AXE_FALSE );
  }

  DXDIAG_INIT_PARAMS  dxdiag_params;
  ZeroMemory( &dxdiag_params, sizeof(DXDIAG_INIT_PARAMS) );

  dxdiag_params.dwSize = sizeof( DXDIAG_INIT_PARAMS );
  dxdiag_params.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
  dxdiag_params.bAllowWHQLChecks = FALSE;
  dxdiag_params.pReserved = NULL;

  hr = state.dxdiag_provider->Initialize( &dxdiag_params );

  if( hr < 0 ) {
    stop_dxdiag();
    return( AXE_FALSE );
  }

  hr = state.dxdiag_provider->GetRootContainer( &state.dxdiag_root );

  if( hr < 0 ) {
    stop_dxdiag();
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

IDxDiagContainer* get_dxdiag_section( char* section ) {
  HRESULT             hr;

  IDxDiagContainer*   child = NULL;
  WCHAR               wtmp[256];
  char*               token;
  char                separation[10] = ".";
  bool                first = true;

  // -- patch
  // I don't know why, but If we don't copy the string here in RELEASE mode
  // it crashed in strtok.c ...
  char                section2[256];
  strcpy( section2, section );
  token = strtok( section2, separation );

  // -- patch
  // this only works in DEBUG mode (?!?!)
  // token = strtok(section, separation);
  while( token != NULL ) {
    str_to_wstr( token, wtmp );

    if( first == true ) {
      hr = state.dxdiag_root->GetChildContainer( wtmp, &child );
      first = false;
    } else {
      hr = child->GetChildContainer( wtmp, &child );
    }

    if( hr < 0 ) {
      return( NULL );
    }

    token = strtok( NULL, separation );
  }

  return( child );
}

int get_bool_dxdiag( char* section, const char* property ) {
  VARIANT value;

  if( get_variant_dxdiag(&value, section, property) == AXE_TRUE ) {
    return( (value.boolVal) ? AXE_TRUE : AXE_FALSE );
  }

  return( AXE_FALSE );
}

int get_int_dxdiag( char* section, const char* property ) {
  VARIANT value;

  if( get_variant_dxdiag(&value, section, property) == AXE_TRUE ) {
    return( value.iVal );
  }

  return( AXE_FALSE );
}

int get_str_dxdiag( char* to_copy, char* section, const char* property ) {
  VARIANT value;

  if( get_variant_dxdiag(&value, section, property) == AXE_TRUE ) {
    wstr_to_str( value.bstrVal, to_copy );
    return( AXE_TRUE );
  }

  to_copy[0] = 0;
  return( AXE_FALSE );
}

int get_variant_dxdiag( VARIANT* value, char* section, const char* property ) {
  HRESULT hr;

  VariantInit( value );

  if( state.dxdiag_root == NULL ) {
    return( AXE_FALSE );
  }

  IDxDiagContainer*   child = NULL;

  child = get_dxdiag_section( section );

  if( child == NULL ) {
    return( AXE_FALSE );
  }

  WCHAR wtmp[256];

  str_to_wstr( property, wtmp );

  hr = child->GetProp( wtmp, value );
  if( hr < 0 ) {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

void str_to_wstr( const char* string, wchar_t* wide_string ) {
  int len = (int) strlen( string ) + 1;

  for( register int i = 0; i < len; ++i ) {
    wide_string[i] = string[i];
  }
}

void wstr_to_str( const wchar_t* wide_string, char* string ) {
  int len = (int) wcslen( wide_string ) + 1;

  for( register int i = 0; i < len; ++i ) {
    string[i] = (char) wide_string[i];
  }
}

int stop_dxdiag() {
  SAFE_RELEASE( state.dxdiag_provider );
  SAFE_RELEASE( state.dxdiag_root );
  CoUninitialize();
  return( AXE_TRUE );
}

time_t get_date( const char* str ) {

  // this string comes like "7/28/2003 14:19:00"
  struct tm date;

  sscanf(
    str,
    "%d/%d/%d %d:%d:%d",
    &date.tm_mon,
    &date.tm_mday,
    &date.tm_year,
    &date.tm_hour,
    &date.tm_min,
    &date.tm_sec );

  date.tm_year -= 1900;
  date.tm_mon -= 1;

  return( mktime(&date) );
}

int get_list_num( const int pos, const char* separator, char* list ) {
  char*   token;
  int     i;
  i = 0;

  token = strtok( list, separator );

  while( token != NULL && i < pos ) {
    token = strtok( NULL, separator );
    ++i;
  }

  if( token != NULL ) {
    return( atoi(token) );
  }

  return( AXE_FALSE );
}

/* $Id: axsi_util.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
