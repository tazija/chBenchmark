#ifndef COUCHBASEDRIVER_H
#define COUCHBASEDRIVER_H

#include "Driver.h"

class CouchbaseDriver : public Driver {
public:
  virtual string getName();

  virtual void init(Context &context);

  virtual ~CouchbaseDriver();
};

#endif //COUCHBASEDRIVER_H