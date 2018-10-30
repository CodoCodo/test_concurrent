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


/* 测试thread对象使用lamda表达式 */
class Person {
public:
    Person(const string &name = "") : mName(name) {}
    string mName;
};

static int test_thread_with_lamda(int argc, char *argv[]){
    Person person("mdsj");
    std::thread tmpThread([](Person &rPerson) {
        for (int i = 0; i < 3; ++i) {
            cout << rPerson.mName << endl;
            sleep(2);
        }
    }, std::ref(person));

    cout << "waiting for finished" << endl;
    tmpThread.join();
    cout << "finished" << endl;
    return 0;
}

int main(int argc, char *argv[]) {
    return test_thread_with_lamda(argc, argv);
}
