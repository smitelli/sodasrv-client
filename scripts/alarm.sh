#!/usr/bin/bash

alarming=$(wget -q -O - "http://alala.smitelli.com/soda/?page=alarm")

if [ "$alarming" == "1" ]; then
    play -v 1.5 /root/sodasrv/alarm.wav &
fi
