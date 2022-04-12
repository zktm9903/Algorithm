#include <stdio.h>
#define MAX_SIZE 10
#define INFINITY 987654321

typedef struct edge { //엣지 구조체
    int node;
    int weight;
}edges;

int n, m;
int visit[MAX_SIZE];
int nodeWeight[MAX_SIZE];
edges edge[MAX_SIZE][MAX_SIZE];
int edgeCount[MAX_SIZE];
int startNode;
edges preEdge[MAX_SIZE];

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

    printf("시작할 노드의 번호를 입력 : ");
    scanf("%d", &startNode);
}

void init() { //초기화 함수
    for (int i = 0; i < m; i++) {
        nodeWeight[i] = INFINITY; //무제한으로 초기화
    }

    nodeWeight[startNode] = 0; //최소 경로 0으로 초기화
    visit[startNode] = 1; //방문 여부 확인

    //시작 지점에서 갈 수 있는 노드 최소경로 업데이트
    for (int i = 0; i < edgeCount[startNode]; i++) { 
        int nextNode = edge[startNode][i].node;
        int weight = edge[startNode][i].weight;

        nodeWeight[nextNode] = weight;

        //사용된 마지막 엣지 기록
        preEdge[nextNode].node = 0; 
        preEdge[nextNode].weight = weight;
    }
    
}

void dijkstra() {
    init();

    int count = 1; //방문 노드 체크 변수

    while (count != m) { //모든 노드를 방문할 때까지
        int min = INFINITY;
        int idx = 0;

        for (int i = 0; i < m; i++) { //최소 경로가 가장 작은 노드 찾기
            if(visit[i] == 0)
                if (min > nodeWeight[i]) {
                    min = nodeWeight[i];
                    idx = i;
                }
        }

        visit[idx] = 1; //노드 방문

        //현재 노드에서 갈 수 있는 노드 최소 경로 업데이트
        for (int i = 0; i < edgeCount[idx]; i++) {
            int nextNode = edge[idx][i].node;
            int weight = edge[idx][i].weight;

            if (visit[nextNode] == 0) { 
                if (nodeWeight[nextNode] > nodeWeight[idx]+ weight) {
                    nodeWeight[nextNode] = nodeWeight[idx] + weight;

                    //사용된 마지막 엣지 기록
                    preEdge[nextNode].node = idx;
                    preEdge[nextNode].weight = weight;
                }
            }
        }
        count++;
    }

    printf("-------------------------------------------------\n");
    printf("node   :    0   1   2   3   4   5   6   7   8   9\n");
    printf("weight :    ");
    for (int i = 0; i < m; i++) {
        printf("%d  ", nodeWeight[i]); //최소 경로 출력
    }
    printf("\n-------------------------------------------------\n");

    printf("--------------------used edge----------------------\n");
    //사용된 엣지 출력
    for (int i = 0; i < m; i++) {
        if (i == startNode)
            continue;

        printf("%d<-->%d    weight:%d\n", i, preEdge[i].node, preEdge[i].weight);
    }

}

int main() {
    input();

    dijkstra();

    return 0;
}