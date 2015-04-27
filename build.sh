#! /bin/bash
make
echo "===== compilou"
for i in ./*.exe
do
    filename=$(basename "$i")
    filename="${filename%.*}"
    echo "=== testando $filename"
    ./$filename
    echo "=== acabou   $filename"

done
#make clean
