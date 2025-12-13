/* Advent of Code
 * Solution for Day 3: Lobby, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <string.h>

int main() {
    FILE* banks;
    if((banks = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char c;
    int upper = -1, lower = -1, prev_upper = -1;
    int total_joltage = 0;

    while(c = fgetc(banks)) {
        
        if(c == '\n' || c == EOF) {
            // Happens if the largest number is found at the end. 
            // If so, grab the previous highest number and make it the new highest, then take the last number and put it at the end
            if (lower == -1) {
                lower = upper;
                upper = prev_upper;
            }
            printf("final highest: %d%d\n", upper, lower); 
            total_joltage += (upper * 10) + lower; // First number in the tens place, second number in the ones place

            // Reset
            upper = lower = prev_upper = -1;

            if(c == EOF) break;
        }
        else {
            int jolt = c - '0';
            
            // Reset lower if a new upper is found, it will now be the highest base possible
            if(jolt > upper) {
                prev_upper = upper;
                upper = jolt;
                lower = -1;
            } 
            else if (jolt > lower) {
                lower = jolt;
            }
        }
    }

    printf("Total Joltage: %d\n", total_joltage);
    fclose(banks);
}
