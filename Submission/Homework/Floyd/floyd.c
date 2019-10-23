#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h> 
typedef struct{
	int sourceVertex, destVertex;
	int edgeWeight;
}edge;
 
typedef struct{
	int vertices, edges;
	edge* edgeMatrix;
}graph;
 
graph loadGraph(char* fileName, int V, int E){
	FILE* fp = fopen(fileName,"r");
 
	graph G;
	int i;
 
	//fscanf(fp,"%d%d",&G.vertices,&G.edges);
 	G.vertices = V;
	G.edges = E;
	G.edgeMatrix = (edge*)malloc(G.edges*sizeof(edge));
 
	for(i=0;i<G.edges;i++)
		fscanf(fp,"%d,%d,%d",&G.edgeMatrix[i].sourceVertex,&G.edgeMatrix[i].destVertex,&G.edgeMatrix[i].edgeWeight);
 
	fclose(fp);
 
	return G;
}
 
void floydWarshall(graph g){
	int processWeights[g.vertices][g.vertices], processedVertices[g.vertices][g.vertices];
	int i,j,k;
 
	for(i=0;i<g.vertices;i++)
		for(j=0;j<g.vertices;j++){
			processWeights[i][j] = SHRT_MAX;
			processedVertices[i][j] = (i!=j)?j+1:0;
		}
 
	for(i=0;i<g.edges;i++)
		processWeights[g.edgeMatrix[i].sourceVertex-1][g.edgeMatrix[i].destVertex-1] = g.edgeMatrix[i].edgeWeight;
 
	for(i=0;i<g.vertices;i++)
		for(j=0;j<g.vertices;j++)
			for(k=0;k<g.vertices;k++){
				if(processWeights[j][i] + processWeights[i][k] < processWeights[j][k]){
					processWeights[j][k] = processWeights[j][i] + processWeights[i][k];
					processedVertices[j][k] = processedVertices[j][i];
				}
			}
 
	//printf("pair    dist   path");
	for(i=0;i<g.vertices;i++)
		for(j=0;j<g.vertices;j++){
			if(i!=j){
				int u = i+1;
				int v =  j+1;
				//printf("\n%d -> %d %3d %5d",u,v,processWeights[i][j],u);
				do{	
					k = processedVertices[k-1][j];
					//printf("->%d",k);
				}while(k!=j+1);
			}
		}
}
 
int main(int argc,char* argv[]){
		int numV = atoi(argv[1]);
		int numE = atoi(argv[2]);
		clock_t start, delta;
		start = clock();
		floydWarshall(loadGraph(argv[3],numV, numE));
		delta = clock() - start ;
		double time_taken = ((double) delta)/ CLOCKS_PER_SEC;
		printf("Time taken: %f \n", time_taken);

	return 0;
}
