#include <iostream>
#include <ucontext.h>

static ucontext_t ctx[3];

static void f1(void) {
  std::cout << "start f1\n";
  swapcontext(&ctx[1], &ctx[2]);
  std::cout << "finish f1\n";
}

static void f2(void) {
  std::cout << "start f2\n";
  swapcontext(&ctx[2], &ctx[1]);
  std::cout << "finish f2\n";
}

int main() {
  std::cout << "main ----- start\n";

  char st1[32768]; // must large than 32k in mac os
  char st2[32768];

  getcontext(&ctx[1]);
  ctx[1].uc_stack.ss_sp = st1;
  ctx[1].uc_stack.ss_size = sizeof st1;
  ctx[1].uc_link = &ctx[0];
  makecontext(&ctx[1], f1, 0);

  std::cout << "main ----- after makecontext ctx[1]\n";

  getcontext(&ctx[2]);
  ctx[2].uc_stack.ss_sp = st2;
  ctx[2].uc_stack.ss_size = sizeof st2;
  ctx[2].uc_link = &ctx[1];
  makecontext(&ctx[2], f2, 0);

  std::cout << "main ----- after makecontext ctx[2]\n";

  swapcontext(&ctx[0], &ctx[2]);

  std::cout << "main ----- after swapcontext\n";

  return 0;
}
