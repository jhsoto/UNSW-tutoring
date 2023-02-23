// Stores 10 numbers scanned from input into an array

#define ARRAY_SIZE 10

int main() {
    int array[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        scanf("%d", &array[i]);
    }

    return 0;
}