#include <unistd.h>
#include <iostream>
#include "mcp3008Spi.h"

using namespace std;

/**
 * mcp3008SpiTest.cpp
 * Main program to read out 20 times ch0 and ch1
 */
int main(void)
{
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int i = 20;

    while(i > 0)
    {
    	auto digit = a2d.readValueChannel0();
    	// change form digits to cm water level
    	auto level = (digit - 185) * 0.367;
    	cout << "Ch0: Digit: " << digit << ", Pegel: " << level << "cm" << endl;
    	cout << "Ch1: Digit: " << a2d.readValueChannel1() << endl;
        sleep(1);
        i--;
    }
    return 0;
}
