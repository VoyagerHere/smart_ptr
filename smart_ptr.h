#ifndef SMART_PTR_H
#define SMART_PTR_H

#include "ref_count.h"

#include <cstddef>
#include <cstdio>

template <typename T>
class smart_ptr
{
private:
  T* data;
  ref_count* var_ref_count;

  class access_check
  {
    private:
      bool check;

    public:
      void set_check() {
        check = true;
      }

      bool get_check() const {
        return check;
      }

      void reset_check() {
        check = false;
      }

      void get_access_error() const {
        std::fprintf(stderr, "Warning: Attempting to access null smart pointer.\n");
      }
  } check;

  void __clean__() {
    delete var_ref_count;
    delete data;
    var_ref_count = nullptr;
    data = nullptr;
  }
public:
  smart_ptr()  : data(nullptr), var_ref_count(nullptr), check(false) {}
  smart_ptr(T* object) : data(object) {
    var_ref_count = new ref_count();
    var_ref_count->increment();
    check.reset_check();
  }
  virtual ~smart_ptr(){
    if (var_ref_count) {
      int decrement_count = var_ref_count->decrement();
      if (decrement_count <= 0) {
        __clean__();
      }
    }
  }
  smart_ptr(const smart_ptr<T>& other)
      : data{other.data}, var_ref_count{other.var_ref_count} {
    var_ref_count->increment();
    check.reset_check();
  }
  smart_ptr(smart_ptr<T>&& other)
      : data{other.data}, var_ref_count{other.var_ref_count}, check{other.check} {
    other.data = nullptr;
    other.var_ref_count = nullptr;
    other.check.reset_check();
  }
  smart_ptr<T>& operator=(const smart_ptr<T>& other) {
    if (this != &other) {
      if (var_ref_count && var_ref_count->decrement() == 0) {
        __clean__();
      }
      data = other.data;
      var_ref_count = other.var_ref_count;
      check.reset_check();
      var_ref_count->increment();
    }
    return *this;
  }
  smart_ptr<T>& operator=(smart_ptr<T>&& other) {
    if (this != &other) {
      __clean__();
      data = other.data;
      var_ref_count = other.var_ref_count;
      check = std::move(other.check);
      check.reset_check();
      other.data = nullptr;
      other.var_ref_count = nullptr;
      other.check.reset_check();
    }
    return *this;
  }
  
  T* operator->() {
    if(!check.get_check()) {
      check.get_access_error();
    }
    return data;
  }
  T& operator*() {
    if(!check.get_check()) {
      check.get_access_error();
    }
    return *data;
  }
  
  operator bool(){
    return (*this == nullptr);
  }
  
  bool operator==(std::nullptr_t) {
    check.set_check();
    return (data == nullptr);
  }
  
  bool operator!=(std::nullptr_t) {
    return !(this->operator==(nullptr));
  }
  
  int get_ref_count() const{
    return var_ref_count->get_count();
  }

};


template <typename T>
class smart_ptr<T[]>
{
private:
  T* data;
  ref_count* var_ref_count;

  class access_check
  {
    private:
      bool check;

    public:
      void set_check() {
        check = true;
      }

      bool get_check() const {
        return check;
      }

      void reset_check() {
        check = false;
      }

      void get_access_error() const {
        std::fprintf(stderr, "Warning: Attempting to access null smart pointer.\n");
      }
  } check;

  void __clean__() {
    delete var_ref_count;
    delete data;
    var_ref_count = nullptr;
    data = nullptr;
  }
public:
  smart_ptr()  : data(nullptr), var_ref_count(nullptr), check(false) {}
  smart_ptr(T* object) : data(object) {
    var_ref_count = new ref_count();
    var_ref_count->increment();
    check.reset_check();
  }
  virtual ~smart_ptr(){
    if (var_ref_count) {
      int decrement_count = var_ref_count->decrement();
      if (decrement_count <= 0) {
        __clean__();
      }
    }
  }
  smart_ptr(const smart_ptr<T>& other)
      : data{other.data}, var_ref_count{other.var_ref_count} {
    var_ref_count->increment();
    check.reset_check();
  }
  smart_ptr(smart_ptr<T>&& other)
      : data{other.data}, var_ref_count{other.var_ref_count}, check{other.check} {
    other.data = nullptr;
    other.var_ref_count = nullptr;
    other.check.reset_check();
  }
  smart_ptr<T>& operator=(const smart_ptr<T>& other) {
    if (this != &other) {
      if (var_ref_count && var_ref_count->decrement() == 0) {
        __clean__();
      }
      data = other.data;
      var_ref_count = other.var_ref_count;
      check.reset_check();
      var_ref_count->increment();
    }
    return *this;
  }
  smart_ptr<T>& operator=(smart_ptr<T>&& other) {
    if (this != &other) {
      __clean__();
      data = other.data;
      var_ref_count = other.var_ref_count;
      check = std::move(other.check);
      check.reset_check();
      other.data = nullptr;
      other.var_ref_count = nullptr;
      other.check.reset_check();
    }
    return *this;
  }
  
  T* operator->() {
    if(!check.get_check()) {
      check.get_access_error();
    }
    return data;
  }
  T& operator*() {
    if(!check.get_check()) {
      check.get_access_error();
    }
    return *data;
  }

  T& operator[](int index) {
    if(!check.get_check()) {
      check.get_access_error();
    }
    return *(data + index);
  }
  
  operator bool(){
    return (*this == nullptr);
  }
  
  bool operator==(std::nullptr_t) {
    check.set_check();
    return (data == nullptr);
  }
  
  bool operator!=(std::nullptr_t) {
    return !(this->operator==(nullptr));
  }
  
  int get_ref_count() const{
    return var_ref_count->get_count();
  }

};

#endif // SMART_PTR_H