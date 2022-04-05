#!/bin/bash 

words=80
count=3

logfile="result_english_exact_multiple.txt"
text="english.1024MB"
words_source="fivewords.txt"
aux_file="aux.txt"

echo "aho-corasick (${count} results per pattern number)" | tee -a $logfile
sed -n '1,1p' $words_source > $aux_file
aux_count=1
for i in $(seq $words); do
    for j in $(seq $count); do
        /usr/bin/time -f %e -o $logfile -a ./pmt -c -a ac -p $aux_file $text
    done
    aux_count=$((aux_count+1))
    sed -n "1,${aux_count}p" $words_source > $aux_file
done

echo "grep (${count} results per pattern number)" | tee -a $logfile
sed -n '1,1p' $words_source > $aux_file
aux_count=1
for i in $(seq $words); do
    for j in $(seq $count); do
        /usr/bin/time --quiet -f %e -o $logfile -a grep -c -f $aux_file $text
    done
    aux_count=$((aux_count+1))
    sed -n "1,${aux_count}p" $words_source > $aux_file
done
