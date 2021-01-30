# spi
sudo adduser pi spi

$ cd /etc/udev/rules.d/
$ sudo nano local.rules
ACTION=="add", KERNEL=="spidev0.0", MODE="0666"

# get Ubidots Python lib
$ sudo apt-get install python-setuptools
$ sudo easy_install pip
$ sudo pip install ubidots==1.6.6
