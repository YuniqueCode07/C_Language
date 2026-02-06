#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int main()
{
    int N, k, sum, power, copy, digit;
    bool isSuperHarshad;

    printf("Give me the limit N : ");
    scanf("%d", &N);
    for (int i = 2; i < N; i++) {
        k = 0;
        power = i;
        isSuperHarshad = true;

        while (isSuperHarshad) {
            sum = 0;
            copy = power;

            while (copy > 0) {
                digit = copy % 10;
                sum += digit;
                copy /= 10;
            }

            if ((sum > 0) && !(power % sum)) {
                k = k+1;
                if (power > (INT_MAX / i)) {
                    isSuperHarshad = false;
                } else {
                    power *= i;
                }
            } else {
                isSuperHarshad = false;
            }
        }

        if (k > 1) {
            printf("[%d, %d]\n", i, k);
        }
    }
    return 0;
}
