/* Advent of Code
 * Solution for Day 2: Red-Nosed Reports
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int max_line = 50; /* The maximum number of characters to read in per line */
const char* delimiter = " "; /* The delimiter that separates each digit in the input */

int main(int argc, char* argv[]){

    /* Error check input file name */
    if(argc < 2){
        fprintf(stderr, "Missing input file. \nUsage: ./day02 <input text file name>\n");
        exit(EXIT_FAILURE);
    }

    /* Open file into input, w/ error checking */
    FILE* input;
    if((input = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char report[max_line];
    int num_safe = 0;
    while(fgets(report, max_line, input) != NULL){
        /* Grab the first two levels and determine if the levels must be increasing or decreasing */
        char* level = strtok(report, delimiter);
        char* next = strtok(NULL, delimiter);
        int increasing = ((atoi(level) - atoi(next)) > 0) ? 0 : 1; 
        int safe = 1;

        /* Compare the levels with each other until there aren't any left */
        do{
            /* Determine the delta between the levels, accepting negatives if levels are increasing */
            int level_delta = atoi(level) - atoi(next);

            /* Decreasing case, delta must be b/w 1 and 3 */
            if(!increasing && (level_delta <= 0 || level_delta > 3)){
                safe = 0;
                break;
            }
            /* Increasing case, delta must be b/w -1 and -3 */
            else if(increasing && (level_delta >= 0 || level_delta < -3)){
                safe = 0;
                break;
            }

            level = next;
            next = strtok(NULL, delimiter);
        }
        while(next != NULL);

        if(safe){
            ++num_safe;
        }
    }

    printf("Number of safe reports: %d\n", num_safe);

    exit(EXIT_SUCCESS);
}