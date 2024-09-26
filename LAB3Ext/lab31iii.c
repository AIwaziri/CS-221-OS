#include <stdio.h>
#include <stdbool.h>


bool is_even(int num) {
    return num % 2 == 0;
}

void read_num(int List[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &List[i]);
    }
}


void display_num(int List[], int size) {
    for (int i = 0; i < size; i++) {
        if (is_even(List[i])) {
            printf("%d is even.\n", List[i]);
        } else {
            printf("%d is odd.\n", List[i]);
        }
    }
}

int main() {
    int List[5];
    read_num(List, 5);
    display_num(List, 5);

    return 0;
}
