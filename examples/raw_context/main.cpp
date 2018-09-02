#include <iostream>

#include <ypp/kernel/exec_manager.h>

using namespace std;

ypp::exec_manager manager;

char stack[32768];
ypp::exec_context f1_ctx;
void f1(void *) {
  cout << "f1" << endl;
  manager.switch_to_base();
}

int main() {
  f1_ctx.init(stack, 32768, f1, nullptr);

  cout << "start!" << endl;
  manager.switch_to(f1_ctx);
  cout << "end!" << endl;
  return 0;
}