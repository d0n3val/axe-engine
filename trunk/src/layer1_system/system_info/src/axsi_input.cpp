/**
* @file
* Axe 'system_info' code for gathering input device information
*/
#include "axsi_stdafx.h"

extern _state state;

/// Global state of the library

/**
* Comment
*/
int axsi_get_input( axsi_input* input_info ) {
  ZeroMemory( &input_info, sizeof(axsi_input) );
  axsi_set_error( 1 );
  return( AXE_FALSE );

  /*
	if(input_info == NULL) {
		axsi_set_error(3);
		return(AXE_FALSE);
	}

	if(state.input_set == true) {
		memcpy(input_info, &state.input_data, sizeof(axsi_input));
		return(AXE_TRUE);
	}

	if(start_dxdiag() == AXE_FALSE) {
		axsi_set_error(4);
		return(AXE_TRUE);
	}

	char tmp[256];

	// input device ...............

	if(get_dxdiag_section("DxDiag_Directinput.DxDiag_inputDevices.0") != NULL) {

		//state.input_data.device_enabled = AXE_TRUE;

	} else {
		ZeroMemory(&state.input_data, sizeof(axsi_input));
		//state.input_data.device_enabled = AXE_FALSE;
	}

	// ok, stop COM and return results
	stop_dxdiag();

	memcpy(input_info, &state.input_data, sizeof(axsi_input));

	state.input_set = true;

	return(AXE_TRUE);
	*/
}

/* $Id: axsi_input.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
