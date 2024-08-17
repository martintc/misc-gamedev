#include "logger.h"
#include <iostream>

void Logger::info(std::string message) {
	std::cout << "INFO: " + message << std::endl;
}

void Logger::warn(std::string message) {
	std::cout << "WARN: " + message << std::endl;
}

void Logger::error(std::string message) {
	std::cout << "ERROR: " + message << std::endl;
}
