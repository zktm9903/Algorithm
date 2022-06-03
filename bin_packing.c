#include <stdio.h>
#define MAX_SIZE 100
#define INF 987654321
#define OBJECT_CNT 8

typedef struct basket { //�� ����ü
    int height; //���� ����
    int objectIdx; //��� �ִ� ������Ʈ�� ������ �ε���
    int object[OBJECT_CNT]; //����ִ� ������Ʈ �迭
}basket;

basket baskets[MAX_SIZE]; //�� ����ü ����
int lastContainer = -1; //���������� ���� �� �ε���

int C = 10; //����ϴ� ���� ����
int volume[OBJECT_CNT] = { 7,5,6,4,2,3,7,5 }; //������Ʈ���� ���ǵ�

void print_packing() {
    //������Ʈ���� ���ǵ� ���
    printf("volume = [");
    for (int i = 0; i < OBJECT_CNT; i++) {
        printf("%d, ", volume[i]);
    }
    printf("]\n");

    //�븶�� ����ִ� ������Ʈ�� ���
    for (int i = 0; i <= lastContainer; i++) {
        printf("%d��° �뿡 �ִ� objects : ", i + 1);
        for (int j = 0; j < baskets[i].objectIdx; j++) {
            printf("%d, ", baskets[i].object[j]);
        }
        printf("\n");
    }
}

void bin_packing(char fit) {
    lastContainer = -1;
    for (int i = 0; i < MAX_SIZE; i++) { //�ٱ��� �ʱ�ȭ
        baskets[i].height = 0;
        baskets[i].objectIdx = 0;
    }

    if (fit == 'f') {
        printf("---------------first fit---------------\n");
        for (int i = 0; i < OBJECT_CNT; i++) {
            int container = 0;
            while (1) {
                if (baskets[container].height + volume[i] <= C) { //��°� ������ ���̶�� ���
                    baskets[container].height += volume[i];
                    baskets[container].object[baskets[container].objectIdx++] = volume[i];
                    break;
                }

                lastContainer = ++container;
            }
        }
    }

    if (fit == 'b') {
        printf("---------------best fit---------------\n");
        for (int i = 0; i < OBJECT_CNT; i++) {
            int min = INF;
            int idx = -1;
            for (int j = 0; j <= lastContainer; j++) { //���� ����� �� �߿���
                if (baskets[j].height + volume[i] <= C) { //��°� �����ϴٸ� 
                    if (min > C - (baskets[j].height + volume[i])) { //����� �� ���� ���ǰ� �ּ��� �� ã��
                        min = C - (baskets[j].height + volume[i]);
                        idx = j;
                    }
                }
            }
            if (min != INF) { //���� ����� �� �߿��� �ϳ��� ������ ��
                baskets[idx].height += volume[i];
                baskets[idx].object[baskets[idx].objectIdx++] = volume[i];
            }
            else { //���� ����� �� �߿����� ��°� �Ұ����� ��
                lastContainer++;
                baskets[lastContainer].height += volume[i];
                baskets[lastContainer].object[baskets[lastContainer].objectIdx++] = volume[i];

            }
        }
    }

    print_packing();
}

int main() {
    //fisrt fit = 'f'
    //best fit = 'b'
    bin_packing('f');
    bin_packing('b');

    return 0;
}