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

#endif // REF_COUNT_H
