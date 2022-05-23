#include <stdio.h>
#include <string.h>
#define min(a,b)  (((a) < (b)) ? (a) : (b))

char str1[50];
char str2[50];
int dp[51][51];
char memo[51][51][1000];

void printDP() { //dp 출력
    printf("--------------------\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d", dp[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}

void memoInsert(int i, int j, int flag) { //경로 저장
    char insert[100] = "";

    char char1[2] = { str1[i - 1], '\0' };
    char char2[2] = { str2[j - 1], '\0' };
    char text[2] = "";
    sprintf(text, "%d", i);
    strcat(insert, text);

    if (flag == -1) { //아무 변화 없을 경우
        strcat(memo[i][j], memo[i - 1][j - 1]);
        return;
    }
    if (flag == 0) { //삽입 경우
        strcat(memo[i][j], memo[i][j - 1]);

        strcat(insert, "번째에 ");
        strcat(insert, char2);
        strcat(insert, "를 삽입, ");
    }
    if (flag == 1) { //삭제 경우
        strcat(memo[i][j], memo[i - 1][j]);

        strcat(insert, "번째의 ");
        strcat(insert, char1);
        strcat(insert, "을 삭제, ");
    }
    if (flag == 2) { //교체 경우
        strcat(memo[i][j], memo[i - 1][j - 1]);

        strcat(insert, "번째를 ");
        strcat(insert, char2);
        strcat(insert, "로 교체, ");
    }

    strcat(memo[i][j], insert);
}

void editDistDP(int m, int n)
{
    //초기화 작업
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int i = 0; i <= n; i++) dp[0][i] = i;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) { //문자가 같다면 왼쪽 위의 dp값 가져오기
                dp[i][j] = dp[i - 1][j - 1];
                memoInsert(i, j, -1);
            }


            else { //문자가 다르다면 왼쪽, 위, 왼쪽 위 값에 1을 더하기(가장 작은 값에)
                dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));

                if (dp[i][j] - 1 == dp[i][j - 1])      memoInsert(i, j, 0); //왼
                else if (dp[i][j] - 1 == dp[i - 1][j])      memoInsert(i, j, 1); //위
                else if (dp[i][j] - 1 == dp[i - 1][j - 1])  memoInsert(i, j, 2); //왼쪽위
            }
        }
    }

    printf("최소 편집 비용 : %d\n", dp[m][n]);
    printf("최소 편집 과정 : %s\n", memo[m][n]);
}

void input() {
    printf("첫번째 문자열 : ");
    scanf("%s", str1);
    printf("두번째 문자열 : ");
    scanf("%s", str2);
}

int main()
{
    input();
    editDistDP(strlen(str1), strlen(str2));

    return 0;
}