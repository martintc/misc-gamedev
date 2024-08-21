#pragma once

#include <iostream>
#include <string>

class Logger {
 public:
	static void info(std::string message) {
		std::cout << "INFO: " + message << std::endl;
	}

	static void warn(std::string message) {
		std::cout << "WARN: " + message << std::endl;
	}

	static void err(std::string message) {
		std::cout << "ERROR: " + message << std::endl;
	}
};
