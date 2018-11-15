#include <iostream>
#include <unistd.h>
#include <condition_variable>
#include "threadsafe_print.h"
#include <thread>

using namespace std;

class BackgroundTask;
class BackgroundTask {
public:
    BackgroundTask() 
    :mbWork(false) {}

    void operator()() {
        THREAD_SAFE_PRINT("before wait");
        std::unique_lock<std::mutex> lk(mMutex);
        mDataCond.wait(lk, [this]{ return mbWork;});
        mbWork = false;
        THREAD_SAFE_PRINT("after wait");
        lk.unlock();
    }

    void notify() {
        std::lock_guard<std::mutex> lk(mMutex);
        THREAD_SAFE_PRINT("before notify");
        sleep(1);
        mbWork = true;
        mDataCond.notify_one();
        THREAD_SAFE_PRINT("after notify");
    }
    
    static void threadFunc(BackgroundTask &obj) {
        obj();
    }

private:
    std::mutex mMutex;
    std::condition_variable mDataCond;
    bool mbWork;
};



/* 测试condition_variable的唤醒 */
int test_condition_wake(int argc, char *argv[]) {
    BackgroundTask bgt;
    std::thread tmpThread(BackgroundTask::threadFunc, std::ref(bgt));
    bgt.notify();
    tmpThread.join();
    return 0;
}

int main(int argc, char *argv[]) {
    return test_condition_wake(argc, argv);
}