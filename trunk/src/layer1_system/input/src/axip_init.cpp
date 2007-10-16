/**
* @file
* Init and close all devices
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 May 2004
*/
#include "axip_stdafx.h"

/**
* Init directinput
*/
AXIP_API int axip_init( HWND window, HINSTANCE instance ) {
  AXE_ASSERT( window != NULL && instance != NULL && false == state.init);

  /*$1- Save current window and instance pareametes for future use -----------*/
  state.window = window;
  state.instance = instance;

  HRESULT result;

  /*$1- Create directinput object  -------------------------------------------*/
  result = DirectInput8Create( state.instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**) &state.dinput, NULL );
  AXE_CHECK_ERROR( result == DI_OK, 8 );

  /*$1- set a callback to call for every device attached to the system -------*/
  result = state.dinput->EnumDevices( DI8DEVCLASS_ALL, init_device_callback, NULL, DIEDFL_ATTACHEDONLY );
  AXE_CHECK_ERROR( result == DI_OK, 9 );

  /*$1- All ok */
  state.init = true;

  return( AXE_TRUE );
}

/**
* Internal function that will call each init function per device attached
*/
BOOL CALLBACK init_device_callback( const DIDEVICEINSTANCE* device_instance, void* user_data ) {
  AXE_ASSERT( user_data == NULL );

  bool  result = true;
  int   type = LOBYTE( LOWORD(device_instance->dwDevType) );

  axip_device *device = NULL;

  switch( type )
  {
    case DI8DEVTYPE_KEYBOARD:
      device = new axip_keyboard;
      result = init_keyboard( device_instance, (axip_keyboard*) device );
      break;

    case DI8DEVTYPE_MOUSE:
      device = new axip_mouse;
      result = init_mouse( device_instance, (axip_mouse*) device );
      break;

    case DI8DEVTYPE_1STPERSON:
    case DI8DEVTYPE_FLIGHT:
    case DI8DEVTYPE_GAMEPAD:
    case DI8DEVTYPE_JOYSTICK:
      //result = init_joystick( device_instance, device );
      result = false;
      break;

    default:
      result = false;
      break;
  }

  if( false == result ) {
    AXE_RELEASE(device);
  } else {
    state.device_list.add( device );
  }

  return( DIENUM_CONTINUE );
}

/**
* Finish directinput
*/
AXIP_API int axip_done() {
  AXE_ASSERT(state.init == true);
  if( NULL != state.dinput ) {
    state.dinput->Release();
    state.dinput = NULL;
  }

  state.init = false;

  return( AXE_TRUE );
}

/* $Id: axip_init.cpp,v 1.2 2004/06/11 20:14:29 doneval Exp $ */
