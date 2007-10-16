/**
* @file
* Axe 'system_info' code for gathering sound device information
*/
#include "axsi_stdafx.h"

extern _state state;

/// Global state of the library

/**
* Comment
*/
int axsi_get_sound( axsi_sound* sound_info ) {
  if( sound_info == NULL ) {
    axsi_set_error(3);
    return( AXE_FALSE );
  }

  if( state.sound_set == true ) {
    memcpy( sound_info, &state.sound_data, sizeof(axsi_sound) );
    return( AXE_TRUE );
  }

  if( start_dxdiag() == AXE_FALSE ) {
    axsi_set_error( 4 );
    return( AXE_TRUE );
  }

  // sound device ...............
  if( get_dxdiag_section("DxDiag_DirectSound.DxDiag_SoundDevices.0") != NULL ) {
    state.sound_data.device_enabled = AXE_TRUE;

    get_str_dxdiag( state.sound_data.device_name, "DxDiag_DirectSound.DxDiag_SoundDevices.0", "szDescription" );

    state.sound_data.device_acceleration_level = get_int_dxdiag(
        "DxDiag_DirectSound.DxDiag_SoundDevices.0",
        "lAccelerationLevel" );

    // -- music ---
    state.sound_data.music_enabled = AXE_FALSE;
    state.sound_data.music_accel = AXE_FALSE;

    if( get_dxdiag_section("DxDiag_DirectMusic") != NULL ) {
      if( get_bool_dxdiag("DxDiag_DirectMusic", "bDMusicInstalled") == AXE_TRUE ) {
        state.sound_data.music_enabled = AXE_TRUE;

        state.sound_data.music_accel = get_bool_dxdiag( "DxDiag_DirectMusic", "bAccelerationEnabled" );
      }
    }
  } else {
    ZeroMemory( &state.sound_data, sizeof(axsi_sound) );
    state.sound_data.device_enabled = AXE_FALSE;
  }

  // ok, stop COM and return results
  stop_dxdiag();

  memcpy( sound_info, &state.sound_data, sizeof(axsi_sound) );

  state.sound_set = true;

  return( AXE_TRUE );
}

/* $Id: axsi_sound.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
