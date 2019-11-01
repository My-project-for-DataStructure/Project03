#define _CRT_SECURE_NO_WARNINGS
#define Max_vertex 12
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodestr *nodePointer;
typedef struct nodestr {
	int vernum;
	float cost;
	nodePointer link;
} ty_node;

nodePointer vertex[Max_vertex];
double COST[Max_vertex][Max_vertex];

void Read_and_make_graph();
void addlink(int vernum, int num, float value);
nodePointer newnode(int num, float value);
void chspace(char line[]);

void shortest_path(int start, int destination);

double distance[Max_vertex];
int pred[Max_vertex];
int set_S[Max_vertex];

int main()
{
	int v, u;
	Read_and_make_graph();
	printf("최소경로를 찾을 두 정점을 입력하시오> ");
	scanf("%d %d", &v, &u);
	shortest_path(v, u);

	return 0;
}

void Read_and_make_graph()
{
	int vertex = 0;
	float cost = 0.0;
	char line[80], *ptr;
	FILE *fp;
	int i, u;
	int v = 0;
	for (int a = 0; a < Max_vertex; a++){
		for (int b = 0; b < Max_vertex; b++)
			COST[a][b] = 12345;
	}

	fp = fopen("graphdata.txt", "r");

	fscanf(fp, "%d", &vertex);
	fgets(line, sizeof(line), fp);
	for (i = 0; i < vertex; i++) {
		fscanf(fp, "%d", &u);
		fgets(line, sizeof(line), fp);
		chspace(line);//스페이스바 확인
		ptr = line;
		while (*ptr) {
			v = strtol(ptr, &ptr, 10);//문자를 숫자로
			if (*ptr == 0) break;
			cost = strtod(ptr, &ptr);//문자열을 실수로
			if (cost == 0.0f) break;
			addlink(u, v, cost);
			COST[u][v] = cost;
		}
	}
	fclose(fp);

}

void chspace(char line[])
{
	int i;
	for (i = strlen(line) - 1; i >= 0; i--) {
		if (!isspace(line[i])) {
			line[i + 1] = 0;
			break;
		}
	}
}

void addlink(int vernum, int num, float value)
{
	nodePointer node;
	node = newnode(num, value);
	node->link = vertex[vernum];
	vertex[vernum] = node;
}

nodePointer newnode(int num, float value)
{
	nodePointer node;
	node = (nodePointer)malloc(sizeof(ty_node));
	node->vernum = num;
	node->cost = value;
	node->link = NULL;
	return node;
}

void shortest_path(int start, int destination){
	int i, w, u = 0;
	for (i = 0; i < Max_vertex; i++){
		set_S[i] = 0;
		distance[i] = COST[start][i];
		pred[i] = 0;
	}
	distance[start] = 0;
	set_S[start] = 1;
	for (i = 0; i <Max_vertex - 2; i++){
		u = choose(distance, Max_vertex, set_S);
		set_S[u] = 1;
		if (i == 0)
			pred[u] = start;
		for (w = 0; w < Max_vertex; w++){
			if (distance[u] + COST[u][w] < distance[w]){
				distance[w] = distance[u] + COST[u][w];
				pred[w] = u;
			}
		}
		if (set_S[destination] == 1)
			break;
	}
	int count = 11, pre, line[Max_vertex];
	printf("경로 : ");
	pre = destination;
	while (1){
		line[count] = pre;
		count--;
		if (pre == start)
			break;
		pre = pred[pre];
	}
	for (i = count + 1; i < Max_vertex; i++)
		printf(" %d", line[i]);
	printf("	총비용 : %.1f", distance[destination]);
}

int choose(double distance[], int vert, int set_S[]){
	int i, minpos;
	double min;
	min = 12345;
	minpos = -1;
	for (i = 0; i < vert; i++)
		if (distance[i] < min&& !set_S[i])
		{
			min = distance[i];
			minpos = i;
		}
	return minpos;

}