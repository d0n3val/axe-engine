/**
* @file
* Struct to store info about a loaded plug in
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      17 Oct 2004
*/
#ifndef __AXPL_LOADED_LIB_H__
  #define __AXPL_LOADED_LIB_H__

  #include "axpl_stdafx.h"

struct loaded_plug_in
{
  void*       address;
  axe_string  path;

  loaded_plug_in::loaded_plug_in ()
  {
    address = NULL;
  }

  loaded_plug_in::loaded_plug_in (void* addr, const char* lib_path) :
  address( addr ),
  path( lib_path )
  {
    AXE_ASSERT( address != NULL );
    AXE_ASSERT( lib_path != NULL );
  }
};
#endif // __AXPL_LOADED_LIB_H__

/* $Id: VAssist.tpl,v 1.2 2004/09/12 23:14:38 ilgenio Exp $ */
