#include <unistd.h>
#include <iostream>
#include <fstream>
#include "mcp3008Spi.h"

using namespace std;

/**
 * Main program to read value from mcp3008 channel 0 and calculate level in cm
 */
int main(void)
{
    // read config file
    ifstream in("waterlevel.conf");
    std::string line;
    const std::string separator("=");
    double a(0.0);
    double b(0); 
    int t(0);
    for(auto i=0; i<3; ++i) {
        std::getline(in, line);
        auto separatorPos = line.find(separator);
        auto key = line.substr(0, separatorPos);
        auto val = line.substr(separatorPos+1, std::string::npos);
        if (key=="a") {
             a = std::stod(val);
        } else if (key=="b")  {
             b = std::stod(val);
        } else if (key=="t") {
             t = std::stoi(val);
        }
    }
    in.close();

    // read sensor value
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

    auto digit = a2d.readValueChannel0();
    // change form digits to cm water level (function is based on measurement)
    auto level = digit*a+b;
    // round and add to built in depth (60cm)
    auto intLevel = t + (int)(level+0.5);
    cout << intLevel << endl;
    return 0;
}
