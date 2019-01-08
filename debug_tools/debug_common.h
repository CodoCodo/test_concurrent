#ifndef _DEBUG_COMMON_H
#define _DEBUG_COMMON_H

#include <iostream>

#define DEBUG_COMMON_OS(os) \
  (os << __FILE__ << '\t' << __LINE__ << '\t')

#define DEBUG_COMMON_COUT DEBUG_COMMON_OS(std::cout)

#define DEBUG_COMMON_CERR DEBUG_COMMON_OS(std::cerr)

#endif //_DEBUG_COMMON_H
