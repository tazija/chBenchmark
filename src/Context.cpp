#include "Context.h"
#include "Exception.h"
#include "Options.h"
#include "driver/DriverManager.h"
#include "driver/OdbcDriver.h"
#include "driver/CouchbaseDriver.h"
#include "utils/format.h"

using namespace std;
using namespace utils;

Context *Context::CONTEXT = nullptr;

void Context::init(int argc, char **argv) {
  if (CONTEXT != nullptr) {
	throw Exception("Context is already initialized");
  }
  // register drivers
  DriverManager::registerDriver(new OdbcDriver());
  DriverManager::registerDriver(new CouchbaseDriver());
  // create context
  CONTEXT = new Context(argc, argv);
}

Context* Context::getContext() {
  return CONTEXT;
}

Context::Context(int argc, char **argv) : options(Options(argc, argv)) {
  // generate dataset in csv format
  auto command = options.getCommand();
  if (command == "csv") {
	initModeCsv();
	mode = MODE_CSV;
  } else if (command == "run") {
	initModeRun();
	mode = MODE_RUN;
  } else if (command == "help") {
	mode = MODE_HELP;
  } else {
	throw Exception(format("Unknown command %s", command.c_str()));
  }
}

void Context::initModeCsv() {
  // warehouse count
  warehouseCount = getOption<int>("--warehouse.count");
  // output dataset path
  datasetPath = getOption<string>("--dataset.path");
}

void Context::initModeRun() {
  // input dataset path
  datasetPath = getOption<string>("--dataset.path");
  // results and log output path
  outputPath = getOption<string>("--output.path");
  // number of analytical clients
  analyticalClients = getOption<int>("--analytical.clients");
  // number of transactional clients
  transactionalClients = getOption<int>("--transactional.clients");
  // test duration
  testDuration = getOption<int>("--test.duration");
  if (testDuration < 1) {
	throw Exception(format(
		"Option %s test duration should be greater than zero", "--test.duration"));
  }
  // warmup duration
  warmupDuration = getOption<int>("--warmup.duration");

  string driverName = getOption<string>("--driver");

  driver = DriverManager::getDriver(driverName);
  driver->init(*this);
}