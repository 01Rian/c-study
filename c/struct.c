#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct birdStruct 
{
  char const* jay;
  char const* magpie;
  char const* raven;
  char const* chough;
};

struct birdStruct const aName = {
  .jay = "Jay",
  .magpie = "Magpie",
  .raven = "Raven",
  .chough = "Chough"
};

struct tm1
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

struct tm today1 = { 
  .tm_year = 2019-1900,
  .tm_mon = 4-1,
  .tm_mday = 3,
  .tm_hour = 10, 
  .tm_min = 0,
  .tm_sec = 47, 
};

bool leapYear(unsigned year)
{
  return !(year % 4) && ((year % 100) || !(year % 400));
}

#define DAYS_BEFORE (int const [12]) { \
  [0] = 0, [1] = 31, [2] = 59, [3] = 90, [4] = 120, [5] = 151, \
  [6] = 181, [7] = 212, [8] = 243, [9] = 273, [10] = 304, [11] = 334 \
}

struct tm time_set_yday(struct tm t) 
{
  t.tm_yday += DAYS_BEFORE[t.tm_mon] + t.tm_mday - 1;

  if (t.tm_mon > 1 && leapYear(t.tm_year + 1900)) {
    t.tm_yday++;
  }
  return t;
}


int main(void)
{  
  struct tm today = {
    .tm_year = 2019-1900,
    .tm_mon = 4-1,
    .tm_mday = 3,
    .tm_hour = 10,
    .tm_min = 0,
    .tm_sec = 47, 
  };

  printf("this year is %d, next year will be %d\n", today.tm_year+1900, today.tm_year+1900+1);
  
  today = time_set_yday(today);

  printf("day of the year is %d\n", today.tm_yday);
}