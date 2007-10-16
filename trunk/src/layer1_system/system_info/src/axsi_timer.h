/**
* @file
* axsi_timer class definiton
*/
#ifndef __AXSI_TIMER_H__
  #define __AXSI_TIMER_H__

  #include <windows.h>

/**
* axsi_timer class
* Create acurate time counters
*/
class axsi_timer
{
  private:
    double  frequency;
    double  start_time;
    double  stop_time;
  public:
    axsi_timer() {
      QueryPerformanceFrequency( (LARGE_INTEGER*) &frequency );
    }

    void start() {
      QueryPerformanceCounter( (LARGE_INTEGER*) &start_time );
    }

    void stop() {
      QueryPerformanceCounter( (LARGE_INTEGER*) &stop_time );
    }

    double elapsed() {
      return( ((stop_time - start_time) * 1000) / frequency );
    }

    ~axsi_timer() {
    }
};
#endif /*__axsi_timer_H__*/

/* $Id: axsi_timer.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */