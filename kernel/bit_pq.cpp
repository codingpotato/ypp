#include <iostream>
using namespace std;

#include "bit_priority_queue.h"

int main() {
  bit_priority_queue q;
  
  q.set(1);
  cout << q.first() << " " << 1 << endl;
  q.unset(1);
  
  int shift = sizeof(uint32_t) * 8 - 1;
  q.set(shift);
  cout << q.first() << " " << shift << endl;
  q.unset(shift);
  
  q.set(3);
  q.set(4);
  cout << q.first() << " " << 3 << endl;
}
