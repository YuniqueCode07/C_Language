#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, units, tens, hundreds;

    for (int i = 100; i <= 500; i++) {
        units = i % 10;
        tens = (i / 10) % 10;
        hundreds = (i / 100) % 10;
        N = units * units * units + tens * tens * tens + hundreds * hundreds * hundreds;

        if (N == i) {
            printf("%d\n", i);
        }
    }
    return 0;
}
