/**
* @file
* 
* @author    Carlos Fuentes
* @date      23 Aug 2004
*/
#ifndef __AXSB_BUFFER_H__
  #define __AXSB_BUFFER_H__

  #include "axsb_stdafx.h"

struct axsb_chunck_info
{
  unsigned short  id;
  unsigned int    start;
  unsigned int    size;
};

struct axsb_buffer_info
{
  char*                           ptr;
  size_t                          size;
  size_t                          offset;
  axe_dyn_array<axsb_chunck_info> read_chuncks;
  axe_dyn_array<axsb_chunck_info> write_chuncks;
};
#endif // __AXSB_BUFFER_H__

/* $Id: axsb_buffer.h,v 1.3 2004/08/29 13:01:22 ilgenio Exp $ */
