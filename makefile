build-test: mcp3008Spi.cpp mcp3008SpiTest.cpp
	g++ -std=c++11 -Wall -o OutBin mcp3008Spi.cpp mcp3008SpiTest.cpp

build-ch0: mcp3008Spi.cpp mcp3008SpiTestCh0.cpp
	g++ -std=c++11 -Wall -o OutBinCh0 mcp3008Spi.cpp mcp3008SpiTestCh0.cpp

build-ch1: mcp3008Spi.cpp mcp3008SpiTestCh1.cpp
	g++ -std=c++11 -Wall -o OutBinCh1 mcp3008Spi.cpp mcp3008SpiTestCh1.cpp