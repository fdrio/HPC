#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <omp.h>
#define INFINITY 99999
//#define MAX 1000
 
void dijkstra(double *G,int n,int startnode);
 
int main(int argc, char * argv[])
{
	FILE *fptr;

	int i,j,n,u;
	n = atoi(argv[1]);
//	u = atoi(argv[2]);

    double *G;

	G = (double*) malloc(n*n*sizeof(double));
    fptr = fopen(argv[2],"r");
	if (fptr == NULL) {
		printf("can't open file");
	 }
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            fscanf(fptr,"%lf,",(G+i*n+j));
		}
	fclose(fptr);
    double start, delta;
	start = omp_get_wtime();
	#pragma omp parallel for
	for(u=0; u<n; u++)
    	dijkstra(G,n,u);
	delta = omp_get_wtime() - start;
	double time_taken =  delta;
	printf("Time taken: %lf \n", time_taken);
    free(G); 
    return 0;
}
 
void dijkstra(double *G,int n,int startnode)
{
 
    int *cost;
	int * distance;
	int * pred;
    int * visited;
    int count,mindistance,nextnode,i,j;
    //Start allocation  of memory 
	
	cost = (int *) malloc(n*n*sizeof(int));
	distance = (int *) malloc(n*sizeof(int));
	pred = (int *) malloc(n*sizeof(int));
	visited =  (int *) malloc(n*sizeof(int));
		


    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
		#pragma omp parallel for schedule(runtime) private(j)
        for(j=0;j<n;j++)
            if(*(G+i*n +j)==0)
                *(cost + i*n +j) =INFINITY;
            else
                *(cost+i*n+j) = *(G +i*n +j);
    
    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        *(distance+i)=*(cost + startnode*n+i);
        *(pred+i)=startnode;
        *(visited+i)=0;
    }
    
    *(distance+startnode)=0;
    *(visited+startnode)=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITY;
        
        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(*(distance+i)<mindistance&&!*(visited+i))
            {
                mindistance=*(distance+i);
                nextnode=i;
            }
            
            //check if a better path exists through nextnode            
            *(visited+nextnode)=1;
            for(i=0;i<n;i++)
                if(!*(visited+i))
                    if(mindistance+*(cost+nextnode*n+i)<*(distance+i))
                    {
                        *(distance+i)=mindistance+*(cost+ n*nextnode+i);
                        *(pred+i)=nextnode;
                    }
        count++;
    }
 
    //print the path and distance of each node
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
            //printf("\nDistance of node%d=%d",i,*(distance+i));
           // printf("\nPath=%d",i);
            
            j=i;
            do
            {
                j=*(pred+j);
              // printf("<-%d",j);
            }while(j!=startnode);
      }



	free(cost);
	free(pred);
	free(visited);
	free(distance);
}
