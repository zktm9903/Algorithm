#include <stdio.h>
#define MAX_SIZE 10
#define INFINITY 987654321

typedef struct edge { //���� ����ü
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

void print_edge() { //���� ���
    printf("print edge\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount[i]; j++) {
            printf("%d %d %d\n", i, j, edge[i][j].weight);
        }
    }
    printf("\n");
}

void input() { //���� �Է� �ޱ�
    printf("node�� ������ �Է� : ");
    scanf("%d", &m);

    printf("edge�� ������ �Է� : ");
    scanf("%d", &n);

    printf("edge�� ������ �Է� : (node1 node2 weight)\n");
    for (int i = 0; i < n; i++) {
        int node1, node2, weight;
        scanf("%d %d %d", &node1, &node2, &weight);

        //�瓇������ ����
        edge[node1][edgeCount[node1]].node = node2;
        edge[node1][edgeCount[node1]].weight = weight;

        edge[node2][edgeCount[node2]].node = node1;
        edge[node2][edgeCount[node2]].weight = weight;

        //�� ��忡 ����� ���� ���� ������Ʈ
        edgeCount[node1]++;
        edgeCount[node2]++;
    }

    printf("������ ����� ��ȣ�� �Է� : ");
    scanf("%d", &startNode);
}

void init() { //�ʱ�ȭ �Լ�
    for (int i = 0; i < m; i++) {
        nodeWeight[i] = INFINITY; //���������� �ʱ�ȭ
    }

    nodeWeight[startNode] = 0; //�ּ� ��� 0���� �ʱ�ȭ
    visit[startNode] = 1; //�湮 ���� Ȯ��

    //���� �������� �� �� �ִ� ��� �ּҰ�� ������Ʈ
    for (int i = 0; i < edgeCount[startNode]; i++) { 
        int nextNode = edge[startNode][i].node;
        int weight = edge[startNode][i].weight;

        nodeWeight[nextNode] = weight;

        //���� ������ ���� ���
        preEdge[nextNode].node = 0; 
        preEdge[nextNode].weight = weight;
    }
    
}

void dijkstra() {
    init();

    int count = 1; //�湮 ��� üũ ����

    while (count != m) { //��� ��带 �湮�� ������
        int min = INFINITY;
        int idx = 0;

        for (int i = 0; i < m; i++) { //�ּ� ��ΰ� ���� ���� ��� ã��
            if(visit[i] == 0)
                if (min > nodeWeight[i]) {
                    min = nodeWeight[i];
                    idx = i;
                }
        }

        visit[idx] = 1; //��� �湮

        //���� ��忡�� �� �� �ִ� ��� �ּ� ��� ������Ʈ
        for (int i = 0; i < edgeCount[idx]; i++) {
            int nextNode = edge[idx][i].node;
            int weight = edge[idx][i].weight;

            if (visit[nextNode] == 0) { 
                if (nodeWeight[nextNode] > nodeWeight[idx]+ weight) {
                    nodeWeight[nextNode] = nodeWeight[idx] + weight;

                    //���� ������ ���� ���
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
        printf("%d  ", nodeWeight[i]); //�ּ� ��� ���
    }
    printf("\n-------------------------------------------------\n");

    printf("--------------------used edge----------------------\n");
    //���� ���� ���
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