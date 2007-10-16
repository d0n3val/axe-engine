/**
* @file
* Init each device type
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      22 May 2004
*/
#include "axip_stdafx.h"

/**
* Init all keyboard devices attached
*/
bool init_keyboard( const DIDEVICEINSTANCE* device_instance, axip_keyboard* keyboard ) {
  AXE_ASSERT( NULL != device_instance && NULL != keyboard );

  HRESULT result;

  /*$1- create the keyboard device -------------------------------------------*/
  result = state.dinput->CreateDevice( device_instance->guidInstance, &keyboard->dinput_device, NULL );
  AXE_CHECK_ERROR( result == DI_OK, 10 );

  /*$1- set dataforma --------------------------------------------------------*/
  result = keyboard->dinput_device->SetDataFormat( &c_dfDIKeyboard );
  AXE_CHECK_ERROR( result == DI_OK, 10 );

  /*$1- set cooperative level ------------------------------------------------*/
  result = keyboard->dinput_device->SetCooperativeLevel(
      state.window,
      DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY );
  AXE_CHECK_ERROR( result == DI_OK, 10 );

  /*$1- set buffered reading of keyboard -------------------------------------*/
  DIPROPDWORD dinput_property;

  dinput_property.diph.dwSize = sizeof( DIPROPDWORD );
  dinput_property.diph.dwHeaderSize = sizeof( DIPROPHEADER );
  dinput_property.diph.dwObj = 0;
  dinput_property.diph.dwHow = DIPH_DEVICE;
  dinput_property.dwData = MAX_KEYBOARD_EVENTS;

  result = keyboard->dinput_device->SetProperty( DIPROP_BUFFERSIZE, &dinput_property.diph );
  AXE_CHECK_ERROR( result == DI_OK, 10 );

  /*$1- save the name of the device ------------------------------------------*/
  strcpy_s( keyboard->name, AXIP_MAX_DEVICE_NAME_LEN, device_instance->tszInstanceName );

  return( true );
}

/**
* Init all mouse devices attached
*/
bool init_mouse( const DIDEVICEINSTANCE* device_instance, axip_mouse* mouse ) {
  AXE_ASSERT( NULL != device_instance && NULL != mouse );

  HRESULT result;

  /*$1- create the mouse device ----------------------------------------------*/
  result = state.dinput->CreateDevice( device_instance->guidInstance, &mouse->dinput_device, NULL );
  AXE_CHECK_ERROR( result == DI_OK, 11 );

  /*$1- set dataformat -------------------------------------------------------*/
  result = mouse->dinput_device->SetDataFormat( &c_dfDIMouse2 );
  AXE_CHECK_ERROR( result == DI_OK, 11 );

  /*$1- set cooperative level ------------------------------------------------*/
  result = mouse->dinput_device->SetCooperativeLevel( state.window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
  AXE_CHECK_ERROR( result == DI_OK, 11 );

  /*$1- set buffered reading of keyboard -------------------------------------*/
  DIPROPDWORD dinput_property;

  dinput_property.diph.dwSize = sizeof( DIPROPDWORD );
  dinput_property.diph.dwHeaderSize = sizeof( DIPROPHEADER );
  dinput_property.diph.dwObj = 0;
  dinput_property.diph.dwHow = DIPH_DEVICE;
  dinput_property.dwData = MAX_MOUSE_EVENTS;

  result = mouse->dinput_device->SetProperty( DIPROP_BUFFERSIZE, &dinput_property.diph );
  AXE_CHECK_ERROR( result == DI_OK, 11 );

  /*$1- get device capabilities  ---------------------------------------------*/
  DIDEVCAPS capabilities;
  capabilities.dwSize = sizeof( DIDEVCAPS );

  result = mouse->dinput_device->GetCapabilities( &capabilities );
  AXE_CHECK_ERROR( result == DI_OK, 11 );

  /*$1- fill with capabilities -----------------------------------------------*/
  mouse->num_vkeys = (int) capabilities.dwButtons;

  /*$1- Put the cursor at 0,0 to make sure vars are correctly reset  ---------*/
  //mouse->set_pos( mengine->mdisplay.mainwindow, 0, 0 );

  /*$1- save the name of the device ------------------------------------------*/
  strcpy_s( mouse->name, AXIP_MAX_DEVICE_NAME_LEN, device_instance->tszInstanceName );

  return( true );
}

/**
* Init all joystick devices attacked
*/
/*
bool init_joystick( const DIDEVICEINSTANCE* device_instance ) {
  AXE_CHECK_ERROR( device_instance != NULL, 12 );
  return( false );
}*/
/* $Id: axip_init_devices.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
