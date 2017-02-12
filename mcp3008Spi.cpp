#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "mcp3008Spi.h"


using namespace std;

/**
 * Open SPI device in read/write mode, sets bits per word and speed
 */
int mcp3008Spi::spiOpen(const std::string& devspi){
    int statusVal = -1;
    spifd = open(devspi.c_str(), O_RDWR);
    if(spifd < 0){
        perror("could not open SPI device");
        exit(1);
    }

    statusVal = ioctl (spifd, SPI_IOC_WR_MODE, &mode);
    if(statusVal < 0){
        perror("Could not set SPIMode (WR)...ioctl fail");
        exit(1);
    }

    statusVal = ioctl (spifd, SPI_IOC_RD_MODE, &mode);
    if(statusVal < 0) {
      perror("Could not set SPIMode (RD)...ioctl fail");
      exit(1);
    }

    statusVal = ioctl (spifd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord);
    if(statusVal < 0) {
      perror("Could not set SPI bitsPerWord (WR)...ioctl fail");
      exit(1);
    }

    statusVal = ioctl (spifd, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord);
    if(statusVal < 0) {
      perror("Could not set SPI bitsPerWord(RD)...ioctl fail");
      exit(1);
    }

    statusVal = ioctl (spifd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if(statusVal < 0) {
      perror("Could not set SPI speed (WR)...ioctl fail");
      exit(1);
    }

    statusVal = ioctl (spifd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if(statusVal < 0) {
      perror("Could not set SPI speed (RD)...ioctl fail");
      exit(1);
    }
    return statusVal;
}

/**
 * Close the SPI device
 */
int mcp3008Spi::spiClose(){
    int statusVal = -1;
    statusVal = close(spifd);
        if(statusVal < 0) {
      perror("Could not close SPI device");
      exit(1);
    }
    return statusVal;
}

/**
 * Write and read data to the SPI device
 * Read data is saved back in given data buffer and replaces written data
 */
int mcp3008Spi::spiWriteRead( unsigned char *data, int length){

  struct spi_ioc_transfer spi[length];
  memset( spi, 0, length*sizeof(spi_ioc_transfer) );
  int i = 0;
  int retVal = -1;

// one spi transfer for each byte

  for (i = 0 ; i < length ; i++){

    spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
    spi[i].rx_buf        = (unsigned long)(data + i) ; // receive into "data"
    spi[i].len           = sizeof(*(data + i)) ;
    spi[i].delay_usecs   = 0 ;
    spi[i].speed_hz      = speed ;
    spi[i].bits_per_word = bitsPerWord ;
    spi[i].cs_change = 0;
  }

 retVal = ioctl (spifd, SPI_IOC_MESSAGE(length), &spi) ;

 if(retVal < 0){
    perror("Problem transmitting spi data..ioctl");
    exit(1);
 }

return retVal;

}

/**
 * Reads value of given channel
 * SPI_MODE_0 (MODE 0) (defined in linux/spi/spidev.h), speed = 1MHz &
 * bitsPerWord=8.
 *
 * i.e. transmit ->  byte1 = 0b00000001 (start bit)
 *                   byte2 = 0b1XXX0000 (SGL/DIF = 1, channel=0-7)
 *                   byte3 = 0b00000000 (Don't care)
 *      receive  ->  byte1 = junk
 *                   byte2 = junk + b8 + b9
 *                   byte3 = b7 - b0
 *
 * after conversion must merge data[1] and data[2] to get final result
 *
 */
int mcp3008Spi::readValue(Channel channel){
	unsigned char data[3] = {0};

	data[0] = 1;  //  first byte transmitted -> start bit
	data[1] = 0b10000000 |( ((channel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, channel = 0-7)
	data[2] = 0; // third byte transmitted....don't care

	spiWriteRead(data, sizeof(data) );

	int a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
	a2dVal |=  (data[2] & 0xff);
	return a2dVal;
}

/**
 * Read  value of channel 0
 */
int mcp3008Spi::readValueChannel0(){
	return readValue(CH0);
}

/**
 * Read value of channel 1
 */
int mcp3008Spi::readValueChannel1(){
	return readValue(CH1);
}

mcp3008Spi::mcp3008Spi(){
    mode = SPI_MODE_0 ;
    bitsPerWord = 8;
    speed = 1000000;
    spifd = -1;

    spiOpen(std::string("/dev/spidev0.0"));

    }

mcp3008Spi::mcp3008Spi(const std::string& devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord){
    mode = spiMode ;
    bitsPerWord = spibitsPerWord;
    speed = spiSpeed;
    spifd = -1;

    spiOpen(devspi);

}

mcp3008Spi::~mcp3008Spi(){
    spiClose();
}
