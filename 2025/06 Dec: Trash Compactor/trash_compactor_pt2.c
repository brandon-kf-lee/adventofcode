/* Advent of Code
 * Solution for Day 6: Trash Compactor, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_DIGITS 4

int main() {
    FILE* homework;
    if((homework = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    int column_check = 0;     // Used to check if a given column of characters is a question delimeter
    int question = 0;         // The question number currently being evaluated
    int operand_n = 0;        // The operand currently being read in
    int operand = 0;          // The operand to operate on after its built
    char operator;            // The operator used to add/multiply the operands

    long long answer;         // One question's answer
    long long total_sum = 0;  // All the question's answers added up

    char* line[N_DIGITS];     // Unparsed lines of input from the homework document
    size_t line_len = 0;      // True length of the one line minus newline

    // Read every line of the input (except for the operators) and strip newline off the end 
    for(int i = 0; i < N_DIGITS; ++i) {
        getline(&line[i], &line_len, homework);
        line[i][strcspn(line[i], "\n")] = 0;
    }
    // Set the true line length after reading in operands
    line_len = strlen(line[0]); 

    // Scan the first operator
    fscanf(homework, " %c", &operator); 
    // Set the answer base to 0 if addition, 1 if other (assuming multiplication)
    answer = (operator == '+') ? 0 : 1; 

    // Scan the homework file vertically, working one column at a time
    for(int ch = 0; ch < line_len; ++ch) {
        
        // Populate the operand with its vertical digit
        for(int digit = 0; digit < N_DIGITS; ++digit) {
            // If the character is a digit, add it to the current operand
            // Use digit shifting and append the (converted) number at the end (as seen in Day 2's solution)
            if(isdigit(line[digit][ch])) {
                operand = (operand * 10) + ((unsigned char)line[digit][ch] - '0');
            }
            column_check += line[digit][ch];
        }

        // Add/multiply operand if it isn't a question delimiter
        if(column_check != N_DIGITS * ' ') {            
            switch(operator) {
                case '*': 
                    answer *= operand;
                    break;
                case '+': 
                    answer += operand;
                    break;
                default:
                    fprintf(stderr, "Unknown operator '%c'\n", operator);
                    return 1;
                    break; 
            }

            column_check = 0;
            ++operand_n;
            operand = 0;
        }
        
        // If a column of input is exactly N_OPERAND number of spaces, it must be a question delimiter. Reset loop.
        else {
            total_sum += answer;
            ++question;
            operand_n = 0;
            fscanf(homework, " %c", &operator);
            answer = (operator == '+') ? 0 : 1;
        }
    }
    // Add the last sum/product not caught within the loop
    total_sum += answer;

    // Free all dynamic memory
    for(int i = 0 ; i < N_DIGITS; ++i) free(line[i]);

    printf("Assumptions: (maximum) %d digits in an operand (rows - 1)\n", N_DIGITS);
    printf("Total sum: %lld\n", total_sum);
    fclose(homework);
    return 0;
}