#ifndef YPP_KERNEL_THREAD_H
#define YPP_KERNEL_THREAD_H

#include "application.h"
#include "impl/circ_queue.h"
#include "scheduler.h"

namespace ypp {

enum class thread_status : char { stopped = 0, blocked, running, pending };
static_assert(static_cast<char>(thread_status::stopped) <
              static_cast<char>(thread_status::running));
static_assert(static_cast<char>(thread_status::blocked) <
              static_cast<char>(thread_status::running));
static_assert(static_cast<char>(thread_status::running) >=
              static_cast<char>(thread_status::running));
static_assert(static_cast<char>(thread_status::pending) >=
              static_cast<char>(thread_status::running));

struct basic_thread : private kernel_impl::circ_queue<basic_thread>::node {
  friend scheduler;
  template <std::size_t stack_size>
  friend struct thread;

  inline basic_thread(int priority = 0) : priority_{priority} {}

  inline thread_status status() const {
    return status_;
  }

  inline bool on_run_queue() const {
    return static_cast<char>(status_) >=
           static_cast<char>(thread_status::running);
  }

  inline void schedule() {
    application::instance.scheduler().schedule_thread(*this);
  }

  virtual void run() = 0;

private:
  int priority_;
  thread_status status_ = thread_status::stopped;

  char *stack_ = nullptr;
  size_t stack_size_;
};

template <std::size_t stack_size>
struct thread : public basic_thread {
  inline thread(int priority = 0) : basic_thread{priority} {
    stack_ = stack_allocation_;
    stack_size_ = stack_size;
  }

private:
  char stack_allocation_[stack_size];
};

} // namespace ypp

#endif /* YPP_KERNEL_THREAD_H */
