#!/bin/bash 

sizes=30
count=3

logfile="result_proteins_approx_mut.txt"
text="proteins.100MB"


echo "sellers (${count} results per pattern size)" | tee -a $logfile
pattern="E"
increment="E"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e $err -a sl $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done

echo "wu-manber (${count} results per pattern size)" | tee -a $logfile
pattern="E"
increment="E"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e $err -a wm $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done


sizes=16

echo "ukkonen (${count} results per pattern size)" | tee -a $logfile
pattern="E"
increment="E"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e $err -a uk $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done
