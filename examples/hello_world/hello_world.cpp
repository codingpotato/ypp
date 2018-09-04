#include <cstdio>
#include <ypp/kernel/application.h>
#include <ypp/kernel/scheduler.h>
#include <ypp/kernel/thread.h>

using namespace ypp;

enum struct thread_priority { important, main, unimportant };

struct important_thread : thread<> {
  important_thread() : thread{static_cast<int>(thread_priority::important)} {}

  void run() override {
    printf("Important stuff!\n");
  }
};

struct unimportant_thread : thread<> {
  unimportant_thread()
      : thread{static_cast<int>(thread_priority::unimportant)} {}

  void run() override {
    printf("Unmportant stuff!\n");
  }
};

important_thread imp;
unimportant_thread unimp;

struct hello_world_thread : thread<> {
  hello_world_thread() : thread{static_cast<int>(thread_priority::main)} {}

  void run() override {
    printf("Hello world!\n");
    unimp.schedule();
    imp.schedule();
    printf("Hello world again!\n");
    yield();
    printf("Hello world third time!\n");
  }
};

struct main_thread : thread<> {
  main_thread() : thread{static_cast<int>(thread_priority::main)} {}

  void run() override {
    printf("Main here!\n");
  }
};

hello_world_thread hello_world_th;
main_thread main_th;

auto sched = make_scheduler_with_priorities<8>();
int main() {
  application::instance.register_scheduler(sched);
  hello_world_th.schedule();
  main_th.schedule();

  printf("Ready to start!\n");
  application::instance.start();
}
