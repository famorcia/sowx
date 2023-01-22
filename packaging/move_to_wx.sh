#!/bin/sh
list_of_file=`find . -type f | grep "Wx"`

for file in ${list_of_file} 
do
   new_file_name=`echo ${file} | sed "s@Wx@Wx@g"`
   echo ${file}
   echo ${new_file_name}
   mv ${file} ${new_file_name}
done


list_of_file_with_ww=`find . -type f | xargs grep -l "Wx" | grep -v git`
for file in ${list_of_file_with_ww}
do 
   echo "2:" ${file}
   echo ${file} | xargs sed -i "s@Wx@Wx@g"
done
