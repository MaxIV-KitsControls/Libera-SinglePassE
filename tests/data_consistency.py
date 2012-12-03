#!/usr/bin/python
import PyTango
import subprocess
import sys

if (len(sys.argv)<5):
    print "Usage: data_consistency.py application_option device_instance attribute_name test_option utility_option(is optional) value(is optional)"
    print "        application_options are: "
    print "                        -a to test nodes on the spe or ebpm application"
    print "                        -p to test nodes on the platform application"
    print "        device_instance is an instance of the tango device server in the following format: "
    print "                        domain/family/member "
    print "        attribute_name is the name of the tango attribute corresponding to a single node, for example: "
    print "                        Fan1Speed corresponds to the mci node 'fans.left_front'"
    print "        test_options are: "
    print "                        -rd to test read only nodes"
    print "                        -wr to test write only nodes"
    print "                        -rd to test read and write nodes"
    print "        in case of testing write or read and write nodes, utility_options are: "
    print "                        -ireg write values through ireg"
    print "                        -tango write values through tango (set by default)"
    print "        in case of testing write or read and write nodes, the value can be set, the default is 10: "
    print "Usage example: python data_consistency.py -p a/b/c Fan1Speed -rd"
    sys.exit(0)


nodesDictionary={'Level': '.attenuation.att_id', 'Fan1Speed': 'fans.left', 'Fan2Speed': 'fans.right', 'Temp1': 'boards.icb0.sensors.ID_0.value', 'Temp2': 'boards.icb0.sensors.ID_1.value', 'Temp3': 'boards.icb0.sensors.ID_2.value'}

if (nodesDictionary.has_key(sys.argv[3])):
    node=nodesDictionary[sys.argv[3]]
    is_node=1
else:
    is_node=0
    
    

li="/opt/libera/bin/libera-ireg"

device = PyTango.DeviceProxy(sys.argv[2])

#libera_ip=device.get_property('LiberaIpAddr')['LiberaIpAddr'][0]
libera_ip='10.0.4.174'
libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]

if(is_node):
    if (sys.argv[1]=='-a'):
        boards="boards."
        boards+=libera_board
        boards+=node
        node=boards
        li_args = [li,
                   node,
                   "-h",
                   libera_ip]
                
        out=subprocess.Popen(li_args,stdout=subprocess.PIPE)
        node_value, err = out.communicate()
        
    elif (sys.argv[1]=='-p'):
        if "Fan" in sys.argv[3]:
            
            nodefront=node+"_front"
            noderear=node+"_rear"
            nodemiddle=node+"_middle"
            
            li_args_front = [li,
               nodefront,
               "-h",
               libera_ip,
               "-P"]  
            li_args_rear = [li,
               noderear,
               "-h",
               libera_ip,
               "-P"] 
            li_args_middle = [li,
               nodemiddle,
               "-h",
               libera_ip,
               "-P"] 
            
            out=subprocess.Popen(li_args_front,stdout=subprocess.PIPE)
            node_value_front, err = out.communicate()            
            node_value_front= node_value_front.split(":")[1].strip()
            node_value_front=int(node_value_front)
            
            out=subprocess.Popen(li_args_rear,stdout=subprocess.PIPE)
            node_value_rear, err = out.communicate()
            node_value_rear= node_value_rear.split(":")[1].strip()
            node_value_rear=int(node_value_rear)

            
            out=subprocess.Popen(li_args_middle,stdout=subprocess.PIPE)
            node_value_middle, err = out.communicate()
            node_value_middle= node_value_middle.split(":")[1].strip()            
            node_value_middle=int(node_value_middle)
           
            node_value=(node_value_front+node_value_rear+node_value_middle)/3
            
            node_value="node: "+str(node_value)

        else :              
            li_args = [li,
               node,
               "-h",
               libera_ip,
               "-P"]     
        
            out=subprocess.Popen(li_args,stdout=subprocess.PIPE)
            node_value, err = out.communicate()
    
    #print (node_value)
    
    #read node value and attribute value and check consistency
    if (sys.argv[4]=='-rd'):
        value = device.read_attribute(sys.argv[3])
        
        val=node_value.split(":")[1].strip()
        if "gt" in val:
            val=val.split("_")[1].strip()
            
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
    
    #write value through ireg or tango
    elif (sys.argv[4]=='-wr'):
        
        value = 10
        write_option='-tango'

        if (len(sys.argv)>6):
            value=sys.argv[6]
        if (len(sys.argv)>5):
            write_option=sys.argv[5]
        if (write_option=='-tango'):
            device.write_attribute(sys.argv[3], value)
        elif (write_option=='-ireg'):
            if (sys.argv[1]=='-a'):
                li_args = [li,
                           "-h",
                           libera_ip,
                           node+
                           "="+
                           str(value)]
            elif (sys.argv[1]=='-p'):
                li_args = [li,
                           "-P",
                           "-h",
                           libera_ip,
                           node+
                           "="+
                           str(value)]    
                
            exe=subprocess.Popen(li_args,stdout=subprocess.PIPE)
            new_value, err = exe.communicate()
    
    
        
    #read node value and attribute value and check for consistency. 
    #then write value through ireg or tango and check for consistency again
    elif (sys.argv[4]=='-rdwr'):
        value = device.read_attribute(sys.argv[3])
        
        val=node_value.split(":")[1].strip()
        if "gt" in val:
            val=val.split("_")[1].strip()
            
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
                    
        value = 10
        write_option='-tango'

        if (len(sys.argv)>6):
            value=sys.argv[6]
        if (len(sys.argv)>5):
            write_option=sys.argv[5]
        if (write_option=='-tango'):
            device.write_attribute(sys.argv[3], value)
        elif (write_option=='-ireg'):
            if (sys.argv[1]=='-a'):
                li_args = [li,
                           "-h",
                           libera_ip,
                           node+
                           "="+
                           str(value)]
            elif (sys.argv[1]=='-p'):
                li_args = [li,
                           "-P",
                           "-h",
                           libera_ip,
                           node+
                           "="+
                           str(value)]    
                
            exe=subprocess.Popen(li_args,stdout=subprocess.PIPE)
            new_value, err = exe.communicate()
                        
        value = device.read_attribute(sys.argv[3])
        if (sys.argv[1]=='-a'):
            li_args = [li,
                       node,
                       "-h",
                       libera_ip]
        elif (sys.argv[1]=='-p'):
            li_args = [li,
                       node,
                       "-h",
                       libera_ip,
                       "-P"]    
                
        out=subprocess.Popen(li_args,stdout=subprocess.PIPE)
        node_value, err = out.communicate()
    
        val=node_value.split(":")[1].strip()
        if "gt" in val:
            val=val.split("_")[1].strip()
    
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
