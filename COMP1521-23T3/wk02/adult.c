// Determines if someone is an adult
#include <stdio.h>

int main() {
    int age;

    printf("Enter your age: ");
    scanf("%d", &age);

    if (age >= 18) {
        printf("You are an adult!\n");
    } else {
        printf("You are not an adult.\n");
    }

    return 0;
}