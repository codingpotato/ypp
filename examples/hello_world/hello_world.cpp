#include <cstdio>
#include <ypp/kernel/application.h>
#include <ypp/kernel/scheduler.h>
#include <ypp/kernel/thread.h>

using namespace ypp;

struct hello_world_thread : thread<255> {
  void run() override {
    printf("Hello world!\n");
  }
};

auto sched = make_scheduler_with_priorities<32>();
hello_world_thread th;

int main() {
  application::instance.register_scheduler(sched);
  th.schedule();

  application::instance.start();

  return 0;
}
