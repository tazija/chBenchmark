#include "Options.h"
#include "Exception.h"
#include "utils/format.h"

Options::Options(int argc, char **argv) {
  // command -k v --key1 value1 --key2=value2
  // --command -k v --key1 value1 --key2=value2
  for (int index = 0; index < argc; index++) {
	string arg = argv[index];
	switch (index) {
	case 0: // program path
	  program = arg;
	  break;
	case 1: // command may or may not start with --
	  command = arg.find("--") == 0 ? arg.replace(0, 2, "") : arg;
	  break;
	default: // parse options
	  // key should start with - or --
	  size_t position = string::npos;
	  if (arg.find("-") == 0) {
		position = arg.find('=', 0);
	  } else {
		throw Exception(format("Option %s is unexpected", arg.c_str()));
	  }
	  string key;
	  string value;
	  // --key=value
	  if (position != string::npos) {
		key = arg.substr(0, position);
		value = arg.substr(position + 1, arg.size() - (position + 1));
		// --key value
	  } else {
		key = arg;
		int nextIndex = index + 1;
		string nextArg;
		// next argument is option value
		if (nextIndex < argc && (nextArg = argv[nextIndex]).find("-") == string::npos) {
		  index = nextIndex;
		  value = nextArg;
		}
	  }
	  options[key] = value;
	}
  }
  if (command.empty()) {
	throw Exception("Command is expected");
  }
}

string Options::getCommand() {
  return command;
}