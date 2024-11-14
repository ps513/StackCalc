#include "mathlib.h"

#include <math.h>
#include <stdio.h>

double Abs(double x) {
    if (x < 0) {
        return (x * -1);
    }
    return x;
}

double Sqrt(double x) {
    
    if (x < 0) {
        return nan("nan");
    }

    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}

double Sin(double x) {

    
    double two_pi = (2 * M_PI);
    while (x < 0) {
        x += two_pi;
    }
    while (x >= two_pi) {
        x -= two_pi;
    }

    double result = 0.0;
    double term = 1.0;
    double n = 0.0;
    double denominator = 0.0;
    double sqrt_of_x = x * x;

   
    while (Abs(term) >= EPSILON) {
        if (n == 0) {
            term *= x;
        } else {
            
            denominator = (2 * n) * (2 * n + 1);
            term = ((-term * sqrt_of_x) / denominator);
        }
        n += 1.0;
        result += term;
    }
    return result;
}

double Cos(double x) {
    
    double two_pi = (2 * M_PI);
    while (x < 0) {
        x += two_pi;
    }
    while (x > two_pi) {
        x -= two_pi;
    }

    double result = 0.0;
    double term = 1.0;
    double n = 0.0;
    double denominator = 0.0;
    double sqrt_of_x = x * x;

    
    while (Abs(term) >= EPSILON) {
        if (n == 0) {
            term = 1.0;
        } else {
            
            denominator = (2 * n) * (2 * n - 1);
            term = ((-term * sqrt_of_x) / denominator);
        }
        n += 1.0;
        result += term;
    }
    return result;
}

double Tan(double x) {
    
    double two_pi = (2 * M_PI);
    while (x < 0) {
        x += two_pi;
    }
    while (x >= two_pi) {
        x -= two_pi;
    }

    double sin_value = Sin(x);
    double cos_value = Cos(x);
    if (cos_value < EPSILON && cos_value > -EPSILON) {
        return 0.0;
    } else {
        return sin_value / cos_value;
    }
}
