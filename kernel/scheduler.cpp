#include "scheduler.h"
#include "thread.h"

namespace ypp {

inline void scheduler::switch_to(basic_thread &th, exec_context &from_ctx) {
  th.status_ = thread_status::running;
  current_thread_ = &th;
  th.ctx_.switch_from(from_ctx);
}

inline void scheduler::auto_switch(exec_context &from_ctx) {
  if (priority_pqueue_.empty()) {
    current_thread_ = nullptr;
    base_context_.switch_from(from_ctx);
  } else {
    auto *thread = priority_queues_[priority_pqueue_.first()].head_peek();
    switch_to(*thread, from_ctx);
  }
}

inline void scheduler::switch_no_return_to(basic_thread &th) {
  th.status_ = thread_status::running;
  current_thread_ = &th;
  th.ctx_.switch_no_return();
}

inline void scheduler::auto_switch_no_return() {
  if (priority_pqueue_.empty()) {
    current_thread_ = nullptr;
    base_context_.switch_no_return();
  } else {
    auto *thread = priority_queues_[priority_pqueue_.first()].head_peek();
    switch_no_return_to(*thread);
  }
}

[[noreturn]] void scheduler::start() {
  started_ = true;
  if (!priority_pqueue_.empty()) {
    auto *thread = priority_queues_[priority_pqueue_.first()].head_peek();
    switch_to(*thread, base_context_);
  }
  while (true) {
  }
}

void scheduler::schedule_thread(basic_thread &th) {
  auto &priority_queue = priority_queues_[th.priority_];
  if (priority_queue.empty()) {
    priority_pqueue_.set(th.priority_);
  }
  priority_queue.tail_push(&th);
  if (started_) {
    if (current_thread_ == nullptr) {
      switch_to(th, base_context_);
    } else if (current_thread_->priority_ > th.priority_) {
      current_thread_->status_ = thread_status::pending;
      switch_to(th, current_thread_->ctx_);
    }
  }
}

void scheduler::yield_thread(basic_thread &th) {
  auto &priority_queue = priority_queues_[th.priority_];
  if (priority_queue.head_peek() == &th) {
    if (priority_queue.tail_peek() != &th) {
      th.status_ = thread_status::pending;
      priority_queue.head_pop_tail_push();
      auto *next = priority_queue.head_peek();
      switch_to(*next, th.ctx_);
    }
  } else {
    /* thread queue status is incorrect, attempt to recover */
    auto_switch(th.ctx_);
  }
}

void scheduler::finish_thread(basic_thread &th) {
  auto &priority_queue = priority_queues_[th.priority_];
  if (priority_queue.head_peek() == &th) {
    priority_queue.head_pop();
    if (priority_queue.empty()) {
      priority_pqueue_.unset(th.priority_);
      auto_switch_no_return();
    } else {
      auto *thread = priority_queue.head_peek();
      switch_no_return_to(*thread);
    }
  } else {
    /* thread queue status is incorrect, attempt to recover */
    auto_switch_no_return();
  }
}

} // namespace ypp
