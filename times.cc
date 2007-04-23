#ifdef HAVE_LANGINFO_H
#include <langinfo.h>
#endif

#include "times.h"

namespace ledger {

ptime time_now = boost::posix_time::second_clock::universal_time();
date  date_now = boost::gregorian::day_clock::universal_day();

#ifdef SUPPORT_DATE_AND_TIME
moment_t& now(time_now);
#else
moment_t& now(date_now);
#endif

bool day_before_month = false;
static bool  day_before_month_initialized = false;

moment_t parse_datetime(const char * str)
{
  if (! day_before_month_initialized) {
#ifdef HAVE_NL_LANGINFO
    const char * d_fmt = nl_langinfo(D_FMT);
    if (d_fmt && std::strlen(d_fmt) > 1 && d_fmt[1] == 'd')
      day_before_month = true;
    day_before_month_initialized = true;
#endif
  }
#if 0
  return parse_abs_datetime(in);
#else
  int year = ((str[0] - '0') * 1000 +
	      (str[1] - '0') * 100 +
	      (str[2] - '0') * 10 +
	      (str[3] - '0'));

  int mon = ((str[5] - '0') * 10 +
	     (str[6] - '0'));

  int day = ((str[8] - '0') * 10 +
	     (str[9] - '0'));

  return moment_t(boost::gregorian::date(year, mon, day));
#endif
}

moment_t datetime_range_from_stream(std::istream& in)
{
}

}
