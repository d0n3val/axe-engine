/**
* @file
* Query some info about loaded plug -ns
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      17 Oct 2004
*/

#include "axpl_stdafx.h"

/**
* Ask if some plug in is already loaded
*/
AXPL_API int is_plug_in_loaded( const char* path )
{
  AXE_LIST_FOR_ITEM(state.loaded_libs, loaded_plug_in, p_item)
  {
    if ( p_item->data.path == path ) {
      return(AXE_TRUE);
    }
  }

  return(AXE_FALSE);
}

/* $Id: VAssist.tpl,v 1.2 2004/09/12 23:14:38 ilgenio Exp $ */
