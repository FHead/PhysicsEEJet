#!/bin/bash

Input=$1
InputBase=`basename $1 .pu14`

# csplit -n 4 -f "SingleEvent_${InputBase}_" $Input '/^end/' {*}
# gawk '/# event/{x="part"++i;}{print>x;}' $Input

mkdir -p SingleEvent_$InputBase

gawk '
    /end/ {
        ++part;
        if (output_file) close(output_file);
        output_file=sprintf("part-%04d.txt", part)
    }
    {print >output_file}
' $Input

for i in part*txt
do
   cat $i | grep -v "event" | grep -v "end" | awk '
      function abs(x){return ((x < 0.0) ? -x : x)}
      {
         if(abs($6)>0)         print $1,$2,$3,1;
         else if(abs($5)==11)  print $1,$2,$3,2;
         else if(abs($5)==13)  print $1,$2,$3,2;
         else if(abs($5)==15)  print $1,$2,$3,2;
         else if(abs($5)==22)  print $1,$2,$3,3;
         else if(abs($5)>=100) print $1,$2,$3,4;
         else if(abs($5)==12)  print $1,$2,$3,5;
         else if(abs($5)==14)  print $1,$2,$3,5;
         else if(abs($5)==16)  print $1,$2,$3,5;
         else                  print $1,$2,$3,6;
      }
      ' > SingleEvent_$InputBase/$i
done

rm part*txt
