#include <gtest/gtest.h>
#include <ypp/kernel/task.h>

using namespace ypp;

TEST(TaskTest, TaskStatusRawValueTest) {
  EXPECT_LT(static_cast<char>(task_status::stopped),
            static_cast<char>(task_status::running));
  EXPECT_LT(static_cast<char>(task_status::blocked),
            static_cast<char>(task_status::running));

  EXPECT_GE(static_cast<char>(task_status::running),
            static_cast<char>(task_status::running));
  EXPECT_GE(static_cast<char>(task_status::pending),
            static_cast<char>(task_status::running));
}

struct test_task : task<255> {
  void run() override {}
};

TEST(TaskTest, ConstructionTestDefault) {
  test_task t;

  EXPECT_EQ(task_status::stopped, t.status());
}
