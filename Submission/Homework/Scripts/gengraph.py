import networkx as nx
import sys
import pandas as pd
seed = 0
num_nodes = int(sys.argv[1])
print("Number of nodes: ",num_nodes)

rgraph= nx.erdos_renyi_graph(num_nodes, p=0.75,seed=seed, directed=True)
df_graph = nx.convert_matrix.to_pandas_adjacency(rgraph)
filename = "randomgraph_"+str(num_nodes)+".csv"
print(filename)
df_graph.to_csv(filename, header=False, index=False)



