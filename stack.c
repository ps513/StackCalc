#include "stack.h"

#include <stdbool.h>
#include <stdio.h>

int stack_size = 0;
double stack[64];

bool stack_push(double item) {
    
    if (stack_size == STACK_CAPACITY) {
        return false;
    }
    
    stack[stack_size] = item;
    stack_size += 1;
    return true;
}

bool stack_pop(double *item) {
    
    if (stack_size == 0) {
        return false;
    }
    
    stack_size -= 1;
    *item = stack[stack_size];
    return true;
}

bool stack_peek(double *item) {
    
    double element;
    double *element_ptr = &element;

    if (stack_pop(element_ptr)) {
        *item = element;
        stack_push(element);
        return true;
    }
    
    return false;
}

void stack_clear(void) {
    
    stack_size = 0;
}

void stack_print(void) {
    
    if (stack_size == 0) {
        return; 
    }
   
    printf("%.10f", stack[0]);
    
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
