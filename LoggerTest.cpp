#include<iostream>
#include<unistd.h>
#include"Logger.h"
#include<string>
#include<sstream>

int main()
{
  // create an object of Logger class, log file name is provided
  Logger::Logger log("MyLogger");
  int pid = fork();
  int i = 10;
  int myPid = getpid();
  enum Logger::logType logT = Logger::DEBUG;
  std::stringstream str;
  str << "This is written by process " << myPid;
  // if (pid == 0)
  //   sleep(100);
  // else
  //   sleep(5000);
  for (;i > 0; i--)
    log.write(logT,str.str().c_str());
  return 0;
}
