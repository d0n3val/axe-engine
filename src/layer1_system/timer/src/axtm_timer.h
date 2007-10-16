/**
* @file
* Axe 'timer' library PRIVATE include header
*/
#ifndef __AXTM_TIMER_H__
  #define __AXTM_TIMER_H__

/**
* axtm_timer class
* Create accurate time counters
* Check Paul Hope article at 
* http://www.flipcode.com/cgi-bin/msg.cgi?showThread=COTD-RDTSCTimer&forum=cotd&id=-1
*/
class axtm_timer
{
  private:
    double        frequency;
    double        start_time;
    double        stop_time;
    unsigned int  start_ticks;
    unsigned int  stop_ticks;

    double        mark;
  public:
    /**
    * Constructor
    */
    axtm_timer()
    {
      QueryPerformanceFrequency( (LARGE_INTEGER*) &frequency );
      start_time = mark = now();
      start_ticks = now_ticks();
      stop_time = 0.0;
      stop_ticks = 0;
    }

    /**
    * Get actual time
    */
    inline double now()
    {
      double  tmp;
      QueryPerformanceCounter( (LARGE_INTEGER*) &tmp );
      tmp /= frequency;
      return( tmp );
    }

    /**
    * Get actual tick count
    */
    inline unsigned int now_ticks()
    {
      unsigned int    ticks;
      unsigned int*   p_ticks = &ticks;
      __asm
      {
        rdtsc
        mov ebx, p_ticks
        mov[ebx], eax
      }

      return( ticks );
    }

    /**
    * Start now the timer
    */
    float start()
    {
      double  tmp;

      stop_time = 0.0;
      stop_ticks = 0;
      tmp = elapsed();

      start_time = now();
      start_ticks = now_ticks();
      return( (float) tmp );
    }

    /**
    * Stop the timer
    */
    float stop()
    {
      stop_time = now();
      stop_ticks = now_ticks();
      return( elapsed() );
    }

    /**
    * Set a mark now
    */
    void set_mark()
    {
      mark = now();
    }

    /**
    * Get elapsed from start
    */
    inline float elapsed()
    {
      if( stop_time > start_time )
      {
        return( (float) ((stop_time - start_time)) );
      }
      else
      {
        return( (float) ((now() - start_time)) );
      }
    }

    /**
    * Get elapsed from mark
    */
    inline float mark_elapsed( bool update_mark = true )
    {
      if( stop_time > start_time )
      {
        return( (float) ((stop_time - start_time)) );
      }
      else
      {
        double  n = now();
        double  m = mark;
        if( true == update_mark )
        {
          mark = n;
        }

        return( (float) ((n - m)) );
      }
    }

    /**
    * Get elapsed ticks from start
    */
    inline unsigned int elapsed_ticks()
    {
      if( stop_ticks > start_ticks )
      {
        return( stop_ticks - start_ticks );
      }
      else
      {
        return( now_ticks() - start_ticks );
      }
    }

    /**
    * Destructor
    */
    ~axtm_timer()
    {
    }
};
#endif /*__AXTM_TIMER_H__*/

/* $Id: axtm_timer.h,v 1.2 2004/09/20 21:28:10 doneval Exp $ */
