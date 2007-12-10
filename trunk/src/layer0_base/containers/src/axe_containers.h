/**
* @file
* Axe 'containers' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  24/11/2003
*/
#ifndef __AXE_CONTAINERS_H__
  #define __AXE_CONTAINERS_H__

/*$1-  Lib version -----------------------------------------------------------*/
  #define AXE_CONTAINERS_VERSION  1
  #define AXE_CONTAINERS_NAME     "CONTAINERS"
  #define AXE_CONTAINERS_LIBID    'AXCT'

/** @example axct_test.cpp */

/*$1- Double linked list -----------------------------------------------------*/
  #include "axe_list.h"

/*$1- Static array template --------------------------------------------------*/
  #include "axe_stc_array.h"

/*$1- Dynamic array template -------------------------------------------------*/
  #include "axe_dyn_array.h"

/*$1- BitSet template --------------------------------------------------------*/
  #include "axe_bitset.h"

/*$1- Variant template -------------------------------------------------------*/
  #include "axe_any.h"
#endif // __AXE_CONTAINERS_H__

/* $Id: axe_containers.h,v 1.3 2004/06/15 21:24:35 doneval Exp $ */
