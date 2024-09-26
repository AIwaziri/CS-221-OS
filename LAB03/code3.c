#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    int i, num_multiplications;

    file = fopen("input_file.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(file, "%d", &num_multiplications);

    int A[num_multiplications], B[num_multiplications], C[num_multiplications];
    for (i = 0; i < num_multiplications; i++) {
        fscanf(file, "%d %d", &A[i], &B[i]);
    }

    for (i = 0; i < num_multiplications; i++) {
        C[i] = A[i] * B[i];
    }
    fclose(file);


    printf("Results of multiplication:\n");
    for (i = 0; i < num_multiplications; i++) {
        printf("%d * %d = %d\n", A[i], B[i], C[i]);
    }

    return 0;
}
