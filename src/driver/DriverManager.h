#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include <string>
#include <map>
#include "Driver.h"

using namespace std;

class DriverManager {
private:
  static map<string, Driver *> drivers;

public:
  static Driver *getDriver(const string &name);

  static void registerDriver(Driver *driver);
};

#endif //DRIVERMANAGER_H