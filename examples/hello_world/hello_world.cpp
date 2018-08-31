#include <iostream>
#include <ypp/kernel/application.h>
#include <ypp/kernel/scheduler.h>
#include <ypp/kernel/thread.h>

using namespace std;
using namespace ypp;

struct hello_world_thread : thread<255> {
  void run() override {
    cout << "Hello world!" << endl;
  }
};

static auto sched = make_scheduler_with_priorities<32>();
int main() {
  application::instance.register_scheduler(sched);

  hello_world_thread th;
  th.schedule();

  application::instance.start();

  return 0;
}
