#include <stdio.h>
#include <stdlib.h>

int main()
{
    int choice, moisture;

    printf("Give me the soil type:\n1. Sandy\n2. Clay\n3. Loamy \n");
    do {
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);

    printf("Give me your moisture level: \n");
    do {
        scanf("%d", &moisture);
    } while (moisture < 0 || moisture > 100);

    if ((choice = 1 && moisture <= 20) || (choice = 2 && moisture <= 30) || (choice = 3 && moisture <= 25)) {
        printf("I recommend you irrigation \n");
    } else {
        printf("No need for irrigation \n");
    }
    return 0;
}
