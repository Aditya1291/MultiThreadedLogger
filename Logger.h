// Logger.h

#include<iostream>
#include<fstream>
#include<string>
#include<mutex>
#include<time.h>
#include <unistd.h>
#ifndef LOGGER_H
#define LOGGER_H

namespace Logger {

  // Macros for Error codes
  #define LOG_FILE_CREATION_FAILED 0

  // Enum for LogTypes
  enum logType { INFO, DEBUG, WARN, ERROR };

  class Logger
  {
  private:
    // open logStream corresponding to logFile
    bool open();
    // get current local time
    void getCurrentTime(char *buf);
    // close the logStream
    void close();

    std::string m_logFileName;	// log file
    std::ofstream m_logStream;  // stream corresponding to log file
    std::mutex m_logFileWriteLock; // write lock

  public:
    // write a message prefixed with corresponding logType, into the log file
    void write (enum logType flag,
		const char *messagexo);
    // parametrised constructor
    Logger(
	   const char *fileName
	   );
    // destructor
    ~Logger();
  };
}
#endif //LOGGER_H
