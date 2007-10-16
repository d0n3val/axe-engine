/**
* @file
* _state class include header
* Used to store all data about current library state
*/
#ifndef __AXSI_STATE_H__
  #define __AXSI_STATE_H__

  #include "axsi_stdafx.h"
  #include <dxdiag.h>

/**
* This class stores all data related to the state of the library
* @todo this must be a singleton
*/
class _state
{
  public:
    int                 last_error;       /// last error code
    char                error_file[128];  /// file name of last error
    long                error_line;       /// line of last error
    int                 error_output;     /// output send on set error
    int                 dump_output;      /// output send on dump call
    int                 mode;             /// indicates debug or release compilation mode
    unsigned long       cpu_flags;

    /// last error code
    unsigned long       cpu_extended_flags;

    /// last error code
    unsigned long       cpu_info;

    /// last error code
    unsigned long       cpu_info2;
    int                 os_version;
    int                 dx_version;

    IDxDiagProvider*    dxdiag_provider;
    IDxDiagContainer*   dxdiag_root;

    axsi_system         system_data;
    axsi_cpu_flags      cpu_flags_data;
    axsi_display        display_data;
    axsi_input          input_data;
    axsi_sound          sound_data;
    axsi_network        network_data;

    bool                system_set;
    bool                display_set;
    bool                input_set;
    bool                sound_set;
    bool                network_set;
    bool                cpu_flags_set;
  public:
    _state() {
      last_error = 0;
      mode = 1;
      error_output = AXSI_NONE;
      dump_output = AXSI_OUTPUT_DEBUG;
      error_line = 0;

      cpu_flags = cpu_extended_flags = cpu_info = cpu_info2 = 0;
      os_version = dx_version = -1;

      dxdiag_provider = NULL;
      dxdiag_root = NULL;

      system_set = display_set = input_set = false;
      sound_set = network_set = cpu_flags_set = false;
    }

    ~_state() {
      if( dxdiag_provider != NULL ) {
        stop_dxdiag();
      }
    }
};
#endif // __AXSI_STATE_H__

/* $Id: axsi_state.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
