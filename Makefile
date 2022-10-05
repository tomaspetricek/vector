include config.mk

test: test.cpp X.h X.cpp vector.h
	g++ $(CXXFLAGS) test.cpp X.cpp -o test
