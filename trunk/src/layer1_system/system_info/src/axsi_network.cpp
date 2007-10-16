/**
* @file
* Axe 'system_info' code for gathering network device information
*/
#include "axsi_stdafx.h"

extern _state state;

/// Global state of the library

/**
* Comment
*/
int axsi_get_network( axsi_network* network_info ) {
  ZeroMemory( &network_info, sizeof(axsi_network) );
  axsi_set_error(1);
  return( AXE_FALSE );
}

/* $Id: axsi_network.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
