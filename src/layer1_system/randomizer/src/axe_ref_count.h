/**
* @file
* 
* @author    Carlos Fuentes de los SAntos
* @date      24 Apr 2004
*/
#ifndef __AXE_REF_COUNT_H__
#define __AXE_REF_COUNT_H__

//#include <crtdbg.h>

/**
* This class is a base class for objects with reference count interface
* and automatic delete if count is equal to 0
*/
class ref_count
{
private:
  int count;
public:
  ref_count(void);
  virtual ~ref_count(void);

  void upcount(void);
  void downcount(void);
};


#endif // __AXE_REF_COUNT_H__
/* $Id: axe_ref_count.h,v 1.1 2004/07/27 21:19:28 ilgenio Exp $ */
