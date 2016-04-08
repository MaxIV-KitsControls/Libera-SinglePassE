Libera-SinglePassE
==================

Tango DeviceServer of the Libera SinglePass E

Cloning this repository
-----------------------

This repository has a dependency on itech proprietary library 


Building Libera-SinglePassE
-----------------------------

### Prerequisites
- ITech Libera Single Pass E Libraries 2.8
	libliberamci.so.2.8
	libliberaistd.so.2.8
	libliberaisig.so.2.8
	libliberainet.so.2.8
- Tango 8
	libtango.so.8
	liblog4tango.so.5
	libomniORB4.so.1
	libomniDynamic4.so.1
	libomnithread.so.3
	libzmq.so.3
	libCOS4.so.1


### Compilation
To compile
``` shell
cd src
make clean
make
```

### Packaging
To make the debian package, just call the following command from the project directory
``` shell
dpkg-buildpackage -us -uc
```
