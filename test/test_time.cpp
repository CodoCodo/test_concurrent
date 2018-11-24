/* 测试c++的时间功能 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {
    std::chrono::milliseconds ms(5802);
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);

    cout << "before sleep " << endl;
    std::this_thread::sleep_for(s);
    cout << "after sleep " << endl;
    return 0;
}

