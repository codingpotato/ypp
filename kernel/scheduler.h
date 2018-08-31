#ifndef YPP_KERNEL_SCHEDULER_H
#define YPP_KERNEL_SCHEDULER_H

#include <cstddef>
#include "impl/bit_priority_queue.h"
#include "impl/circ_queue.h"

namespace ypp {

struct basic_thread;

struct scheduler {
  friend struct application;
  friend struct basic_thread;
  template <std::size_t priority_count>
  friend struct scheduler_allocation;

  scheduler(const scheduler &) = delete;
  scheduler &operator=(const scheduler &) = delete;
  scheduler(scheduler &&) = default;
  scheduler &operator=(scheduler &&) = default;

private:
  inline scheduler(kernel_impl::circ_queue<basic_thread> *priority_queues)
      : priority_queues_{priority_queues} {}

  void schedule_thread(basic_thread &th);

  inline void start() {
    /* TODO */
  }

  kernel_impl::bit_priority_queue priority_pqueue_;
  kernel_impl::circ_queue<basic_thread> *priority_queues_;
};

template <std::size_t priority_count>
struct scheduler_allocation : public scheduler {
  static_assert(priority_count <= 32,
                "Only a maximum of 32 priorities current supported!");

  inline scheduler_allocation() : scheduler{priority_queues_allocation_} {}

  scheduler_allocation(const scheduler_allocation &) = delete;
  scheduler_allocation &operator=(const scheduler_allocation &) = delete;
  scheduler_allocation(scheduler_allocation &&) = delete;
  scheduler_allocation &operator=(scheduler_allocation &&) = delete;

private:
  kernel_impl::circ_queue<basic_thread>
      priority_queues_allocation_[priority_count];
};

template <std::size_t priority_count>
inline auto make_scheduler_with_priorities() {
  return scheduler_allocation<priority_count>{};
}

} // namespace ypp

#endif /* YPP_KERNEL_SCHEDULER_H */
