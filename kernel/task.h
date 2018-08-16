#ifndef TASK_H
#define TASK_H

#include "circ_queue.h"
#include <cstddef>

namespace ypp {

enum class task_status : char { stopped = 0, blocked, running, pending };

struct basic_task : circ_queue<basic_task>::node {
  template <std::size_t stack_size>
  friend struct task;

  inline basic_task(int priority = 1) : priority_{priority} {}

  inline task_status status() {
    return status_;
  }

private:
  int priority_;
  task_status status_ = task_status::stopped;
  char *stack_ptr_ = nullptr;
};

template <std::size_t stack_size>
struct task : public basic_task {
  inline task(int priority = 1) : basic_task{priority} {
    stack_ptr_ = stack_;
  }

private:
  char stack_[stack_size];
};

} // namespace ypp

#endif /* TASK_H */