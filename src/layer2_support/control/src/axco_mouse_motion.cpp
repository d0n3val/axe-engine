/**
* @file
* Updates and checks mouse motion alerts
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      10 Jul 2004
*/
#include "axco_stdafx.h"

/**
* Updates mouse motion
*/
void update_mouse_mov( int device_num, int x, int y )
{
  axco_mouse_info*  mouse_info = get_mouse_device( device_num );

  mouse_info->last_x_motion += x;
  mouse_info->last_y_motion += y;

  axco_set_mouse_pos( mouse_info->x + x, mouse_info->y + y, device_num );
}

/**
* Updates mouse motion
*/
AXCO_API int axco_get_mouse_motion( int device_num, int* x, int* y )
{
  axco_mouse_info*  mouse_info = get_mouse_device( device_num );

  *x = mouse_info->last_x_motion;
  *y = mouse_info->last_y_motion;

  mouse_info->last_x_motion = 0;
  mouse_info->last_y_motion = 0;

  return(AXE_TRUE);
}

/* $Id: axco_mouse_motion.cpp,v 1.2 2004/08/29 18:28:44 doneval Exp $ */
