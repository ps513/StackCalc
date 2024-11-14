#include "operators.h"

#include "mathlib.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


double operator_add(double lhs, double rhs) {
    double sum = lhs + rhs;
    return sum;
}

double operator_sub(double lhs, double rhs) {
    double diff = lhs - rhs;
    return diff;
}

double operator_mul(double lhs, double rhs) {
    double product = lhs * rhs;
    return product;
}

double operator_div(double lhs, double rhs) {
    double quo = lhs / rhs;
    return quo;
}

bool apply_binary_operator(binary_operator_fn op) {
    
    if (stack_size < 2) {
        return false;
    }

    
    double left_num;
    double right_num;

    assert(stack_pop(&right_num));
    assert(stack_pop(&left_num));

    double result = op(left_num, right_num);

    assert(stack_push(result));
    return true;
}

bool apply_unary_operator(unary_operator_fn op) {
    
    if (stack_size < 1) {
        return false;
    }

    double x;
    
    assert(stack_pop(&x));
    
    double result = op(x);
    
    assert(stack_push(result));
    return true;
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
