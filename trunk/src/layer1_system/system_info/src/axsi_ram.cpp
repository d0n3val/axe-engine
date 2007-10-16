/**
* @file
* Axe 'system_info' code for gathering RAM stats
*/
#include "axsi_stdafx.h"

#define AXSI_DIV_MEM  1024

extern _state state;

/// Global state of the library

/**
* Comment
*/
AXSI_API unsigned int axsi_get_total_ram() {
  MEMORYSTATUS  mem_stats;

  GlobalMemoryStatus( &mem_stats );

  return( (unsigned int) (mem_stats.dwTotalPhys + mem_stats.dwTotalPageFile) / AXSI_DIV_MEM );
}

/**
* Comment
*/
AXSI_API unsigned int axsi_get_total_real_ram() {
  MEMORYSTATUS  mem_stats;

  GlobalMemoryStatus( &mem_stats );

  return( (unsigned int) (mem_stats.dwTotalPhys / AXSI_DIV_MEM) );
}

/**
* Comment
*/
AXSI_API unsigned int axsi_get_free_ram() {
  MEMORYSTATUS  mem_stats;

  GlobalMemoryStatus( &mem_stats );

  return( (unsigned int) (mem_stats.dwAvailPhys + mem_stats.dwAvailPageFile) / AXSI_DIV_MEM );
}

/**
* Comment
*/
AXSI_API unsigned int axsi_get_free_real_ram() {
  MEMORYSTATUS  mem_stats;

  GlobalMemoryStatus( &mem_stats );

  return( (unsigned int) (mem_stats.dwAvailPhys / AXSI_DIV_MEM) );
}

/**
* Comment
*/
AXSI_API int axsi_get_percent_used_ram() {
  MEMORYSTATUS  mem_stats;

  GlobalMemoryStatus( &mem_stats );

  return( (int) mem_stats.dwMemoryLoad );
}

/* $Id: axsi_ram.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */