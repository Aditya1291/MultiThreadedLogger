# compiler
CXX=g++


all: logger loggerTest

loggerTest: logger
	$(CXX) LoggerTest.cpp Logger.o -o LoggerTest -g -std=c++11 -I.
logger:
	$(CXX) -c Logger.cpp -o Logger.o -g -std=c++11

clean:
	rm -rf *.o
	rm -rf LoggerTest
	rm -rf *~
