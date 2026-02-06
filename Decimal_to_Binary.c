#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, remainder, power;

    printf("Give me a number greater than 0 : ");
    do {
        scanf("%d", &N);
    } while (N < 0);

    int position = 0;
    int result = 0;

    while (N) {
        remainder = N % 2;
        N /= 2;
        power = 1;
        position += 1;
        for (int i = 1; (i <= position - 1); i++) {
            power *= 10;
        }
        result = result + remainder * power;
    }

    printf("%d", result);
    return 0;
}
