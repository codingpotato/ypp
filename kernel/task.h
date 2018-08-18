#ifndef TASK_H
#define TASK_H

#include <cstddef>
#include "circ_queue.h"
#include "scheduler.h"

namespace ypp {

enum class task_status : char { stopped = 0, blocked, running, pending };

struct basic_task : circ_queue<basic_task>::node {
  friend scheduler;
  template <std::size_t stack_size>
  friend struct task;

  inline basic_task(int priority = 1) : priority_{priority} {}

  inline task_status status() const {
    return status_;
  }

  inline bool on_run_queue() const {
    return static_cast<char>(status_) >=
           static_cast<char>(task_status::running);
  }

  inline void schedule() {
    scheduler::global_scheduler().schedule_task(*this);
  }

  virtual void run() = 0;

private:
  int priority_;
  task_status status_ = task_status::stopped;

  char *stack_ = nullptr;
  size_t stack_size_;
};

template <std::size_t stack_size>
struct task : public basic_task {
  inline task(int priority = 1) : basic_task{priority} {
    stack_ = stack_allocation_;
    stack_size_ = stack_size;
  }

private:
  char stack_allocation_[stack_size];
};

} // namespace ypp

#endif /* TASK_H */
