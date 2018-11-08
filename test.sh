#!/bin/zsh

GRN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

for filename in /bin/* /sbin/* /usr/lib/* /usr/bin/* /usr/sbin/*; do
    RESULT=$(diff <(nm -p $filename 2>&-) <(./ft_nm $filename 2>&-))
    if [[ $? -ne 0 ]]
    then
	echo "[${RED}ko${NC}] -- $filename"
	echo "$filename" >> nm_fail.txt
	sleep 1
    else
	echo "[${GRN}ok${NC}] -- $filename"
    fi
done

#for filename in ./test/*; do
#    ./ft_nm $filename
#done

for filename in /bin/* /sbin/* /usr/lib/* /usr/bin/* /usr/sbin/*; do
    RESULT=$(diff <(otool -t $filename 2>&-) <(./ft_otool $filename 2>&-))
    if [[ $? -ne 0 ]]
    then
	echo "[${RED}ko${NC}] -- $filename"
	echo "$filename" >> otool_fail.txt
	sleep 1
    else
	echo "[${GRN}ok${NC}] -- $filename"
    fi
done

for filename in ./test/*; do
    ./ft_otool $filename
done
