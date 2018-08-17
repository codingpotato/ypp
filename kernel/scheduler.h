#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstddef>
#include "bit_priority_queue.h"
#include "circ_queue.h"

namespace ypp {

struct basic_task;

struct scheduler {
  friend basic_task;

  template <std::size_t priority_count>
  struct run_queue {
    friend scheduler;

    static_assert(priority_count <= 32,
                  "Only a maximum of 32 priorities current supported!");

  private:
    circ_queue<basic_task> priority_queues_allocation_[priority_count];
  };

  static inline scheduler &global_scheduler() {
    return global_scheduler_;
  }

  template <std::size_t priority_count>
  inline void initialize(run_queue<priority_count> &queue) {
    priority_queues_ = queue.priority_queues_allocation_;
  }

  inline void start() {
    /* TODO */
  }

  void schedule_task(basic_task &tsk);

private:
  static scheduler global_scheduler_;

  bit_priority_queue priority_pqueue_;
  circ_queue<basic_task> *priority_queues_ = nullptr;
};

} // namespace ypp

#endif /* SCHEDULER_H */
