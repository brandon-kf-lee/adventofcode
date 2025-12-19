/* Advent of Code
 * Solution for Day 6: Trash Compactor, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>

#define N_PROBLEMS 1000
#define N_OPERANDS 4

int main() {
    FILE* homework;
    if((homework = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    int question_sets[N_PROBLEMS][N_OPERANDS];  // All of the problems in the homework document to complete
    char operator;                              // The operator used to add/multiply the operands
    long long answer;                           // One question's answer
    long long total_sum = 0;                    // All the question's answers added up

    // Scan each operand horizontally, number by number, and add them to their proper place in question_sets
    // The first operands in every question is scanned and put into queston_sets first, then the second operands, etc.
    for(int i = 0; i < N_OPERANDS; ++i) {
        for(int j = 0; j < N_PROBLEMS; ++j) {
            fscanf(homework, "%d", &question_sets[j][i]);
        }
    }

    // Once all problems are sorted properly, add/multiply them all
    for(int i = 0; i < N_PROBLEMS; ++i) {
        // Add space before %c to ignore all whitespace
        fscanf(homework, " %c", &operator);
        switch(operator) {
            case '*': 
                answer = 1;
                for(int j = 0; j < N_OPERANDS; ++j) answer *= question_sets[i][j];
                break;
            case '+': 
                answer = 0;
                for(int j = 0; j < N_OPERANDS; ++j) answer += question_sets[i][j];
                break;
            default:
                fprintf(stderr, "Unknown operator '%c'\n", operator);
                break;
        }
        total_sum += answer;
    }

    printf("Assumptions:\n  %d problems (columns)\n     %d operands (rows - 1)\n", N_PROBLEMS, N_OPERANDS);
    printf("Total sum: %lld\n", total_sum);
    fclose(homework);
    return 0;
}