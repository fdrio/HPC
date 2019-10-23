
graphsize=(10 110 210 310 410)

eval gcc ../Dijkstra/dijkstra.c -o dijkstra
eval gcc ../Dijkstra/dijkstra_parallel.c -fopenmp -o dijkstra_parallel
for i in "${graphsize[@]}"
do
	echo "Serial Times: "
	eval  ./../Dijkstra/dijkstra $i 0 ../RandomGraphsDijkstra/randomgraph_$i.csv
done 


echo "--------------------------------------"

for j in "${graphsize[@]}"
do
	echo "Parallel Times: "
	eval  ./../Dijkstra/dijkstra_parallel $j 0 ../RandomGraphsDijkstra/randomgraph_$j.csv


done 


