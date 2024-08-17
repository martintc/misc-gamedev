#pragma once

#include <string>

class Logger {
 public:
	static void info(std::string message);
	static void warn(std::string message);
	static void error(std::string message);
};
