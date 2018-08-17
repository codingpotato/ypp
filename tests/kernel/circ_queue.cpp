#include "kernel/circ_queue.h"
#include "gtest/gtest.h"

using namespace ypp;

struct object : circ_queue<object>::node {
  object(int i) : i_{i} {}

  int val() {
    return i_;
  }

private:
  int i_;
};

TEST(CircQueueTest, TestEmptyQueue) {
  circ_queue<object> q;

  EXPECT_TRUE(q.empty());
}

TEST(CircQueueTest, PushPopTestBasic) {
  circ_queue<object> q;

  q.tail_push(new object{12});
  EXPECT_FALSE(q.empty());
  auto *obj = q.head_pop();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(12, obj->val());
  delete obj;
}

TEST(CircQueueTest, PushPopTestMultipleOperations) {
  circ_queue<object> q;

  q.tail_push(new object{20});
  q.tail_push(new object{30});
  EXPECT_FALSE(q.empty());
  auto *obj = q.head_pop();
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(20, obj->val());
  delete obj;

  q.tail_push(new object{40});
  obj = q.head_pop();
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(30, obj->val());
  delete obj;

  obj = q.head_pop();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(40, obj->val());
  delete obj;
}
