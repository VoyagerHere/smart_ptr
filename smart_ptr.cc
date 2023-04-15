#include "smart_ptr.h"


template <class T>
smart_ptr<T>::smart_ptr() : data(nullptr), var_ref_count(nullptr) {}

template <class T>
smart_ptr<T>::smart_ptr(T* object) : data{object} {
  var_ref_count = new ref_count();
  var_ref_count->increment();
}

template <class T>
smart_ptr<T>::~smart_ptr() {
  if (var_ref_count) {
    int decrement_count = var_ref_count->decrement();
    if (decrement_count <= 0) {
      __clean__();
    }
  }
}

template <class T>
smart_ptr<T>::smart_ptr(const smart_ptr<T>& other)
    : data{other.data}, var_ref_count{other.var_ref_count} {
  var_ref_count->increment();
}

template <class T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr<T>& other) {
  if (this != &other) {
    if (var_ref_count && var_ref_count->decrement() == 0) {
      __clean__();
    }
    data = other.data;
    var_ref_count = other.var_ref_count;
    var_ref_count->increment();
  }
  return *this;
}

template <class T>
T& smart_ptr<T>::operator*() {
  return *data;
}

template <class T>
T& smart_ptr<T>::operator[](int index) {
  return *(data + index);
}

template <class T>
T* smart_ptr<T>::operator->() {
  return data;
}

template <class T>
smart_ptr<T>::operator bool() const {
  return this->operator==();
}

template <class T>
int smart_ptr<T>::get_ref_count() const {
  return var_ref_count->get_count();
}

template <class T>
void smart_ptr<T>::__clean__() {
  delete var_ref_count;
  delete data;
  var_ref_count = nullptr;
  data = nullptr;
}

template <class T>
bool smart_ptr<T>::operator==(std::nullptr_t) {
  return data == nullptr;
}
template <class T>
bool smart_ptr<T>::operator!=(std::nullptr_t) {
  return !(this->operator==());
}