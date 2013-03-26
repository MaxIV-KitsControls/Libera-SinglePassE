#!/usr/bin/python
import PyTango
from symbol import try_stmt
import unittest
import time
import exceptions

# XXX Impose to run the test on the Libera platform
import subprocess

class LiberaTestCase(unittest.TestCase):

    TANGO_DEVICES = ["test/itech/libera-spe4", "test/itech/libera-spe5","test/itech/libera-spe6", "test/itech/libera-spe7"]

    ATTRIBUTES = {'AttenuationLevel': '.attenuation.att_id',
                     'status_adc_overflow': '.interlock.status.adc_overflow',
                     'status_y': '.interlock.status.y',
                     'status_x': '.interlock.status.x',
                     'interlock_status': '.interlock.status',
                     'overflow_threshold': '.interlock.limits.overflow.threshold',
                     'limit_max_y': '.interlock.limits.position.max.y',
                     'limit_max_x': '.interlock.limits.position.max.x',
                     'limit_min_y': '.interlock.limits.position.min.y',
                     'limit_min_x': '.interlock.limits.position.min.x',
                     'interlock_enabled': '.interlock.enabled',
                     'signal_expansion': '.interlock.signal_expansion',
                     'linear_sum_offs': '.calibration.linear.sum.offs',
                     'linear_sum_k': '.calibration.linear.sum.k',
                     'linear_q_offs': '.calibration.linear.q.offs',
                     'linear_q_offs': '.calibration.linear.q.k',
                     'linear_y_offs': '.calibration.linear.y.offs',
                     'linear_y_k': '.calibration.linear.y.k',
                     'linear_x_offs': '.calibration.linear.x.offs',
                     'linear_x_k': '.calibration.linear.x.k',
                     'calibration_kd': '.calibration.kd',
                     'calibration_kc': '.calibration.kc',
                     'calibration_kb': '.calibration.kb',
                     'calibration_ka': '.calibration.ka',
                     'Fan1Speed': 'fans.left',
                     'Fan2Speed': 'fans.right'
                     }

    def setUp(self):
        self._tests = ["testTriggerReset"]
        self.li = "/opt/libera/bin/libera-ireg"
        self.devices = []
        for device in LiberaTestCase.TANGO_DEVICES :
            self.devices += [PyTango.DeviceProxy(device)]


    def testTriggerReset(self):

        for device in self.devices :
            "when :"
            trigger_read1=device.read_attribute('TriggerCounter').value
            device.command_inout('ResetTrigger')
            trigger_read2=device.read_attribute('TriggerCounter').value

            "then :"
            self.assertTrue(trigger_read2<trigger_read1, "**ERROR** trigger counter before reset : %s  is not smaller then trigger counter after : %s" % (trigger_read1, trigger_read2) )


    def testBufferSize(self):
        sizes = [10, 13, 100, 256, 8192]

        for device in self.devices :
            for expected in sizes :
                "when:"
                device.BufferSize = expected
                #XXX We should expect to exit the write request with the value taken account in the low level
                time.sleep(1)
                actual = device.BufferSize

                "then:"
                self.assertEquals(expected, actual, "BufferSize is not set correctly : %s (expected : %s)" % (actual, expected))


    def testReadWriteBooleanAttribute(self):
        # Absolute random values
        values = [True, False ]
        attributes = [
                'interlock_enabled',
                ]
        for device in self.devices :
            for attribute in attributes :
                for expected in values :
                    self._write_read_test(device, attribute, expected)

    def testReadWriteUnsignedIntegerAttribute(self):
        # Absolute random values
        values = [10, 25, 0, 38, 10000]
        attributes = [
                'overflow_threshold',
                ]
        for device in self.devices :
            for attribute in attributes :
                for expected in values :
                    self._write_read_test(device, attribute, expected)

    def testLinearXOffsAttribute(self):
        for device in self.devices :
            self._write_read_test(device, 'linear_x_offs', -10.0)

    def testCalibrationKdAttribute(self):
        for device in self.devices :
            self._write_read_test(device, 'calibration_kd', -10.0)

    def testReadWriteDoubleAttribute(self):
        # Absolute random valuess
        values = [-10.0, -25.45, 0.0, 38.56, 10000.0]
        # XXX Bad practice to test several attribute in one unit test
        # TODO Check if unittest accept the parametrized test
        attributes = [
                'limit_max_y',
                'limit_max_x',
                'limit_min_y',
                'limit_min_x',
                'signal_expansion',
                'linear_sum_offs',
                'linear_sum_k',
                'linear_q_offs',
                'linear_q_k',
                'linear_y_offs',
                'linear_y_k',
                #Check testLinearXOffsAttribute 'linear_x_offs',
                'linear_x_k',
                #'calibration_kd',
                'calibration_kc',
                'calibration_kb',
                'calibration_ka']

        for device in self.devices :
            for attribute in attributes :
                for expected in values :
                    self._write_read_test(device, attribute, expected)


    def testWrongBufferSize(self):
        sizes = [1, 8193, 1000000]
        attribute = "BufferSize"
        for device in self.devices :
            for wrong in sizes :
                "when:"
                self.assertRaises(PyTango.DevFailed, lambda : device.write_attribute(attribute, wrong) )


    def testSignalSize(self):

        signals = ["A", "B", "C", "D"]
        sizes = [10, 55, 100, 5400, 7300, 8192]

        for device in self.devices :
            for expected in sizes :
                "when:"
                device.BufferSize = expected
                #XXX We should expect to exit the write request with the value taken account in the low level
                time.sleep(1)
                actual = device.BufferSize

                "then:"
                self.assertEquals(expected, actual, "BufferSize is not set correctly : %s (expected : %s)" % (actual, expected))

                "then:"
                for signal in signals :
                    value = device.read_attribute(signal).value
                    actual = len(value)
                    self.assertEquals(expected, actual, "The signal %s has not the expected lenght : %s (expected %s)" % (signal, actual, expected))

    def testPlatformTemperature(self):

        for device in self.devices :
            libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]
            libera_ip=device.get_property('LiberaIpAddr')['LiberaIpAddr'][0]
            attributes = (
                ("Temp1", 'boards.'+ libera_board + '.sensors.ID_2.value'),
                ("Temp2", 'boards.icb0.sensors.ID_8.value'),
                ("Temp3", 'boards.evrx2.sensors.ID_6.value'))
                
            for attribute in attributes:
                li_args = [self.li, attribute[1], "-h", libera_ip, '-P']

                out=subprocess.Popen(li_args,stdout=subprocess.PIPE)
                node_value, err = out.communicate()
                #XXX This test has a part of random : the temperature is not expected to keep the same between the request with the low level library and the device !!!
                expected = float(node_value.split(":")[1].strip())
                #read node value and attribute value and check consistency
                actual = device.read_attribute(attribute[0]).value

                ratio = actual/expected
                self.assertTrue( (ratio<1.1 and ratio>.9), "The temperature %s is not the expected ratio: %s (expected %s)" % (attribute[0], actual, expected))


    def testPlatformFanSpeed(self):

        for device in self.devices :
            libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]
            libera_ip=device.get_property('LiberaIpAddr')['LiberaIpAddr'][0]
            attributes = (
                ("Fan1Speed", LiberaTestCase.ATTRIBUTES["Fan1Speed"]),
                ("Fan2Speed", LiberaTestCase.ATTRIBUTES["Fan2Speed"]))

            for attribute in attributes:
                expected = min( float(self.read_ireg_p(libera_ip, attribute[1]+"_rear")),
                                float(self.read_ireg_p(libera_ip, attribute[1]+"_front")),
                                float(self.read_ireg_p(libera_ip, attribute[1]+"_middle")) )

                #XXX This test has a part of random : the fan speed is not expected to keep the same between the request with the low level library and the device !!!
                #read node value and attribute value and check consistency
                actual = device.read_attribute(attribute[0]).value

                ratio = actual/expected
                self.assertTrue( (ratio<1.1 and ratio>.9), "The temperature %s is not the expected ratio: %s (expected %s)" % (attribute[0], actual, expected))


    def test_read_attenuation_level(self):
        attenuations = [0, 1, 10 ,20 ,31]
        attribute = "AttenuationLevel"

        for device in self.devices :
            for expected in attenuations:
                libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]
                libera_ip=device.get_property('LiberaIpAddr')['LiberaIpAddr'][0]
                node="boards." + libera_board + LiberaTestCase.ATTRIBUTES[attribute]

                #read node value and attribute value and check consistency
                self.write_ireg(libera_ip, node, "gt_%s" % expected)
                #XXX We should expect to exit the write request with the value taken account in the low level
                time.sleep(1)
                actual = device.read_attribute(attribute).value

                self.assertEquals( expected, actual, "The attribute %s is not at the expected value: %s (expected %s)" % (attribute, actual, expected))


    def test_write_attenuation_level(self):
        attenuations = [0,1,10,20,31]
        attribute = "AttenuationLevel"

        for device in self.devices :
            for expected in attenuations:
                libera_board=device.get_property('LiberaBoard')['LiberaBoard'][0]
                libera_ip=device.get_property('LiberaIpAddr')['LiberaIpAddr'][0]
                node="boards." + libera_board + LiberaTestCase.ATTRIBUTES[attribute]

                #read node value and attribute value and check consistency
                device.write_attribute(attribute, expected)
                actual = self.read_ireg(libera_ip, node)

                self.assertEquals( "%s" % expected, actual, "Writing on the attribute %s failed : actual=%s (expected %s)" % (attribute, actual, expected))


    def test_write_wrong_attenuation_level(self):
        attenuations = [-10,32 ,100]
        attribute = "AttenuationLevel"

        for device in self.devices :
            for wrong in attenuations:
                self.assertRaises(PyTango.DevFailed, lambda : device.write_attribute(attribute, wrong))


#TEST UTILITIES
    def _write_read_test(self, device, attribute, expected ):
            "when:"
            print "%s %s %s" % (device.name(), attribute, expected)
            #setattr(device, attribute, expected)
            device.write_attribute(attribute, expected)
            #XXX We should expect to exit the write request with the value taken account in the low level
            #time.sleep(1)
            actual = getattr(device, attribute)
            #actual = device.read_attribute(attribute)

            "then:"
            self.assertEquals(expected, actual, "%s is not set correctly : %s (expected : %s)" % (attribute, actual, expected))

#UTILITIES
    def read_ireg(self, libera_ip, node):
        return self.ireg(libera_ip, node, '')

    def read_ireg_p(self, libera_ip, node):
        return self.ireg(libera_ip, node, '-P')

    def write_ireg(self, libera_ip, node, value):
        return self.ireg(libera_ip, "%s=%s" % (node,value), '' )

    def write_ireg_p(self, libera_ip, node, value):
        return self.ireg(libera_ip, "%s=%s" % (node,value), '-P' )

    def ireg(self, libera_ip, cmd, opts):
        result = ""

        li_args = [self.li, cmd, "-h", libera_ip, opts]
        #print "cmd %s" % (li_args)
        out = subprocess.Popen(li_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        node_value, err = out.communicate()


        if ( len(err) == 0 ):
            values = node_value.split(":")
            if( len(values) >= 2  ) :
                result = values[1].strip()
                #??? WHICH CASE ?
                if "gt" in result:
                    result=result.split("_")[1].strip()
        else:
            print "node_value %s, err %s" % (node_value, err)
        

        return result

    def num(s):
        try:
            return int(s)
        except exceptions.ValueError:
            return float(s)


if __name__ == '__main__':
    suiteFew = unittest.TestSuite()
    suiteFew.addTest(LiberaTestCase("testReadWriteDoubleAttribute"))
    unittest.TextTestRunner(verbosity=2).run(suiteFew)
    #unittest.TextTestRunner(verbosity=2).run(unittest.makeSuite(LiberaTestCase))
