#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#define VALID_OPTIONS "mh" 

int main(int argc, char **argv) {
    
    char *expr = malloc(1024); // Allocates memory for expr
    expr[0] = '\0';

    // Code below is from Professor Veenstra's class examples my modifications

    int cl; 
    bool saw_dash_m = false;
    bool saw_dash_h = false;
    bool is_invalid_option = false;

    
    stack_size = 0;

    
    while ((cl = getopt(argc, argv, VALID_OPTIONS)) != -1) {
        switch (cl) {
        case 'h': saw_dash_h = true; break;
        case 'm': saw_dash_m = true; break;
        case '?':
            is_invalid_option = true;
            saw_dash_h = true;
            break;
        default:
           
            break;
        }
    }

    if (saw_dash_h) {
        printf("%s", USAGE);
        if (is_invalid_option) {
            free(expr);
            return 1;
        }
        free(expr);
        return 0;
    }

    while (1) {
        fprintf(stderr, "> ");

        expr = fgets(expr, 1024, stdin);
        if (expr == NULL) {
            free(expr);
            return 0;
        }

        stack_clear();

   
        char *saveptr;
        
        bool error_occured = false;
  
        const char *token = strtok_r(expr, " ", &saveptr);
        double hold_parse;
       
        while (token != NULL) {
            
            if (parse_double(token, &hold_parse)) {
                
                if (!stack_push(hold_parse)) {
                    fprintf(stderr, ERROR_NO_SPACE, hold_parse);
                    error_occured = true;
                    break;
                }
            } else if (binary_operators[(
                           unsigned char) token[0]]) {
                if (stack_size < 2) {
                    fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
                    error_occured = true;
                    break;
                }
                
                apply_binary_operator(binary_operators[(unsigned char) token[0]]);
            } else if ((saw_dash_m
                           && libm_unary_operators[(
                               unsigned char) token[0]]) 
                       || (!saw_dash_m
                           && my_unary_operators[(
                               unsigned char) token[0]])) { 
                if (stack_size < 1) {
                    fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
                    error_occured = true;
                    break;
                }
                
                apply_unary_operator((saw_dash_m) ? libm_unary_operators[(unsigned char) token[0]]
                                                  : my_unary_operators[(unsigned char) token[0]]);
            } else {
                fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                error_occured = true;
                break;
               
            }
            token = strtok_r(NULL, " ", &saveptr); 
        }
        
        if (!error_occured && (stack_size > 0)) {
            stack_print();
            printf("\n");
        }

        
        free(expr);
        expr = malloc(1024); 
        expr[0] = '\0';
    }
    
    free(expr);
    return 0;
}
