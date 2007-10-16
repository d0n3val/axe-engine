/**
* @file
* Get info for each device found
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      22 May 2004
*/
#include "axip_stdafx.h"

/**
* Get total number of devices found
*/
AXIP_API int axip_get_num_devices() {
  AXE_ASSERT( NULL != state.dinput );
  return( state.device_list.size );
}

/**
* Get info about certain device
*/
AXIP_API int axip_get_device( const int num_device, axip_device_info* device_info ) {
  AXE_ASSERT( NULL != device_info );
  AXE_ASSERT( num_device >= 0 && num_device < state.device_list.size );

  /*$1- Get the device user is asking for  -----------------------------------*/
  axip_device*  dev = state.device_list[num_device];

  /*$1- Fill the struct with data --------------------------------------------*/
  strcpy_s( device_info->name, AXIP_MAX_DEVICE_NAME_LEN, dev->name );
  device_info->type = dev->type;
  device_info->active = ( true == dev->active ) ? AXE_TRUE : AXE_FALSE;
  device_info->num_vkeys = dev->num_vkeys;

  return( AXE_TRUE );
}

/**
* Get directly a device name
*/
const char* axip_get_device_name( const int num_device ) {
  AXE_ASSERT( num_device >= 0 && num_device < state.device_list.size );

  /*$1- Get the device user is asking for  -----------------------------------*/
  axip_device*  dev = state.device_list[num_device];

  return( dev->name );
}
