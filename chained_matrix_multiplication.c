#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX_SIZE 100

int matrix[MAX_SIZE][2];
int dp[MAX_SIZE][MAX_SIZE];
char memo[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int n;

int MatrixChainOrder(int i, int j) //연쇄 행렬 최소 곱셈 알고리즘
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

    for (int k = i; k < j; k++) //필요한 값들 불러와서 비교
    {
        int another = MatrixChainOrder(i, k) + MatrixChainOrder(k + 1, j) + matrix[i][0] * matrix[k][1] * matrix[j][1]; //결합

        if (dp[i][j] > another) { //더 작은 값이라면 교체
            dp[i][j] = another;

            //결합 과정 저장
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

void memoInit() { //과정 저장 문자열 초기화
    for (int i = 0; i < n; i++) {
        itoa(i+1, memo[i][i], 10);
    }
}

void input() { //행렬 입력받기
    printf("행렬의 개수 : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("%d번째 행렬의 row, column : ", i+1);
        scanf("%d %d", &matrix[i][0], &matrix[i][1]);
    }

    memoInit();
}

int main()
{
    input();
    printf("최소 연산 횟수 : %d \n", MatrixChainOrder(0, n - 1));
    printf("최소 연산 과정 : %s", memo[0][n - 1]);
    return 0;
}