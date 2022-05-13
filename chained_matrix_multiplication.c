#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX_SIZE 100

int matrix[MAX_SIZE][2];
int dp[MAX_SIZE][MAX_SIZE];
char memo[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int n;

int MatrixChainOrder(int i, int j) //���� ��� �ּ� ���� �˰���
{
    if (i == j) 
    {
        return 0;
    }
    if (dp[i][j] != 0)
    {
        return dp[i][j];
    }
    dp[i][j] = 987654321;

    for (int k = i; k < j; k++) //�ʿ��� ���� �ҷ��ͼ� ��
    {
        int another = MatrixChainOrder(i, k) + MatrixChainOrder(k + 1, j) + matrix[i][0] * matrix[k][1] * matrix[j][1]; //����

        if (dp[i][j] > another) { //�� ���� ���̶�� ��ü
            dp[i][j] = another;

            //���� ���� ����
            char tmp[MAX_SIZE] = "(";
            strcat(tmp, memo[i][k]);
            strcat(tmp, "*");
            strcat(tmp, memo[k+1][j]);
            strcat(tmp, ")");
            strcpy(memo[i][j], tmp);
        }
    }
    return dp[i][j];
}

void memoInit() { //���� ���� ���ڿ� �ʱ�ȭ
    for (int i = 0; i < n; i++) {
        itoa(i+1, memo[i][i], 10);
    }
}

void input() { //��� �Է¹ޱ�
    printf("����� ���� : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("%d��° ����� row, column : ", i+1);
        scanf("%d %d", &matrix[i][0], &matrix[i][1]);
    }

    memoInit();
}

int main()
{
    input();
    printf("�ּ� ���� Ƚ�� : %d \n", MatrixChainOrder(0, n - 1));
    printf("�ּ� ���� ���� : %s", memo[0][n - 1]);
    return 0;
}