#!/bin/bash

DATE=$(date +'%Y_%m_%d')
DATETIME=$(date +'%d.%m.%Y;%H:%M:%S')
FILENAME="waterlevel_$DATE.csv"

#print header if file not existing
if [ ! -f $FILENAME ]
then
    echo "Date;Time;Level" > $FILENAME
fi

#call SPI bin and store return code
LEVEL_CM=$(echo $(./OutBinStub))
#write level to csv file
echo "$DATETIME;$LEVEL_CM" >> $FILENAME

#send level value to ubidots skript
./sendtoubidots.py $LEVEL_CM
