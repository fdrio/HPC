for ((n=500; n<=100000; n+=500));
do
	eval python3 gengraph.py $n 

done
