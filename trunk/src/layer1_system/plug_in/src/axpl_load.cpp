/**
* @file
* Load and unloads plug-ins
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      04 Oct 2004
*/
#include "axpl_stdafx.h"

/**
* Set plug-in search directory (default is own directory)
*/
AXPL_API int axpl_set_directory( const char* file_name )
{
  AXE_ASSERT( NULL != file_name );
  AXE_ASSERT( strlen(file_name) < MAX_DIR_LEN );

  strcpy_s( state.default_directory, 256, file_name );

  return( AXE_TRUE );
}

/**
* Load a plug in
*/
AXPL_API const AXE_ID axpl_load( const char* file_name )
{
  AXE_ASSERT( NULL != file_name );

  axe_string path("%s%s", state.default_directory, file_name);

  void*   lib_id = LoadLibraryEx( path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
  AXE_ASSERT( NULL != lib_id );

  loaded_plug_in plug_in(lib_id, path);

  AXE_ID id = (AXE_ID) state.loaded_libs.add(plug_in);

  return( id );
}

/**
* Unload a plug in
*/
AXPL_API int axpl_unload( const AXE_ID plug_in_id )
{
  axe_list_item<loaded_plug_in>*  item = ( axe_list_item < loaded_plug_in > * ) plug_in_id;
#ifdef _DEBUG
  bool                    ok = state.loaded_libs.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  AXE_ASSERT( NULL != item->data.address );

  int res = (int) FreeLibrary( (HMODULE) item->data.address );

  AXE_ASSERT( 1 == res );
  return( res );
}

/**
* Get a function pointer for a plug in already loaded
*/
AXPL_API const void* axpl_get_function( const AXE_ID plug_in_id, const char* function_name )
{
  AXE_ASSERT( NULL != function_name );

  axe_list_item<loaded_plug_in>*  item = ( axe_list_item < loaded_plug_in > * ) plug_in_id;
#ifdef _DEBUG
  bool                    ok = state.loaded_libs.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  AXE_ASSERT( NULL != item->data.address );

  void* p_func = (void*) GetProcAddress((HMODULE) item->data.address, (LPCSTR) function_name);

  AXE_ASSERT(NULL != p_func);
  return(p_func);
}

/* $Id$ */
