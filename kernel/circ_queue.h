#ifndef CIRC_QUEUE_H
#define CIRC_QUEUE_H

template<class N>
struct circ_queue {
  struct node {
    friend circ_queue;

  private:
    N *next_ = nullptr;
  };

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

#endif /* CIRC_QUEUE_H */