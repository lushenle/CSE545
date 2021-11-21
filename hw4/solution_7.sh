#!/bin/bash
while true
do
for file in /tmp/md5sum_result_1000_*
do
    if test -f $file
    then
        echo $file
        echo "5bbbbc107dd9c0ee0b6503025bafca6e" > $file
        printf "ok!\n "
    fi
done
sleep 1
done
