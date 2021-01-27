#ifndef DRIVER_H
#define DRIVER_H

#include <string>

using namespace std;

class Context;

class Driver {
public:
  virtual string getName() = 0;

  virtual void init(Context &context) = 0;

  virtual ~Driver() {};
};

#endif // DRIVER_H