/**
* @file
* Axe 'system_info' code to detect cpu capabilities
*/
#include "axsi_stdafx.h"

extern long   GetDXVersion( unsigned long* pdwDirectXVersion );

extern _state state;

/// Global state of the library

/**
* Comment
*/
AXSI_API int axsi_os_version() {
  if( state.os_version >= 0 ) {
    return( state.os_version );
  }

  OSVERSIONINFO os_version;

  // read the OS Version data
  os_version.dwOSVersionInfoSize = sizeof( os_version );
  GetVersionEx( &os_version );

  switch( os_version.dwPlatformId )
  {
    case VER_PLATFORM_WIN32s:         // win32 or win 3.1
      state.os_version = AXSI_WINDOWS_OLD;
      break;

    case VER_PLATFORM_WIN32_WINDOWS:  // win95, win98 ot winME
      switch( os_version.dwMinorVersion )
      {
        case 0:
          // this is win95 system
          if( os_version.szCSDVersion[1] == 'C' || os_version.szCSDVersion[1] == 'B' ) {
            state.os_version = AXSI_WINDOWS_95_SR2;
          } else {
            state.os_version = AXSI_WINDOWS_95;
          }

          break;

        case 10:
          if( os_version.szCSDVersion[1] == 'A' ) {
            state.os_version = AXSI_WINDOWS_98_SE;
          } else {
            state.os_version = AXSI_WINDOWS_98;
          }

          break;

        case 90:
          state.os_version = AXSI_WINDOWS_ME;
          break;
      }

      break;

    case VER_PLATFORM_WIN32_NT:
      // NT, 2K or XP
      switch( os_version.dwMinorVersion )
      {
        case 51:
          state.os_version = AXSI_WINDOWS_NT3;
          break;

        case 0:
          if( os_version.dwMajorVersion == 4 ) {
            state.os_version = AXSI_WINDOWS_NT4;
          } else {
            state.os_version = AXSI_WINDOWS_2K;
          }

          break;

        case 1:
          state.os_version = AXSI_WINDOWS_XP;
          break;

        case 2:
          state.os_version = AXSI_WINDOWS_2003;
          break;

        default:
          state.os_version = AXSI_WINDOW_FUTURE;
          break;
      }

      break;
  }

  if( state.os_version <= 0 ) {
    state.os_version = AXSI_WINDOWS_UNKNOWN;
  }

  return( state.os_version );
}

/**
* Comment
*/
AXSI_API const char* axsi_os_version_string() {
  if( axsi_os_version() == AXE_FALSE ) {
    return( NULL );
  }

  switch( state.os_version )
  {
    case AXSI_WINDOWS_OLD:
      return( "Windows 32s or 3.1" );

    case AXSI_WINDOWS_95:
      return( "Windows 95" );

    case AXSI_WINDOWS_95_SR2:
      return( "Windows 95 SR2" );

    case AXSI_WINDOWS_98:
      return( "Windows 98" );

    case AXSI_WINDOWS_98_SE:
      return( "Windows 98 Second Edition" );

    case AXSI_WINDOWS_ME:
      return( "Windows Millenium Edition" );

    case AXSI_WINDOWS_NT3:
      return( "Windows NT 3.51" );

    case AXSI_WINDOWS_NT4:
      return( "Windows NT 4.0" );

    case AXSI_WINDOWS_2K:
      return( "Windows 2000" );

    case AXSI_WINDOWS_XP:
      return( "Windows XP" );

    case AXSI_WINDOWS_2003:
      return( "Windows 2003 Server" );
  }

  return( "Unknown Windows" );
}

/**
* Comment
*/
AXSI_API int axsi_directx_version() {
  if( state.dx_version >= 0 ) {
    return( state.dx_version );
  }

  unsigned long dx_version;

  GetDXVersion( &dx_version );

  switch( dx_version )
  {
    case 0x00000000:
      state.dx_version = AXSI_DX_NO_INSTALLED;
      break;

    case 0x00010000:
      state.dx_version = AXSI_DX_1;
      break;

    case 0x00020000:
      state.dx_version = AXSI_DX_2;
      break;

    case 0x00030000:
      state.dx_version = AXSI_DX_3;
      break;

    case 0x00030001:
      state.dx_version = AXSI_DX_3a;
      break;

    case 0x00050000:
      state.dx_version = AXSI_DX_5;
      break;

    case 0x00060000:
      state.dx_version = AXSI_DX_6;
      break;

    case 0x00060100:
      state.dx_version = AXSI_DX_61;
      break;

    case 0x00060101:
      state.dx_version = AXSI_DX_61a;
      break;

    case 0x00070000:
      state.dx_version = AXSI_DX_7;
      break;

    case 0x00070001:
      state.dx_version = AXSI_DX_7a;
      break;

    case 0x00080000:
      state.dx_version = AXSI_DX_8;
      break;

    case 0x00080100:
      state.dx_version = AXSI_DX_81;
      break;

    case 0x00080101:
      state.dx_version = AXSI_DX_81a;
      break;

    case 0x00080102:
      state.dx_version = AXSI_DX_81b;
      break;

    case 0x00080200:
      state.dx_version = AXSI_DX_82;
      break;

    case 0x00090000:
      state.dx_version = AXSI_DX_9;
      break;

    case 0x00090001:
      state.dx_version = AXSI_DX_9a;
      break;

    case 0x00090002:
      state.dx_version = AXSI_DX_9b;
      break;

    default:
      state.dx_version = AXSI_DX_UNKNOWN;
      break;
  }

  if( dx_version > 0x00090002 ) {
    state.dx_version = AXSI_DX_FUTURE;
  }

  return( state.dx_version );
}

/**
* Comment
*/
AXSI_API const char* axsi_directx_version_string() {
  if( axsi_directx_version() == AXE_FALSE ) {
    return( NULL );
  }

  switch( state.dx_version )
  {
    case AXSI_DX_NO_INSTALLED:
      return( "No DirectX installed" );

    case AXSI_DX_UNKNOWN:
      return( "??" );

    case AXSI_DX_1:
      return( "1.0" );

    case AXSI_DX_2:
      return( "2.0" );

    case AXSI_DX_3:
      return( "3.0" );

    case AXSI_DX_3a:
      return( "3.0a" );

    case AXSI_DX_5:
      return( "5.0" );

    case AXSI_DX_6:
      return( "6.0" );

    case AXSI_DX_61:
      return( "6.1" );

    case AXSI_DX_61a:
      return( "6.1a" );

    case AXSI_DX_7:
      return( "7.0" );

    case AXSI_DX_7a:
      return( "7.0a" );

    case AXSI_DX_8:
      return( "8.0" );

    case AXSI_DX_81:
      return( "8.1" );

    case AXSI_DX_81a:
      return( "8.1a" );

    case AXSI_DX_81b:
      return( "8.1b" );

    case AXSI_DX_82:
      return( "8.2" );

    case AXSI_DX_9:
      return( "9.0" );

    case AXSI_DX_9a:
      return( "9.0a" );

    case AXSI_DX_9b:
      return( "9.0b" );

    case AXSI_DX_FUTURE:
      return( ">9.0b" );
  }

  return( NULL );
}

/* $Id: axsi_platform.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */