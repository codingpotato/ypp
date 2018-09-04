#ifndef YPP_KERNEL_EXEC_CONTEXT_H
#define YPP_KERNEL_EXEC_CONTEXT_H

#include <cstddef>
#include <ypp/board/config.h>

namespace ypp {

namespace {
extern "C" void make_ctx(void *ctx, void *stack_ptr, void (*func)(void *),
                         void *target);
extern "C" void jump_ctx(void *from, void *to);
} // namespace

struct exec_context {
  inline exec_context() {}

  exec_context(const exec_context &) = delete;
  exec_context &operator=(const exec_context &) = delete;
  exec_context(exec_context &&) = delete;
  exec_context &operator=(exec_context &&) = delete;

  inline void init(void *stack_ptr, std::size_t size, void (*func)(void *),
                   void *target) {
    make_ctx(data_, static_cast<char *>(stack_ptr) + size, func, target);
  }
  inline void switch_from(exec_context *current) {
    jump_ctx(current, data_);
  }

private:
  char data_[EXEC_CONTEXT_SIZE];
};

} // namespace ypp

#endif /* YPP_KERNEL_EXEC_CONTEXT_H */
