build-test: mcp3008Spi.cpp mcp3008SpiTest.cpp
	g++ -std=c++0x -Wall -o OutBin mcp3008Spi.cpp mcp3008SpiTest.cpp

build-ch0: mcp3008Spi.cpp mcp3008SpiTestCh0.cpp
	g++ -std=c++0x -Wall -o OutBinCh0 mcp3008Spi.cpp mcp3008SpiTestCh0.cpp

build-ch1: mcp3008Spi.cpp mcp3008SpiTestCh1.cpp
	g++ -std=c++0x -Wall -o OutBinCh1 mcp3008Spi.cpp mcp3008SpiTestCh1.cpp

build-stub: mcp3008SpiTestStub.cpp
	g++ -std=c++0x -Wall -o OutBinStub mcp3008SpiTestStub.cpp

build-bin: mcp3008Spi.h mcp3008Spi.cpp mcp3008SpiCh0.cpp
	g++ -std=c++0x -Wall -o readSpiCh0mcp3008.bin mcp3008Spi.cpp mcp3008SpiTestCh0.cpp
