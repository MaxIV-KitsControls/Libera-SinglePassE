#!/usr/bin/python
import PyTango
import sys

if (len(sys.argv)<2):
    print "Usage: trigger_reset_test.py device_instance"
    print "        device_instance is an instance of the tango device server in the following format: "
    print "                        domain/family/member "
    print "Usage example: python trigger_reset_test.py a/b/c "
    sys.exit(0)



device = PyTango.DeviceProxy(sys.argv[1])

trigger_read1=device.read_attribute('TriggerCounter').value

device.command_inout('ResetTrigger')

trigger_read2=device.read_attribute('TriggerCounter').value


if (trigger_read2<trigger_read1):
            print "OK"
            print "trigger counter before reset : ",
            print trigger_read1
            print " is smaller then trigger counter after : ",
            print trigger_read2
else:
            print >> sys.stderr, "**ERROR**"
            print "trigger counter before reset : ",
            print trigger_read1
            print " is not smaller then trigger counter after : ",
            print trigger_read2




