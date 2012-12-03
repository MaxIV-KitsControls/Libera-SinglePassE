#!/usr/bin/python
import PyTango
import sys
import time

if (len(sys.argv)<3):
    print "Usage: buffer_size_test.py device_instance buffer_size"
    print "        device_instance is an instance of the tango device server in the following format: "
    print "                        domain/family/member "
    print "        buffer_size is the size of signal "
    print "Usage example: python buffer_size_test.py a/b/c 20"
    sys.exit(0)



device = PyTango.DeviceProxy(sys.argv[1])

buff_write = sys.argv[2]

device.write_attribute('BufferSize', int(buff_write))
time.sleep(1)
buff_read=device.read_attribute('BufferSize').value

if (int(buff_write)==int(buff_read)):
            print "OK"
            print "Buffer size set is : " ,
            print buff_write
            print "Buffer size red is : " ,
            print buff_read
else:
            print >> sys.stderr, "**ERROR**"
            print "Buffer size set is : " ,
            print buff_write
            print "Buffer size red is : " ,
            print buff_read




