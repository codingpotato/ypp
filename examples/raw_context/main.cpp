#include <iostream>

#include <ypp/kernel/exec_manager.h>

using namespace std;

ypp::exec_manager manager;

char stack1[32768];
ypp::exec_context f1_ctx;

char stack2[32768];
ypp::exec_context f2_ctx;

struct F1 {
  F1(string const &n) : name{n} {}

  void run() {
    cout << name << endl;
    manager.switch_to_base();
    cout << name << endl;
    manager.switch_to(f2_ctx);
  }

private:
  string name;
};

struct F2 {
  F2(string const &n) : name{n} {}

  void run() {
    cout << name << endl;
    manager.switch_to(f1_ctx);
    cout << name << endl;
    manager.switch_to_base();
  }

private:
  string name;
};

template <typename T>
void do_run(void *target) {
  static_cast<T *>(target)->run();
}

int main() {
  F1 f1{"f1"};
  F2 f2{"f2"};

  f1_ctx.init(stack1, 32768, &do_run<F1>, &f1);
  f2_ctx.init(stack2, 32768, &do_run<F2>, &f2);

  cout << "start!" << endl;
  manager.switch_to(f2_ctx);
  cout << "main!" << endl;
  manager.switch_to(f1_ctx);
  cout << "end!" << endl;
  return 0;
}