#include <stdio.h>
#include <stdlib.h>

int main()
{
    int year;

    printf("Give me a year: ");
    do {
        scanf("%d", &year);
    } while (year < 1000 || year > 9999);

    if ((!(year % 4) && (year % 100)) || (!(year % 100) && (!(year % 400)))) {
        printf("%d is a leap year\n", year);
    } else {
        printf("%d is not a leap year\n", year);
    }

    return 0;
}
