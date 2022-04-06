#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 60000

int arr[MAX_SIZE];
int leftMidRight[3];

void printArr() { //�迭 ��� �Լ�
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void randomInit() { //�迭 ���� �ʱ�ȭ �Լ�
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_SIZE; i++) {
		arr[i] = rand() % 100 + 1;
	}
}

void swap(int a, int b) { //�ڸ� �ٲٱ� �Լ�
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int swapInMedian(int a, int b) { //�̵�� ���� ���� �� ��ȯ
	int tmp = leftMidRight[a];
	leftMidRight[a] = leftMidRight[b];
	leftMidRight[b] = tmp;
}


int partitionPivotLeft(int left, int right) { //���� �Լ�
	int pivot = arr[left]; //���� ������ ���� �ǹ����� ����
	int low = left + 1;
	int high = right;

	while (low <= high) //low�� high�� ������ ������ ����
	{
		while (low <= right && pivot >= arr[low]) // �ǹ����� ������ ������
		{
			low++; 
		}
		while (high >= (left + 1) && pivot <= arr[high]) //�ǹ����� ũ�� ������
		{
			high--; 
		}
		if (low <= high) //�������� ���� ����
		{
			swap(low, high); //��ȯ
		}
	}
	swap(left, high); 
	return high;  
}

int whatIsMedian(int left, int mid, int right) { //�̵�� ����
	leftMidRight[0] = arr[left];
	leftMidRight[1] = arr[mid];
	leftMidRight[2] = arr[right];

	for (int i = 0; i < 3; i++) { //���� ����
		int max = 0;
		int idx = -1;
		for (int j = i; j < 3; j++) {
			if (max < arr[j]) {
				max = arr[j];
				idx = j;
			}
		}
		swapInMedian(i, idx); //��ȯ
	}

	//��� �� ����
	if (leftMidRight[1] == arr[left])
		return 0;
	else if (leftMidRight[1] == arr[mid])
		return 1;
	else
		return 2; 
}

int partitionPivotMedian(int left, int right) { //���� �Լ�
	int mid = (left + right) / 2; //�߰��� ����

	int res = whatIsMedian(left, mid, right); //ũ���� ����� ����
	int pivot;
	int median;

	if (res == 0) 
		median = left;
	else if (res == 1)
		median = mid;
	else 
		median = right;
	
	pivot = arr[median];
	swap(left, median); //���� ���� ���� �߰��� ��ȯ
	
	int low = left + 1;
	int high = right;

	while (low <= high) //low�� high�� ������ ������ ����
	{
		while (low <= right && pivot >= arr[low]) // �ǹ����� ������ ������
		{
			low++;
		}
		while (high >= (left + 1) && pivot <= arr[high]) //�ǹ����� ũ�� ������
		{
			high--;
		}
		if (low <= high) //�������� ���� ����
		{
			swap(low, high); //��ȯ
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
			pivot = partitionPivotLeft(left, right); //�ǹ� ��ġ �ޱ�
		else
			pivot = partitionPivotMedian(left, right);

		quickSort(left, pivot - 1, pivotChoice);
		quickSort(pivot + 1, right, pivotChoice);
	}
}

int main() {
	clock_t start1, start2, end1, end2;

	randomInit(); //���� �ʱ�ȭ
	//printf("before sort : "); printArr();

	start1 = clock();
	quickSort(0, MAX_SIZE - 1, 0); //���� ���� ���� �Ǻ������ϴ� ����Ʈ
	end1 = clock();

	//printf("after sort : "); printArr();
	printf("quick Sort (left pivot) time : %.6f\n", (float)(end1 - start1) / CLOCKS_PER_SEC); //�ð� ���

	randomInit(); //���� �ʱ�ȭ
	//printf("before sort : "); printArr();

	start2 = clock();
	quickSort(0, MAX_SIZE - 1, 1); //��� ���� �Ǻ������ϴ� ����Ʈ
	end2 = clock();

	//printf("after sort : "); printArr();
	printf("quick Sort (median pivot) time : %.6f\n", (float)(end2 - start2) / CLOCKS_PER_SEC); //�ð� ���
	return 0;
}