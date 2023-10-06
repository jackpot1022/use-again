#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

void set_init(int n) // set_union에서 쓰이는 부모를 체크하는 배열을 초기화시키는 함수
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
    }
}

int set_find(int curr) // curr가 속하는 집합을 반환하는 함수
{
    if (parent[curr] == -1)
    {
        return curr;
    }
    parent[curr] = set_find(parent[curr]);
    if (parent[curr] == -1) //만약 루트를 찾았다면
    {
    	parent[curr] = curr; //루트의 위치를 바로 저장
    }
    return parent[curr];
}

void set_union(int a, int b) // 두 원소가 속한 집합을 합치는 함수
{
    int root_a = set_find(a);
    int root_b = set_find(b);
    if (root_a != root_b)
    {
        parent[root_a] = root_b;
    }
}

typedef struct Edge // 간선을 나타내는 구조체
{ 
int start, end, weight;
} Edge;

typedef struct GraphType { // 그래프를 나타내는 구조체
int edge_num; // 간선의 개수
int vertex_num; // 정점의 개수
Edge edges[2 * MAX_VERTICES];
} GraphType;

void graph_init(GraphType* graph) //그래프 초기화시키는 함수
{
    graph->edge_num = 0;
    printf("정점의 개수를 입력해주세요.\n");
    scanf("%d", &graph->vertex_num); //정점의 개수 입력받는 함수

    for (int i = 0; i < 2 * MAX_VERTICES; i++)
    {
        graph->edges[i].start = 0;
        graph->edges[i].end = 0;
        graph->edges[i].weight = INF;
    }
}

void insert_edge(GraphType* graph, int start, int end, int w) //간선을 추가하는 함수
{
    graph->edges[graph->edge_num].start = start;
    graph->edges[graph->edge_num].end = end;
    graph->edges[graph->edge_num].weight = w;
    graph->edge_num++;
}

int compare(const void* a, const void* b) //정렬기준을 가중치의 오름차순으로 설정하는 함수
{
    Edge *pa = (Edge*)a;
    Edge *pb = (Edge*)b;

    if(pa->weight > pb->weight)
        return 1;
    else if(pa->weight < pb->weight)
        return -1;
    else
        return 0;
}

void kruskal(GraphType *graph)
{
    int edge_accepted = 0; // 현재까지 선택된 간선의 수
    int upar, vpar; // 정점 u와 정점 v의 부모
    Edge shortest; // 가장 짧은 간선
    int i = 0;

    set_init(graph->edge_num); // 초기화
    qsort(graph->edges, graph->edge_num, sizeof(Edge), compare);  //간선 정렬
    while (edge_accepted < graph->vertex_num -1)
    {
        shortest = graph->edges[i];
        upar = set_find(shortest.start);
        vpar = set_find(shortest.end);

        if (upar != vpar)
        {
            printf("간선 (%d,%d) %d 선택\n", shortest.start, shortest.end, shortest.weight);
            edge_accepted++;
            set_union(shortest.start, shortest.end); // 두개의 집합을 합친다.
        }
        i++;
    }
}

int main(void)
{
GraphType *g;
g = (GraphType *)malloc(sizeof(GraphType));
graph_init(g);
insert_edge(g, 0, 1, 29);
insert_edge(g, 1, 2, 16);
insert_edge(g, 2, 3, 12);
insert_edge(g, 3, 4, 22);
insert_edge(g, 4, 5, 27);
insert_edge(g, 5, 0, 10);
insert_edge(g, 6, 1, 15);
insert_edge(g, 6, 3, 18);
insert_edge(g, 6, 4, 25);
kruskal(g);
free(g);
return 0;
}
