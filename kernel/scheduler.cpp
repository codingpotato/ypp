#include "scheduler.h"
#include "thread.h"

namespace ypp {

void scheduler::schedule_thread(basic_thread &th) {
  auto &priority_queue = priority_queues_[th.priority_];
  if (priority_queue.empty()) {
    priority_pqueue_.set(th.priority_);
  }
  priority_queue.tail_push(&th);
  switch_thread();
}

void scheduler::finish_thread(basic_thread const &th) {
  auto &priority_queue = priority_queues_[th.priority_];
  if (priority_queue.head_peek() == &th) {
    priority_queue.head_pop();
    if (priority_queue.empty()) {
      priority_pqueue_.unset(th.priority_);
    }
  }
  switch_thread();
}

void scheduler::switch_thread() {
  if (priority_pqueue_.empty()) {
    exec_manager_.switch_to_base();
  } else {
    auto *thread = priority_queues_[priority_pqueue_.first()].head_peek();
    thread->status_ = thread_status::running;
    exec_manager_.switch_to(thread->ctx_);
  }
}

} // namespace ypp
