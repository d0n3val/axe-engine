/**
* @file
* 
* @author    Carlos Fuentes de los SAntos
* @date      24 Apr 2004
*/
#ifndef __AXE_REF_COUNT_H__
  #define __AXE_REF_COUNT_H__

/**
* This class is a base class for objects with reference count interface
* and automatic delete if count is equal to 0
*/
class ref_count
{
  private:
    int count;
  public:
    ref_count( void )
    {
      count = 0;
    }

    virtual~ref_count( void )
    {
      AXE_ASSERT( count == 0 );
    }

    void upcount( void )
    {
      ++count;
    }

    void downcount( void )
    {
      if( --count == 0 )
      {
        delete this;
      }
    }
};
#endif // __AXE_REF_COUNT_H__

/* $Id: axe_ref_count.h,v 1.2 2004/08/26 22:28:30 ilgenio Exp $ */
