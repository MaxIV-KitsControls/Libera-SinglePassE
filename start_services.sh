#!/bin/bash
itech/dummy-application/src/libera-dummy --no-daemon -d - 3 -p 5679 &
itech/platform-application/src/platform-dummy --no-daemon -d - 3 -p 5678 &
