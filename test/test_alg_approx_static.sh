#!/bin/bash 

sizes=70
count=3

logfile="result_proteins_approx_static.txt"
text="proteins.200MB"

echo "ukkonen (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e 5 -a uk $pattern $text
    done
    pattern=$pattern$increment
done

echo "sellers (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e 5 -a sl $pattern $text
    done
    pattern=$pattern$increment
done

echo "wu-manber (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e 5 -a wm $pattern $text
    done
    pattern=$pattern$increment
done

count=32

echo "agrep (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a agrep -c -5 $pattern $text
    done
    pattern=$pattern$increment
done
