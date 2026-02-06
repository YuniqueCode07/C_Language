#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    int odd = 0;
    int even = 0;
    int position_odd = 1;
    int position_even = 1;

    printf("Give me a number greater than 0 : ");
    scanf("%d", &N);
    while (N) {
        if (N % 2) {
            odd = odd + (N % 10) * position_odd;
            position_odd *= 10;
        } else {
            even = even + (N % 10) * position_even;
            position_even *= 10;
        }
        N /= 10;
    }

    printf("The odd number is : %d\nThe even number is : %d", odd, even);
    return 0;
}
