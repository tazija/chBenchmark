#ifndef UTILS_FORMAT_H
#define UTILS_FORMAT_H

#include <memory>
#include <string>
#include <stdarg.h>
#include <stdio.h>

using namespace std;

namespace utils {
  static string format(const string &format, ...) {
	// reserve two times as much as the length of the format
	int final_n, n = ((int)format.size()) * 2; /*  */
	unique_ptr<char[]> formatted;
	va_list ap;
	while (1) {
	  // wrap the plain char array into the unique_ptr
	  formatted.reset(new char[n]);
	  strcpy(&formatted[0], format.c_str());
	  va_start(ap, format);
	  final_n = vsnprintf(&formatted[0], n, format.c_str(), ap);
	  va_end(ap);
	  if (final_n < 0 || final_n >= n) {
		n += abs(final_n - n + 1);
	  } else {
		break;
	  }
	}
	return string(formatted.get());
  }
};
#endif //UTILS_FORMAT_H
