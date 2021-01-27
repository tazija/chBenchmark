#ifndef UTILS_CONVERT_H
#define UTILS_CONVERT_H

#include "../Exception.h"
#include "format.h"
#include <stdio.h>
#include <sstream>
#include <string>

using namespace std;
using namespace utils;

namespace utils {
  template<typename T> T convert(const string &value) {
	if (!value.empty()) {
	  T result;
	  istringstream stream(value);
	  if (value.find("0x") != 0) {
		stream >> std::hex >> result;
	  } else {
		stream >> std::dec >> result;
	  }
	  if (stream.fail()) {
		throw Exception(format("Can't convert %s", value.c_str()));
	  }
	  return result;
	}
	return T();
  }
}
#endif //UTILS_CONVERT_H
