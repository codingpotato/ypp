#ifndef YPP_KERNEL_SCHEDULER_H
#define YPP_KERNEL_SCHEDULER_H

#include <cstddef>
#include "bit_priority_queue.h"
#include "circ_queue.h"

namespace ypp {

struct basic_task;

struct scheduler {
  friend struct application;
  friend struct basic_task;
  template <std::size_t priority_count>
  friend struct scheduler_allocation;

  scheduler(const scheduler &) = delete;
  scheduler &operator=(const scheduler &) = delete;
  scheduler(scheduler &&) = default;
  scheduler &operator=(scheduler &&) = default;

private:
  inline scheduler(kernel_impl::circ_queue<basic_task> *priority_queues)
      : priority_queues_{priority_queues} {}

  void schedule_task(basic_task &tsk);

  inline void start() {
    /* TODO */
  }

  kernel_impl::bit_priority_queue priority_pqueue_;
  kernel_impl::circ_queue<basic_task> *priority_queues_;
};

template <std::size_t priority_count>
struct scheduler_allocation {
  friend struct application;

  inline scheduler_allocation()
      : scheduler_{run_queue_.priority_queues_allocation_} {}

  scheduler_allocation(const scheduler_allocation &) = delete;
  scheduler_allocation &operator=(const scheduler_allocation &) = delete;
  scheduler_allocation(scheduler_allocation &&) = delete;
  scheduler_allocation &operator=(scheduler_allocation &&) = delete;

private:
  template <std::size_t queue_priority_count>
  struct run_queue {
    friend struct scheduler_allocation<queue_priority_count>;

    static_assert(priority_count <= 32,
                  "Only a maximum of 32 priorities current supported!");

    inline run_queue() {}

    run_queue(const run_queue &) = delete;
    run_queue &operator=(const run_queue &) = delete;
    run_queue(run_queue &&) = delete;
    run_queue &operator=(run_queue &&) = delete;

  private:
    kernel_impl::circ_queue<basic_task>
        priority_queues_allocation_[queue_priority_count];
  };

  run_queue<priority_count> run_queue_;
  scheduler scheduler_;
};

template <std::size_t priority_count>
inline auto make_scheduler_with_priorities() {
  return scheduler_allocation<priority_count>{};
}

} // namespace ypp

#endif /* YPP_KERNEL_SCHEDULER_H */
