#ifndef ANTI_DISTRACTION_BLOCKING_QUEUE_H
#define ANTI_DISTRACTION_BLOCKING_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <deque>
#include <iostream>

/**
 * Ref: https://stackoverflow.com/questions/12805041/c-equivalent-to-javas-blockingqueue
 *
 * @tparam T
 */
template<typename T>
class BlockingQueue {
 public:
  std::mutex d_mutex;
  std::condition_variable d_condition;
  std::deque<T> d_queue;
 public:
  void push(T &&value) {
    {
      std::unique_lock<std::mutex> lock(this->d_mutex);
      d_queue.push_front(std::move(value));
    }
    this->d_condition.notify_one();
  }
  void push(const T &value) {
    {
      std::unique_lock<std::mutex> lock(this->d_mutex);
      d_queue.push_front(value);
    }
    this->d_condition.notify_one();
  }
  T pop() {
    std::unique_lock<std::mutex> lock(this->d_mutex);
    this->d_condition.wait(lock, [=] { return !this->d_queue.empty(); });
    T rc(std::move(this->d_queue.back()));
    this->d_queue.pop_back();
    return rc;
  }
};

#endif //ANTI_DISTRACTION_BLOCKING_QUEUE_H
