#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 60000

int arr[MAX_SIZE];
int leftMidRight[3];

void printArr() { //배열 출력 함수
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void randomInit() { //배열 랜덤 초기화 함수
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_SIZE; i++) {
		arr[i] = rand() % 100 + 1;
	}
}

void swap(int a, int b) { //자리 바꾸기 함수
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int swapInMedian(int a, int b) { //미디안 선정 과정 속 교환
	int tmp = leftMidRight[a];
	leftMidRight[a] = leftMidRight[b];
	leftMidRight[b] = tmp;
}


int partitionPivotLeft(int left, int right) { //분할 함수
	int pivot = arr[left]; //제일 왼쪽의 값을 피벗으로 설정
	int low = left + 1;
	int high = right;

	while (low <= high) //low와 high가 만나기 전까지 진행
	{
		while (low <= right && pivot >= arr[low]) // 피벗보다 작으면 지나감
		{
			low++; 
		}
		while (high >= (left + 1) && pivot <= arr[high]) //피벗보다 크면 지나감
		{
			high--; 
		}
		if (low <= high) //교차하지 않은 상태
		{
			swap(low, high); //교환
		}
	}
	swap(left, high); 
	return high;  
}

int whatIsMedian(int left, int mid, int right) { //미디안 선택
	leftMidRight[0] = arr[left];
	leftMidRight[1] = arr[mid];
	leftMidRight[2] = arr[right];

	for (int i = 0; i < 3; i++) { //선택 정렬
		int max = 0;
		int idx = -1;
		for (int j = i; j < 3; j++) {
			if (max < arr[j]) {
				max = arr[j];
				idx = j;
			}
		}
		swapInMedian(i, idx); //교환
	}

	//가운데 값 도출
	if (leftMidRight[1] == arr[left])
		return 0;
	else if (leftMidRight[1] == arr[mid])
		return 1;
	else
		return 2; 
}

int partitionPivotMedian(int left, int right) { //분할 함수
	int mid = (left + right) / 2; //중간값 선정

	int res = whatIsMedian(left, mid, right); //크기장 가운데값 도출
	int pivot;
	int median;

	if (res == 0) 
		median = left;
	else if (res == 1)
		median = mid;
	else 
		median = right;
	
	pivot = arr[median];
	swap(left, median); //제일 왼쪽 값과 중간값 교환
	
	int low = left + 1;
	int high = right;

	while (low <= high) //low와 high가 만나기 전까지 진행
	{
		while (low <= right && pivot >= arr[low]) // 피벗보다 작으면 지나감
		{
			low++;
		}
		while (high >= (left + 1) && pivot <= arr[high]) //피벗보다 크면 지나감
		{
			high--;
		}
		if (low <= high) //교차하지 않은 상태
		{
			swap(low, high); //교환
		}
	}
	swap(left, high);
	return high;
}

void quickSort(int left, int right, int pivotChoice) {
	if (left <= right)
	{
		int pivot;

		if(pivotChoice == 0)
			pivot = partitionPivotLeft(left, right); //피벗 위치 받기
		else
			pivot = partitionPivotMedian(left, right);

		quickSort(left, pivot - 1, pivotChoice);
		quickSort(pivot + 1, right, pivotChoice);
	}
}

int main() {
	clock_t start1, start2, end1, end2;

	randomInit(); //랜덤 초기화
	//printf("before sort : "); printArr();

	start1 = clock();
	quickSort(0, MAX_SIZE - 1, 0); //가장 왼쪽 값을 피봇으로하는 퀵소트
	end1 = clock();

	//printf("after sort : "); printArr();
	printf("quick Sort (left pivot) time : %.6f\n", (float)(end1 - start1) / CLOCKS_PER_SEC); //시간 출력

	randomInit(); //랜덤 초기화
	//printf("before sort : "); printArr();

	start2 = clock();
	quickSort(0, MAX_SIZE - 1, 1); //가운데 값을 피봇으로하는 퀵소트
	end2 = clock();

	//printf("after sort : "); printArr();
	printf("quick Sort (median pivot) time : %.6f\n", (float)(end2 - start2) / CLOCKS_PER_SEC); //시간 출력
	return 0;
}