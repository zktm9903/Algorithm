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

void primMST(int start) { //prim �˰���
    for (int i = 0; i < vertexCnt; i++) { //��� ����ġ �ʱ�ȭ
        nodeWeight[i] = INF;
    }
    for (int i = 0; i < vertexCnt; i++) { //���������� �̵��� �� �ִ� ��� �ʱ�ȭ
        nodeWeight[i] = edge[start][i];
        nodeWeightMemo[i] = start;
    }
    visit[start] = 1;
    tspMemo[tspIdx++] = start; //�湮�� ��� ���� ����

    printf("mst = {\n");
    for (int i = 0; i < vertexCnt - 1; i++) {
        int min = INF;
        int second = -1;

        for (int j = 0; j < vertexCnt; j++) { //����ġ�� ���� ���� ��� ã��
            if(visit[j] == 0)
                if (min > nodeWeight[j]) {
                    min = nodeWeight[j];
                    second = j;
                }
        }

        //����ġ�� ���� ���� ��� �湮
        nodeWeight[second] = min;
        visit[second] = 1;
        tspMemo[tspIdx++] = second; //�湮�� ��� ���� ����

        printf("{%d, %d, %d},\n", nodeWeightMemo[second], second, min);

        for (int j = 0; j < vertexCnt; j++) { //�湮�� ��忡�� �� �� �ִ� ��� �ʱ�ȭ
            if (visit[j] == 0)
                if (nodeWeight[j] > edge[second][j]) {
                    nodeWeight[j] = edge[second][j];
                    nodeWeightMemo[j] = second;
                }
        }
    }
    printf("}\n");
    tspMemo[tspIdx++] = start; //�湮�� ��� ���� ����
}

void printTSP() { //tsp ���
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