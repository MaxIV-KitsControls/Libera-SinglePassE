#!/usr/bin/python
import PyTango
import subprocess
import sys
import exceptions

if (len(sys.argv)<3):
    print "Usage: data_consistency_app.py device_instance attribute_name test_option utility_option(is optional) value(is optional)"
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
    print "Usage example: python data_consistency_app.py a/b/c Level -rd"
    sys.exit(0)

def num(s):
    try:
        return int(s)
    except exceptions.ValueError:
        return float(s)

nodesDictionary={'AttenuationLevel': '.attenuation.att_id',
                 'status_adc_overflow': '.interlock.status.adc_overflow', 'status_y': '.interlock.status.y',
                 'status_x': '.interlock.status.x', 'interlock_status': '.interlock.status',
                 'overflow_threshold': '.interlock.limits.overflow.threshold',
                 'limit_max_y': '.interlock.limits.position.max.y',
                 'limit_max_x': '.interlock.limits.position.max.x',
                 'limit_min_y': '.interlock.limits.position.min.y',
                 'limit_min_x': '.interlock.limits.position.min.x',
                 'interlock_enabled': '.interlock.enabled', 'signal_expansion': '.interlock.signal_expansion',
                 'linear_sum_offs': '.calibration.linear.sum.offs','linear_sum_k': '.calibration.linear.sum.k',
                 'linear_q_offs': '.calibration.linear.q.offs','linear_q_offs': '.calibration.linear.q.k',
                 'linear_y_offs': '.calibration.linear.y.offs','linear_y_k': '.calibration.linear.y.k',
                 'linear_x_offs': '.calibration.linear.x.offs','linear_x_k': '.calibration.linear.x.k',
                 'calibration_kd': '.calibration.kd','calibration_kc': '.calibration.kc','calibration_kb': '.calibration.kb','calibration_ka': '.calibration.ka'}

if (nodesDictionary.has_key(sys.argv[2])):
    node=nodesDictionary[sys.argv[2]]
    is_node=1
else:
    is_node=0
    
    

li="/opt/libera/bin/libera-ireg"

device = PyTango.DeviceProxy(sys.argv[1])

libera_ip=device.get_property('LiberaIpAddr')['LiberaIpAddr'][0]
#libera_ip='10.0.4.128'
libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]

if(is_node):
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
    #read node value and attribute value and check consistency
    if (sys.argv[3]=='-rd'):
        value = device.read_attribute(sys.argv[2])
        
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
    elif (sys.argv[3]=='-wr'):
        
        value = 10
        write_option='-tango'

        if (len(sys.argv)>5):
            value=int(sys.argv[5])
        if (len(sys.argv)>4):
            write_option=sys.argv[4]
        if (write_option=='-tango'):
            device.write_attribute(sys.argv[2], value)
        elif (write_option=='-ireg'):           
            li_args = [li,
                       "-h",
                       libera_ip,
                       node+
                       "="+
                       str(value)]
            exe=subprocess.Popen(li_args,stdout=subprocess.PIPE)
            new_value, err = exe.communicate()
    
    
        
    #read node value and attribute value and check for consistency. 
    #then write value through ireg or tango and check for consistency again
    elif (sys.argv[3]=='-rdwr'):
        value = device.read_attribute(sys.argv[2])
        
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

        if (len(sys.argv)>5):
            value=num(sys.argv[5])
        if (len(sys.argv)>4):
            write_option=sys.argv[4]
        if (write_option=='-tango'):
            device.write_attribute(sys.argv[2], value)
        elif (write_option=='-ireg'):
            li_args = [li,
                       "-h",
                       libera_ip,
                       node+
                       "="+
                       str(value)]
            exe=subprocess.Popen(li_args,stdout=subprocess.PIPE)
            new_value, err = exe.communicate()
                        
        value = device.read_attribute(sys.argv[2])
        li_args = [li,
                   node,
                   "-h",
                   libera_ip]
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

