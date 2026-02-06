#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, Un;
    int U_previous = 0;
    int U_next = 1;

    printf("Give me the nth number of the fibonacci series you want to calculate : ");
    do {
        scanf("%d", &N);
    } while (N < 0);

    if (N == 0) {
        Un = U_previous;
    } else if (N == 1) {
        Un = U_next;
    } else {
        for (int i = 2; i <= N; i++) {
            Un = U_next + U_previous;
            U_previous = U_next;
            U_next = Un;
        }
    }

    printf("U%d = %d\n", N, Un);

    return 0;
}
