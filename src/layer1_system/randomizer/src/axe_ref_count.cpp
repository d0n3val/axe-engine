#include "axrt_stdafx.h"

/**
*  Constructor
*/
ref_count::ref_count()
{
  count = 0;
}

/**
* Destructor
*/
ref_count::~ref_count()
{
  AXE_ASSERT(count == 0);
}

/**
* adds a reference to object
*/
void ref_count::upcount()
{
  ++count;
}

/**
* releases a reference to object
*/
void ref_count::downcount()
{
  if(--count == 0)
    delete this;
}
