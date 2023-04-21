#include "StdAfx.h"

#include "Logger.h"
#include "Constants.h"


using namespace std;


Logger::Logger() {
	log_file.open(LOG_FILE_NAME, ios::in | ios::out | ios::app);
	if (!log_file.is_open()) {
		//cout << "Íåèçâåñòíàÿ îøèáêà ïðè îòêðûòèè log-ôàéëà!\n";
		open_status_OK = false;
	}
}


Logger::~Logger() {
	log_file.close();
}


bool Logger::GetStatus() {
	return open_status_OK;
}


void Logger::operator << (const char* text) {
	loggerMutex.lock();
	log_file << text << '\n';
	log_file.flush();
	loggerMutex.unlock();
}


ostream& operator << (ostream& output, Logger& logger) {
	string str;

	logger.loggerMutex.lock();
	logger.log_file.seekg(0);

	while (!logger.log_file.eof()) {
		std::getline(logger.log_file, str);
		output << str << '\n';
	}

	logger.loggerMutex.unlock();

	return output;
}
