#!/bin/bash 

sizes=30
count=3

logfile="result_proteins_approx_mut.txt"
text="proteins.200MB"

echo "ukkonen (${count} results per pattern size)" | tee -a $logfile
pattern="a"
increment="a"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e $err -a uk $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done

echo "sellers (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e $err -a sl $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done

echo "wu-manber (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -e $err -a wm $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done

count=32

echo "agrep (${count} results per pattern size)" | tee -a $logfile
pattern="aaaaaa"
increment="a"
err=0
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a agrep -c -$err $pattern $text
    done
    pattern=$pattern$increment
    err=$((err+1))
done
