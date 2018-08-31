#include "exec_context.h"

namespace ypp {

void exec_context::init(void *stack_ptr, std::size_t size, void (*func)(void *),
                        void *target) {
  /* TODO */
}

void exec_context::switch_from(exec_context *current) {
  /* TODO */
}

} // namespace ypp