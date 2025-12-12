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

    unsigned long long invalid_ids = 0;
    unsigned long long range[2] = {0, 0};
    int c = 0;
    int range_ind = 0; // Index of the range being read
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

        // If anything except a ','
        if(c != ',' && c != EOF) {
            fprintf(stderr, "Invalid number '%c' detected in range. Exiting.\n", c);
            return 1;
        }

        // Use snprintf to determine how many digits in each range bound (Reference in README)
        int range_n[2];
        range_n[0] = snprintf(0, 0, "%lld", range[0]);
        range_n[1] = snprintf(0, 0, "%lld", range[1]);

        printf("lower: %lld, n = %d\n", range[0], range_n[0]);
        printf("upper: %lld, n = %d\n", range[1], range_n[1]);

        unsigned long long id, pattern, pattern_n, split;
        int ranges_i, max_run = 2; // Cycling through the number of digit legnths, max_run # of times (e.g. 6-7 digits)

        // If there is no change of digit count between ranges, below code should only one run once (an unfortunately hacky solution)
        if(abs(range_n[1] - range_n[0]) < 1) max_run = 1;

        // Working on the assumption that ranges will not cover 2 or more differences in number length
        for(ranges_i = 0; ranges_i < max_run; ++ranges_i) {

            // Only generate patterns based on up to half the digits in the bounds. Any pattern larger than that repeated twice would not fit. 
            for(int possible_patterns = 0; possible_patterns < (range_n[ranges_i] / 2); ++possible_patterns) {
                // Get the pattern starting with the first digit, then first and second, etc.
                split = pow(10, range_n[ranges_i] - 1 - possible_patterns);
                pattern = range[ranges_i] / split;
                pattern_n = possible_patterns + 1;
                id = 0;

                //printf("first pattern: %lld\n", pattern);

                // If there is any remainder when building the pattern up, pattern will not fit.
                if(range_n[ranges_i] % pattern_n != 0) {
                    continue;
                }

                while (id <= range[1]){

                    /*  Iteratively build pattern 
                        Based on shifting the patterns to the left and adding the patterns to the end until complete
                        Iteration number is based on how many times the pattern can fit in the original number's length
                        1. Start with the original number of digits (range_n[ranges_i])
                        2. Subtract the number of digits in the pattern (pattern_n)
                        3. Subtract by the size of the pattern itself (multiplied by the times already ran through)
                    */
                    id = 0;
                    for(int j = 0; j < range_n[ranges_i] / pattern_n; ++j) {
                        id += pattern * (int)(pow)(10, range_n[ranges_i] - pattern_n - (j * pattern_n));
                    }

                    printf("\nID: %lld\n", id);
                    printf("pattern: %lld\n", pattern);    
                    //printf("size of pattern: %lld\n", pattern_n);
                    printf("do not go past: %lld\n", (pattern * (int)pow(10, pattern_n) / pattern));  

                    // The numbers created may be invalid and start below the lower boundary (i.e. 2122-2424, but generated 2121)
                    if(id >= range[0] && id <= range[1]){

                        //Deduplicate. Within the pattern, check if there are any duplicate patterns inside
                        if (pattern_n != 1);
                        
                        // Without escape characters: "^([0-9]+)\1+$"
                        char* regex_pattern = {"^\\([0-9]\\+\\)\\1\\+$"};     
                        //printf("regex pattern: %s\n", regex_pattern);
                        
                        regex_t regex;
                        int regex_ret;
                        if((regex_ret = regcomp(&regex, regex_pattern, 0)) != 0) {
                            char msg[100];
                            regerror(regex_ret, &regex, msg, 100);
                            fprintf(stderr, "Error compiling regex: %s\n", msg);                
                            return 1;
                        }

                        char pattern_s[pattern_n];
                        snprintf(pattern_s, pattern_n + 1, "%lld", pattern);
                        printf("pattern to check: %s\n", pattern_s);

                        // If pattern isn't found, not duplicate
                        if((regex_ret = regexec(&regex, pattern_s, 0, NULL, 0)) != 0) {
                            invalid_ids += id;
                            printf("Invalid ID: %lld\n", id);         
                        }    
                        else {
                            printf("Duplicate found: %lld\n", id);
                        }

                        // TODO: Free regex memory
                    }


                    // Ensure the pattern doesn't go past lower_n number of digits (i.e. pattern 9 cannot go to 10, 99 cannot go to 100)
                    if(++pattern >= (pattern * (int)pow(10, pattern_n) / pattern)) {
                    // if(++pattern >= split) {
                        break; 
                    }
                }
            }
        }

        // The above work may not cover 2 or more differences in number length (i.e. 11-3333 may not be covered)
        if(abs(range_n[1] - range_n[0]) + 1 > 2) {
            printf("WARNING: Ranges %lld-%lld pass a wide range of numbers, some invalid IDs may have been skipped.\n", range[0], range[1]);
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

    return 0;
}