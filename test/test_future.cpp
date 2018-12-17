#include <iostream>
#include "info_uploader_server.h"
#include <thread>

using namespace std;

class Hello {
public:
  void HelloStart(int input) {
    cout << "hello" << input << endl;
  }
};

int upload_func(int frame_id) {
    sleep(2);
    cout << __FUNCTION__ << '\t' << __LINE__ << '\t' << frame_id << endl;
    return 12;
}

int main(int argc, char *argv[]) {
    Hello hello;
    std::thread th(&Hello::HelloStart, &hello, 5);
    cout << "before sleep" << endl;
    sleep(4);
    cout << "end" << endl;
    th.join();
    return 0;
}

