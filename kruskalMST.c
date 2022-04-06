#include <stdio.h>
#define MAX_SIZE 10

typedef struct edge { //엣지 구조체
    int firstNode;
    int secondNode;
    int weight;
}edges;

int n, m;
edges edge[MAX_SIZE];
int root[MAX_SIZE];

void print_edge() { //엣지 출력
    printf("print edge\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", edge[i].firstNode, edge[i].secondNode, edge[i].weight);
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
        scanf("%d %d %d", &edge[i].firstNode, &edge[i].secondNode, &edge[i].weight);
    }
}

void swap(int root, int child) { //교환
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

void heapSort() { //힙 정렬(오름차순)
    //최대 힙 구성
    for (int i = 1; i < n; i++) {
        int child = i;
        do {
            int parent = (child - 1) / 2; // 부모 노드 찾기
            if (edge[parent].weight < edge[child].weight) { //자식 노드가 더 클 경우
                swap(parent, child);
            }
            child = parent;
        } while (child != 0);
    }
    // 힙 크기를 줄임과 동시에 반복적으로 힙을 구성
    for (int i = n - 1; i >= 0; i--) {
        swap(0, i); //루트 값을 마지막으로 이동
        int parent = 0;
        int child = 1;
        do {
            child = 2 * parent + 1;
            // 자식 둘 중 큰 값을 고름
            if (edge[child].weight < edge[child + 1].weight && child < i - 1) {
                child++;
            }
            // 부모보다 자식이 더 크면 교환
            if (edge[parent].weight < edge[child].weight && child < i) {
                swap(parent, child);
            }
            parent = child;
        } while (child < i);
    }
}

int find(int a) { //루트 찾기 
    if (root[a] != a)
        return find(root[a]);

    return a;
}

int hasCycle(int a, int b) { //싸이클 검사
    int rootA = find(a);
    int rootB = find(b);

    return rootA == rootB; //루트가 같다면 1 반환
}

void insertUnion(int a, int b) { //집합 합치기
    int rootA = find(a);
    int rootB = find(b);

    //작은 것을 기준으로 루트 변경
    if (rootA < rootB)
        root[b] = rootA;
    else
        root[a] = rootB;
}

void rootInit() { // 루트 초기화
    for (int i = 0; i < MAX_SIZE; i++) {
        root[i] = i;
    }
}

void KruskalMST() { //크루스칼 최소 신장 알고리즘
    heapSort();
    rootInit();

    int edgeCount = 0; //엣지 갯수
    int totalWeight = 0; //총 가중치

    printf("------- used edges -------\n");
    for (int i = 0; i < n ; i++) {
        int firstNode = edge[i].firstNode;
        int secondNode = edge[i].secondNode;
        int weight = edge[i].weight;

        if (hasCycle(firstNode, secondNode)) continue; //사이클이 생길지 검사

        //사이클이 생기지 않는다면
        insertUnion(firstNode, secondNode); // 집합으로 합치기
        printf("%d <--> %d   weight:%d\n", firstNode, secondNode, weight); //엣지 정보 출력

        edgeCount++;
        totalWeight += weight;

        if (edgeCount == (m - 1)) // 엣지 갯수가 노드 갯수보다 1만큼 작을 경우
            break;
    }

    printf("weight : %d", totalWeight); //전체 가중치 출력
}

int main() {
    input();

    KruskalMST();

    return 0;
}