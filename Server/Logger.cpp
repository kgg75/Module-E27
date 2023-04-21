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
	char str[BUFFER_LENGTH];

	logger.loggerMutex.lock();
	logger.log_file.seekg(ios_base::beg);	// устанавливаем текущую позицию чтения на начало

	while (logger.log_file.getline(str, BUFFER_LENGTH))
		output << str << '\n';

	logger.log_file.clear();	// сбрасываем ошибки потока
	logger.loggerMutex.unlock();

	return output;
}
