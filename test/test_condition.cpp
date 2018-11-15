#include <iostream>
#include <unistd.h>
#include <condition_variable>
#include "threadsafe_print.h"
#include <thread>

using namespace std;

class BackgroundTask {
public:
    BackgroundTask() 
    :mbWork(false) {}

    void operator()(int sleepCnt) const {
        std::unique_lock<std::mutex> lk(mMutex);
        THREAD_SAVE_PRINT("before wait");
        mDataCond.wait(lk, [this]{ return mbWork;})
        THREAD_SAVE_PRINT("after wait");
        lk.unlock();
    }

    void notify() {
        std::lock_guard<std::mutex> lk(mMutex);
        THREAD_SAVE_PRINT("before notify");
        mDataCond.notify_one();
        THREAD_SAVE_PRINT("after notify");
    }

private:
    std::mutex mMutex;
    std::condition_variable mDataCond;
    bool mbWork;
};

/* 测试condition_variable的唤醒 */
int test_condition_wake(int argc, char *argv[]) {
    BackgroundTask bgt;
    std::thread tmpThread(bgt);
    bgt.notify();
    tmpThread.join();
    return 0;
}

int main(int argc, char *argv[]) {
    return test_condition_wake(argc, argv);
}
