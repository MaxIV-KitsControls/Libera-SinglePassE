#!/usr/bin/python
import PyTango
import sys
import time

if (len(sys.argv)<4):
    print "Usage: test_signal_size.py device_instance attribute_name buffer_size"
    print "        device_instance is an instance of the tango device server in the following format: "
    print "                        domain/family/member "
    print "        attribute_name is the name of the tango attribute corresponding to a single node, for example: "
    print "                        Fan1Speed corresponds to the mci node 'fans.left_front'"
    print "        buffer_size is the size of signal "
    print "Usage example: python test_signal_size.py a/b/c SumT 20"
    sys.exit(0)



device = PyTango.DeviceProxy(sys.argv[1])

buff = sys.argv[3]

device.write_attribute('BufferSize', int(buff))
time.sleep(3)
buff=device.read_attribute('BufferSize').value

value = device.read_attribute(sys.argv[2]).value

sig_length=len(value)

if (int(buff)==int(sig_length)):
            print "OK"
            print "Buffer size : " ,
            print buff
            print "Signal size : " ,
            print sig_length
else:
            print >> sys.stderr, "**ERROR**"
            print "Buffer size : " ,
            print buff
            print "Buffer size : " ,
            print sig_length

