#!/bin/sh
set -e

if [ "x$1" != "x" ] && [ "x$2" != "x" ]; then
    sed "s/TANGO_HOST_PLACEHOLDER/$1/g" /usr/local/bin/LiberaSinglePass/LiberaSinglePass.sh > /etc/init.d/LiberaSinglePass
    sed -i "s/TANGO_INSTANCE_PLACEHOLDER/$2/g" /etc/init.d/LiberaSinglePass
else
    echo "Run the following script to configure the startup script:"
    echo "    sudo /usr/local/bin/LiberaSinglePass/configure.sh TANGOHOST TANGOINSTANCE"
    echo "e.g.:"
    echo "    sudo /usr/local/bin/LiberaSinglePass/configure.sh 10.0.0.1:10000 1"
    echo "Then start the service with:"
    echo "    service \"LiberaSinglePass\" start"
fi
