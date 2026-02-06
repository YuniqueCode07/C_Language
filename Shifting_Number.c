#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, occurence;

    printf("Give me a number : ");
    scanf("%d", &N);

    printf("Give me the digit you want to remove its first occurence only : ");
    do {
        scanf("%d", &occurence);
    } while (occurence > 9 || occurence < 0);

    int result = 0;
    int position = 1;
    while (((N % 10) != occurence) && N) {
        result = (N % 10) * position + result;
        N /= 10;
        position *= 10;
    }
    if ((N % 10) == occurence) {
        N = N / 10;
        result = (result + N * position) * 10;
    }

    printf("The final number is %d", result);
    return 0;
}
