#include <unistd.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <functional>

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

class PersonHandler {
public:
    PersonHandler(const string &operation)
    :mOperation(operation){
    }
    void handle(const Person &person) {
        cout << mOperation << '\t' << person.mName << endl;
    }
    static int helloFunc(shared_ptr<PersonHandler> pHandler, Person &person) {
        cout << __FUNCTION__ << '\t' << person.mName << endl;
        pHandler->handle(person);
    }
    string mOperation;
};

static int test_thread_with_lamda(int argc, char *argv[]){
    vector<thread> threadBuffers;
    Person person("mdsj");

    /* 打印系统线程个数 */
    cout << "system thread count is " << std::thread::hardware_concurrency() << endl;

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
            cout << "joining id is " << t.get_id() << endl;
            t.join();
        }
    }
    cout << "finished" << endl;
    return 0;
}

typedef std::function<void ()> MyFunc;
static int test_func(int argc, char *argv[]) {
    Person myPerson("lily");
    shared_ptr<PersonHandler> pHandler(new PersonHandler("fire"));
    MyFunc  myf = std::bind(PersonHandler::helloFunc, pHandler, myPerson);
    myf();
    return 0;
}

int main(int argc, char *argv[]) {
    return test_func(argc, argv);
}
