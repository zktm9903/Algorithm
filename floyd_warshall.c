#include <stdio.h>
#define MAX_SIZE 100

int n, m;
int edge[MAX_SIZE][MAX_SIZE];

void printWeight() { //그래프 초기화
	printf("\n--------------------------------------------\n");
	printf("    ");
	for (int i = 0; i < n; i++) {
		printf("%4d", i);
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
		printf("%4d", i);
		for (int j = 0; j < n; j++) {
			if (edge[i][j] == 987654321)
				printf("%4s", "INF");
			else
				printf("%4d", edge[i][j]);
		}
		printf("\n");
	}
}

void input() {
	printf("노드의 갯수 : ");
	scanf("%d", &n);

	printf("엣지의 갯수 : ");
	scanf("%d", &m);

	for (int i = 0; i < MAX_SIZE; i++) //그래프 초기화
		for (int j = 0; j < MAX_SIZE; j++) {
			edge[i][j] = 987654321; //나머지는 무한대

			if (i == j) edge[i][j] = 0; //자기 자신 노드로 가는 가중치는 0
		}
			

	for (int i = 0; i < m; i++) { //그래프 입력
		int node1, node2, weight;
		scanf("%d %d %d", &node1, &node2, &weight);

		edge[node1][node2] = weight; //양방향 입력
		edge[node2][node1] = weight;
	}
}

void Floyd_Warshall() { //플로이드 와샬 알고리즘
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (edge[i][k] + edge[k][j] < edge[i][j]) 
					edge[i][j] = edge[i][k] + edge[k][j]; //거리 업데이트
}

int main() {
	input();

	Floyd_Warshall();
	printWeight();

	return 0;
}