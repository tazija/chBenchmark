#include <string>
#include "DriverManager.h"

using namespace std;

map<string, Driver *> DriverManager::drivers = map<string, Driver *>();

Driver *DriverManager::getDriver(const string &name) {
  return drivers[name];
}

void DriverManager::registerDriver(Driver *driver) {
  drivers[driver->getName()] = driver;
}