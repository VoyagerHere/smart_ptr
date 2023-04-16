#ifndef REF_COUNT_H
#define REF_COUNT_H

class ref_count {
private:
  int var_ref_count;

public:
  ref_count();
  void increment();
  int decrement();
  int get_count() const;
  ref_count(const ref_count& other);
  ref_count& operator=(const ref_count& other);
};

inline ref_count::ref_count() : var_ref_count(0) {}

inline void ref_count::increment() {
  var_ref_count++;
}

inline int ref_count::decrement() {
  return --var_ref_count;
}

inline int ref_count::get_count() const {
  return var_ref_count;
}

inline ref_count::ref_count(const ref_count& other)
    : var_ref_count(other.var_ref_count) {}

inline ref_count& ref_count::operator=(const ref_count& other) {
  var_ref_count = other.var_ref_count;
  return *this;
}

#endif // REF_COUNT_H
