#ifndef OPTIONS_H
#define OPTIONS_H

#include "utils/convert.h"
#include <map>
#include <optional>
#include <string>

using namespace std;
using namespace utils;

class Options {
private:
  // program path
  string program;
  // command such as help, csv or run
  string command;
  // map of options
  map<string, string> options;
public:
  Options(int argc, char **argv);

  string getCommand();

  template<typename T> T getOption(const string &name) {
	return getOption<T>(name, nullopt);
  }

  template<typename T> T getOption(const string &name, optional<string> defaultValue) {
	map<string, string>::iterator iterator = options.find(name);
	string value;
	if (iterator != options.end()) {
	  // option found
	  value = iterator->second;
	} else {
	  throw Exception(format("Missing option %s", name.c_str()));
	}
	if (value.empty() && defaultValue) {
	  value = defaultValue.value();
	}
	return convert<T>(value);
  }
};
#endif //OPTIONS_H