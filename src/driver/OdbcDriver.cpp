#include "OdbcDriver.h"
#include "../Context.h"
#include <string>

using namespace std;

string OdbcDriver::getName() {
  return "odbc";
}

void OdbcDriver::init(Context &context) {
  // data source name, user and password
  dsn = context.getOption<string>("--odbc.dsn");
  user = context.getOption<string>("--odbc.user");
  password = context.getOption<string>("--odbc.password");
}

OdbcDriver::~OdbcDriver() {
}