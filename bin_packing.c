#include <stdio.h>
#define MAX_SIZE 100
#define INF 987654321
#define OBJECT_CNT 8

typedef struct basket { //통 구조체
    int height; //현재 높이
    int objectIdx; //들어 있는 오브젝트의 마지막 인덱스
    int object[OBJECT_CNT]; //들어있는 오브젝트 배열
}basket;

basket baskets[MAX_SIZE]; //통 구조체 선언
int lastContainer = -1; //마지막으로 사용된 통 인덱스

int C = 10; //허용하는 통의 높이
int volume[OBJECT_CNT] = { 7,5,6,4,2,3,7,5 }; //오브젝트들의 부피들

void print_packing() {
    //오브젝트들의 부피들 출력
    printf("volume = [");
    for (int i = 0; i < OBJECT_CNT; i++) {
        printf("%d, ", volume[i]);
    }
    printf("]\n");

    //통마다 들어있는 오브젝트들 출력
    for (int i = 0; i <= lastContainer; i++) {
        printf("%d번째 통에 있는 objects : ", i + 1);
        for (int j = 0; j < baskets[i].objectIdx; j++) {
            printf("%d, ", baskets[i].object[j]);
        }
        printf("\n");
    }
}

void bin_packing(char fit) {
    lastContainer = -1;
    for (int i = 0; i < MAX_SIZE; i++) { //바구니 초기화
        baskets[i].height = 0;
        baskets[i].objectIdx = 0;
    }

    if (fit == 'f') {
        printf("---------------first fit---------------\n");
        for (int i = 0; i < OBJECT_CNT; i++) {
            int container = 0;
            while (1) {
                if (baskets[container].height + volume[i] <= C) { //담는게 가능한 통이라면 담기
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
            for (int j = 0; j <= lastContainer; j++) { //현재 사용한 통 중에서
                if (baskets[j].height + volume[i] <= C) { //담는게 가능하다면 
                    if (min > C - (baskets[j].height + volume[i])) { //담았을 때 남는 부피가 최소인 값 찾기
                        min = C - (baskets[j].height + volume[i]);
                        idx = j;
                    }
                }
            }
            if (min != INF) { //현재 사용한 통 중에서 하나라도 가능할 때
                baskets[idx].height += volume[i];
                baskets[idx].object[baskets[idx].objectIdx++] = volume[i];
            }
            else { //현재 사용한 통 중에서는 담는게 불가능할 때
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