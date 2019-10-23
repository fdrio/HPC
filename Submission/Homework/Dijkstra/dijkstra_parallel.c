#include<stdio.h>
#include <omp.h>
#include <time.h>

#define INFINITY 99999
#define MAX 1000
 
void dijkstra(float G[MAX][MAX],int n,int startnode);
 
int main(int argc, char * argv[])
{
	FILE *fptr;

    float G[MAX][MAX];
	int i,j,n,u;
	n = atoi(argv[1]);
	u = atoi(argv[2]);
    fptr = fopen(argv[3],"r");
	if (fptr == NULL) {
		printf("can't open file");
	 }
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            fscanf(fptr,"%f,",&G[i][j]);
		}
	fclose(fptr);
	clock_t start, delta;
	start = clock();	
    dijkstra(G,n,u);
    delta = clock() - start;
	double time_taken = ((double) delta)/ CLOCKS_PER_SEC;
	printf("Time taken: %f \n", time_taken);
    return 0;
}
 
void dijkstra(float G[MAX][MAX],int n,int startnode)
{
 
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
    
    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITY;
        
        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
            
            //check if a better path exists through nextnode 
            visited[nextnode]=1;
            
			#pragma omp parallel for schedule(runtime) private(i)           
			for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }
 
    //print the path and distance of each node
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
            //printf("\nDistance of node%d=%d",i,distance[i]);
           // printf("\nPath=%d",i);
            
            j=i;
            do
            {
                j=pred[j];
               // printf("<-%d",j);
            }while(j!=startnode);
      }
}
