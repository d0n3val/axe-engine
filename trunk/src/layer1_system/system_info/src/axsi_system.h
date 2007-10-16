/**
* @file
* Axe 'system_info' header for get_system help functions
*/
#ifndef __AXSI_SYSTEM_H__
  #define __AXSI_SYSTEM_H__

int           get_cpu_count();
unsigned int  get_cpu_speed();
int           get_cpu_family();
int           get_cpu_model();
int           get_cpu_stepping();
int           get_cpu_vendor();
int           get_cpu_type_id( const int family, const int model, const int vendor );
const char*   get_cpu_name( const int family, const int model, const int vendor );
unsigned int  read_cpu_counter();
#endif /*__AXSI_SYSTEM_H__*/

/* $Id: axsi_system.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
