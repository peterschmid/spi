#include <unistd.h>
#include <iostream>
#include <fstream>
#include "mcp3008Spi.h"

using namespace std;

/**
 * Main program to read 20 times from mcp3008 channel 0 and calculate level
 */
int main(void)
{
    std::cout<<"Read waterlevel.conf"<<std::endl;
    ifstream in("waterlevel.conf");
    std::string line;
    const std::string separator("=");
    double a(0.0);
    double b(0); 
    int t(0);
    for(auto i=0; i<3; ++i) {
        std::getline(in, line);
        auto separatorPos = line.find(separator);
        std::string key = line.substr(0, separatorPos);
        std::string val = line.substr(separatorPos+1, std::string::npos);
        std::cout << key << ":" << val << std::endl;
        if (key=="a") {
             a = std::stod(val);
        } else if (key=="b")  {
             b = std::stod(val);
        } else if (key=="t") {
             t = std::stoi(val);
        }
        std::cout << "a=" <<  a << ", b=" << b << ", t=" << t << std::endl;
    }
    in.close();

    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int i = 20;

    while(i > 0)
    {
    	auto digit = a2d.readValueChannel0();
    	// change form digits to cm water level
    	auto level = digit*a+b;
    	cout << "Ch0: Digit: " << digit << ", Pegel: " << level << "cm" << endl;
        sleep(1);
        i--;
    }
    return 0;
}
