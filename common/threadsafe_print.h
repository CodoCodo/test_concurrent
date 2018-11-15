#ifndef _THREADSAFE_PRINT_H
#define _THREADSAFE_PRINT_H

#include <iostream>
#include <mutex>
#include "timestamp.h"

namespace ThreadSafe {
    std::mutex gPrintMutex;
};

#define THREAD_SAFE_OUTPUT(os, x) \
    do { \
        std::lock_guard<std::mutex> _lk(ThreadSafe::gPrintMutex); \
        os << __FILE__ << '\t' << __LINE__ << '\t' << getTimeStamp() << '\t' << x << std::endl; \
    } while(0)

#define THREAD_SAFE_PRINT(x) THREAD_SAFE_OUTPUT(std::cout, x)
#define THREAD_SAFE_ERROR(x) THREAD_SAFE_OUTPUT(std::cerr, x)

#endif /* _THREADSAFE_PRINT_H */
