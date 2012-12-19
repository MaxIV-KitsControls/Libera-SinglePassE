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

libera_ip='10.0.4.128'

nodesDictionary={'Fan1Speed': '.fans.left',
                 'Fan2Speed': '.fans.right'}

if (nodesDictionary.has_key(sys.argv[3])):
    node=nodesDictionary[sys.argv[3]]
    is_node=1
else:
    is_node=0
    
    

li="/opt/libera/bin/libera-ireg"

if(is_node):
    
    node_rear=node + '.rear'
    node_front=node + '.front'
    node_middle=node + '.middle'
    
    
    li_args_rear = [li,
               node_rear,
               "-h",
               libera_ip,
               '-P']
            
    out_rear=subprocess.Popen(li_args_rear,stdout=subprocess.PIPE)
    node_rear_value, err = out_rear.communicate() 
    val_rear=node_rear_value.split(":")[1].strip()
    
    li_args_front = [li,
               node_front,
               "-h",
               libera_ip,
               '-P']
            
    out_front=subprocess.Popen(li_args_front,stdout=subprocess.PIPE)
    node_front_value, err = out_front.communicate()   
    val_front=node_front_value.split(":")[1].strip()
    
    li_args_middle = [li,
               node_middle,
               "-h",
               libera_ip,
               '-P']
            
    out_middle=subprocess.Popen(li_args_middle,stdout=subprocess.PIPE)
    node_middle_value, err = out_middle.communicate()
    val_middle=node_middle_value.split(":")[1].strip()
    
    
    val=min([val_front,val_rear,val_middle])
        
    value = device.read_attribute(sys.argv[3])

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
