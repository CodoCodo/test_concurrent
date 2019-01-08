#include "md5.h"
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
  MD5 md5_obj("abc");
  std::cout << md5_obj.toStr() << std::endl;
  return 0;
}
