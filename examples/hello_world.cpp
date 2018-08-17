#include <iostream>
#include "kernel/scheduler.h"
#include "kernel/task.h"

using namespace std;
using namespace ypp;

struct hello_world_task : task<255> {
  void run() override {
    cout << "Hello world!" << endl;
  }
};

int main() {
  scheduler::run_queue<32> queue;
  scheduler::global_scheduler().initialize(queue);

  hello_world_task tsk;
  tsk.schedule();

  scheduler::global_scheduler().start();

  return 0;
}
