#include <unistd.h>
#include <iostream>
#include "mcp3008Spi.h"

using namespace std;

/**
 * Main program to read value from mcp3008 channel 0 and calculate level
 */
int main(void)
{
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

    auto digit = a2d.readValueChannel0();
    // change form digits to cm water level
    auto level = digit*0.3478-63.702;
    auto intLevel = (int)(level+0.5);
    if (intLevel<0) {
        intLevel=0;
    }
    cout << intLevel << endl;
    return 0;
}
