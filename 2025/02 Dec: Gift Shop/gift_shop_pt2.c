/* Advent of Code
 * Solution for Day 2: Gift Shop, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <regex.h>

int main() {
    FILE* ranges;
    if((ranges = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    unsigned long long invalid_ids = 0;      // Summation for all the invalid IDs
    
    int c = 0;                               // Single character being read in
    int range_ind = 0;                       // Index of the current range being read
    unsigned long long range[2] = {0, 0};    // Input ranges as they come in; [lower bound, upper bound]
    int range_n[2];                          // Number of digits in a bound; [lower bound, upper bound]

    unsigned long long id;                   // ID generated within the range
    unsigned long long pattern;              // The pattern being repeated to create potential invalid IDs
    unsigned long long pattern_n;            // Number of digits in a pattern
    unsigned long long split;                // The number used to split IDs into their various places (e.g. tens place, hundreds place, etc.)

    // (POSIX) Regex solely used to detect possible duplicate invalid IDs
    // Regex means: Find a number with any length duplicated two or more times, and count it only if the entire string is composed of that pattern
    regex_t regex;
    char* regex_pattern = {"^\\([0-9]\\+\\)\\1\\+$"};  // Without escape characters: "^([0-9]+)\1+$"      
    regcomp(&regex, regex_pattern, 0);

    // Start by reading file character by character
    while(c = fgetc(ranges)){
        // If '-', start writing to upper range
        if (c == '-') {
            range_ind = (range_ind + 1) % 2;
            continue;
        }
        
        if(isdigit(c)) {
            // Read the file character by character and mathematically combine them to recreate the integer representation
            range[range_ind] = (range[range_ind] * 10) + ((unsigned char)c - '0');
            continue;
        }

        // If anything else except for a ','
        if(c != ',' && c != EOF) {
            fprintf(stderr, "Invalid number '%c' detected in range. Exiting.\n", c);
            return 1;
        }

        // Use snprintf to determine how many digits in each range bound (Reference in README)
        range_n[0] = snprintf(0, 0, "%lld", range[0]);
        range_n[1] = snprintf(0, 0, "%lld", range[1]);

        printf("lower: %lld, n = %d\n", range[0], range_n[0]);
        printf("upper: %lld, n = %d\n", range[1], range_n[1]);

        // Get the number of times the range crosses a difference in number length + 1 (i.e. 244 (3 digits) - 4245 (4 digits))
        int max_run = (range_n[1] - range_n[0]) + 1;
        for(int digits = 0; digits < max_run; ++digits) {
            
            // After evaluating the original lower range, replace it with the smallest number in the next number of digits (i.e. 345 -> 1000)
            if(digits >= 1) {
                range[0] = (range[0] * (int)pow(10, range_n[0]) / range[0]);
                range_n[0]++;
                printf("\nNEW RANGE:\nlower: %lld, n = %d\n", range[0], range_n[0]);
                printf("upper: %lld, n = %d\n", range[1], range_n[1]);
            }

            // Only generate patterns based on up to half the digits in the bounds. Any pattern larger than that repeated twice would not fit. 
            for(int possible_patterns = 0; possible_patterns < (range_n[0] / 2); ++possible_patterns) {
                // Get the pattern starting with the first digit, then first and second, etc.
                split = pow(10, range_n[0] - 1 - possible_patterns);
                pattern = range[0] / split;
                pattern_n = possible_patterns + 1;
                id = 0;

                // If there is any remainder when building the pattern up, pattern will not fit.
                if(range_n[0] % pattern_n != 0) {
                    continue;
                }

                while (id <= range[1]){

                    /*  Iteratively use pattern to build ID
                        Based on shifting the patterns to the left and adding the patterns to the end until complete
                        Iteration number is based on how many times the pattern can fit in the original number's length
                        1. Start with the lower bound number of digits (range_n[0])
                        2. Subtract the number of digits in the pattern (pattern_n)
                        3. Subtract by the size of the pattern itself (multiplied by the times already ran through)
                    */
                    id = 0;
                    for(int j = 0; j < range_n[0] / pattern_n; ++j) {
                        id += pattern * (int)(pow)(10, range_n[0] - pattern_n - (j * pattern_n));
                    }

                    printf("\nID: %lld\n", id);
                    printf("pattern: %lld\n", pattern);    

                    // The numbers created may be invalid and start below the lower boundary (i.e. 2122-2424, but generated 2121)
                    if(id >= range[0] && id <= range[1]){

                        // Deduplicate. Within the pattern, check if there are any duplicate patterns inside
                        // Works on the assumption that if there is a internal repeating pattern, the pattern must have been caught by a previous ID generation step
                        char pattern_s[pattern_n];
                        snprintf(pattern_s, pattern_n + 1, "%lld", pattern);

                        // If pattern isn't found, not duplicate
                        if((regexec(&regex, pattern_s, 0, NULL, 0)) != 0) {
                            invalid_ids += id;
                            printf("Invalid ID: %lld\n", id);         
                        }    
                        else {
                            printf("Duplicate found: %lld\n", id);
                        }
                    }

                    // Ensure the pattern doesn't go past lower_n number of digits (i.e. pattern 9 cannot go to 10, 99 cannot go to 100)
                    if(++pattern >= (pattern * (int)pow(10, pattern_n) / pattern)) {
                        break; 
                    }
                }
            }
        }

        // Reset range 
        range[0] = 0;
        range[1] = 0;
        range_ind = 0;
        printf("\n");

        if(c == EOF) break;
    }

    printf("Summation: %lld\n", invalid_ids);
    fclose(ranges);
    regfree(&regex);

    return 0;
}