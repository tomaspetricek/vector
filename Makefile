include config.mk

test: test.cpp vector.h
	g++ $(CXXFLAGS) test.cpp X.cpp -o test

benchmark-gcc: benchmark.cpp vector.h
	g++ $(CXXFLAGS) $(CXXFLAGSOPT) benchmark.cpp -lbenchmark -o benchmark-gcc

benchmark-clang: benchmark.cpp vector.h
	clang++ $(CXXFLAGS) $(CXXFLAGSOPT) benchmark.cpp -lbenchmark -o benchmark-clang
