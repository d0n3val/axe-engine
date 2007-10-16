/**
* @file
* Axe 'system_info' header for cpu_flags help functions
*/
#ifndef __AXSI_CPU_FLAGS_H__
  #define __AXSI_CPU_FLAGS_H__

int cpu_check_fpu();
int cpu_check_cpuid();
int cpu_check_rdtsc();
int cpu_check_apic();
int cpu_check_cmov();
int cpu_check_mtrr();
int cpu_check_mmx();
int cpu_check_3dnow();
int cpu_check_3dnow_ex();
int cpu_check_simd();
int cpu_check_simd2();
int cpu_check_fastcall();
int cpu_check_htt();
int cpu_check_fxsr();

int read_cpu_flags();
int read_cpu_extended_flags();
#endif /*__AXSI_CPU_FLAGS_H__*/

/* $Id: axsi_cpu_flags.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */