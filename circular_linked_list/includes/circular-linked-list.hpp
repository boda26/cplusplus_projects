#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  void PushBack(T data);
  void SetOrder(Order o);
  Node<T>* Head();
  Node<T>* Tail();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  //int i = 0;
  do {
    os << iter->data << '\t';
    iter = iter->next;
    //std::cout << i << std::endl;
  } while (iter != cll.head_);
  return os;
}

template <typename T>
Node<T>* CircularLinkedList<T>::Head() {
  return head_;
}

template <typename T>
Node<T>* CircularLinkedList<T>::Tail() {
  return tail_;
}

template <typename T>
void CircularLinkedList<T>::SetOrder(Order o) {
  node_order_ = o;
}

template <typename T>
void CircularLinkedList<T>::PushBack(T data) {
  auto* n = new Node<T>(data);
  if (head_ == nullptr) {
    head_ = tail_ = n;
    tail_->next = head_;
    return;
  }
  tail_->next = n;
  tail_ = n;
  tail_->next = head_;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
    return;
  }
  auto* src = source.head_;
  Node<T>* prev = nullptr;
  do {
    auto* cur = new Node<T>(src->data);
    if (src == source.head_) {
      head_ = cur;
    }
    if (src == source.tail_) {
      tail_ = cur;
    }
    if (prev != nullptr) {
      prev->next = cur;
    }
    prev = cur;
    src = src->next;
  } while (src != source.head_);
  tail_->next = head_;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  auto* cur = head_;
  if (head_ != nullptr) {
    auto* cur = head_;
    do {
      auto* next = cur->next;
      delete cur;
      cur = next;
    } while (cur != head_);
    head_ = tail_ = nullptr;
  }
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    return *this;
  }
  auto* src = source.head_;
  Node<T>* prev = nullptr;
  do {
    auto* cur = new Node<T>(src->data);
    if (src == source.head_) {
      head_ = cur;
    }
    if (src == source.tail_) {
      tail_ = cur;
    }
    if (prev != nullptr) {
      prev->next = cur;
    }
    prev = cur;
    src = src->next;
  } while (src != source.head_);
  tail_->next = head_;
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ != nullptr) {
    auto* cur = head_;
    do {
      auto* next = cur->next;
      delete cur;
      cur = next;
    } while (cur != head_);
    head_ = tail_ = nullptr;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  auto* n = new Node<T>(data);
  if (head_ == nullptr) {head_ = tail_ = n;tail_->next = head_;return;}
  if (node_order_ == Order::kASC) {
    if (data < head_->data) {
      tail_->next = n;
      n->next = head_;
      head_ = n;
      return;
    }
    auto* cur = head_;
    while (cur->next != head_ && cur->next->data < data) {cur = cur->next;}
    if (cur == tail_) {
      cur->next = n;
      n->next = head_;
      tail_ = n;
    } else {
      n->next = cur->next;
      cur->next = n;
    }
  } else {  //DESC
    if (data >= head_->data) {
      tail_->next = n;
      n->next = head_;
      head_ = n;
      return;
    }
    auto* cur = head_;
    while (cur->next != head_ && cur->next->data > data) {
      cur = cur->next;
    }
    if (cur == tail_) {
      cur->next = n;
      n->next = head_;
      tail_ = n;
    } else {
      n->next = cur->next;
      cur->next = n;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) {
    return;
  }
  auto* t = tail_;
  auto* cur = head_;
  Node<T>* next = nullptr;
  Node<T>* prev = nullptr;
  tail_ = head_;
  head_ = nullptr;
  while (cur != t) {
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  cur->next = prev;
  head_ = cur;
  tail_->next = head_;
}

#endif