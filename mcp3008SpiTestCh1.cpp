#include <unistd.h>
#include <iostream>
#include "mcp3008Spi.h"

using namespace std;

/**
 * Main program to read 20 times digits from mcp3008 channel 1
 */
int main(void)
{
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int i = 20;

    while(i > 0)
    {
    	cout << "Ch1: Digit: " << a2d.readValueChannel1() << endl;
        sleep(1);
        i--;
    }
    return 0;
}
