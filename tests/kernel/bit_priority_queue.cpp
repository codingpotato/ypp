#include <gtest/gtest.h>
#include <ypp/kernel/bit_priority_queue.h>

using namespace ypp;

TEST(BitPriorityQueueTest, EmptyTest) {
  bit_priority_queue q;

  EXPECT_TRUE(q.empty());
  q.set(3);
  EXPECT_FALSE(q.empty());
  q.unset(3);
  EXPECT_TRUE(q.empty());
}

TEST(BitPriorityQueueTest, SetGetTestBasic) {
  bit_priority_queue q;

  EXPECT_FALSE(q.test(3));
  q.set(3);
  EXPECT_TRUE(q.test(3));
  q.unset(3);
  EXPECT_FALSE(q.test(3));
}

TEST(BitPriorityQueueTest, SetGetTestMultipleBits) {
  bit_priority_queue q;

  EXPECT_FALSE(q.test(3));
  EXPECT_FALSE(q.test(5));
  q.set(3);
  EXPECT_TRUE(q.test(3));
  EXPECT_FALSE(q.test(5));
  q.set(5);
  EXPECT_TRUE(q.test(3));
  EXPECT_TRUE(q.test(5));
  q.unset(3);
  EXPECT_FALSE(q.test(3));
  EXPECT_TRUE(q.test(5));
  q.unset(5);
  EXPECT_FALSE(q.test(3));
  EXPECT_FALSE(q.test(5));
}

TEST(BitPriorityQueueTest, FirstBitTestMinimum) {
  bit_priority_queue q;

  q.set(1);
  EXPECT_EQ(1, q.first());
  q.unset(1);
}

TEST(BitPriorityQueueTest, FirstBitTestMaximum) {
  bit_priority_queue q;

  int shift = sizeof(uint32_t) * 8 - 1;
  q.set(shift);
  EXPECT_EQ(shift, q.first());
  q.unset(shift);
}

TEST(BitPriorityQueueTest, FirstBitTestMultipleBits) {
  bit_priority_queue q;

  q.set(5);
  q.set(6);
  EXPECT_EQ(5, q.first());
  q.set(3);
  EXPECT_EQ(3, q.first());
  q.set(12);
  EXPECT_EQ(3, q.first());
  q.unset(3);
  EXPECT_EQ(5, q.first());
}
