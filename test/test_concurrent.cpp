#include <unistd.h>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

class BackgroundTask {
public:
    void operator()(int sleepCnt) const {
        for (int i = 0; i < sleepCnt; ++i) {
            sleep(2);
            cout << "hello here" << endl;
        }
    }
};

static int test_thread(int argc, char *argv[]) {
    BackgroundTask bgt;
    std::thread tmpThread(bgt, 5);

    cout << "waiting for finished" << endl;
    tmpThread.join();
    cout << "finished" << endl;
    return 0;
}

int main(int argc, char *argv[]) {
    return test_thread(argc, argv);
}
