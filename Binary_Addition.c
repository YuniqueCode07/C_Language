#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int A, B, temp;
    bool isBinaryA, isBinaryB;

    printf("Give me the first binary number : ");
    do {
        isBinaryA = true;
        scanf("%d", &A);
        temp = A;

        if (temp == 0) isBinaryA = true;
        while (temp > 0) {
            int digit = temp % 10;
            if (digit != 0 && digit != 1) {
                isBinaryA = false;
                printf("Invalid! Use only 0 and 1. Try again: ");
                break;
            }
            temp /= 10;
        }
    } while (!isBinaryA);

    printf("Give me the second binary number : ");
    do {
        isBinaryB = true;
        scanf("%d", &B);
        temp = B;

        while (temp > 0) {
            int digit = temp % 10;
            if (digit != 0 && digit != 1) {
                isBinaryB = false;
                printf("Invalid! Use only 0 and 1. Try again: ");
                break;
            }
            temp /= 10;
        }
    } while (!isBinaryB);

    int carry = 0;
    int result = 0;
    int position = 1;

    while (A || B || carry) {
        int addition = (A % 10) + (B % 10) + carry;
        int result_digit = addition % 2;
        carry = addition / 2;

        result = result + result_digit * position;
        position *= 10;
        A /= 10;
        B /= 10;
    }

    printf("Result: %d\n", result);
    return 0;
}
