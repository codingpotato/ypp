#include <iostream>

#include <ypp/kernel/exec_context.h>

using namespace std;

char stack1[32768];
ypp::exec_context f1_ctx;

char stack2[32768];
ypp::exec_context f2_ctx;

ypp::exec_context base_ctx;

struct F1 {
  F1(string const &n) : name{n} {}

  void run() {
    cout << name << endl;
    base_ctx.switch_from(f1_ctx);
    cout << name << endl;
    f2_ctx.switch_from(f1_ctx);
  }

private:
  string name;
};

struct F2 {
  F2(string const &n) : name{n} {}

  void run() {
    cout << name << endl;
    f1_ctx.switch_from(f2_ctx);
    cout << name << endl;
    base_ctx.switch_from(f2_ctx);
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
  f2_ctx.switch_from(base_ctx);
  cout << "main!" << endl;
  f1_ctx.switch_from(base_ctx);
  cout << "end!" << endl;
  return 0;
}