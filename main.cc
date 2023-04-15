#include <iostream>

#include "smart_ptr.h"

int calc_sum(smart_ptr<int>& values, int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += *(values.operator->() + i);
  }
  return sum;
}
int* init(int size = 10) {
  int* arr = new int[size];
  for (int i = 0; i < size; ++i) {
    arr[i] = i;
  }
  return arr;
}

int main() {
  smart_ptr<int> ptr = new int[10];
  int res = calc_sum(ptr, 10);
  smart_ptr<int> data = init();
  if(data) {
    printf("%i\n", data[0]);
  }
  return 0;
}