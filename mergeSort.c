#include <stdio.h>
#define MAX_SIZE 10
#define INFINITY 987654321

typedef struct edge { //엣지 구조체
    int node;
    int weight;
}edges;

int n, m; //edge 갯수, node 갯수
edges edge[MAX_SIZE][MAX_SIZE]; //엣지 정보를 저장할 2차원 배열
int edgeCount[MAX_SIZE]; //각 노드에 연결된 엣지 갯수
int nodeWeight[MAX_SIZE]; //노드까지 가는데 필요한 가중치
int visit[MAX_SIZE]; //노드 방문 여부
int totalWeight; //총 가중치
edges rememberEdge[MAX_SIZE]; //사용된 엣지 출력을 위한 배열
int startNode = 0; //시작 노드

void print_edge() { //엣지 출력
    printf("print edge\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount[i]; j++) {
            printf("%d %d %d\n", i, j, edge[i][j].weight);
        }
    }
    printf("\n");
}

void input() { //정보 입력 받기
    printf("node의 개수를 입력 : ");
    scanf("%d", &m);

    printf("edge의 개수를 입력 : ");
    scanf("%d", &n);

    printf("edge의 정보를 입력 : (node1 node2 weight)\n");
    for (int i = 0; i < n; i++) {
        int node1, node2, weight;
        scanf("%d %d %d", &node1, &node2, &weight);

        //양뱡향으로 연결
        edge[node1][edgeCount[node1]].node = node2;
        edge[node1][edgeCount[node1]].weight = weight;

        edge[node2][edgeCount[node2]].node = node1;
        edge[node2][edgeCount[node2]].weight = weight;

        //각 노드에 연결된 엣지 갯수 업데이트
        edgeCount[node1]++;
        edgeCount[node2]++;
    }
}

void updateNodeWeight(int node) { //해당 노드에서 갈 수 있는 노드의 가중치 갱신
    for (int i = 0; i < edgeCount[node]; i++) {
        int nextNode = edge[node][i].node;
        int weight = edge[node][i].weight;

        if (nodeWeight[nextNode] > weight) { //기존의 가중치보다 작을 경우
            nodeWeight[nextNode] = weight;

            rememberEdge[nextNode].node = node;
            rememberEdge[nextNode].weight = weight;
        }
            
    }
}

void init() { //초기화 함수
    for (int i = 0; i < m; i++) {
        nodeWeight[i] = INFINITY; //노드 가중치를 무한으로 설정
    }

    nodeWeight[startNode] = 0; //시작 노드의 가중치는 0
    visit[startNode] = 1; //시작 노드를 방문

    updateNodeWeight(startNode); //시작 노드를 중점으로 갈 수 있는 노드 가중치 갱신
}

void primMST() {
    int totalCountEdge = 0;

    printf("------- used edges -------\n");
    while (totalCountEdge < (m - 1)) { //엣지 갯수가 노드 갯수보다 1만큼 작을 때까지
        int min = INFINITY;
        int index = -1;

        for (int i = 0; i < m; i++) { //가장 적은 가중치로 갈 수 있는 노드 탐색
            if (visit[i] == 0) {
                if (min > nodeWeight[i]) {
                    min = nodeWeight[i];
                    index = i;
                }
            }
        }
        
        visit[index] = 1; //해당 노드 방문
        totalWeight += min; //총 가중치 갱신
        totalCountEdge++; //총 엣지 갯수 갱신

        printf("%d <--> %d   weight:%d\n", index, rememberEdge[index].node, rememberEdge[index].weight); //엣지 정보 출력

        updateNodeWeight(index); //새로 방문한 노드를 기점으로 갈 수 있는 노드 가중치 갱신
    }
    
    printf("weight : %d", totalWeight); //전체 가중치 출력
}

int main() {
    input();
    init();

    primMST();
    return 0;
}