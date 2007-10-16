/**
* @file
* Axe 'system_info' code to detect cpu capabilities
*/
#include "axsi_stdafx.h"

extern _state state;

/// Global state of the library

/**
* Comment
*/
AXSI_API int axsi_get_cpu_flags( axsi_cpu_flags* cpu_flags_info ) {
  if( cpu_flags_info == NULL ) {
    axsi_set_error( 3 );
    return( AXE_FALSE );
  }

  if( state.cpu_flags_set == true ) {
    memcpy( cpu_flags_info, &state.cpu_flags_data, sizeof(axsi_cpu_flags) );
    return( AXE_TRUE );
  }

  state.cpu_flags_data.fpu = cpu_check_fpu();
  state.cpu_flags_data.cpuid = cpu_check_cpuid();
  state.cpu_flags_data.rdtsc = cpu_check_rdtsc();
  state.cpu_flags_data.apic = cpu_check_apic();
  state.cpu_flags_data.cmov = cpu_check_cmov();
  state.cpu_flags_data.mtrr = cpu_check_mtrr();
  state.cpu_flags_data.mmx = cpu_check_mmx();
  state.cpu_flags_data.sse = cpu_check_simd();
  state.cpu_flags_data.sse2 = cpu_check_simd2();
  state.cpu_flags_data.f3dnow = cpu_check_3dnow();
  state.cpu_flags_data.f3dnow_ex = cpu_check_3dnow_ex();
  state.cpu_flags_data.fastcall = cpu_check_fastcall();
  state.cpu_flags_data.htt = cpu_check_htt();
  state.cpu_flags_data.fxsr = cpu_check_fxsr();

  memcpy( cpu_flags_info, &state.cpu_flags_data, sizeof(axsi_cpu_flags) );

  state.cpu_flags_set = true;

  return( AXE_TRUE );
}

/*$off*/

/**
* Comment
*/
int cpu_check_fpu() {
  unsigned short  status;
  int             found = 0;

  _asm
  {
    fninit                // reset FP status word
    mov[status], 5a5ah    // initialise temp word to non-zero value
    fnstsw[status]        // save FP status word
    mov ax, [status]      // check FP status word
    cmp al, 0             // see if correct status with written
    jne DONE

    fnstcw[status]        // save FP control word
    mov ax, [status]      // check FP control word
    and ax, 103fh         // see if seleced parts look OK
    cmp ax, 3fh           // check that 1s & 0s correctly read
    jne DONE
    mov found, 1
    DONE :
  };

  if( found != 0 ) {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_cpuid() {
  unsigned long result = 0;

  _asm
  {
    pushfd                // Get original EFLAGS
    pop eax
    mov ecx, eax
    xor eax, 200000h      // Flip ID bit in EFLAGS
    push eax              // Save new EFLAGS value on stack        									
    popfd                 // Replace current EFLAGS value
    pushfd                // Get new EFLAGS
    pop eax               // Store new EFLAGS in EAX
    xor eax, ecx
    jz DONE               // Failure - NO CPUID Support

    // The processor supports the CPUID instruction.
    mov result, 1
    DONE :
  }

  return( result );
}

/*$on*/

/**
* Comment
*/
int cpu_check_rdtsc() {
  if( state.cpu_flags & (1 << 4) ) {

    // RDTSC exists, check if OS support it
    __try
    {
      _asm rdtsc
    }

    __except( EXCEPTION_EXECUTE_HANDLER ) {
      return( AXE_FALSE );
    }

    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_simd() {
  if( state.cpu_flags & (1 << 25) ) {

    // SIMD exists, check if OS support it
    __try
    {
      _asm
      {
        pushad            /*  */
        orps xmm1, xmm1   /*  */
        popad             /*  */
        //ADDPS(_XMM0,_XMM1)
      }
    }

    __except( EXCEPTION_EXECUTE_HANDLER ) {

      // SIMD exists but it is not supported by OS
      return( AXE_FALSE );
    }

    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_simd2() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 26) ) {

    // SIMD2 exists, check if OS support it
    __try
    {
      _asm
      {
        pushad            /*  */
        paddq xmm1, xmm2
        popad             /*  */
      }
    }

    __except( EXCEPTION_EXECUTE_HANDLER ) {

      // SIMD2 exists but it is not supported by OS
      return( AXE_FALSE );
    }

    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_mmx() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 23) ) {

    // MMX exists, check if OS support it
    __try
    {
      __asm
      {
        pxor mm0, mm0
        emms
      }
    }

    __except( EXCEPTION_EXECUTE_HANDLER ) {

      // MMX exists but it is not supported by OS
      return( AXE_FALSE );
    }

    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_apic() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 9) ) {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_cmov() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 15) ) {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_mtrr() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 12) ) {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_3dnow() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_extended_flags & (1 << 31) ) {

    // 3DNOW exists, check if OS support it
    /*
		__try {
			__asm {
				pfrcp mm0, mm0
				emms
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER) {
			// 3DNOW exists but it is not supported by OS
			return(AXE_FALSE);
		}*/
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_3dnow_ex() {
  if( cpu_check_3dnow() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_extended_flags & (1 << 30) ) {

    /*
		// 3DNOW EX exists, check if OS support it
		__try {
			__asm {
				pfrcp mm0, mm0
					emms
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER) {
			// 3DNOW EX exists but it is not supported by OS
			return(AXE_FALSE);
		}*/
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_fastcall() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 11) ) {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_htt() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 28) ) {

    // OK, the micro allow HTT, check if it is enabled
    // ask for number of logical CPUs
    int logical_cpu_count = 0;

    logical_cpu_count = ( state.cpu_info2 >> 16 ) & 0xF;
    if( logical_cpu_count > 0 ) {
      return( AXE_TRUE );
    }
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int cpu_check_fxsr() {
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  if( state.cpu_flags & (1 << 24) ) {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Comment
*/
int read_cpu_flags() {

  // check cached data
  if( state.cpu_flags != 0 ) {
    return( AXE_TRUE );
  }

  // we need a CPU with cpuid enabled
  if( cpu_check_cpuid() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  // go
  _asm
  {
    pushad
    mov eax, 1
    cpuid
    mov state.cpu_info, eax
    mov state.cpu_info2, ebx
    mov state.cpu_flags, edx
    popad
  }

  // try to get extended CPU flags
  __try
  {
    read_cpu_extended_flags();
  }

  __except( EXCEPTION_EXECUTE_HANDLER ) {
    state.cpu_extended_flags = 0;
  }

  return( AXE_TRUE );
}

/**
* Comment
*/
int read_cpu_extended_flags() {

  // check cached data
  if( state.cpu_extended_flags != 0 ) {
    return( AXE_TRUE );
  }

  unsigned long eax_max;
  unsigned long ebx_max;
  unsigned long ecx_max;
  unsigned long edx_max;

  _asm
  {
    mov eax, 0
    cpuid                 // eax = max cpuid
    cpuid                 // issue max CPUID and store the results
    mov eax_max, eax
    mov ebx_max, ebx
    mov ecx_max, ecx
    mov edx_max, edx

    mov eax, 0x80000000   // issue the base extended function
    cpuid

    // check the results of the extended base function with the max standard function
    cmp eax, eax_max
    jne extended_range
    cmp ebx, ebx_max
    jne extended_range
    cmp ecx, ecx_max
    jne extended_range
    cmp edx, edx_max
    jne extended_range
    jmp no_extended       // all the registers as the same as the max base function, no extended functions
    extended_range :
    test eax, 0x80000000  // the top bit of eax must be set
    je no_extended

    mov state.cpu_extended_flags, eax
    no_extended :
  }

  return( AXE_TRUE );
}

/* $Id: axsi_cpu_flags.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
