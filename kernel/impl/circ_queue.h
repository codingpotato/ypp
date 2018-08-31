#ifndef YPP_KERNEL_CIRC_QUEUE_H
#define YPP_KERNEL_CIRC_QUEUE_H

namespace ypp {
namespace kernel_impl {

template <class N>
struct circ_queue {
  struct node {
    friend circ_queue;

    inline node() {}

    node(const node &) = delete;
    node &operator=(const node &) = delete;
    node(node &&) = delete;
    node &operator=(node &&) = delete;

  private:
    N *next_ = nullptr;
  };

  inline circ_queue() {}

  circ_queue(const circ_queue &) = delete;
  circ_queue &operator=(const circ_queue &) = delete;
  circ_queue(circ_queue &&) = default;
  circ_queue &operator=(circ_queue &&) = default;

  inline bool empty() const {
    return tail_ == nullptr;
  }

  inline void tail_push(N *new_node) {
    if (empty()) {
      new_node->next_ = new_node;
    } else {
      new_node->next_ = tail_->next_;
      tail_->next_ = new_node;
    }
    tail_ = new_node;
  }

  inline N *head_pop() {
    if (empty()) {
      return nullptr;
    } else {
      N *first = tail_->next_;
      if (first->next_ == first) {
        tail_ = nullptr;
      } else {
        tail_->next_ = first->next_;
      }
      return first;
    }
  }

private:
  N *tail_ = nullptr;
};

} // namespace kernel_impl
} // namespace ypp

#endif /* YPP_KERNEL_CIRC_QUEUE_H */
