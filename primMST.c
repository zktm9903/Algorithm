#include <stdio.h>
#define MAX_SIZE 10
#define INFINITY 987654321

typedef struct edge { //���� ����ü
    int node;
    int weight;
}edges;

int n, m; //edge ����, node ����
edges edge[MAX_SIZE][MAX_SIZE]; //���� ������ ������ 2���� �迭
int edgeCount[MAX_SIZE]; //�� ��忡 ����� ���� ����
int nodeWeight[MAX_SIZE]; //������ ���µ� �ʿ��� ����ġ
int visit[MAX_SIZE]; //��� �湮 ����
int totalWeight; //�� ����ġ
edges rememberEdge[MAX_SIZE]; //���� ���� ����� ���� �迭
int startNode = 0; //���� ���

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
}

void updateNodeWeight(int node) { //�ش� ��忡�� �� �� �ִ� ����� ����ġ ����
    for (int i = 0; i < edgeCount[node]; i++) {
        int nextNode = edge[node][i].node;
        int weight = edge[node][i].weight;

        if (nodeWeight[nextNode] > weight) { //������ ����ġ���� ���� ���
            nodeWeight[nextNode] = weight;

            rememberEdge[nextNode].node = node;
            rememberEdge[nextNode].weight = weight;
        }
            
    }
}

void init() { //�ʱ�ȭ �Լ�
    for (int i = 0; i < m; i++) {
        nodeWeight[i] = INFINITY; //��� ����ġ�� �������� ����
    }

    nodeWeight[startNode] = 0; //���� ����� ����ġ�� 0
    visit[startNode] = 1; //���� ��带 �湮

    updateNodeWeight(startNode); //���� ��带 �������� �� �� �ִ� ��� ����ġ ����
}

void primMST() {
    int totalCountEdge = 0;

    printf("------- used edges -------\n");
    while (totalCountEdge < (m - 1)) { //���� ������ ��� �������� 1��ŭ ���� ������
        int min = INFINITY;
        int index = -1;

        for (int i = 0; i < m; i++) { //���� ���� ����ġ�� �� �� �ִ� ��� Ž��
            if (visit[i] == 0) {
                if (min > nodeWeight[i]) {
                    min = nodeWeight[i];
                    index = i;
                }
            }
        }
        
        visit[index] = 1; //�ش� ��� �湮
        totalWeight += min; //�� ����ġ ����
        totalCountEdge++; //�� ���� ���� ����

        printf("%d <--> %d   weight:%d\n", index, rememberEdge[index].node, rememberEdge[index].weight); //���� ���� ���

        updateNodeWeight(index); //���� �湮�� ��带 �������� �� �� �ִ� ��� ����ġ ����
    }
    
    printf("weight : %d", totalWeight); //��ü ����ġ ���
}

int main() {
    input();
    init();

    primMST();
    return 0;
}