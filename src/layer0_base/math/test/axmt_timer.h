/**
* @file
* axsi_timer class definiton
*/
#ifndef __AXMT_TIMER_H__
  #define __AXMT_TIMER_H__

  #include <windows.h>

/**
* axsi_timer class
* Create accurate time counters
*/
class axmt_timer
{
  private:
    double  frequency;
    double  start_time;
    double  stop_time;
  public:
    axmt_timer() {
      QueryPerformanceFrequency( (LARGE_INTEGER*) &frequency );
      start();
    }

    void start() {
      QueryPerformanceCounter( (LARGE_INTEGER*) &start_time );
      stop_time = 0;
    }

    void stop() {
      QueryPerformanceCounter( (LARGE_INTEGER*) &stop_time );
    }

    double elapsed() {
      if( stop_time == 0 ) {
        stop();
      }

      return( (stop_time - start_time) / frequency );
    }

    float elapsedf() {
      return( (float) elapsed() );
    }

    ~axmt_timer() {
    }
};
#endif /*__axsi_timer_H__*/

/* $Id: axmt_timer.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */