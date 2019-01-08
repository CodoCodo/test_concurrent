#ifndef _DMS_RUN_KEY_H
#define _DMS_RUN_KEY_H

#include <string>

class DmsRunKey {
 public:
  std::string Generate();
  static int Test(int argc, char *argv[]);
};

#endif // _DMS_RUN_KEY_H
