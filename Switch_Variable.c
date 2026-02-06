#include <stdio.h>
#include <stdlib.h>

int main()
{
    int A, B;

    printf("A = ");
    scanf("%d", &A);

    printf("B = ");
    scanf("%d", &B);

    A += B;
    B = A - B;
    A -= B;

    printf("After switching variables\nA = %d\nB = %d\n", A, B);
    return 0;
}
