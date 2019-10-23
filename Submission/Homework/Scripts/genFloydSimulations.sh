
graphsize=(10 110 210 310 410)

eval gcc ../Floyd/floyd.c -o floyd
eval gcc ../Floyd/floyd_parallel.c -fopenmp -o floyd_parallel
for i in "${graphsize[@]}"
do
	echo "Serial Times: "
	eval  ./../Floyd/floyd $i $i ../RandomGraphsFloyd/randomgraphs_"$i"_3.csv
done 


echo "--------------------------------------"

for j in "${graphsize[@]}"
do
	echo "Parallel Times: "
	eval  ./../Floyd/floyd_parallel $((j - 1)) $j ../RandomGraphsFloyd/randomgraphs_"$j"_3.csv


done 


