#!/bin/bash

DATETIME=$(date +'%d.%m.%Y;%H:%M:%S')
FILENAME="wasserstand_$DATE.csv"

#print header if file not existing
if [ ! -f $FILENAME ]
then
    echo "Date;Time;Pegelstand" > $FILENAME
fi

PEGELSTAND_CM=$( echo mpc3003.bin)
#write pegel to csv file
echo "$DATETIME;$PEGELSTAND_CM" >> $FILENAME