#include <iostream>

#include "smart_ptr.h"

int calc_sum(smart_ptr<int[]>& values, int size) {
  int sum = 0;
  if (values == nullptr){
    return 0;
  }
  for (int i = 0; i < size; i++) {
    sum += *(values.operator->() + i);
  }
  return sum;
}
void fill_arr(smart_ptr<int[]>& values, int size) {
  if (values == nullptr){
    return;
  }
  for (int i = 0; i < size; ++i) {
    values[i] = i;
  }
}
int* init(int size = 10) {
  int* arr = new int[size];
  for (int i = 0; i < size; ++i) {
    arr[i] = i;
  }
  return arr;
}

int main() {
  smart_ptr<int[]> ptr = new int[10];
  fill_arr(ptr, 10);
  int res = calc_sum(ptr, 10);
  std::cout << "Reference count is:" << ptr.get_ref_count() << std::endl;
  smart_ptr<int[]> data = init();
  printf("%i\n", data[0]);
  if(data) {
    printf("%i\n", data[0]);
  }
  return 0;
}