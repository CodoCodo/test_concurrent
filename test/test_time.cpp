/* 测试c++的时间功能 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <set>
#include "person.h"

struct Hello {
  uint8_t a;
  uint8_t b;
  uint8_t c;

  static const int id = 0x778;
}__attribute__((packed));

#if 0

using namespace std;

int test_set() {
    set<string> mySet;
    mySet.insert("caocao");
    mySet.insert("dianwei");
    mySet.insert("guojia");
    
    auto iter = mySet.find("caocao");
    cout << "caocao is " << (iter != mySet.end()) << endl;

    iter = mySet.find("guanyu");
    cout << "guanyu is " << (iter != mySet.end()) << endl;
}

int test_map() {
    map<string, int> myTable;
    myTable["liubei"] = 1;
    myTable["guanyu"] = 2;
    myTable["zhangfei"] = 3;
    myTable.erase(myTable.find("guanyu"));

    return 0;
}

int test_chrono(int argc, char *argv[]) {
    std::chrono::milliseconds ms(5802);
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);

    cout << "before sleep " << endl;
    std::this_thread::sleep_for(s);
    cout << "after sleep " << endl;
    return 0;
}

#endif

#include <vector>


int main(int argc, char *argv[]) {
    struct Hello tmpHello;
    std::cout << sizeof(tmpHello) << std::endl;
    return 0;
}

