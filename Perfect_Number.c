#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, Sum;

    printf("Give me a number greater than 0: ");
    do {
        scanf("%d", &N);
    } while (N < 1);

    for (int i = 1; i <= N; i++) {
        Sum = 0;
        for (int j = 1; (j <= i / 2); j++) {
            if (!(i % j)) {
                Sum += j;
            }
        }

        if (Sum == i) {
            printf("%d is a perfect number\n", i);
        }
    }
    return 0;
}
