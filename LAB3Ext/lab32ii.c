#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int number;
    bool state; 
} NumberState;

void set_state(NumberState *num_state) {
    num_state->state = (num_state->number % 2 == 0);
}


void read_num(NumberState List[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &List[i].number);
        set_state(&List[i]);
    }
}

void display_num(NumberState List[], int size) {
    for (int i = 0; i < size; i++) {
        if (List[i].state) {
            printf("%d is even.\n", List[i].number);
        } else {
            printf("%d is odd.\n", List[i].number);
        }
    }
}

int main() {
    NumberState List[5];
    read_num(List, 5);
    display_num(List, 5);

    return 0;
}
