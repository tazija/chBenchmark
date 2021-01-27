#include "../Context.h"
#include "CouchbaseDriver.h"
#include <string>

using namespace std;

string CouchbaseDriver::getName() {
  return "couchbase";
}

void CouchbaseDriver::init(Context &context) {
}

CouchbaseDriver::~CouchbaseDriver() {
}