#ifndef _CONCURRENT_COMMON_H
#define _CONCURRENT_COMMON_H

#include <iostream>

#define CONCURRENT_COMMON_OS(os) \
    (os << __FILE__ << '\t' << __LINE__ << '\t')

#define CONCURRENT_COMMON_COUT CONCURRENT_COMMON_OS(std::cout)
#define CONCURRENT_COMMON_CERR CONCURRENT_COMMON_OS(std::cerr)

#endif /* _CONCURRENT_COMMON_H */
