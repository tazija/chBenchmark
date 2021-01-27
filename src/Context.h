#ifndef CONTEXT_H
#define CONTEXT_H

#include "Options.h"
#include <optional>
#include <string>

using namespace std;

class Driver;

class Context {
private:
  static Context *CONTEXT;

  Options options;

  // mode "csv", "run" or "help"
  int mode;

  // MODE_CSV
  int warehouseCount;
  string datasetPath;

  // MODE_RUN
  string outputPath;
  int analyticalClients;
  int transactionalClients;
  int testDuration;
  int warmupDuration;
  Driver *driver;

  Context(int argc, char **argv);

  void initModeCsv();

  void initModeRun();
public:
  const static int MODE_CSV = 1;

  const static int MODE_RUN = 2;

  const static int MODE_HELP = 3;

  static void init(int argc, char *argv[]);

  static Context* getContext();

  template<typename T> T getOption(const string &name) {
	return options.getOption<T>(name);
  }

  template<typename T> T getOption(const string &name, optional<string> defaultValue) {
	return options.getOption<T>(name, defaultValue);
  }
};
#endif //CONTEXT_H