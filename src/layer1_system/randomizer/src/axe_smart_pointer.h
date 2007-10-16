#pragma once
/**
* @file
* 
* @author    Carlos Fuentes de los Santos
* @date      21 Apr 2004
*/
#ifndef __AXE_SMART_POINTER__
#define __AXE_SMART_POINTER__

#include"axe_ref_count.h"

// toDO : I will add all possible operators

/**
* A template class for intrusive smart pointers.
*/
template<class T>
class ptr
{
private:
  T* pointer;
public:
  ptr(void);
  ptr(T* p);
  ptr(ptr<T> & p);
  ~ptr(void);

  operator const T*(void) const;
  operator T*(void) const;
  T& operator*(void) const;
  T* operator->(void) const ;
  ptr& operator=(ptr<T> &p);
  ptr& operator=(T* p);
  bool operator==(const ptr<T> &p) const;
  bool operator==(const T* p)const;
  bool operator!=(const ptr<T> &p) const;
  bool operator!=(const T* p) const;
};

/**
* Default Constructor
*/
template<class T>
ptr<T>::ptr(void)
{
  pointer = NULL;
}

/**
* Constructor for a class T
*/
template<class T>
ptr<T>::ptr(T* p)
{
  pointer = p;
  if(pointer)
    pointer->upcount();
}

/**
* Copy constructor
*/
template<class T>
ptr<T>::ptr(ptr<T>& p)
{
  pointer = (T*)p;
  if(pointer)
    pointer->upcount();
}

/**
* Destructor
*/
template<class T>
ptr<T>::~ptr()
{
  if(pointer)
    pointer->downcount();
}

/**
* Cast T operator
*/
template<class T>
inline ptr<T>::operator T*(void) const
{
  return(pointer);
}

/**
* Const Cast T operator
*/
template<class T>
inline ptr<T>::operator const T*(void) const
{
  return(pointer);
}

/**
* '*' operator
*/
template<class T>
inline T& ptr<T>::operator *(void) const
{
  AXE_ASSERT(pointer);
  return(*pointer);  
}

/**
* '->' operator
*/
template<class T>
inline T* ptr<T>::operator ->(void) const
{
  AXE_ASSERT(pointer);
  return(pointer);
}

/**
* '=' operator for ptr
*/
template<class T>
inline ptr<T>& ptr<T>::operator =(ptr<T> &p)
{
  return(operator=((T*)p));
}

/**
* '=' operator for T class
*/
template<class T>
inline ptr<T>& ptr<T>::operator =(T* p)
{
  if(pointer)
    pointer->downcount();
  pointer = p;
  if(pointer)
    pointer->upcount();

  return(*this);
}

/**
* Operator ==
**/
template<class T>
inline bool ptr<T>::operator==(const ptr<T> &p) const
{
  return(operator==((T*)p));
}

/**
* Operator ==
**/
template<class T>
inline bool ptr<T>::operator==(const T* p)const
{
  return(pointer == p);
}

/**
* Operator !=
**/
template<class T>
inline bool ptr<T>::operator!=(const ptr<T> &p) const
{
  return(!operator==(p));
}

/**
* Operator !=
**/
template<class T>
inline bool ptr<T>::operator!=(const T* p) const
{
  return(!operator==(p));
}


#endif  // __AXE_SMART_POINTER__
/* $Id: axe_smart_pointer.h,v 1.1 2004/07/27 21:19:28 ilgenio Exp $ */
