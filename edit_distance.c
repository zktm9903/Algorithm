#include <stdio.h>
#include <string.h>
#define min(a,b)  (((a) < (b)) ? (a) : (b))

char str1[50];
char str2[50];
int dp[51][51];
char memo[51][51][1000];

void printDP() { //dp ���
    printf("--------------------\n");
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d", dp[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}

void memoInsert(int i, int j, int flag) { //��� ����
    char insert[100] = "";

    char char1[2] = { str1[i - 1], '\0' };
    char char2[2] = { str2[j - 1], '\0' };
    char text[2] = "";
    sprintf(text, "%d", i);
    strcat(insert, text);

    if (flag == -1) { //�ƹ� ��ȭ ���� ���
        strcat(memo[i][j], memo[i - 1][j - 1]);
        return;
    }
    if (flag == 0) { //���� ���
        strcat(memo[i][j], memo[i][j - 1]);

        strcat(insert, "��°�� ");
        strcat(insert, char2);
        strcat(insert, "�� ����, ");
    }
    if (flag == 1) { //���� ���
        strcat(memo[i][j], memo[i - 1][j]);

        strcat(insert, "��°�� ");
        strcat(insert, char1);
        strcat(insert, "�� ����, ");
    }
    if (flag == 2) { //��ü ���
        strcat(memo[i][j], memo[i - 1][j - 1]);

        strcat(insert, "��°�� ");
        strcat(insert, char2);
        strcat(insert, "�� ��ü, ");
    }

    strcat(memo[i][j], insert);
}

void editDistDP(int m, int n)
{
    //�ʱ�ȭ �۾�
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int i = 0; i <= n; i++) dp[0][i] = i;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) { //���ڰ� ���ٸ� ���� ���� dp�� ��������
                dp[i][j] = dp[i - 1][j - 1];
                memoInsert(i, j, -1);
            }


            else { //���ڰ� �ٸ��ٸ� ����, ��, ���� �� ���� 1�� ���ϱ�(���� ���� ����)
                dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));

                if (dp[i][j] - 1 == dp[i][j - 1])      memoInsert(i, j, 0); //��
                else if (dp[i][j] - 1 == dp[i - 1][j])      memoInsert(i, j, 1); //��
                else if (dp[i][j] - 1 == dp[i - 1][j - 1])  memoInsert(i, j, 2); //������
            }
        }
    }

    printf("�ּ� ���� ��� : %d\n", dp[m][n]);
    printf("�ּ� ���� ���� : %s\n", memo[m][n]);
}

void input() {
    printf("ù��° ���ڿ� : ");
    scanf("%s", str1);
    printf("�ι�° ���ڿ� : ");
    scanf("%s", str2);
}

int main()
{
    input();
    editDistDP(strlen(str1), strlen(str2));

    return 0;
}