#include <stdio.h>
#include <stdlib.h>

int main()
{
    float BMI, weight, height;

    printf("Give me your weight (kg): ");
    do {
        scanf("%f", &weight);
    } while (weight <= 0);

    printf("Give me your height (m): ");
    do {
        scanf("%f", &height);
    } while (height <= 0);

    BMI = weight / (height * height);
    printf("Your BMI (Body Mass Index) is equal to: %.2f\n", BMI);

    if (BMI <= 18.5) {
        printf("Underweight\n");
    } else if (BMI <= 24.9) {
        printf("Normal weight\n");
    } else if (BMI <= 29.9) {
        printf("Overweight\n");
    } else {
        printf("Obesity\n");
    }
    return 0;
}
