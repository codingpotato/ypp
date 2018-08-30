#ifndef YPP_KERNEL_APPLICATION_H
#define YPP_KERNEL_APPLICATION_H

#include "scheduler.h"

namespace ypp {

struct application {
  static application instance;

  application(const application &) = delete;
  application &operator=(const application &) = delete;
  application(application &&) = delete;
  application &operator=(application &&) = delete;

  template <std::size_t priority_count>
  inline void
  register_scheduler(scheduler_allocation<priority_count> &scheduler) {
    scheduler_ = &scheduler.scheduler_;
  }

  inline ypp::scheduler &scheduler() {
    return *scheduler_;
  }

  inline void start() {
    if (scheduler_ != nullptr) {
      scheduler_->start();
    }
  }

private:
  application();

  ypp::scheduler *scheduler_ = nullptr;
};

} // namespace ypp

#endif /* YPP_KERNEL_APPLICATION_H */
