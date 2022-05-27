#include <stdio.h>
#define INF 987654321
#define vertexCnt 6

int visit[vertexCnt];
int nodeWeight[vertexCnt];
int nodeWeightMemo[vertexCnt];
int tspMemo[vertexCnt + 1];
int tspIdx;

int edge[vertexCnt][vertexCnt] = {
    {0, 3, INF, 2, 4, INF},
    {3, 0, 1, 4, INF, 2},
    {INF, 1, 0, INF, INF, 1},
    {2, 4, INF, 0, 5, 7},
    {4, INF, INF, 5, 0, 9},
    {INF, 2, 1, 7, 9, 0},
};

void primMST(int start) { //prim 알고리즘
    for (int i = 0; i < vertexCnt; i++) { //노드 가중치 초기화
        nodeWeight[i] = INF;
    }
    for (int i = 0; i < vertexCnt; i++) { //시작점에서 이동할 수 있는 노드 초기화
        nodeWeight[i] = edge[start][i];
        nodeWeightMemo[i] = start;
    }
    visit[start] = 1;
    tspMemo[tspIdx++] = start; //방문한 노드 순서 저장

    printf("mst = {\n");
    for (int i = 0; i < vertexCnt - 1; i++) {
        int min = INF;
        int second = -1;

        for (int j = 0; j < vertexCnt; j++) { //가중치가 가장 작은 노드 찾기
            if(visit[j] == 0)
                if (min > nodeWeight[j]) {
                    min = nodeWeight[j];
                    second = j;
                }
        }

        //가중치가 가장 작은 노드 방문
        nodeWeight[second] = min;
        visit[second] = 1;
        tspMemo[tspIdx++] = second; //방문한 노드 순서 저장

        printf("{%d, %d, %d},\n", nodeWeightMemo[second], second, min);

        for (int j = 0; j < vertexCnt; j++) { //방문한 노드에서 갈 수 있는 노드 초기화
            if (visit[j] == 0)
                if (nodeWeight[j] > edge[second][j]) {
                    nodeWeight[j] = edge[second][j];
                    nodeWeightMemo[j] = second;
                }
        }
    }
    printf("}\n");
    tspMemo[tspIdx++] = start; //방문한 노드 순서 저장
}

void printTSP() { //tsp 출력
    printf("tsp = ");
    for (int i = 0; i < vertexCnt + 1; i++) {
        printf("%d ", tspMemo[i]);
    }
}

int main() {
    primMST(0);
    printTSP();
    return 0;
}