#!/bin/bash 

sizes=60
count=3

logfile="result_proteins_approx_static.txt"
text="proteins.100MB"


echo "sellers (${count} results per pattern size)" | tee -a $logfile
pattern="EEEEEE"
increment="E"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e 5 -a sl $pattern $text
    done
    pattern=$pattern$increment
done

echo "wu-manber (${count} results per pattern size)" | tee -a $logfile
pattern="EEEEEE"
increment="E"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e 5 -a wm $pattern $text
    done
    pattern=$pattern$increment
done

sizes=32

echo "agrep (${count} results per pattern size)" | tee -a $logfile
pattern="EEEEEE"
increment="E"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a --quiet agrep -c -5 $pattern $text
    done
    pattern=$pattern$increment
done

sizes=16

echo "ukkonen (${count} results per pattern size)" | tee -a #$logfile
pattern="EEEEEE"
increment="E"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e 5 -a uk $pattern $text
    done
    pattern=$pattern$increment
done
