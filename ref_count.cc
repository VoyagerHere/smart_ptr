#include "ref_count.h"

ref_count::ref_count() : var_ref_count(0) {}

void ref_count::increment() {
  ++var_ref_count;
}

int ref_count::decrement() {
  return --var_ref_count;
}

int ref_count::get_count() const {
  return var_ref_count;
}

ref_count::ref_count(const ref_count& other) : var_ref_count(other.var_ref_count) {}

ref_count& ref_count::operator=(const ref_count& other) {
  if (this != &other) {
    var_ref_count = other.var_ref_count;
  }
  return *this;
}