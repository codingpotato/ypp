#ifndef YPP_KERNEL_EXEC_MANAGER_H
#define YPP_KERNEL_EXEC_MANAGER_H

#include "exec_context.h"

namespace ypp {

struct exec_manager {
  inline exec_manager() : current_{&base_} {}

  exec_manager(const exec_manager &) = delete;
  exec_manager &operator=(const exec_manager &) = delete;
  exec_manager(exec_manager &&) = delete;
  exec_manager &operator=(exec_manager &&) = delete;

  inline void switch_to(exec_context &ctx, void *target = nullptr) {
    if (&ctx != current_) {
      exec_context *origin = current_;
      current_ = &ctx;
      ctx.switch_from(origin, target);
    }
  }

  inline void switch_to_base() {
    switch_to(base_);
  }

private:
  exec_context *current_;
  exec_context base_;
};

} // namespace ypp

#endif /* YPP_KERNEL_EXEC_MANAGER_H */
