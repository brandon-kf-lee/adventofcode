/* Advent of Code
 * Solution for Day 2: Gift Shop, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main() {
    FILE* ranges;
    if((ranges = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    unsigned long long invalid_ids = 0;
    unsigned long long range[2] = {0, 0};
    int c = 0;
    int i = 0; // Index of the range being read
    while(c = fgetc(ranges)){
        // If '-', start writing to upper range
        if (c == '-') {
            i = (i + 1) % 2;
            continue;
        }
        
        if(isdigit(c)) {
            // Read the file character by character and mathematically combine them to recreate the integer representation
            range[i] = (range[i] * 10) + ((unsigned char)c - '0');
            continue;
        }

        // If anything except a ','
        if(c != ',' && c != EOF) {
            fprintf(stderr, "Invalid number '%c' detected in range. Exiting.\n", c);
            return 1;
        }

        // Use snprintf to determine how many digits in each range bound (Reference in README)
        int lower_n = snprintf(0, 0, "%lld", range[0]);
        int upper_n = snprintf(0, 0, "%lld", range[1]);

        printf("lower: %lld, n = %d\n", range[0], lower_n);
        printf("upper: %lld, n = %d\n", range[1], upper_n);

        /* The working assumption is that these patterns can only form on numbers with an even number of digits (i.e. 1010 and not 10101)
           Steps: 
           1. If the number is odd, go to the next closest even digit number
           2. Cut the number in half and get the first half (the pattern, i.e. 10)
           3. Concatenate the pattern to the end of the pattern to get the repeating sequence (i.e. 1010)
           4. Ensure the new number is not out of bounds
           5. Increment the pattern by 1 and do step 3 - 4 again
        */

        unsigned long long pattern, pattern_half, split;
        unsigned long long lower = range[0];
        
        // There will be a future upper bound check to ensure this move doens't go out of bounds
        if((lower_n % 2) != 0) {
            lower = (int)pow(10, lower_n);
            lower_n++;
        }

        split = (int)pow(10, (lower_n / 2));  // The power of 10 to divide the range bound with
        pattern_half = (lower / split);       // Get the repeating pattern: the first half of the range bound number
        
        // Make the potential invalid ID and ensure it's not out of bounds
        while(((pattern = (pattern_half * split) + pattern_half) <= range[1])){
            if(++pattern_half > split) break; // Ensure the pattern doesn't go past lower_n number of digits (i.e. pattern 9 cannot go to 10, 99 cannot go to 100)
            
            // The numbers created may be invalid and start below the lower boundary (i.e. 2122-2424, but generated 2121)
            if(pattern >= range[0]){
                invalid_ids += pattern;
                printf("Invalid ID: %lld\n", pattern);
            }
            
        }

        // The above work may not cover 2 or more differences in number length (i.e. 11-3333 may not be covered)
        if(abs(upper_n - lower_n) + 1 > 2) {
            printf("WARNING: Ranges %lld-%lld pass a wide range of numbers, some invalid IDs may have been skipped.\n", range[0], range[1]);
        }

        // Reset range 
        range[0] = 0;
        range[1] = 0;
        i = (i + 1) % 2;
        printf("\n");

        if(c == EOF) break;
    }

    printf("Summation: %lld\n", invalid_ids);
    fclose(ranges);

    return 0;
}