/***********************************************************************
 * This header file contains the mcp3008Spi class definition.
 * Its main purpose is to communicate with the MCP3008 chip using
 * the userspace spidev facility.
 * The class contains four variables:
 * mode        -> defines the SPI mode used. In our case it is SPI_MODE_0.
 * bitsPerWord -> defines the bit width of the data transmitted.
 *        This is normally 8. Experimentation with other values
 *        didn't work for me
 * speed       -> Bus speed or SPI clock frequency. According to
 *                https://projects.drogon.net/understanding-spi-on-the-raspberry-pi/
 *            It can be only 0.5, 1, 2, 4, 8, 16, 32 MHz.
 *                Will use 1MHz for now and test it further.
 * spifd       -> file descriptor for the SPI device
 *
 * The class contains two constructors that initialize the above
 * variables and then open the appropriate spidev device using spiOpen().
 * The class contains one destructor that automatically closes the spidev
 * device when object is destroyed by calling spiClose().
 * The spiWriteRead() function sends the data "data" of length "length"
 * to the spidevice and at the same time receives data of the same length.
 * Resulting data is stored in the "data" variable after the function call.
 * ****************************************************************************/
#ifndef MCP3008SPI_H
#define MCP3008SPI_H

#include <string>
#include <linux/spi/spidev.h>

class mcp3008Spi{

	enum Channel
	{
	    CH0,
	    CH1,
	    CH2,
		CH3,
		CH4,
		CH5,
		CH6,
		CH7
	};

public:
    mcp3008Spi();
    mcp3008Spi(const std::string& devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord);
    ~mcp3008Spi();
    int spiWriteRead( unsigned char *data, int length);
    int readValue(Channel channel);
    int readValueChannel0();

private:
    unsigned char mode;
    unsigned char bitsPerWord;
    unsigned int speed;
    int spifd;

    int spiOpen(const std::string& devspi);
    int spiClose();

};

#endif
