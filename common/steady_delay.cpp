#include <unistd.h>
#include <sys/select.h>
#include "steady_delay.h"

int SteadyDelay::DelayWithSelect(int64_t milliseconds){
  struct timeval tv;
  tv.tv_sec = milliseconds / 1000;
  tv.tv_usec = (milliseconds % 1000) * 1000;
  int ret;
  do
  {
    ret = select(0, NULL, NULL, NULL, &tv);
  } while (ret < 0 && errno == EINTR);
  return 0;
}
