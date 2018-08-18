#include <iostream>
#include <ucontext.h>

namespace cpu {

struct native {
  struct context {
    inline void init(void *stack, size_t stack_size, void (*entrance)(void),
                     context &base_ctx) {
      getcontext(&ctx_);
      ctx_.uc_stack.ss_sp = stack;
      ctx_.uc_stack.ss_size = stack_size;
      ctx_.uc_link = &base_ctx.ctx_;
      makecontext(&ctx_, entrance, 0);
    }

    inline void switch_to(context &target) {
      swapcontext(&ctx_, &target.ctx_);
    }

  private:
    ucontext_t ctx_;
  };
};

using current = native;

} // namespace cpu

static cpu::current::context f1_ctx;
static cpu::current::context f2_ctx;

static void f1(void) {
  std::cout << "start f1\n";
  f1_ctx.switch_to(f2_ctx);
  std::cout << "finish f1\n";
}

static void f2(void) {
  std::cout << "start f2\n";
  f2_ctx.switch_to(f1_ctx);
  std::cout << "finish f2\n";
}

int main() {
  std::cout << "main ----- start\n";

  cpu::current::context base_ctx;

  char st1[32768]; // must large than 32k in mac os
  char st2[32768];

  f1_ctx.init(st1, sizeof(st1), f1, base_ctx);
  std::cout << "main ----- f1 context created\n";

  f2_ctx.init(st2, sizeof(st2), f2, base_ctx);
  std::cout << "main ----- f2 context created\n";

  base_ctx.switch_to(f2_ctx);
  base_ctx.switch_to(f1_ctx);

  std::cout << "main ----- finished\n";

  return 0;
}
