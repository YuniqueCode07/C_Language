#include <stdio.h>
#include <stdlib.h>

int main()
{
    int Hd, Md, Ha, Ma, DH, DM;

    printf("Departure Hour: ");
    do {
        scanf("%d", &Hd);
    } while (Hd < 0 || Hd > 23);

    printf("Departure Minutes: ");
    do {
        scanf("%d", &Md);
    } while (Md < 0 || Md > 59);

    printf("Arrival Hour: ");
    do {
        scanf("%d", &Ha);
    } while (Ha < 0 || Ha > 23);

    printf("Arrival Minutes: ");
    do {
        scanf("%d", &Ma);
    } while (Ma < 0 || Ma > 59);

    DM = Ma - Md;
    DH = Ha - Hd;

    if (DM < 0) {
        DM += 60;
        DH -= 1;
    }

    if (DH < 0) {
        DH += 24;
    }

    printf("The duration is %d hours and %d minutes\n", DH, DM);

    return 0;
}
