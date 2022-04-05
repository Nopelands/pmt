#!/bin/bash 

sizes=100
count=3

logfile="result_english_single.txt"
text="english.1024MB"

echo "boyer-moore (${count} results per pattern size)" | tee -a $logfile
pattern="a"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -a bm $pattern $text
    done
    pattern=$pattern$increment
done
echo "knuth-morris-pratt (${count} results per pattern size)" | tee -a $logfile
pattern="a"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -a kmp $pattern $text
    done
    pattern=$pattern$increment
done
echo "aho-corasick (${count} results per pattern size)" | tee -a $logfile
pattern="a"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -a ac $pattern $text
    done
    pattern=$pattern$increment
done
echo "grep (${count} results per pattern size)" | tee -a $logfile
pattern="a"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a --quiet grep -c $pattern $text
    done
    pattern=$pattern$increment
done

sizes=64

echo "shift-or (${count} results per pattern size)" | tee -a $logfile
pattern="a"
increment="a"
for i in $(seq $sizes); do
    for i in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -a so $pattern $text
    done
    pattern=$pattern$increment
done
