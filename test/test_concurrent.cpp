#include <unistd.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

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


/* 测试thread对象使用lamda表达式 */
class Person {
public:
    Person(const string &name = "") : mName(name) {}
    string mName;
};

static int test_thread_with_lamda(int argc, char *argv[]){
    vector<thread> threadBuffers;
    Person person("mdsj");
    threadBuffers.emplace_back([](Person &rPerson) {
        for (int i = 0; i < 3; ++i) {
            cout << rPerson.mName << endl;
            sleep(2);
        }
    }, std::ref(person));

    thread t2([]() {
        for (int i = 0; i < 2; ++i) {
            cout << "thread 2" << endl;
        }
    });
    threadBuffers.push_back(std::move(t2));

    cout << "waiting for finished" << endl;
    for (auto &t : threadBuffers) {
        if (t.joinable()) {
            cout << "joining" << endl;
            t.join();
        }
    }
    cout << "finished" << endl;
    return 0;
}

int main(int argc, char *argv[]) {
    return test_thread_with_lamda(argc, argv);
}
