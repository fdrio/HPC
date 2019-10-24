for ((n=500; n<=10000; n+=100));
do
	eval python3 gengraph.py $n 

done
