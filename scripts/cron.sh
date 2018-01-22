#!/usr/bin/bash

wget -q -O /dev/null --header="X-Soda-Auth: __FILL_ME_IN__" "http://alala.smitelli.com/soda/?page=listener&key=heartbeat&val=1" &
wget -q -O /dev/null --header="X-Soda-Auth: __FILL_ME_IN__" "http://alala.smitelli.com/soda/?page=listener&key=temperature&val=$(./probetimer /dev/ttyS0)" &
wget -q -O /dev/null --header="X-Soda-Auth: __FILL_ME_IN__" "http://alala.smitelli.com/soda/?page=listener&key=quantity&val=$(./probetimer /dev/ttyS1)" &
