#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, result_2;
    int sign = 1;

    printf("Give me a number : ");
    scanf("%d", &N);
    int position = 1;
    if (N < 0) {
        sign = -1;
        N *= -1;
    }
    int saveN = N;
    int result_1 = N % 10;
    while (N / 10) {
        N /= 10;
        position *= 10;
        result_2 = N;
    }
    int sub = result_2 - result_1;
    saveN += sub;
    saveN = (saveN - result_2 * position + result_1 * position) * sign;

    printf("The swapped number is %d", saveN);

    return 0;
}
