#!/bin/bash


#for i in $(seq 1 100)
#do
#	name=test_$i.txt
#	./aleatoire > $name
#done	


for file in *.txt *.pdf
do
	encode=$(basename $file .txt).huff
	echo $file
	decode=$(basename $file .txt).res
	./huff_encode $file $encode 1>/dev/null
	./huff_decode $encode > $decode
	if diff $decode $file
	then
		echo 'OK'
		rm $encode $decode
	else 
		echo "KO"
	fi
done
