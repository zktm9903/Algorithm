#include <stdio.h>
#define MAX_SIZE 10

typedef struct edge { //���� ����ü
    int firstNode;
    int secondNode;
    int weight;
}edges;

int n, m;
edges edge[MAX_SIZE];
int root[MAX_SIZE];

void print_edge() { //���� ���
    printf("print edge\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", edge[i].firstNode, edge[i].secondNode, edge[i].weight);
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
        scanf("%d %d %d", &edge[i].firstNode, &edge[i].secondNode, &edge[i].weight);
    }
}

void swap(int root, int child) { //��ȯ
    int temp1 = edge[root].firstNode;
    int temp2 = edge[root].secondNode;
    int temp3 = edge[root].weight;

    edge[root].firstNode = edge[child].firstNode;
    edge[root].secondNode = edge[child].secondNode;
    edge[root].weight = edge[child].weight;

    edge[child].firstNode = temp1;
    edge[child].secondNode = temp2;
    edge[child].weight = temp3;
}

void heapSort() { //�� ����(��������)
    //�ִ� �� ����
    for (int i = 1; i < n; i++) {
        int child = i;
        do {
            int parent = (child - 1) / 2; // �θ� ��� ã��
            if (edge[parent].weight < edge[child].weight) { //�ڽ� ��尡 �� Ŭ ���
                swap(parent, child);
            }
            child = parent;
        } while (child != 0);
    }
    // �� ũ�⸦ ���Ӱ� ���ÿ� �ݺ������� ���� ����
    for (int i = n - 1; i >= 0; i--) {
        swap(0, i); //��Ʈ ���� ���������� �̵�
        int parent = 0;
        int child = 1;
        do {
            child = 2 * parent + 1;
            // �ڽ� �� �� ū ���� ��
            if (edge[child].weight < edge[child + 1].weight && child < i - 1) {
                child++;
            }
            // �θ𺸴� �ڽ��� �� ũ�� ��ȯ
            if (edge[parent].weight < edge[child].weight && child < i) {
                swap(parent, child);
            }
            parent = child;
        } while (child < i);
    }
}

int find(int a) { //��Ʈ ã�� 
    if (root[a] != a)
        return find(root[a]);

    return a;
}

int hasCycle(int a, int b) { //����Ŭ �˻�
    int rootA = find(a);
    int rootB = find(b);

    return rootA == rootB; //��Ʈ�� ���ٸ� 1 ��ȯ
}

void insertUnion(int a, int b) { //���� ��ġ��
    int rootA = find(a);
    int rootB = find(b);

    //���� ���� �������� ��Ʈ ����
    if (rootA < rootB)
        root[b] = rootA;
    else
        root[a] = rootB;
}

void rootInit() { // ��Ʈ �ʱ�ȭ
    for (int i = 0; i < MAX_SIZE; i++) {
        root[i] = i;
    }
}

void KruskalMST() { //ũ�罺Į �ּ� ���� �˰���
    heapSort();
    rootInit();

    int edgeCount = 0; //���� ����
    int totalWeight = 0; //�� ����ġ

    printf("------- used edges -------\n");
    for (int i = 0; i < n ; i++) {
        int firstNode = edge[i].firstNode;
        int secondNode = edge[i].secondNode;
        int weight = edge[i].weight;

        if (hasCycle(firstNode, secondNode)) continue; //����Ŭ�� ������ �˻�

        //����Ŭ�� ������ �ʴ´ٸ�
        insertUnion(firstNode, secondNode); // �������� ��ġ��
        printf("%d <--> %d   weight:%d\n", firstNode, secondNode, weight); //���� ���� ���

        edgeCount++;
        totalWeight += weight;

        if (edgeCount == (m - 1)) // ���� ������ ��� �������� 1��ŭ ���� ���
            break;
    }

    printf("weight : %d", totalWeight); //��ü ����ġ ���
}

int main() {
    input();

    KruskalMST();

    return 0;
}