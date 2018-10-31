#!/bin/bash

for filename in /bin/* /sbin/* /usr/lib/* /usr/bin/*; do
    echo -- $filename
    RESULT=$(diff <(nm -p $filename) <(./ft_nm $filename))
    if [[ $? -ne 0 ]]
    then
 #   nvim -d <(nm -p $filename) <(./ft_nm $filename)
    echo "$filename" >> fail.txt
    fi
#    read 
done
