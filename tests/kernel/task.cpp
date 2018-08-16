#include "kernel/task.h"
#include "gtest/gtest.h"

using namespace ypp;

TEST(BitPriorityQueueTest, ConstructionTest) {
  task<255> t;

  EXPECT_EQ(task_status::stopped, t.status());
}