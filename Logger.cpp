// Logger.cpp

#include"Logger.h"

// <name>Logger</name>
// <arg1:filename>Log file name </arg1>
// <ret>none</ret>
// <about>constructor</about>
Logger::Logger::Logger(const char *fileName) 
{
  m_logFileName = fileName;	// set the log file name
  bool ret = open();		// open the log file
  if (ret < 0)
    throw LOG_FILE_CREATION_FAILED;
    // ??? search: what if constructor throws an exception
}

// <name>~Logger</name>
// <ret>none</ret>
// <about>destructor</about>
Logger::Logger::~Logger()
{
  m_logStream.close();
}

// <name>open</name>
// <ret>true: log stream is open | false: if not open </ret>
// <about>open logStream corresponding to logFile</about>
bool Logger::Logger::open()
{
  // ??? search: std::ofstream::open()
  m_logStream.open(m_logFileName, std::ofstream::out|std::ofstream::trunc);
  //  verify whether logStram is properly openned or not 
  // TODO: Why it is done, if better way exists then write code in comments.
  if (m_logStream.is_open())
    return true;
  else
    return false;
}

// <name>getCurrentTime</name>
// <arg1:buf>out buffer to hold the date & time</arg1>
// <ret>void</ret>
// <about>prepare the date & time formated string</about>
void Logger::Logger::getCurrentTime(char *buf)
{
  time_t     now;
  struct tm  *tstruct;
  tstruct = localtime(&now);
  time (&now);
  tstruct = localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, 80 , "[ %X ]:[ %d-%m-%Y ]", tstruct);
}

// <name>close</name>
// <ret>void</ret>
// <about>close the log stream</about>
void Logger::Logger::close()
{
  m_logStream.close();
}

// <name> </name>
// <arg1> </arg1>
// <ret> </ret>
// <about> </about>
void Logger::Logger::write(enum logType flag, const char* message)
{
  std::string logFlag;
  char buf [80];

  // based on logType flag decide the log tag
  switch(flag) {
  case INFO:
    logFlag = "[ INFO ]:";
    break;
  case DEBUG:
    logFlag = "[ DEBUG ]:";
    break;
  case WARN:
    logFlag = "[ WARN ]:";
    break;
  case ERROR:
    logFlag = "[ ERROR ]:";
    break;
  }

  // ???
  //sleep till you acquire lock on mutex
  while (!m_logFileWriteLock.try_lock()) {
    //sleep in microseconds.
    usleep(1000);
  }
  Logger::Logger::getCurrentTime(buf);
  std::string dateString(buf);
  m_logStream << logFlag.c_str()  << dateString.c_str() << ":[ " << message << " ]" << std::endl;
  m_logStream.flush();	// ??? search: flush
  m_logFileWriteLock.unlock();	// ???
}
