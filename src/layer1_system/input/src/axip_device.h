/*
* @file
* Data that describes a single DInput device
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      22 May 2004
*/
#ifndef __AXIP_DEVICE_H__
  #define __AXIP_DEVICE_H__

  #include "axip_stdafx.h"

  #define MAX_DEVICE_NAME_LEN MAX_PATH

/**
* Base data struct for a device
*/
class axip_device
{
  public:
    LPDIRECTINPUTDEVICE8  dinput_device;
    axip_device_type      type;
    int                   num_vkeys;
    char                  name[AXIP_MAX_DEVICE_NAME_LEN];
    bool                  active;
    unsigned int          num_events;
  public:
    axip_device();
    virtual                     ~axip_device();
    virtual bool                update( const int my_id ) = 0;
    virtual const axip_event*   get_events() const = 0;
  protected:
    bool  update_device( DIDEVICEOBJECTDATA* buffer, DWORD* buffer_size );
    bool  acquire_device( bool acquire );
};
#endif // __AXIP_DEVICE_H__

/* $Id: axip_device.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
