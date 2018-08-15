#include <iostream>
using namespace std;

#include "circ_queue.h"

struct object : circ_queue<object>::node {
  object(int i) : i_{i} { }
  
  int val() { return i_; }
  
private:
  int i_;  
};

int main() {
  circ_queue<object> q;
  
  cout << q.empty() << " " << 1 << endl;
  
  q.tail_push(new object{12});
  cout << q.empty() << " " << 0 << endl;
  auto *obj = q.head_pop();
  cout << q.empty() << " " << 1 << endl;
  cout << obj->val() << " " << 12 << endl;
  delete obj;
  
  q.tail_push(new object{20});
  q.tail_push(new object{30});
  cout << q.empty() << " " << 0 << endl;
  obj = q.head_pop();
  cout << q.empty() << " " << 0 << endl;
  cout << obj->val() << " " << 20 << endl;
  delete obj;
  
  q.tail_push(new object{40});
  obj = q.head_pop();
  cout << obj->val() << " " << 30 << endl;
  delete obj;
  
  obj = q.head_pop();
  cout << q.empty() << " " << 1 << endl;
  cout << obj->val() << " " << 40 << endl;
  delete obj;
}
