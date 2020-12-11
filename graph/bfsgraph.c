#include <stdio.h>
#include <stdlib.h>
#include "bfsgraph.h"

// Initializes graph for breadth-first search
void init_graph(bfsgraph* g, int vertices){
	g->nVertices = vertices;
	int i;
	for(i=1; i <= vertices; i++) {
		g->adj_list[i] = 0;
		g->pred[i] = 0;
		g->dist[i] = INF;
		g->color[i] = WHITE;
	}
}

// Adds new edge (x,y)
void add_edge(bfsgraph* g, int x, int y){
	if( x <= g->nVertices && y <= g->nVertices){
		pbfsedgenode pxy = malloc(sizeof(bfsedgenode));
		pbfsedgenode pyx = malloc(sizeof(bfsedgenode));
		
		pxy->nodenum = y;
		pxy->next = g->adj_list[x];
		g->adj_list[x] = pxy;
		
		pyx->nodenum = x;
		pyx->next = g->adj_list[y];
		g->adj_list[y] = pyx;		
	} 
}


/*
BFS(G,s)
1.   for each u in V
2.      color[u] = WHITE
3.      d[u] = INF
4.      p[u] = NIL
5.   d[s] = 0
6.   color[s] = GRAY
7.   Q = EMPTY
8.   ENQUEUE(Q,s)
9.   while Q != EMPTY
10.    u = DEQUEUE(Q)
11.	   for each v in Adj[u]
12.        if color[v] == WHITE
13.           color[v] = GRAY
14.           d[v] = d[u]+1
15.           p[v] = u
16.	          ENQUEUE(Q,v)   
17.    color[u] = BLACK
18.  return
*/


// Actual breadth-first search from node s
void bfsearch(bfsgraph* g, int s){
	int queue[MAXVERTS];
	int head = 0;
	int tail = 0;
	int i=0;
	
	for(i=1; i <= g->nVertices; i++) {
		g->pred[i] = 0;
		g->dist[i] = INF;
		g->color[i] = WHITE; 
	}
	
	g->dist[s] = 0;
	g->color[s] = GREY;
	queue[tail] = s;
	tail++;
	g->color2[s] = RED;
	
	while( head != tail) {
		int u = queue[head];
		head++;

		pbfsedgenode pedge = g->adj_list[u];
		while(pedge != 0){
			int v = pedge->nodenum;
			if(g->color[v] == WHITE) {
				if (g->color2[u] == BLUE) {
					g->color2[v] = RED;
				}
				else if (g->color2[u] == RED) {
					g->color2[v] = BLUE;
				}
				g->color[v] = GREY;
				g->dist[v] = g->dist[u] +1;
				g->pred[v] = u;
				queue[tail] = v;
				tail++;
			}
			pedge = pedge->next;
		}
		
		// DEBUG INFO:
		printf("%d processed: d[%d] = %d, color2[%d] = %d\n",u,u,g->dist[u],u,g->color2[u]);
		
		g->color[u] = BLACK;
	}
}

void check_bipartite(bfsgraph* g, int graphsize) {
	int u = 1, error = 0;
	for (int i = 0; i < graphsize; ++i)
	{
		pbfsedgenode pedge = g->adj_list[u];
		while(pedge != 0){
			int v = pedge->nodenum;
			if (g->color2[u] == g->color2[v])
			{
				printf("This is not a bipartite graph!\n");
				error = 1;
				break;
			}
			pedge = pedge->next;
		}
		if (error)
		{
			break;
		}
		++u;
	}
	if (!error)
	{
		printf("This is a bipartite graph!\n");
	}
	
}

// Free allocated memory
void delete_graph(bfsgraph* g, int vertices){
	int i;
	for(i=1; i <= vertices; i++) {
		pbfsedgenode pedge = g->adj_list[i];
		pbfsedgenode pnext = 0;
		
		while(pedge != 0) {
			pnext = pedge->next;
			free(pedge);
			pedge = pnext;
		} 
	}
}
