#ifndef MCP3008SPI_H
#define MCP3008SPI_H

#include <string>
#include <linux/spi/spidev.h>

/**
 * mcp3008Spi class for accessing A/D converter mcp3008 by SPI
 * mode        : SPI_MODE_0.
 * bitsPerWord : 8
 * speed       : 1MHz (SPI clock frequency) (possible 0.5, 1, 2, 4, 8, 16, 32 MHz)
 * spifd       : file descriptor for the SPI device
 */

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
    /**
     * Write and read function to SPI
     */
    int spiWriteRead( unsigned char *data, int length);
    /**
     * Read value from selected channel
     */
    int readValue(Channel channel);
    /**
     * Read value fix from channel 0
     */
    int readValueChannel0();
    /**
     * Read value fix from channel 1
     */
    int readValueChannel1();

private:
    unsigned char mode;
    unsigned char bitsPerWord;
    unsigned int speed;
    int spifd;

    int spiOpen(const std::string& devspi);
    int spiClose();

};

#endif
