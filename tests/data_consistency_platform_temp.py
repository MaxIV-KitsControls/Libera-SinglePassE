#!/usr/bin/python
import PyTango
import subprocess
import sys

if (len(sys.argv)<3):
    print "Usage: data_consistency_platform_fans.py device_instance attribute_name "
    print "        device_instance is an instance of the tango device server in the following format: "
    print "                        domain/family/member "
    print "        attribute_name is the name of the tango attribute corresponding to a single node, for example: "
    print "                        Fan1Speed corresponds to the mci node 'fans.left_front'"
    print "Usage example: python data_consistency_platform_fans.py a/b/c Fan1Speed"
    sys.exit(0)

device = PyTango.DeviceProxy(sys.argv[2])
libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]

libera_ip='10.0.4.128'

temp1='boards.'+ libera_board + '.sensors.ID_2.value'

nodesDictionary={'Temp1': temp1, 'Temp2': 'boards.icb0.sensors.ID_8.value', 'Temp3': 'boards.evrx2.sensors.ID_6.value'}


if (nodesDictionary.has_key(sys.argv[3])):
    node=nodesDictionary[sys.argv[3]]
    is_node=1
else:
    is_node=0
    
    

li="/opt/libera/bin/libera-ireg"

if(is_node):
    
    li_args = [li,
               node,
               "-h",
               libera_ip,
               '-P']
            
    out=subprocess.Popen(li_args,stdout=subprocess.PIPE)
    node_value, err = out.communicate()
    #read node value and attribute value and check consistency
    value = device.read_attribute(sys.argv[3])
    
    val=node_value.split(":")[1].strip()
        
    if(val==str(value.value)):
        print "OK"
        print "Node value:",
        print val,
        print " AND " ,
        print "Attribute value:",
        print value.value
    else:
        print >> sys.stderr, "**ERROR**"
        print "Node value:",
        print val,
        print " AND " ,
        print "Attribute value:",
        print value.value
