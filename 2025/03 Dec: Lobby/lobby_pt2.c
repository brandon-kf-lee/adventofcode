/* Advent of Code
 * Solution for Day 3: Lobby, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BANK 100  // Maximum number of batteries in a bank
#define BANK_SIZE 12  // Number of batteries to turn on

int main() {
    FILE* banks;
    if((banks = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char jolt;                              // Each individual jolt read in
    int battery = 0;                        // The index of a given battery in a bank
    char bank[BANK_SIZE + 1];               // The bank of batteries (+ 1 to give space for a null char at the end)
    memset(bank, 0, sizeof(bank));
    unsigned long long total_joltage = 0;   // Summative joltage of all banks

    while(jolt = fgetc(banks)) {
        
        // Indicates the end of a bank
        if(jolt == '\n' || jolt == EOF) {
            bank[BANK_SIZE] = 0;
            total_joltage += atoll(bank);

            // Reset
            memset(bank, 0, sizeof(bank));
            battery = 0;

            if(jolt == EOF) break;
        }
        else {            

            for(int place = 0; place < BANK_SIZE; ++place) {
                //printf("  evaluating place %d\n", place);
                //printf("  %c < %c && (%d) >= (%d)\n", bank[place], jolt, MAX_BANK - battery, BANK_SIZE - place);
                if(bank[place] < jolt && (MAX_BANK - battery) >= (BANK_SIZE - place)) {
                    bank[place] = jolt;
                    //printf("    clearing from index %d, %d bytes\n", place + 1, (BANK_SIZE - place));
                    // Ensure the rest of the bank array is -1 to ensure valid comparisons after replacements
                    memset(&bank[place + 1], 0, (BANK_SIZE - place));
                    //printf("    %c placed in: %d\n", jolt, place);
                    //printf("    string so far: %s\n", bank);
                    break;
                }
            }

            battery++;
        }
    }

    // printf("%s\n", bank);
    // memset(&bank[5], -1, sizeof(bank) - 5);
    // printf("%s\n", bank);

    printf("Total Joltage: %lld\n", total_joltage);
    fclose(banks);
}
