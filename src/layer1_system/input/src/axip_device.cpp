/**
* @file
* Class for a generic device
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      23 May 2004
*/
#include "axip_stdafx.h"

/**
* Constructor
*/
axip_device::axip_device()
{
  dinput_device = NULL;
  type = AXIP_DEVICE_UNKNOWN;
  num_vkeys = 0;
  active = false;
  num_events = 0;
}

/**
* Destructor
*/
axip_device::~axip_device()
{
  if( NULL != dinput_device )
  {
    dinput_device->Release();
    dinput_device = NULL;
  }
}

/**
* Update, store all buffered data from last call
*/
bool axip_device::update_device( DIDEVICEOBJECTDATA* buffer, DWORD* buffer_size )
{
  HRESULT result;

  result = dinput_device->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), buffer, buffer_size, 0 );

  switch( result )
  {
    case DI_OK:
      break;

    /*$1- Overflow, redefine MAX_KEYBOARD/MOUSE_EVENTS in axip_stdafx.h --------*/
    case DI_BUFFEROVERFLOW:
      AXE_ASSERT( 0 );
      return( true );

    /*$1- Data is not yet available --------------------------------------------*/
    case E_PENDING:
      return( false );

    /*$1- The operation cannot be performed unless the device is acquired  -----*/
    case DIERR_NOTACQUIRED:
      acquire_device( true );
      return( false );

    /*$1- Access to the input device has been lost. It must be reacquired  -----*/
    case DIERR_INPUTLOST:
      acquire_device( true );
      return( false );

    /*$1- Unknown error --------------------------------------------------------*/
    default:
      AXE_ASSERT( 0 );
  }

  return( true );
}

/**
* Claim the device to the OS
*/
bool axip_device::acquire_device( bool acquire )
{
  HRESULT result;

  /*$1- We want to gain control of the device --------------------------------*/
  if( true == acquire )
  {
    result = dinput_device->Acquire();
  }
  else
  {
    result = dinput_device->Unacquire();
  }

  switch( result )
  {
    case DI_OK:
    case S_FALSE:
      break;

    case DIERR_OTHERAPPHASPRIO:
      AXE_CHECK_ERROR( 0, 13 );
      break;

    default:
      AXE_ASSERT( 0 );
      break;
  }

  return( true );
}

/* $Id: axip_device.cpp,v 1.2 2004/09/20 21:28:09 doneval Exp $ */
