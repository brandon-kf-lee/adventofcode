/* Advent of Code
 * Solution for Day 5: Cafeteria, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dll.h"

int main() {
    FILE* inventory;
    if((inventory = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char test_char;
    long long lower, upper;
    range* head = NULL;

    // Build list of ranges
    // If a '\n' newline is detected, must be the end of the ranges section
    while((test_char = fgetc(inventory)) != '\n') {
        ungetc(test_char, inventory);
        fscanf(inventory, "%lld-%lld", &lower, &upper);
        fgetc(inventory); // Ignore one newline at the end of each range 
        insert_range(&head, lower, upper);
    }
   
    printf("Total fresh ingredient: %lld\n", range_total(head));
    fclose(inventory);
    delete_list(head);
    return 0;
}