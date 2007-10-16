/**
* @file
* Axe 'system_info' code for gathering display device information
*/
#include "axsi_stdafx.h"

extern _state state;

/// Global state of the library

/**
* Comment
*/
int axsi_get_display( axsi_display* display_info ) {
  if( display_info == NULL ) {
    axsi_set_error( 3 );
    return( AXE_FALSE );
  }

  if( state.display_set == true ) {
    memcpy( display_info, &state.display_data, sizeof(axsi_display) );
    return( AXE_TRUE );
  }

  if( start_dxdiag() == AXE_FALSE ) {
    axsi_set_error( 4 );
    return( AXE_TRUE );
  }

  char  tmp[256];

  // display device ...............
  if( get_dxdiag_section("DxDiag_DisplayDevices.0") != NULL ) {
    state.display_data.device_enabled = AXE_TRUE;
    get_str_dxdiag( state.display_data.device_name, "DxDiag_DisplayDevices.0", "szDescription" );
    get_str_dxdiag( state.display_data.device_chip_name, "DxDiag_DisplayDevices.0", "szChipType" );
    get_str_dxdiag( state.display_data.device_dac_name, "DxDiag_DisplayDevices.0", "szDACType" );

    get_str_dxdiag( tmp, "DxDiag_DisplayDevices.0", "szManufacturer" );
    state.display_data.device_vendor = get_display_vendor( tmp );

    get_str_dxdiag( tmp, "DxDiag_DisplayDevices.0", "szDisplayMemoryEnglish" );
    state.display_data.device_total_ram = get_display_ram( tmp );

    get_str_dxdiag( state.display_data.device_driver_version, "DxDiag_DisplayDevices.0", "szDriverVersion" );

    get_str_dxdiag( tmp, "DxDiag_DisplayDevices.0", "szDriverDateEnglish" );
    state.display_data.device_driver_date = get_date( tmp );

    state.display_data.device_hardware_accel_enabled = get_bool_dxdiag(
        "DxDiag_DisplayDevices.0",
        "b3DAccelerationEnabled" );

    // monitor ...............
    get_str_dxdiag( tmp, "DxDiag_DisplayDevices.0", "szMonitorMaxRes" );
    state.display_data.monitor_maxres_width = get_list_num( 0, ", ", tmp );

    get_str_dxdiag( tmp, "DxDiag_DisplayDevices.0", "szMonitorMaxRes" );
    state.display_data.monitor_maxres_height = get_list_num( 1, ", ", tmp );

    state.display_data.monitor_res_width = get_int_dxdiag( "DxDiag_DisplayDevices.0", "dwWidth" );

    state.display_data.monitor_res_height = get_int_dxdiag( "DxDiag_DisplayDevices.0", "dwHeight" );

    state.display_data.monitor_res_bpp = get_int_dxdiag( "DxDiag_DisplayDevices.0", "dwBpp" );

    state.display_data.monitor_refresh_rate = get_int_dxdiag( "DxDiag_DisplayDevices.0", "dwRefreshRate" );

    state.display_data.agp_enabled = get_bool_dxdiag( "DxDiag_DisplayDevices.0", "bAGPEnabled" );
  } else {
    ZeroMemory( &state.display_data, sizeof(axsi_display) );

    // redundant but to clarify ...
    state.display_data.device_enabled = AXE_FALSE;
  }

  // ok, stop COM and return results
  stop_dxdiag();

  memcpy( display_info, &state.display_data, sizeof(axsi_display) );

  state.display_set = true;

  return( AXE_TRUE );
}

int get_display_vendor( const char* name ) {
  if( !strcmp("NVIDIA", name) ) {
    return( AXSI_GPU_VENDOR_NVIDIA );
  }

  if( !strcmp("ATI", name) ) {
    return( AXSI_GPU_VENDOR_ATI );
  }

  return( AXSI_GPU_VENDOR_UNKNOWN );
}

int get_display_ram( const char* str ) {

  // this string comes like "128.0 MB"
  int   pos;
  char  tmp[25];

  pos = (int) strcspn( str, "." );
  strncpy( tmp, str, pos );
  tmp[pos] = 0;

  return( atoi(tmp) );
}

/* $Id: axsi_display.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
