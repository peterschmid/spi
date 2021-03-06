#!/usr/bin/python
import sys, time
from ubidots import ApiClient

# This skript sends the given commandline value to the Ubidots IoT cloud service

# read token and var number from file
def readTokenAndVar():
  f=open("ubidots.txt", "r")
  content = f.readlines()
  content = [x.strip('\n') for x in content]
  return content[0], content[1]

# read first command line parameter
sys.argv[1:]
if len(sys.argv) != 2:
    sys.exit('Usage: %s [value to send]' % sys.argv[0])

token1, var1 = readTokenAndVar()
api = ApiClient(token=token1)
my_variable = api.get_variable(var1)
new_value = my_variable.save_value({'value': int(sys.argv[1]), 'timestamp': int(round(time.time() * 1000))})
