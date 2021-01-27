#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

using namespace std;

class Exception : public runtime_error {
public:
  Exception(const string &message, ...) : runtime_error(message) {}

  Exception(const char *message, ...) : runtime_error(message) {}
};
#endif //EXCEPTION_H
