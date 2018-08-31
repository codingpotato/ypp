#ifndef YPP_EXEC_CONTEXT_H
#define YPP_EXEC_CONTEXT_H

#include <cstddef>

namespace ypp {

struct exec_context {
  inline exec_context() {}

  exec_context(const exec_context &) = delete;
  exec_context &operator=(const exec_context &) = delete;
  exec_context(exec_context &&) = delete;
  exec_context &operator=(exec_context &&) = delete;

  void init(void *stack_ptr, std::size_t size, void (*func)(void *),
            void *target);
  void switch_from(exec_context *current);

private:
  char _[64];
};

} // namespace ypp

#endif /* YPP_EXEC_CONTEXT_H */