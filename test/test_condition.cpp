#include <iostream>
#include <unistd.h>
#include <condition_variable>
#include "threadsafe_print.h"
#include <thread>
#include "blocking_queue.h"
#include "person.h"
#include "concurrent_common.h"
#include <chrono>
#include <mutex>
#include <vector>

using namespace std;

class MyLock : public std::mutex {
public:
  int value_;
};

class BackgroundTask;
class BackgroundTask {
public:
    BackgroundTask() 
    :mbWork(false) {}

    void operator()() {
        THREAD_SAFE_PRINT("before wait");
        std::unique_lock<std::mutex> lk(mMutex);
#if 1
        mDataCond.wait(lk, [this]{ 
          cout << "testing mbWork" << endl;
          return mbWork;
        });
#else
        mDataCond.wait(lk);
#endif
        mbWork = false;
        THREAD_SAFE_PRINT("after wait");
        lk.unlock();
    }

    void notify() {
        std::lock_guard<std::mutex> lk(mMutex);
        THREAD_SAFE_PRINT("before notify");
        mbWork = true;
        mDataCond.notify_one();
        THREAD_SAFE_PRINT("after notify");
    }
    
    static void threadFunc(BackgroundTask &obj) {
        obj();
    }

    std::mutex mMutex;
    std::condition_variable mDataCond;
    bool mbWork;
};



/* 测试condition_variable的唤醒 */
int test_condition_wake(int argc, char *argv[]) {
    BackgroundTask bgt;
    std::thread tmpThread(BackgroundTask::threadFunc, std::ref(bgt));
    sleep(1);
    cout << "main notify" << endl;
    bgt.notify();
    cout << "main after notify" << endl;
    sleep(1);
    std::lock_guard<std::mutex> lk(bgt.mMutex);
    cout << "before join" << endl;
    tmpThread.join();
    return 0;
}

/* 测试阻塞队列 */
int test_blocking_queue(int argc, char *argv[]) {
    Person p1("caocao", "0", 40);
    Person p2("guanyu", "1", 34);
    Person p3(std::move(p2));


    BlockingQueue<Person> queue;

    CONCURRENT_COMMON_COUT << "testing blocking queue" << endl;
    queue.push(Person("zhaoyun", "2", 33));
    queue.push(std::move(p1));
    //queue.push_back(p2);

    CONCURRENT_COMMON_COUT << "before pop blocking queue" << endl;
    
    Person p4 = queue.pop();

    CONCURRENT_COMMON_COUT << "after testing blocking queue" << endl;

    return 0;
}

#if 0
// 测试定时唤醒功能
int TestTimerWake(int argc, char *argv[]) {
  std::condition_variable cond_var;
  std::mutex m;
  auto timeout = std::chrono::milliseconds(20);

  std::vector<std::chrono::milliseconds> duration_list;
  std::unique_lock<std::mutex> lk(m);
  auto last_time = std::chrono::steady_clock::now();
  for (int i = 0; i < 10; ++i) {
    if (cond_var.wait_for(lk, timeout) == std::cv_status::timeout) {
      auto current_time = std::chrono::steady_clock::now();
      duration_list.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time));
      last_time = current_time;
    }
  }

  std::cout << "duration_list are " << std::endl;
  for (auto &t : duration_list) {
    std::cout << std::chrono::duration<double, std::chrono::milliseconds>(t).count() << std::endl;
  }

  return 0;
}
#endif 

//测试二次notify的效果
class TestDoubleNotify {
 public:
  TestDoubleNotify()
    :thread_b_(&TestDoubleNotify::ThreadBFunc, std::ref(*this)) {
  }

  ~TestDoubleNotify() {
    THREAD_SAFE_PRINT("destructor.");
    thread_b_.join();
  }

  int operator()(int argc, char *argv[]) {
    sleep(1);
    PostCondition();
    THREAD_SAFE_PRINT("notify once");
    sleep(4);
    PostCondition();
    THREAD_SAFE_PRINT("notify twice");
    return 0;
  }

  void PostCondition() {
    std::lock_guard<std::mutex> lk(mutex_);
    condition_.notify_one();
  }

  void WaitForCondition() {
    std::unique_lock<std::mutex> lk(mutex_);
    condition_.wait(lk);
  }

  void ThreadBFunc() {
    THREAD_SAFE_PRINT("before wait");
    WaitForCondition();
    THREAD_SAFE_PRINT("after wait 1");
    WaitForCondition();
    THREAD_SAFE_PRINT("after wait 2");
  }

 private:
  std::mutex mutex_;
  std::thread thread_b_;
  std::condition_variable condition_;
};

int main(int argc, char *argv[]) {
  TestDoubleNotify testObj;
  return testObj(argc, argv);
}
