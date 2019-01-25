/* 测试c++的时间功能 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>

// 测试时间点
int TestTimePoint(int argc, char *argv[]) {
  auto t1 = std::chrono::steady_clock::now();
  std::chrono::milliseconds d1(1200);
  auto t2 = t1 + d1;
  std::cout << t1.time_since_epoch().count() << std::endl;
  std::cout << t2.time_since_epoch().count() << std::endl;
  return 0;
}

// 测试原生时间类型的单位转换
int TestDuration(int argc, char *argv[]) {
  std::chrono::milliseconds d1(1800);
  d1*=2;
  std::cout << d1.count() << std::endl;
  std::cout << std::chrono::milliseconds::period::num << std::endl;
  std::cout << std::chrono::milliseconds::period::den << std::endl;

  auto s_d1 = std::chrono::duration_cast<std::chrono::seconds>(d1);
  std::cout << s_d1.count() << std::endl;
  return 0;
}


// 测试自定义时间段单位转换
int TestUserDefDuration(int argc, char *argv[]) {
  typedef std::chrono::duration<double> seconds_type;
  typedef std::chrono::duration<double,std::milli> milliseconds_type;
  typedef std::chrono::duration<double,std::ratio<60*60>> hours_type;

  milliseconds_type d1(1500);
  seconds_type s_d1(std::chrono::duration_cast<seconds_type>(d1));

  std::cout << s_d1.count() << std::endl;
  return 0;
}

int main(int argc, char *argv[]) {
  return TestTimePoint(argc, argv);
}
