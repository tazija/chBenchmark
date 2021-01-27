#ifndef ODBCDRIVER_H
#define ODBCDRIVER_H

#include "Driver.h"

class OdbcDriver : public Driver {
private:
  string dsn;
  string user;
  string password;
public:
  virtual string getName();

  virtual void init(Context &context);

  virtual ~OdbcDriver();
};

#endif //ODBCDRIVER_H