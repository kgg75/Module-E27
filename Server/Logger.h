#pragma once


class Logger {
	private:
		std::fstream log_file;
		std::mutex loggerMutex;
		bool open_status_OK = true;
	public:
		Logger();
		~Logger();
		bool GetStatus();
		void operator << (const char* text);
		friend std::ostream& operator << (std::ostream& output, Logger& logger);
};


