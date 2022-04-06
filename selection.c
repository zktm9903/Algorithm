#include <stdio.h>
#define MAX_SIZE 12
int arr[MAX_SIZE] = { 6,3,11,9,12,2,8,15,18,10,7,14 };
int k, n;

void printArr() { //배열 출력 함수
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int a, int b) { //자리 바꾸기 함수
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int partition(int left, int right) { //분할 함수
	int pivot = arr[left]; // 가장 왼쪽값을 피벗으로 설정
	int i = left;
	int j = right;

	while (i < j) {
		while (pivot < arr[j]) { //피벗보다 클 경우
			j--; //왼쪽으로 이동
		}
		while (i < j && pivot >= arr[i]) { //피벗보다 작거나 같을 경우
			i++;	//오른쪽으로 이독
		}
		swap(i, j); //교환
	}

	//피벗을 가운데로 이동
	arr[left] = arr[i];
	arr[i] = pivot; 
		
	return i; //가운데 인덱스 값 반환
}

void selection(int left, int right) {
	int pivot = partition(left, right); // 분할 

	if (k < pivot) selection(left, pivot - 1);  //입력한 값이 피벗 인덱스 값보다 작을 경우
	else if (k == pivot) return; //입력한 값이 피벗 인덱스 값과 같을 경우
	else selection(pivot + 1, right); //입력한 값이 피벗 인덱스 값보다 클 경우
}

int main() {
	printf("몇번째로 큰 값을 고를지 입력 : ");
	scanf("%d", &k);

	printf("---------before array---------\n");
	printArr();
	selection(0, 11);
	printf("----------after array---------\n");
	printArr();

	printf("%d번째로 작은 값은 %d입니다.", k, arr[k-1]);

	return 0;
}

