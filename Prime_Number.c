#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int N;
    bool prime = true;

    printf("Give me a number: ");
    scanf("%d", &N);

    if (N <= 1) {
        prime = false;
    } else {
        for (int i=2; (i <= N / 2); i++) {
            if (!(N % i)) {
                prime = false;
                break;
            }
        }
    }

    if (prime) {
        printf("%d is a prime number\n", N);
    } else {
        printf("%d is not a prime number\n", N);
    }

    return 0;
}
