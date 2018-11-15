#include "timestamp.h"
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>

using namespace std;

int64_t getTimeStamp() {
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    int64_t ts = 0;
    if (res == 0) {
        ts = tv.tv_sec * 1000;
        ts += tv.tv_usec / 1000;
    } else {
        cerr << "gettimeofday failed. " << strerror(errno) << endl;
    }
    return ts;
}
