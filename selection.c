#include <stdio.h>
#define MAX_SIZE 12
int arr[MAX_SIZE] = { 6,3,11,9,12,2,8,15,18,10,7,14 };
int k, n;

void printArr() { //�迭 ��� �Լ�
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int a, int b) { //�ڸ� �ٲٱ� �Լ�
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int partition(int left, int right) { //���� �Լ�
	int pivot = arr[left]; // ���� ���ʰ��� �ǹ����� ����
	int i = left;
	int j = right;

	while (i < j) {
		while (pivot < arr[j]) { //�ǹ����� Ŭ ���
			j--; //�������� �̵�
		}
		while (i < j && pivot >= arr[i]) { //�ǹ����� �۰ų� ���� ���
			i++;	//���������� �̵�
		}
		swap(i, j); //��ȯ
	}

	//�ǹ��� ����� �̵�
	arr[left] = arr[i];
	arr[i] = pivot; 
		
	return i; //��� �ε��� �� ��ȯ
}

void selection(int left, int right) {
	int pivot = partition(left, right); // ���� 

	if (k < pivot) selection(left, pivot - 1);  //�Է��� ���� �ǹ� �ε��� ������ ���� ���
	else if (k == pivot) return; //�Է��� ���� �ǹ� �ε��� ���� ���� ���
	else selection(pivot + 1, right); //�Է��� ���� �ǹ� �ε��� ������ Ŭ ���
}

int main() {
	printf("���°�� ū ���� ���� �Է� : ");
	scanf("%d", &k);

	printf("---------before array---------\n");
	printArr();
	selection(0, 11);
	printf("----------after array---------\n");
	printArr();

	printf("%d��°�� ���� ���� %d�Դϴ�.", k, arr[k-1]);

	return 0;
}

