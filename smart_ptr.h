#ifndef SMART_PTR_H
#define SMART_PTR_H

#include "ref_count.h"
#include <cstddef>


template <typename T>
class smart_ptr
{
private:
  T* data;
  ref_count* var_ref_count;
  void __clean__();
public:
  smart_ptr();
  smart_ptr(T* object);
  virtual ~smart_ptr();
  smart_ptr(const smart_ptr<T>& other);
  smart_ptr<T>& operator=(const smart_ptr<T>& other);
  T* operator->();
  T& operator*();
  T& operator[](int index);
  operator bool() const;
  bool operator==(std::nullptr_t);
  bool operator!=(std::nullptr_t);
  int get_ref_count() const;
};


#endif // SMART_PTR_H