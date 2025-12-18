/* Advent of Code
 * Solution for Day 5: Cafeteria, Part 1
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
    long long lower, upper, id;
    int total_fresh = 0;
    range* head = NULL;

    // Build list of ranges
    // If a '\n' newline is detected, must be the end of the ranges section
    while((test_char = fgetc(inventory)) != '\n') {
        ungetc(test_char, inventory);
        fscanf(inventory, "%lld-%lld", &lower, &upper);
        fgetc(inventory); // Ignore one newline at the end of each range 
        insert_range(&head, lower, upper);
    }

    // Evaluate IDs
    // If EOF is detected (or extraneous '\n'), must be the end of the item section
    while((test_char = fgetc(inventory)) != EOF && test_char != '\n') {
        ungetc(test_char, inventory);
        fscanf(inventory, "%lld", &id);
        fgetc(inventory); // Ignore one newline at the end of each id 
        total_fresh += find_id(&head, id);
    }
   
    printf("Fresh ingredients: %d\n", total_fresh);
    fclose(inventory);
    delete_list(head);
    return 0;
}